#include "Framework.h"
#include "Renderer.h"
#include "Common.h"
#include "EventQ.h"
#include "../Actors/HActor.h"
#include "../Levels/MainLevel.h"

#include <GLES3/gl3.h>
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <cstring>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>
#include <chrono>

AAssetManager* Framework::assetMng = nullptr;
Framework* Framework::instance = nullptr;
Renderer* Framework::curRenderer = nullptr;
EventQ* Framework::eventQ = nullptr;
HLevelBase* Framework::curLevel = nullptr;
GLuint Framework::screenWidth = 0;
GLuint Framework::screenHeight = 0;
float Framework::accTime = 0.0f;
float Framework::deltaTime= 0.0f;
Framework* frameworkInst = nullptr;


Framework::~Framework()
{
    if(instance)
    {
        delete instance;
        instance = nullptr;
    }

    if(curRenderer)
    {
        delete curRenderer;
        curRenderer = nullptr;
    }

    if(curLevel)
    {
        delete curLevel;
        curLevel = nullptr;
    }
}

Framework *Framework::getInstance()
{
    if(!instance)
    {
        instance = new Framework();
    }
    return instance;
}

void Framework::init(const char* VSPath, const char* FSPath)
{
    curRenderer = new Renderer(VSPath, FSPath);
    curRenderer->addClearBit(GL_COLOR_BUFFER_BIT);
    curRenderer->addClearBit(GL_DEPTH_BUFFER_BIT);
    curRenderer->enableGLFeature(GL_DEPTH_TEST);
    curRenderer->enableGLFeature(GL_BLEND);
    curRenderer->setClearColor(0.0f,1.0f,1.0f,1.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    curLevel = GlobalFunction::createNewObject<MainLevel>();
    curLevel->enterGameWorld();
    eventQ = EventQ::getInstance();
}

void Framework::handleEvent()
{
    while(!eventQ->isEmpty())
    {
        curLevel->handleEvent(*eventQ->pollEvent());
    }
}

void Framework::update(const float deltaTime)
{
    curLevel->update(deltaTime);
}
void Framework::render()
{
    curRenderer->readyToDraw();
    curLevel->render();
    //씬 렌더링 그리기 전에 update를 호출해야 한다.
    //그러니까 es의 view renderer에서 onDrawFrame이 호출되면 호출되는 함수를 지정해놓고 해당 함수에서 작업을 하게끔!
}

GLuint Framework::createPngTexture(const char* filePath)
{
    AAsset* rawImage = AAssetManager_open(Framework::assetMng, filePath, AASSET_MODE_UNKNOWN);
    char* buffer = nullptr;
    size_t fileSize = AAsset_getLength(rawImage);
    buffer = new char[fileSize];
    memset(buffer,0,fileSize);
    AAsset_read(rawImage, buffer, fileSize);
    AAsset_close(rawImage);

    std::vector<unsigned char> image;
    unsigned width, height;
    auto data = std::vector<unsigned char>(buffer, buffer+fileSize);
    unsigned error = lodepng::decode(image, width, height, data);
    if (error != 0)
    {
        PRINT_LOG(lodepng_error_text(error), %s);
        return -1;
    }

    GLuint temp;
    glGenTextures(1, &temp);

    glBindTexture(GL_TEXTURE_2D, temp);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

    delete[] buffer;
    buffer = nullptr;
    return temp;
}

void Framework::changeLevel(HLevelBase* level)
{
    if(curLevel)
    {
        delete curLevel;
        curLevel = nullptr;
    }
    curLevel = level;
}

Framework::Framework()
{

}

extern "C"
{
JNIEXPORT void JNICALL Java_com_example_blockgame_GLESNativeLib_init(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_example_blockgame_GLESNativeLib_resize(JNIEnv* env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_com_example_blockgame_GLESNativeLib_draw(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_example_blockgame_GLESNativeLib_readAssetsNative(JNIEnv *env, jobject obj, jobject am);
JNIEXPORT void JNICALL Java_com_example_blockgame_GLESNativeLib_touchEventStart(JNIEnv *env, jobject obj, float x, float y);
JNIEXPORT void JNICALL Java_com_example_blockgame_GLESNativeLib_touchEventMove(JNIEnv *env, jobject obj, float x, float y);
JNIEXPORT void JNICALL Java_com_example_blockgame_GLESNativeLib_touchEventRelease(JNIEnv *env, jobject obj, float x, float y);
};

JNIEXPORT void JNICALL
Java_com_example_blockgame_GLESNativeLib_init(JNIEnv* env, jobject obj)
{
    frameworkInst->init("shader/textureVertex.vs", "shader/textureFrag.fs"); //프레임워크 초기화
}

JNIEXPORT void JNICALL
Java_com_example_blockgame_GLESNativeLib_resize(JNIEnv* env, jobject obj, jint width, jint height)
{
    Framework::screenWidth = width;
    Framework::screenHeight = height;
}
JNIEXPORT void JNICALL
Java_com_example_blockgame_GLESNativeLib_draw(JNIEnv* env, jobject obj)
{
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
    frameworkInst->handleEvent();
    frameworkInst->update(Framework::deltaTime);
    frameworkInst->render();
    std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
    Framework::accTime += sec.count();
    Framework::deltaTime = sec.count();
}

JNIEXPORT void JNICALL
Java_com_example_blockgame_GLESNativeLib_readAssetsNative(JNIEnv *env, jobject obj, jobject am)
{
    frameworkInst = Framework::getInstance();
    frameworkInst->assetMng = AAssetManager_fromJava(env, am);
}

JNIEXPORT void JNICALL
Java_com_example_blockgame_GLESNativeLib_touchEventStart(JNIEnv *env, jobject obj, float x, float y)
{
    Framework::conversionCoordToGLCoordSystem(x, y);
    //위 변환 과정을 통해 openGL의 좌표계 범위와 일치시켜준다.
    Event newEvent(EVENT_TYPE::FINGER_DOWN, x, y);
    frameworkInst->eventQ->pushEvent(newEvent);
}

JNIEXPORT void JNICALL
Java_com_example_blockgame_GLESNativeLib_touchEventMove(JNIEnv *env, jobject obj, float x, float y)
{
    Framework::conversionCoordToGLCoordSystem(x, y);
    Event newEvent(EVENT_TYPE::FINGER_SWIPE, x, y);
    frameworkInst->eventQ->pushEvent(newEvent);
}
JNIEXPORT void JNICALL
Java_com_example_blockgame_GLESNativeLib_touchEventRelease(JNIEnv *env, jobject obj, float x, float y)
{
    Framework::conversionCoordToGLCoordSystem(x, y);
    Event newEvent(EVENT_TYPE::FINGER_UP, x, y);
    frameworkInst->eventQ->pushEvent(newEvent);
}
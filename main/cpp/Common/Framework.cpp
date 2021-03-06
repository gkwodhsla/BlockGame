#include "Framework.h"
#include "Renderer.h"
#include "Common.h"
#include "EventQ.h"
#include "../Actors/HActor.h"
#include "../Levels/MainLevel.h"

#include <cstring>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>
#include <chrono>


#if defined(__ANDROID__) || defined(ANDROID)
#include <GLES3/gl3.h>
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "../parselib/stream/MemInputStream.h"
#include "../parselib/wav/WavStreamReader.h"
#include "../iolib/player/OneShotSampleSource.h"
#include "../iolib/player/SimpleMultiPlayer.h"
#elif defined(IOS)
#include <OpenGLES/ES3/gl.h>
#endif
AAssetManager* Framework::assetMng = nullptr;
Framework* Framework::instance = nullptr;
Renderer* Framework::curRenderer = nullptr;
EventQ* Framework::eventQ = nullptr;
HLevelBase* Framework::curLevel = nullptr;
GLuint Framework::screenWidth = 0;
GLuint Framework::screenHeight = 0;
float Framework::accTime = 0.0f;
float Framework::deltaTime= 0.0f;
bool Framework::isGamePlaying = true;

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
    curRenderer->setClearColor(0.0f,0.0f,0.0f,0.0f);
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
float tempTime = 0.0f;
void Framework::update(const float deltaTime)
{
    curLevel->update(deltaTime);
}
void Framework::render()
{
    curRenderer->readyToDraw();
    curLevel->render();
    //??? ????????? ????????? ?????? update??? ???????????? ??????.
    //???????????? es??? view renderer?????? onDrawFrame??? ???????????? ???????????? ????????? ??????????????? ?????? ???????????? ????????? ?????????!
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

#if defined(__ANDROID__) || defined(ANDROID)
extern "C"
{
JNIEXPORT void JNICALL Java_com_example_blockgame_GLESNativeLib_init(JNIEnv* env, jobject obj);
JNIEXPORT void JNICALL Java_com_example_blockgame_GLESNativeLib_resize(JNIEnv* env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_com_example_blockgame_GLESNativeLib_draw(JNIEnv* env, jobject obj, float deltaTime);
JNIEXPORT void JNICALL Java_com_example_blockgame_GLESNativeLib_readAssetsNative(JNIEnv *env, jobject obj, jobject am);
JNIEXPORT void JNICALL Java_com_example_blockgame_GLESNativeLib_touchEventStart(JNIEnv *env, jobject obj, float x, float y);
JNIEXPORT void JNICALL Java_com_example_blockgame_GLESNativeLib_touchEventMove(JNIEnv *env, jobject obj, float x, float y);
JNIEXPORT void JNICALL Java_com_example_blockgame_GLESNativeLib_touchEventRelease(JNIEnv *env, jobject obj, float x, float y);
JNIEXPORT void JNICALL Java_com_example_blockgame_GLESNativeLib_pause(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_com_example_blockgame_GLESNativeLib_resume(JNIEnv *env, jobject obj);
};

JNIEXPORT void JNICALL
Java_com_example_blockgame_GLESNativeLib_init(JNIEnv* env, jobject obj)
{
    frameworkInst->init("shader/textureVertex.vs", "shader/textureFrag.fs"); //??????????????? ?????????
    PRINT_LOG("init game!", %s)
}

JNIEXPORT void JNICALL
Java_com_example_blockgame_GLESNativeLib_resize(JNIEnv* env, jobject obj, jint width, jint height)
{
    Framework::screenWidth = width;
    Framework::screenHeight = height;
}

JNIEXPORT void JNICALL
Java_com_example_blockgame_GLESNativeLib_draw(JNIEnv* env, jobject obj, float deltaTime)
{
    if(frameworkInst->isGamePlaying)
    {
        if(deltaTime > 0.1f)
        {
            deltaTime = Framework::deltaTime;
        }
        frameworkInst->handleEvent();
        frameworkInst->update(deltaTime);
        frameworkInst->render();
        Framework::deltaTime = deltaTime;
        Framework::accTime += deltaTime;
        //PRINT_LOG(1.0f/deltaTime, %f)
    }
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
    //??? ?????? ????????? ?????? openGL??? ????????? ????????? ??????????????????.
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

JNIEXPORT void JNICALL
Java_com_example_blockgame_GLESNativeLib_pause(JNIEnv *env, jobject obj)
{
    frameworkInst->isGamePlaying = false;
    PRINT_LOG("Pause", %s)
}
JNIEXPORT void JNICALL
Java_com_example_blockgame_GLESNativeLib_resume(JNIEnv *env, jobject obj)
{
    frameworkInst->isGamePlaying = true;
    PRINT_LOG("resume", %s)
}
#elif defined(IOS)
void initGame()
{
    frameworkInst = Framework::getInstance();
    frameworkInst->init("textureVertex.vs", "textureFrag.fs");
}
void render(float deltaTime)
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
void touchEventStart(float x, float y)
{
    Framework::conversionCoordToGLCoordSystem(x, y);
    Event newEvent(EVENT_TYPE::FINGER_DOWN, x, y);
    frameworkInst->eventQ->pushEvent(newEvent);
}
void touchEventMove(float x, float y)
{
    Framework::conversionCoordToGLCoordSystem(x, y);
    Event newEvent(EVENT_TYPE::FINGER_SWIPE, x, y);
    frameworkInst->eventQ->pushEvent(newEvent);
}
void touchEventRelease(float x, float y)
{
    Framework::conversionCoordToGLCoordSystem(x, y);
    Event newEvent(EVENT_TYPE::FINGER_UP, x, y);
    frameworkInst->eventQ->pushEvent(newEvent);
}
#endif
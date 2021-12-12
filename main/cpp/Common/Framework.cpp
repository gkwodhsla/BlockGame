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

class MyCallback:public oboe::AudioStreamDataCallback
{
public:
    oboe::DataCallbackResult
    onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {

        // We requested AudioFormat::Float. So if the stream opens
        // we know we got the Float format.
        // If you do not specify a format then you should check what format
        // the stream has and cast to the appropriate type.
        auto *outputData = static_cast<float *>(audioData);

        // Generate random numbers (white noise) centered around zero.
        const float amplitude = 0.2f;
        for (int i = 0; i < numFrames; ++i){
            outputData[i] = ((float)drand48() - 0.5f) * 2 * amplitude;
        }

        return oboe::DataCallbackResult::Continue;
    }
};
MyCallback myCallback;
std::shared_ptr<oboe::AudioStream> mStream;
void Framework::init(const char* VSPath, const char* FSPath)
{
    curRenderer = new Renderer(VSPath, FSPath);
    curRenderer->addClearBit(GL_COLOR_BUFFER_BIT);
    curRenderer->addClearBit(GL_DEPTH_BUFFER_BIT);
    curRenderer->enableGLFeature(GL_DEPTH_TEST);
    curRenderer->enableGLFeature(GL_BLEND);
    curRenderer->setClearColor(0.0f,0.0f,0.0f,0.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    oboe::AudioStreamBuilder builder;
    builder.setDirection(oboe::Direction::Output);
    builder.setPerformanceMode(oboe::PerformanceMode::LowLatency);
    builder.setSharingMode(oboe::SharingMode::Exclusive);
    builder.setFormat(oboe::AudioFormat::Float);
    builder.setChannelCount(oboe::ChannelCount::Mono);
    builder.setDataCallback(&myCallback);
    oboe::Result result = builder.openStream(mStream);
    if (result != oboe::Result::OK) {
        PRINT_LOG(oboe::convertToText(result), %s)
    }
    mStream->start();
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
    frameworkInst->init("shader/textureVertex.vs", "shader/textureFrag.fs"); //프레임워크 초기화
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
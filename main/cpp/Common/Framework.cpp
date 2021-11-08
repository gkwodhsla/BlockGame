#include "Framework.h"
#include "Renderer.h"
#include "Common.h"
#include "../Actors/HActor.h"


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


AAssetManager* Framework::assetMng = nullptr;
Framework* Framework::instance = nullptr;
Renderer* Framework::curRenderer = nullptr;
GLuint Framework::VAO[2] = {0, 0};
GLuint Framework::VBO[2] = {0, 0};
GLuint Framework::screenWidth = 0;
GLuint Framework::screenHeight = 0;
GLuint Framework::texture = 0;
Framework* frameworkInst = nullptr;
HActor* Framework::testActor = nullptr;

float rect[] =
{
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,//아래 사각형
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f//위에 사각형
};

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

    glDeleteBuffers(2, VBO);
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

    testActor=new HActor();

    /*glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);


    GLuint attribLoc = glGetAttribLocation(curRenderer->getProgramID(), "position");
    glEnableVertexAttribArray(attribLoc);
    glVertexAttribPointer(attribLoc, 3, GL_FLOAT, GL_FALSE,sizeof(float)*5, (GLvoid*)0);

    GLuint attribLoc2 = glGetAttribLocation(curRenderer->getProgramID(), "inputTexPos");
    glEnableVertexAttribArray(attribLoc2);
    glVertexAttribPointer(attribLoc2, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5,(GLvoid*)(sizeof(float)*3));
    //여기까지 사각형 데이터 생성

    glBindVertexArray(0);

    texture = createPngTexture("images/logo.png");*/

}

void Framework::handleEvent()
{
    //추후에 추가
}

void Framework::update(const float deltaTime)
{
    //씬 업데이트
}

void Framework::render()
{
    curRenderer->clearRenderer();


    glm::mat4 worldTransform = glm::translate(glm::mat4(1.0f),glm::vec3(100.f,0.0f,0.0f));
    worldTransform *= glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f,0.0f,1.0f));
    worldTransform *= glm::scale(glm::mat4(1.0f), glm::vec3(300.0f,300.0f,300.0f));
    auto worldTransLoc = glGetUniformLocation(curRenderer->getProgramID(), "worldTrans");
    glUniformMatrix4fv(worldTransLoc, 1, GL_FALSE, glm::value_ptr(worldTransform));


    glm::mat4 cameraTransform = glm::lookAt(glm::vec3(0.0f,0.0f,10.0f),
                                         glm::vec3(0.0f,0.0f,0.0f),
                                         glm::vec3(0.0f,1.0f,0.0f));
    auto cameraTransLoc = glGetUniformLocation(curRenderer->getProgramID(), "cameraTrans");
    glUniformMatrix4fv(cameraTransLoc, 1, GL_FALSE, glm::value_ptr(cameraTransform));

    glm::mat4 projTransform = glm::ortho(-400.0f, 400.0f,-400.0f,400.0f,0.1f,100.0f);
    auto projTransLoc = glGetUniformLocation(curRenderer->getProgramID(), "projTrans");
    glUniformMatrix4fv(projTransLoc, 1, GL_FALSE, glm::value_ptr(projTransform));


    auto uniformLoc = glGetUniformLocation(curRenderer->getProgramID(), "uTexCoord");
    glUniform1i(uniformLoc, 0); //여기 0은 GL_TEXTURE0을 의미한다. 텍스처슬롯!

    testActor->render();
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, texture);
    //glBindVertexArray(VAO[0]);
    //glDrawArrays(GL_TRIANGLES,0,6);

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
        PRINT_LOG(lodepng_error_text(error));
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
    frameworkInst->render();
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
    std::string msg = "Touch Start: " + std::to_string(x) + ", " + std::to_string(y);
    PRINT_LOG(msg.c_str());
}

JNIEXPORT void JNICALL
Java_com_example_blockgame_GLESNativeLib_touchEventMove(JNIEnv *env, jobject obj, float x, float y)
{
    Framework::conversionCoordToGLCoordSystem(x, y);

    //위 변환 과정을 통해 openGL의 좌표계 범위와 일치시켜준다.
    std::string msg = "Touch Move: " + std::to_string(x) + ", " + std::to_string(y);
    PRINT_LOG(msg.c_str());
}
JNIEXPORT void JNICALL
Java_com_example_blockgame_GLESNativeLib_touchEventRelease(JNIEnv *env, jobject obj, float x, float y)
{
    Framework::conversionCoordToGLCoordSystem(x, y);

    //위 변환 과정을 통해 openGL의 좌표계 범위와 일치시켜준다.
    std::string msg = "Touch End: " + std::to_string(x) + ", " + std::to_string(y);
    PRINT_LOG(msg.c_str());
}
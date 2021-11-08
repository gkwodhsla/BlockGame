#pragma once

#include <GLES3/gl3.h>
#include "lodepng/lodepng.h"

class Renderer;
class AAssetManager;
class HActor;

class Framework final //상속을 방지하고, 싱글톤 패턴적용
{
public:
    Framework(const Framework&)=delete;
    Framework& operator=(const Framework&)=delete;
    virtual ~Framework();

public:
    static Framework* getInstance();
    static void init(const char* VSPath, const char* FSPath);
    static void handleEvent();
    static void update(const float deltaTime);
    static void render();
    static GLuint createPngTexture(const char*);
    static inline void conversionCoordToGLCoordSystem(float &x, float &y)
    {
        float ratioX = (float)Framework::screenWidth / 2.0f;
        x /= ratioX;
        x -= 1.0f;

        float ratioY = -(float)Framework::screenHeight / 2.0f;
        y /= ratioY;
        y += 1.0f;
    }

private:
    Framework();

public:
    static AAssetManager* assetMng;
    static Renderer* curRenderer;
    static GLuint screenWidth;
    static GLuint screenHeight;
private:
    static Framework* instance;
    //추후에 레벨 클래스가 추가.
    static GLuint VAO[2];
    static GLuint VBO[2];
    static GLuint texture;
    static HActor* testActor;
};

extern Framework* frameworkInst;
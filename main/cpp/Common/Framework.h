#pragma once

#include <GLES3/gl3.h>
#include "lodepng/lodepng.h"

class Renderer;
class AAssetManager;
class HActor;
class EventQ;
class HLevelBase;

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
    static void changeLevel(HLevelBase* level);
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
    //스크린 좌표계에서 openGL 정규 좌표계로 변경

private:
    Framework();

public:
    static AAssetManager* assetMng;
    static Renderer* curRenderer;
    static EventQ* eventQ; //singleton
    static HLevelBase* curLevel;
    static GLuint screenWidth;
    static GLuint screenHeight;
    static constexpr float rendererSize = 800.0f;
private:
    static Framework* instance;
};

extern Framework* frameworkInst;
#pragma once
#include "HPrimitiveComponent.h"

class PNG;

class ParticleComponent: public HPrimitiveComponent
{
public:
    ParticleComponent(HActor* owner);
    ParticleComponent(const ParticleComponent&) = delete;
    ParticleComponent(const char *filePath, HActor*owner, const bool isCreateMipmap, GLbitfield magFilter,
                      GLbitfield minFilter, const GLbitfield wrappingModeS, const GLbitfield wrappingModeT);
    ParticleComponent&operator=(const ParticleComponent&) = delete;
    virtual ~ParticleComponent();

public:
    void render() override;
    void update(const float deltaTime) override;

public:
    void setPosRange(const std::pair<float, float>& xPos, const std::pair<float, float>& yPos);
    void setVelRange(const std::pair<float, float>& xVel, const std::pair<float, float>& yVel);
    void setAccRange(const std::pair<float, float>& xAcc, const std::pair<float, float>& yAcc);
    void setParticleNum(size_t num);
    void setLifeTime(const float time);
    void setRepeat(bool isParticleRepeat);
    void changeParticleImg(const char* filePath, const bool isCreateMipmap, const GLbitfield magFilter,
                           const GLbitfield minFilter, const GLbitfield wrappingModeS, const GLbitfield wrappingModeT);
    void changeParticleImg(PNG* png);
    void play();
    void stop();

private:
    void setNewParticleData();

private:
    std::pair<float, float> xPosRange = {0.0f, 0.0f};
    std::pair<float, float> yPosRange = {0.0f, 0.0f};
    std::pair<float, float> xVelRange = {0.0f, 0.0f};
    std::pair<float, float> yVelRange = {0.0f, 0.0f};
    std::pair<float, float> xAccRange = {0.0f, 0.0f};
    std::pair<float, float> yAccRange = {0.0f, 0.0f};
    size_t particleNum = 0;
    float lifeTime = 0.0f;
    GLuint rectVBO = 0;
    GLuint velVBO = 0;
    GLuint posVBO = 0;
    GLuint accelVBO = 0;
    PNG* particleImg = nullptr;
    bool isRepeat = false;
    bool isPlay = false;
    float accTime = 0.0f;
    static const float rect[];
};
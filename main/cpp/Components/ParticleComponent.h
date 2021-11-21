#pragma once
#include "HPrimitiveComponent.h"

class PNG;

class ParticleComponent: public HPrimitiveComponent
{
public:
    ParticleComponent() = delete;
    ParticleComponent(const ParticleComponent&) = delete;
    ParticleComponent(const char *filePath, HActor*owner, const bool isCreateMipmap, GLbitfield magFilter,
                      GLbitfield minFilter, const GLbitfield wrappingModeS, const GLbitfield wrappingModeT);
    ParticleComponent&operator=(const ParticleComponent&) = delete;

public:
    void render() override;
    void update(const float deltaTime) override;

public:
    void setPosRange(const std::pair<float, float>& xPos, const std::pair<float, float>& yPos);
    void setVelRange(const std::pair<float, float>& xVel, const std::pair<float, float>& yVel);
    void setAccRange(const std::pair<float, float>& xAcc, const std::pair<float, float>& yAcc);
    void setParticleNum(size_t num);
    void setLifeTime(const float lifeTime);
    void changeParticleImg(const char* filePath, const bool isCreateMipmap, const GLbitfield magFilter,
                           const GLbitfield minFilter, const GLbitfield wrappingModeS, const GLbitfield wrappingModeT);

private:
    std::pair<float, float> xPosRange = {0.0f, 0.0f};
    std::pair<float, float> yPosRange = {0.0f, 0.0f};
    std::pair<float, float> xVelRange = {0.0f, 0.0f};
    std::pair<float, float> yVelRange = {0.0f, 0.0f};
    std::pair<float, float> xAccRange = {0.0f, 0.0f};
    std::pair<float, float> yAccRange = {0.0f, 0.0f};
    size_t particleNum = 0;
    float lifeTime = 0.0f;
    GLuint velVBO = 0;
    GLuint accelVBO = 0;
    PNG* particleImg = nullptr;
};
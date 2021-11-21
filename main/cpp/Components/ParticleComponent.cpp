#include "ParticleComponent.h"
#include "ImageComponent.h"

const float ParticleComponent::rect[] =
        {
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,//아래 사각형
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f//위에 사각형
        };

ParticleComponent::ParticleComponent(const char *filePath, HActor *owner, const bool isCreateMipmap,
                                     GLbitfield magFilter, GLbitfield minFilter,
                                     const GLbitfield wrappingModeS,
                                     const GLbitfield wrappingModeT)
{
    particleImg = GlobalFunction::createNewObject<PNG>(filePath, isCreateMipmap, magFilter, minFilter, wrappingModeS, wrappingModeT);
    setOwner(owner);
    glGenBuffers(1, &rectVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
}

ParticleComponent::~ParticleComponent()
{
    if(rectVBO)
    {
        glDeleteBuffers(1, &rectVBO);
        rectVBO = 0;
    }
    if(velVBO)
    {
        glDeleteBuffers(1, &velVBO);
        velVBO = 0;
    }
    if(accelVBO)
    {
        glDeleteBuffers(1, &accelVBO);
        accelVBO = 0;
    }
}

void ParticleComponent::render()
{
    HPrimitiveComponent::render();
}

void ParticleComponent::update(const float deltaTime)
{
    HPrimitiveComponent::update(deltaTime);
}

void ParticleComponent::setPosRange(const std::pair<float, float> &xPos,
                                    const std::pair<float, float> &yPos)
{
    xPosRange = xPos;
    yPosRange = yPos;
    setNewParticleData();
}

void ParticleComponent::setVelRange(const std::pair<float, float> &xVel,
                                    const std::pair<float, float> &yVel)
{
    xVelRange = xVel;
    yVelRange = yVel;
    setNewParticleData();
}

void ParticleComponent::setAccRange(const std::pair<float, float> &xAcc,
                                    const std::pair<float, float> &yAcc)
{
    xAccRange = xAcc;
    yAccRange = yAcc;
    setNewParticleData();
}

void ParticleComponent::setParticleNum(size_t num)
{
    particleNum = num;
    setNewParticleData();
}

void ParticleComponent::setLifeTime(const float time)
{
    lifeTime = time;
    setNewParticleData();
}

void ParticleComponent::changeParticleImg(const char *filePath, const bool isCreateMipmap,
                                          const GLbitfield magFilter, const GLbitfield minFilter,
                                          const GLbitfield wrappingModeS,
                                          const GLbitfield wrappingModeT)
{
    particleImg->changeImage(filePath, isCreateMipmap, magFilter, minFilter, wrappingModeS, wrappingModeT);
}

void ParticleComponent::setNewParticleData()
{
    if(velVBO)
    {
        glDeleteBuffers(1, &velVBO);
        velVBO = 0;
    }
    if(accelVBO)
    {
        glDeleteBuffers(1, &accelVBO);
        accelVBO = 0;
    }
    auto* velData = new glm::vec2[particleNum];
    auto* accData = new glm::vec2[particleNum];
    for(int i=0;i<particleNum;++i)
    {
        velData[i].x = GlobalFunction::generateRandomFloat(xVelRange.first, xVelRange.second);
        velData[i].y = GlobalFunction::generateRandomFloat(yVelRange.first, yVelRange.second);
        accData[i].x = GlobalFunction::generateRandomFloat(xAccRange.first, xAccRange.second);
        accData[i].y = GlobalFunction::generateRandomFloat(yAccRange.first, yAccRange.second);
    }

    glGenBuffers(1, &velVBO);
    glBindBuffer(GL_ARRAY_BUFFER, velVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*particleNum, velData, GL_STATIC_DRAW);

    glGenBuffers(1, &accelVBO);
    glBindBuffer(GL_ARRAY_BUFFER, accelVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*particleNum, accData, GL_STATIC_DRAW);

    delete[] velData;
    delete[] accData;
}
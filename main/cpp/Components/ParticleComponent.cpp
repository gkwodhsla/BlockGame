#include "ParticleComponent.h"
#include "ImageComponent.h"

ParticleComponent::ParticleComponent(const char *filePath, HActor *owner, const bool isCreateMipmap,
                                     GLbitfield magFilter, GLbitfield minFilter,
                                     const GLbitfield wrappingModeS,
                                     const GLbitfield wrappingModeT)
{

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

}

void ParticleComponent::setVelRange(const std::pair<float, float> &xVel,
                                    const std::pair<float, float> &yVel)
{

}

void ParticleComponent::setAccRange(const std::pair<float, float> &xAcc,
                                    const std::pair<float, float> &yAcc)
{

}

void ParticleComponent::setParticleNum(size_t num)
{

}

void ParticleComponent::setLifeTime(const float lifeTime)
{

}

void ParticleComponent::changeParticleImg(const char *filePath, const bool isCreateMipmap,
                                          const GLbitfield magFilter, const GLbitfield minFilter,
                                          const GLbitfield wrappingModeS,
                                          const GLbitfield wrappingModeT)
{

}

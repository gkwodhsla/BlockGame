#include "ParticleComponent.h"
#include "ImageComponent.h"
#include "../Common/Framework.h"
#include "../Common/Renderer.h"

GLuint ParticleComponent::isInstanceDrawLoc = -1;
GLuint ParticleComponent::isRepeatLoc = -1;
GLuint ParticleComponent::gTimeLoc = -1;
GLuint ParticleComponent::uTexCoordLoc = -1;
GLuint ParticleComponent::velLoc = -1;
GLuint ParticleComponent::accLoc = -1;
GLuint ParticleComponent::addPosLoc = -1;
GLuint ParticleComponent::lifeTimeLoc = -1;

const float ParticleComponent::rect[] =
        {
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,//아래 사각형
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f//위에 사각형
        };

ParticleComponent::ParticleComponent(HActor *owner, int particleNum)
{
    if(isInstanceDrawLoc == -1)
    {
        setStaticData();
    }
    this->particleNum = particleNum;
    setOwner(owner);
    glGenBuffers(1, &rectVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
    setAffectScaleFromParent(false);

    glGenBuffers(1, &velVBO);
    glBindBuffer(GL_ARRAY_BUFFER, velVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*particleNum, nullptr, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &accelVBO);
    glBindBuffer(GL_ARRAY_BUFFER, accelVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*particleNum, nullptr, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &posVBO);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*particleNum, nullptr, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &lifeTimeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lifeTimeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*particleNum, nullptr, GL_DYNAMIC_DRAW);
}
ParticleComponent::ParticleComponent(const char *filePath, HActor *owner, const bool isCreateMipmap,
                                     GLbitfield magFilter, GLbitfield minFilter,
                                     const GLbitfield wrappingModeS,
                                     const GLbitfield wrappingModeT)
{
    if(isInstanceDrawLoc == -1)
    {
        setStaticData();
    }
    particleImg = GlobalFunction::createNewObject<PNG>(filePath, isCreateMipmap, magFilter, minFilter, wrappingModeS, wrappingModeT);
    setOwner(owner);
    glGenBuffers(1, &rectVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
    setAffectScaleFromParent(false);
    //setComponentLocalScale(std::make_pair(5.0f, 5.0f));
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
    if(posVBO)
    {
        glDeleteBuffers(1, &posVBO);
        posVBO = 0;
    }
}

void ParticleComponent::render()
{
    if(isPlay)
    {
        HPrimitiveComponent::render();
        auto programID=Framework::curRenderer->getProgramID();
        glUniform1i(isParticleLoc, true);

        glUniform1i(isRepeatLoc, isRepeat);

        glUniform1f(gTimeLoc, accTime);

        //glUniform1i(uTexCoordLoc, 0); //여기 0은 GL_TEXTURE0을 의미한다. 텍스처슬롯!
        //glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, particleImg->getTextureID());



        glDrawArraysInstanced(GL_TRIANGLES, 0, 6, particleNum);
    }
}

void ParticleComponent::update(const float deltaTime)
{
    if(isPlay)
    {
        accTime += deltaTime;
        HPrimitiveComponent::update(deltaTime);
        if(!isRepeat && accTime>=lifeTime)
            stop();
    }
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
    if(posVBO)
    {
        glDeleteBuffers(1, &posVBO);
        posVBO = 0;
    }
    glGenBuffers(1, &velVBO);
    glBindBuffer(GL_ARRAY_BUFFER, velVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*particleNum, nullptr, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &accelVBO);
    glBindBuffer(GL_ARRAY_BUFFER, accelVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*particleNum, nullptr, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &posVBO);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*particleNum, nullptr, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &lifeTimeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, lifeTimeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*particleNum, nullptr, GL_DYNAMIC_DRAW);
    setNewParticleData();
}

void ParticleComponent::setLifeTime(const float time)
{
    lifeTime = time;
    setNewParticleData();
}

void ParticleComponent::setRepeat(bool isParticleRepeat)
{
    isRepeat = isParticleRepeat;
}

void ParticleComponent::changeParticleImg(const char *filePath, const bool isCreateMipmap,
                                          const GLbitfield magFilter, const GLbitfield minFilter,
                                          const GLbitfield wrappingModeS,
                                          const GLbitfield wrappingModeT)
{
    particleImg->changeImage(filePath, isCreateMipmap, magFilter, minFilter, wrappingModeS, wrappingModeT);
}

void ParticleComponent::changeParticleImg(PNG* png)
{
    particleImg = png;
}

void ParticleComponent::play()
{
    isPlay = true;
    isEnd = false;
    accTime = 0.0f;
}

void ParticleComponent::stop()
{
    isPlay = false;
    isEnd = true;
}

void ParticleComponent::setNewParticleData()
{
    auto* velData = new glm::vec2[particleNum];
    auto* accData = new glm::vec2[particleNum];
    auto* posData = new glm::vec2[particleNum];
    auto* times = new float[particleNum];

    for(int i=0;i<particleNum;++i)
    {
        velData[i].x = GlobalFunction::generateRandomFloat(xVelRange.first, xVelRange.second);
        velData[i].y = GlobalFunction::generateRandomFloat(yVelRange.first, yVelRange.second);
        accData[i].x = GlobalFunction::generateRandomFloat(xAccRange.first, xAccRange.second);
        accData[i].y = GlobalFunction::generateRandomFloat(yAccRange.first, yAccRange.second);
        posData[i].x = GlobalFunction::generateRandomFloat(xPosRange.first, xPosRange.second);
        posData[i].y = GlobalFunction::generateRandomFloat(xPosRange.first, xPosRange.second);
        times[i] = GlobalFunction::generateRandomFloat(0.0f, lifeTime);
    }
    glBindBuffer(GL_ARRAY_BUFFER, velVBO);
    void* ptr = glMapBufferRange(GL_ARRAY_BUFFER,0,sizeof(glm::vec2)*particleNum,
                                 GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_BUFFER_BIT);
    memcpy(ptr, velData, sizeof(glm::vec2)*particleNum);
    glUnmapBuffer(GL_ARRAY_BUFFER);

    glBindBuffer(GL_ARRAY_BUFFER, accelVBO);
    ptr = glMapBufferRange(GL_ARRAY_BUFFER,0,sizeof(glm::vec2)*particleNum,
                                 GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_BUFFER_BIT);
    memcpy(ptr, accData, sizeof(glm::vec2)*particleNum);
    glUnmapBuffer(GL_ARRAY_BUFFER);

    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    ptr = glMapBufferRange(GL_ARRAY_BUFFER,0,sizeof(glm::vec2)*particleNum,
                                 GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_BUFFER_BIT);
    memcpy(ptr, posData, sizeof(glm::vec2)*particleNum);
    glUnmapBuffer(GL_ARRAY_BUFFER);

    glBindBuffer(GL_ARRAY_BUFFER, lifeTimeVBO);
    ptr = glMapBufferRange(GL_ARRAY_BUFFER,0,sizeof(float)*particleNum,
                                 GL_MAP_WRITE_BIT|GL_MAP_INVALIDATE_BUFFER_BIT);
    memcpy(ptr, times, sizeof(float)*particleNum);
    glUnmapBuffer(GL_ARRAY_BUFFER);

    glEnableVertexAttribArray(velLoc);
    glBindBuffer(GL_ARRAY_BUFFER, velVBO);
    glVertexAttribPointer(velLoc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (GLvoid*)0);
    glVertexAttribDivisor(velLoc, 1);

    glEnableVertexAttribArray(accLoc);
    glBindBuffer(GL_ARRAY_BUFFER, accelVBO);
    glVertexAttribPointer(accLoc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (GLvoid*)0);
    glVertexAttribDivisor(accLoc, 1);

    glEnableVertexAttribArray(addPosLoc);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glVertexAttribPointer(addPosLoc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (GLvoid*)0);
    glVertexAttribDivisor(addPosLoc, 1);

    glEnableVertexAttribArray(lifeTimeLoc);
    glBindBuffer(GL_ARRAY_BUFFER, lifeTimeVBO);
    glVertexAttribPointer(lifeTimeLoc, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 1, (GLvoid*)0);
    glVertexAttribDivisor(lifeTimeLoc, 1);

    ptr = nullptr;
    delete[] velData;
    delete[] accData;
    delete[] posData;
    delete[] times;

}

void ParticleComponent::setStaticData()
{
    auto programID=Framework::curRenderer->getProgramID();
    isInstanceDrawLoc = glGetUniformLocation(programID, "isInstanceDraw");
    isRepeatLoc = glGetUniformLocation(programID, "isRepeat");
    gTimeLoc = glGetUniformLocation(programID, "gTime");
    uTexCoordLoc = glGetUniformLocation(programID, "uTexCoord");
    velLoc = glGetAttribLocation(programID, "vel");
    accLoc = glGetAttribLocation(programID, "acc");
    addPosLoc = glGetAttribLocation(programID, "addPos");
    lifeTimeLoc = glGetAttribLocation(programID, "lifeTime");
}
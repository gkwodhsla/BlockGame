#include "BreakableBrick.h"
#include "Ball.h"
#include "../Components/ImageComponent.h"
#include "../Components/BoxCollisionComponent.h"
#include "../Components/ParticleComponent.h"
#include "StageManager.h"

PNG* BreakableBrick::blueImage = nullptr;
PNG* BreakableBrick::redImage = nullptr;
PNG* BreakableBrick::greenImage = nullptr;
PNG* BreakableBrick::orangeImage = nullptr;
PNG* BreakableBrick::purpleImage = nullptr;

float BreakableBrick::xPosMin = -10.0f;
float BreakableBrick::xPosMax = 10.0f;
float BreakableBrick::yPosMin = -10.0f;
float BreakableBrick::yPosMax = 10.0f;
float BreakableBrick::xVelMin = -10.0f;
float BreakableBrick::xVelMax = 10.0f;
float BreakableBrick::yVelMin = -20.0f;
float BreakableBrick::yVelMax = 40.0f;
float BreakableBrick::xAccMin = -10.0f;
float BreakableBrick::xAccMax = 10.0f;
float BreakableBrick::yAccMin = -500.0f;
float BreakableBrick::yAccMax = -300.0f;
float BreakableBrick::particleLifeTime = 2.0f;
int BreakableBrick::particleNum = 50;

BreakableBrick::BreakableBrick()
{
    if(!blueImage)
    {
        blueImage = new PNG("images/blueBlock.png");
        redImage = new PNG("images/redBlock.png");
        greenImage = new PNG("images/greenBlock.png");
        orangeImage = new PNG("images/orangeBlock.png");
        purpleImage = new PNG("images/purpleBlock.png");
    }
    brickImage = createComponent<ImageComponent>(nullptr, this);
    brickImage->attachTo(rootComponent);
    collisionComp->registerCollisionResponse([this](HActor* other)
                                             {
                                                 if(GlobalFunction::Cast<Ball>(other))
                                                 {
                                                     BrickParent::changeBallDirVec(this, other);
                                                     this->setVisibility(false);
                                                     isPlay = true;
                                                     particle->play();
                                                 }
                                             });
    particle = createComponent<ParticleComponent>(this);
    particle->setPosRange(std::make_pair(xPosMin, xPosMax), std::make_pair(yPosMin, yPosMax));
    particle->setVelRange(std::make_pair(xVelMin, xVelMax), std::make_pair(yVelMin, yVelMax));
    particle->setAccRange(std::make_pair(xAccMin, xAccMax), std::make_pair(yAccMin, yAccMax));
    particle->setLifeTime(particleLifeTime);
    particle->setRepeat(false);
    particle->setParticleNum(particleNum);
    particle->attachTo(rootComponent);
    particle->setComponentLocalScale({0.1f, 0.1f});
}

BreakableBrick::BreakableBrick(const char *imgPath)
{
    brickImage = createComponent<ImageComponent>(imgPath, this);
    brickImage->attachTo(rootComponent);
    collisionComp->registerCollisionResponse([this](HActor* other)
                                             {
                                                 if(GlobalFunction::Cast<Ball>(other))
                                                 {
                                                     BrickParent::changeBallDirVec(this, other);
                                                     this->setVisibility(false);
                                                     isPlay = true;
                                                     particle->play();
                                                 }
                                             });
}

BreakableBrick::~BreakableBrick()
{
    if(blueImage)
    {
        delete blueImage;
        delete redImage;
        delete greenImage;
        delete orangeImage;
        delete purpleImage;
        blueImage = nullptr;
        redImage = nullptr;
        greenImage = nullptr;
        orangeImage = nullptr;
        purpleImage = nullptr;
    }
}

void BreakableBrick::render()
{
    HActor::render();
    if(isPlay)
    {
        particle->render();
    }
}

void BreakableBrick::update(const float deltaTime)
{
    HActor::update(deltaTime);
}

void BreakableBrick::setBlockToUse(const BlockColor& color)
{
    switch (color)
    {
        case BlockColor::BLUE:
            brickImage->changeImage(blueImage);
            particle->changeParticleImg(blueImage);
            break;
        case BlockColor::RED:
            brickImage->changeImage(redImage);
            particle->changeParticleImg(redImage);
            break;
        case BlockColor::GREEN:
            brickImage->changeImage(greenImage);
            particle->changeParticleImg(greenImage);
            break;
        case BlockColor::ORANGE:
            brickImage->changeImage(orangeImage);
            particle->changeParticleImg(orangeImage);
            break;
        case BlockColor::PURPLE:
            brickImage->changeImage(purpleImage);
            particle->changeParticleImg(purpleImage);
            break;
    }
}
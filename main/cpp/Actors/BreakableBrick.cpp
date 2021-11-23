#include "BreakableBrick.h"
#include "Ball.h"
#include "../Components/ImageComponent.h"
#include "../Components/BoxCollisionComponent.h"
#include "../Components/ParticleComponent.h"
#include "../Levels/MainLevel.h"
#include "StageManager.h"

PNG* BreakableBrick::blueImage = nullptr;
PNG* BreakableBrick::redImage = nullptr;
PNG* BreakableBrick::greenImage = nullptr;
PNG* BreakableBrick::orangeImage = nullptr;
PNG* BreakableBrick::purpleImage = nullptr;

float BreakableBrick::xPosMin = -25.0f;
float BreakableBrick::xPosMax = 25.0f;
float BreakableBrick::yPosMin = 0.0f;
float BreakableBrick::yPosMax = 3.0f;
float BreakableBrick::xVelMin = -30.0f;
float BreakableBrick::xVelMax = 30.0f;
float BreakableBrick::yVelMin = 0.0f;
float BreakableBrick::yVelMax = 1.0f;
float BreakableBrick::xAccMin = -50.0f;
float BreakableBrick::xAccMax = 50.0f;
float BreakableBrick::yAccMin = -500.0f;
float BreakableBrick::yAccMax = -300.0f;
float BreakableBrick::particleLifeTime = 2.0f;
int BreakableBrick::particleNum = 100;

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
                                                     isHited = true;
                                                 }
                                             });
    particle = createComponent<ParticleComponent>(this, particleNum);
    particle->setPosRange(std::make_pair(xPosMin, xPosMax), std::make_pair(yPosMin, yPosMax));
    particle->setVelRange(std::make_pair(xVelMin, xVelMax), std::make_pair(yVelMin, yVelMax));
    particle->setAccRange(std::make_pair(xAccMin, xAccMax), std::make_pair(yAccMin, yAccMax));
    particle->setLifeTime(particleLifeTime);
    particle->setRepeat(false);
    particle->attachTo(rootComponent);
    particle->setComponentLocalScale({5.0f, 5.0f});

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
        bindVAO();
        particle->render();
    }
}

void BreakableBrick::update(const float deltaTime)
{
    HActor::update(deltaTime);
    if(isHited && particle->getIsEnd())
    {
        auto mainLv = GlobalFunction::Cast<MainLevel>(GlobalFunction::getLevel());
        if(mainLv)
        {
            mainLv->stageManager->decRestBrick();
            mainLv->stageManager->returnToPool(this);
            isHited = false;
        }
    }
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
    isHited = false;
    isPlay = false;
}
#include "BreakableBrick.h"
#include "Ball.h"
#include "../Components/ImageComponent.h"
#include "../Components/BoxCollisionComponent.h"
#include "StageManager.h"

PNG* BreakableBrick::blueImage = nullptr;
PNG* BreakableBrick::redImage = nullptr;
PNG* BreakableBrick::greenImage = nullptr;
PNG* BreakableBrick::orangeImage = nullptr;
PNG* BreakableBrick::purpleImage = nullptr;

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
                                                 }
                                             });
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
    }
}

void BreakableBrick::render()
{
    HActor::render();
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
            break;
        case BlockColor::RED:
            brickImage->changeImage(redImage);
            break;
        case BlockColor::GREEN:
            brickImage->changeImage(greenImage);
            break;
        case BlockColor::ORANGE:
            brickImage->changeImage(orangeImage);
            break;
        case BlockColor::PURPLE:
            brickImage->changeImage(purpleImage);
            break;
    }
}
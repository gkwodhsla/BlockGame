#include "BreakableBrick.h"
#include "../Components/ImageComponent.h"
#include "../Components/BoxCollisionComponent.h"

BreakableBrick::BreakableBrick(const char *imgPath)
{
    brickImage = createComponent<ImageComponent>(imgPath, this);
    brickImage->attachTo(rootComponent);
    collisionComp->registerCollisionResponse([this](HActor* other)
                                             {
                                                 BrickParent::changeBallDirVec(this, other);
                                                 this->setVisibility(false);
                                             });
}

BreakableBrick::~BreakableBrick()
{

}

void BreakableBrick::render()
{
    HActor::render();
}

void BreakableBrick::update(const float deltaTime)
{
    HActor::update(deltaTime);
}

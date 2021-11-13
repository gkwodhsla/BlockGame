#include "UnbreakableBrick.h"
#include "../Components/ImageComponent.h"
#include "../Components/BoxCollisionComponent.h"


UnbreakableBrick::UnbreakableBrick(const char *imgPath)
{
    brickImage = createComponent<ImageComponent>(imgPath, this);
    brickImage->attachTo(rootComponent);
    collisionComp->registerCollisionResponse([this](HActor* other)
    {
        BrickParent::changeBallDirVec(this, other);
    });
}

UnbreakableBrick::~UnbreakableBrick()
{

}

void UnbreakableBrick::render()
{
    HActor::render();
}

void UnbreakableBrick::update(const float deltaTime)
{
    HActor::update(deltaTime);
}

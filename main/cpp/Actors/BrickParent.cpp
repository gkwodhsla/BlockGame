#include "BrickParent.h"
#include "../Components/BoxCollisionComponent.h"

BrickParent::BrickParent()
{
    collisionComp = createComponent<BoxCollisionComponent>(1.0f, 1.0f, this);
    collisionComp->attachTo(rootComponent);
}

void BrickParent::setCollisionBoxWidthAndHeight(float w, float h)
{
    collisionComp->setComponentLocalScale({w, h});
}

BrickParent::~BrickParent()
{

}
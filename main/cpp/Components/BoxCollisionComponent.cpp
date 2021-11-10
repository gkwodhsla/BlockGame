#include "BoxCollisionComponent.h"
#include "CircleCollisionComponent.h"
#include "../Common/Common.h"
#include "../Levels/HLevelBase.h"

BoxCollisionComponent::BoxCollisionComponent(float w, float h, HActor *owner):CollisionParent(owner)
{
    setComponentLocalScale({w, h});
    GlobalFunction::getLevel()->addCollisionObject(this);
}

BoxCollisionComponent::~BoxCollisionComponent()
{

}



void BoxCollisionComponent::checkCollision(const CollisionParent &otherCollisionComp)
{
    if(GlobalFunction::Cast<BoxCollisionComponent>(&otherCollisionComp))
    {
        if(isRectIntersect(this, GlobalFunction::Cast<BoxCollisionComponent>(&otherCollisionComp)))
        {
            collisionResponse(otherCollisionComp.getOwner());
            otherCollisionComp.collisionResponse(this->getOwner());
        }
    }
    else if(GlobalFunction::Cast<CircleCollisionComponent>(&otherCollisionComp))
    {
        if(isRectAndCircleIntersect(this, GlobalFunction::Cast<CircleCollisionComponent>(&otherCollisionComp)))
        {
            collisionResponse(otherCollisionComp.getOwner());
            otherCollisionComp.collisionResponse(this->getOwner());
        }
    }
}

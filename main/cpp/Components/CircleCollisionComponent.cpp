#include "CircleCollisionComponent.h"
#include "BoxCollisionComponent.h"
#include "../Common/Common.h"
#include "../Levels/HLevelBase.h"
#include <cmath>

CircleCollisionComponent::CircleCollisionComponent(float radius, HActor *owner):CollisionParent(owner), radius(radius)
{
    GlobalFunction::getLevel()->addCollisionObject(this);
}

CircleCollisionComponent::~CircleCollisionComponent()
{

}

void CircleCollisionComponent::checkCollision(const CollisionParent& otherCollisionComp)
{
    if(GlobalFunction::Cast<CircleCollisionComponent>(&otherCollisionComp))
    {
        if(isCircleIntersect(this, GlobalFunction::Cast<CircleCollisionComponent>(&otherCollisionComp)))
        {
            collisionResponse(otherCollisionComp.getOwner());
            otherCollisionComp.collisionResponse(this->getOwner());
        }
    }
    else if(GlobalFunction::Cast<BoxCollisionComponent>(&otherCollisionComp))
    {
        if(isRectAndCircleIntersect(GlobalFunction::Cast<BoxCollisionComponent>(&otherCollisionComp), this))
        {
            collisionResponse(otherCollisionComp.getOwner());
            otherCollisionComp.collisionResponse(this->getOwner());
        }
    }


}

void CircleCollisionComponent::setRadius(float rad)
{
    radius = rad;
}

float CircleCollisionComponent::getRadius() const
{
    return radius;
}

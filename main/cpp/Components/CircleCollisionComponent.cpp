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
        auto other = GlobalFunction::Cast<CircleCollisionComponent>(&otherCollisionComp);
        auto otherLoc = other->getComponentWorldLocation();
        auto thisLoc = this->getComponentWorldLocation();

        float dx = otherLoc.first - thisLoc.first;
        float dy = otherLoc.second - thisLoc.second;

        float dist = sqrt(dx*dx +dy*dy);
        if(dist <= other->radius+radius)
        {
            collisionResponse(other->getOwner());
            other->collisionResponse(this->getOwner());
        }
    }
    else if(GlobalFunction::Cast<BoxCollisionComponent>(&otherCollisionComp))
    {

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

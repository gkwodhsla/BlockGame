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
        auto other = GlobalFunction::Cast<BoxCollisionComponent>(&otherCollisionComp);
        auto otherLoc = other->getComponentWorldLocation();
        auto otherScale = other->getComponentWorldScale();
        auto thisLoc = this->getComponentWorldLocation();
        auto thisScale = this->getComponentWorldScale();

        float otherLeft = otherLoc.first - otherScale.first / 2.0f;
        float otherRight = otherLoc.first + otherScale.first / 2.0f;
        float otherBottom = otherLoc.second - otherScale.second / 2.0f;
        float otherTop = otherLoc.second + otherScale.second / 2.0f;

        float thisLeft = thisLoc.first - thisScale.first / 2.0f;
        float thisRight = thisLoc.first + thisScale.first / 2.0f;
        float thisBottom = thisLoc.second - thisScale.second / 2.0f;
        float thisTop = thisLoc.second + thisScale.second / 2.0f;

        if(otherRight<thisLeft)
            return;
        if(thisRight<otherLeft)
            return;
        if(otherTop<thisBottom)
            return;
        if(thisTop<otherBottom)
            return;
        collisionResponse(otherCollisionComp.getOwner());
        other->collisionResponse(this->getOwner());
    }
    else if(GlobalFunction::Cast<CircleCollisionComponent>(&otherCollisionComp))
    {
        auto other = GlobalFunction::Cast<CircleCollisionComponent>(&otherCollisionComp);
        auto otherLoc = other->getComponentWorldLocation();
        auto thisLoc = this->getComponentWorldLocation();
        auto thisScale = this->getComponentWorldScale();
        float otherRad = other->getRadius();

        float thisLeft = thisLoc.first - thisScale.first / 2.0f;
        float thisRight = thisLoc.first + thisScale.first / 2.0f;
        float thisBottom = thisLoc.second - thisScale.second / 2.0f;
        float thisTop = thisLoc.second + thisScale.second / 2.0f;

        thisLeft-=otherRad;
        thisRight+=otherRad;
        thisTop+=otherRad;
        thisBottom-=otherRad;

        if(otherLoc.first <= thisRight &&
           otherLoc.first >= thisLeft &&
           otherLoc.second <= thisTop &&
           otherLoc.second >= thisBottom)
        {
            collisionResponse(otherCollisionComp.getOwner());
            otherCollisionComp.collisionResponse(getOwner());
            return;
        }

        thisLeft+=otherRad;
        thisRight-=otherRad;
        thisTop-=otherRad;
        thisBottom+=otherRad;

        if(isPointInCircle(otherLoc.first, otherLoc.second, otherRad, thisRight, thisTop))//우상단
        {
            collisionResponse(otherCollisionComp.getOwner());
            otherCollisionComp.collisionResponse(getOwner());
        }
        else if(isPointInCircle(otherLoc.first, otherLoc.second, otherRad, thisRight, thisBottom))//우하단
        {
            collisionResponse(otherCollisionComp.getOwner());
            otherCollisionComp.collisionResponse(getOwner());
        }
        else if(isPointInCircle(otherLoc.first, otherLoc.second, otherRad, thisLeft, thisBottom))//좌상단
        {
            collisionResponse(otherCollisionComp.getOwner());
            otherCollisionComp.collisionResponse(getOwner());
        }
        else if(isPointInCircle(otherLoc.first, otherLoc.second, otherRad, thisLeft, thisBottom))//좌하단
        {
            collisionResponse(otherCollisionComp.getOwner());
            otherCollisionComp.collisionResponse(getOwner());
        }
    }
}

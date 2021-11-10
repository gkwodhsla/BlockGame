#include "CollisionParent.h"
#include "BoxCollisionComponent.h"
#include "CircleCollisionComponent.h"

#include <cmath>
CollisionParent::CollisionParent(HActor *owner)
{
    setOwner(owner);
}

void CollisionParent::registerCollisionResponse(const std::function<void(HActor *)> &func)
{
    collisionResponse = func;
}

CollisionParent::~CollisionParent()
{

}

bool CollisionParent::isPointInCircle(float cx, float cy, float cr, float px, float py)
{
    float dx = cx - px;
    float dy = cy - py;
    float dist = sqrt(dx * dx + dy * dy);
    return dist <= cr;
}

bool CollisionParent::isRectIntersect(BoxCollisionComponent* mainCollisionComp, BoxCollisionComponent* otherCollisionComp)
{
    auto otherLoc = otherCollisionComp->getComponentWorldLocation();
    auto otherScale = otherCollisionComp->getComponentWorldScale();
    auto thisLoc = mainCollisionComp->getComponentWorldLocation();
    auto thisScale = mainCollisionComp->getComponentWorldScale();

    float otherLeft = otherLoc.first - otherScale.first / 2.0f;
    float otherRight = otherLoc.first + otherScale.first / 2.0f;
    float otherBottom = otherLoc.second - otherScale.second / 2.0f;
    float otherTop = otherLoc.second + otherScale.second / 2.0f;

    float thisLeft = thisLoc.first - thisScale.first / 2.0f;
    float thisRight = thisLoc.first + thisScale.first / 2.0f;
    float thisBottom = thisLoc.second - thisScale.second / 2.0f;
    float thisTop = thisLoc.second + thisScale.second / 2.0f;

    if(otherRight<thisLeft)
        return false;
    if(thisRight<otherLeft)
        return false;
    if(otherTop<thisBottom)
        return false;
    if(thisTop<otherBottom)
        return false;

    return true;
}

bool CollisionParent::isCircleIntersect(CircleCollisionComponent* mainCollisionComp, CircleCollisionComponent *otherCollisionComp)
{
    auto otherLoc = otherCollisionComp->getComponentWorldLocation();
    auto thisLoc = mainCollisionComp->getComponentWorldLocation();

    float dx = otherLoc.first - thisLoc.first;
    float dy = otherLoc.second - thisLoc.second;

    float dist = sqrt(dx*dx +dy*dy);
    if(dist <= otherCollisionComp->getRadius()+mainCollisionComp->getRadius())
    {
        return true;
    }
    return false;
}

bool CollisionParent::isRectAndCircleIntersect(BoxCollisionComponent* boxCollisionComp, CircleCollisionComponent* circleCollisionComp)
{
    auto otherLoc = circleCollisionComp->getComponentWorldLocation();
    auto thisLoc = boxCollisionComp->getComponentWorldLocation();
    auto thisScale = boxCollisionComp->getComponentWorldScale();
    float otherRad = circleCollisionComp->getRadius();

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
        return true;
    }

    thisLeft+=otherRad;
    thisRight-=otherRad;
    thisTop-=otherRad;
    thisBottom+=otherRad;

    if(isPointInCircle(otherLoc.first, otherLoc.second, otherRad, thisRight, thisTop))//우상단
    {
        return true;
    }
    else if(isPointInCircle(otherLoc.first, otherLoc.second, otherRad, thisRight, thisBottom))//우하단
    {
        return true;
    }
    else if(isPointInCircle(otherLoc.first, otherLoc.second, otherRad, thisLeft, thisBottom))//좌상단
    {
        return true;
    }
    else if(isPointInCircle(otherLoc.first, otherLoc.second, otherRad, thisLeft, thisBottom))//좌하단
    {
        return true;
    }

    return false;
}

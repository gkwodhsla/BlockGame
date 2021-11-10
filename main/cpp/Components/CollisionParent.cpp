#include "CollisionParent.h"
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
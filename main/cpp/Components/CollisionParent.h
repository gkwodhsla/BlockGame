#pragma once
#include "HSceneComponent.h"
#include <functional>

class HActor;

class CollisionParent: public HSceneComponent
{
public:
    CollisionParent() = delete;
    CollisionParent(const CollisionParent&) = delete;
    CollisionParent(HActor* owner);
    CollisionParent&operator=(const CollisionParent&) = delete;
    virtual ~CollisionParent() = 0;
    virtual void checkCollision(const CollisionParent& otherCollisionComp) = 0;
public:
    std::function<void(HActor*)> collisionResponse = nullptr;
    void registerCollisionResponse(const std::function<void(HActor*)>& func);
    bool isPointInCircle(float cx, float cy, float cr, float px, float py);
};
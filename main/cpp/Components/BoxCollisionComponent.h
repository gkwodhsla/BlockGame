#pragma once
#include "CollisionParent.h"


class BoxCollisionComponent: public CollisionParent
{
public:
    BoxCollisionComponent() = delete;
    BoxCollisionComponent(const BoxCollisionComponent&) = delete;
    BoxCollisionComponent&operator=(const BoxCollisionComponent&) = delete;
    BoxCollisionComponent(float w, float h, HActor* owner);
    virtual ~BoxCollisionComponent();

public:
    void checkCollision(const CollisionParent& otherCollisionComp) override;
};

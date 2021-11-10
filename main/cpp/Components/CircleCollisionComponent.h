#pragma once
#include "CollisionParent.h"

class CircleCollisionComponent:public CollisionParent
{
public:
    CircleCollisionComponent() = delete;
    CircleCollisionComponent(const CircleCollisionComponent&) = delete;
    CircleCollisionComponent(float radius, HActor* owner);
    CircleCollisionComponent& operator=(const CircleCollisionComponent&) = delete;
    virtual ~CircleCollisionComponent();

public:
    void checkCollision(const CollisionParent&) override;
    void setRadius(float rad);
    float getRadius()const;

private:
    float radius = 0.0f;
};


#pragma once

#include "HActor.h"

class BoxCollisionComponent;

class BrickParent: public HActor
{
public:
    BrickParent();
    BrickParent(const BrickParent&) = delete;
    BrickParent&operator=(const BrickParent&) = delete;
    virtual ~BrickParent() = 0;
    void setCollisionBoxWidthAndHeight(float w, float h);

protected:
    BoxCollisionComponent* collisionComp = nullptr;
};
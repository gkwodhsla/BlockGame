#pragma once

#include "HActor.h"
#include <random>

class BoxCollisionComponent;
class ImageComponent;

class BrickParent: public HActor
{
public:
    BrickParent();
    BrickParent(const BrickParent&) = delete;
    BrickParent&operator=(const BrickParent&) = delete;
    virtual ~BrickParent() = 0;
    void setCollisionBoxWidthAndHeight(float w, float h);
    BoxCollisionComponent* getCollisionComp();
    static void changeBallDirVec(HActor* me, HActor* other);

protected:
    BoxCollisionComponent* collisionComp = nullptr;
    ImageComponent* brickImage = nullptr;
};
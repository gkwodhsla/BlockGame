#pragma once
#include "BrickParent.h"

class ImageComponent;

class UnbreakableBrick: public BrickParent
{
public:
    UnbreakableBrick(const char* imgPath);
    UnbreakableBrick() = delete;
    UnbreakableBrick(const UnbreakableBrick&) = delete;
    UnbreakableBrick&operator=(const UnbreakableBrick&) = delete;
    virtual ~UnbreakableBrick();

public:
    virtual void render() override;
    virtual void update(const float deltaTime) override;
    void setCollisionComp(float rad);

private:
    ImageComponent* brickImage = nullptr;
};
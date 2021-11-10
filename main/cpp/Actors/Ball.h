#pragma once
#include "HActor.h"

class CircleCollisionComponent;
class ImageComponent;
class Ball: public HActor
{
public:
    Ball();
    Ball(const Ball&) = delete;
    Ball&operator=(const Ball&) = delete;
    virtual ~Ball();

public:
    virtual void render() override;
    virtual void update(const float deltaTime) override;

private:
    ImageComponent* ballImg;
    CircleCollisionComponent* collisionComp;
};
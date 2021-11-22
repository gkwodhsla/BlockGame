#pragma once
#include "HActor.h"

class CircleCollisionComponent;
class ImageComponent;
class MovementComponent;
class ParticleComponent;
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
    void setCollisionComp(float rad);

public:
    ParticleComponent* ballParticle = nullptr;

private:
    ImageComponent* ballImg = nullptr;
    CircleCollisionComponent* collisionComp = nullptr;
    MovementComponent* ballMovement = nullptr;
    static const float ballSpeed;
};
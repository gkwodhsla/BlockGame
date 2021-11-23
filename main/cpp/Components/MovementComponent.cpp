#include "MovementComponent.h"
#include "../Actors/HActor.h"
#include "HSceneComponent.h"
#include "../Common/Framework.h"

MovementComponent::MovementComponent(HActor* owner)
{
    this->owner = owner;
}

void MovementComponent::update(const float deltaTime)
{
    updatePosition(deltaTime);
}

void MovementComponent::setMaxSpeed(const float speed)
{
    this->maxSpeed = speed;
}

void MovementComponent::setMaxAcceleration(const float accel)
{
    maxAcceleration = accel;
}

void MovementComponent::updatePosition(const float deltaTime)
{
    curAccel = befAccel + deltaAccel*deltaTime;
    if(curAccel>=maxAcceleration)
    {
        curAccel = maxAcceleration;
    }
    speed = befSpeed + befAccel * deltaTime;
    if(speed>=maxSpeed)
    {
        speed = maxSpeed;
    }
    HSceneComponent* ownerRootComp = owner->getRootComponent();
    auto dirVec = owner->getActorDirectionalVector();
    auto velocity = std::make_pair(dirVec.x * speed, dirVec.y * speed);
    //속력은 방향벡터 * 속도이다.

    auto befPos = ownerRootComp->getComponentLocalLocation();

    std::pair<float, float> newPos;

    newPos.first = befPos.first + velocity.first * deltaTime;

    newPos.second = befPos.second + velocity.second * deltaTime;

    ownerRootComp->setComponentLocalLocation(newPos);

    befAccel = curAccel;
    befSpeed = speed;
}

void MovementComponent::setDeltaAccel(const float accel)
{
    deltaAccel = accel;
}
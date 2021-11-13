#include "MovementComponent.h"
#include "../Actors/HActor.h"
#include "HSceneComponent.h"

MovementComponent::MovementComponent(HActor* owner)
{
    this->owner = owner;
}

void MovementComponent::update(const float deltaTime)
{
    updatePosition(deltaTime);
}

void MovementComponent::setSpeed(float speed)
{
    this->speed = speed;
}

void MovementComponent::setAcceleration(const std::pair<float, float> &accel)
{
    acceleration = accel;
}

void MovementComponent::updatePosition(const float deltaTime)
{
    HSceneComponent* ownerRootComp = owner->getRootComponent();
    auto dirVec = owner->getActorDirectionalVector();
    auto initVelocity = std::make_pair(dirVec.x * speed, dirVec.y * speed);
    //속력은 방향벡터 * 속도이다.

    auto befPos = ownerRootComp->getComponentLocalLocation();

    std::pair<float, float> newPos;

    newPos.first = befPos.first + (initVelocity.first * deltaTime)+
            (0.5f * acceleration.first * deltaTime * deltaTime);

    newPos.second = befPos.second + (initVelocity.second * deltaTime)+
                    (0.5f * acceleration.second * deltaTime * deltaTime);

    ownerRootComp->setComponentLocalLocation(newPos);
    //거리 = 이전 거리 + 초기 속도 * 시간 + (0.5 * 가속도 * 시간^2)
    //여기에다가 방향벡터를 갱신하는 수식을 작성한다.
    //현재 위치 - 이전 위치 하고 정규화

}

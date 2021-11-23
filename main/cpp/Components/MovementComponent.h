#pragma once

#include "HComponent.h"
#include <utility>
//시간에 따른 이동을 구현한 컴포넌트이다.
//이 컴포넌트를 소유하고 있는 액터의 방향벡터를 이용해
//매 업데이트마다 위치를 갱신시켜준다.
class HActor;

class MovementComponent :public HComponent
{
public:
    MovementComponent() = delete;
    MovementComponent(const MovementComponent&) = delete;
    MovementComponent& operator=(const MovementComponent&) = delete;
    MovementComponent(HActor* owner);
    virtual ~MovementComponent() = default;
    virtual void update(const float deltaTime);
    void setMaxSpeed(const float speed);
    void setMaxAcceleration(const float accel);
    void setDeltaAccel(const float accel);

private:
    void updatePosition(const float deltaTime);

private:
    float maxAcceleration = 100.0f;
    float curAccel = 0.0f;
    float speed = 0.0f;
    float maxSpeed = 100.0f;
    float befSpeed = 0.0f;
    float befAccel = 0.0f;
    float deltaAccel = 50.0f;
};



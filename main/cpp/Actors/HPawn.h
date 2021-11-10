#pragma once

#include "HActor.h"
#include "../Common/EventQ.h"

//class MovementComponent;
class HPlayerController;
//폰은 플레이어의 입력을 받을 수 있는 특수한 액터이다.
class HPawn :public HActor
{
public:
    HPawn();
    HPawn(const HPawn&) = delete;
    HPawn& operator=(const HPawn&) = delete;
    virtual ~HPawn();
    void setCanRecvInputEvent(bool canInput);
    HPlayerController* getController() const;
    virtual void render() override;
    virtual void update(const float deltaTime) override;
    virtual void handleEvent(const Event& e) = 0;
protected:
    //MovementComponent* movementComp = nullptr;
    HPlayerController* controller = nullptr;
    bool canReceiveInputFromPlayer = true;
};
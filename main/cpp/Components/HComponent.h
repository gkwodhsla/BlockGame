#pragma once

#include "../Actors/HActor.h"
#include "../Common/HObject.h"

class HComponent: public HObject
{
public:
    HComponent() = default;
    HComponent(const HComponent&) = delete;
    HComponent& operator=(const HComponent&) = delete;
    virtual ~HComponent() = default;

public:
    virtual void update(const float deltaTime) = 0;
    HActor* getOwner() const
    {
        return owner;
    }

public:
    void setComponentTickable(bool isTickable)
    {
        tickable = isTickable;
    }
    const bool getComponentTickable() const
    {
        return tickable;
    }

protected:
    HActor* owner;
    bool tickable = true;
};

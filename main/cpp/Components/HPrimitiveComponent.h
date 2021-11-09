#pragma once

#include "HSceneComponent.h"

//렌더링되는 SceneComponent이다.
class HPrimitiveComponent: public HSceneComponent
{
public:
    HPrimitiveComponent();
    HPrimitiveComponent(const HPrimitiveComponent&) = delete;
    HPrimitiveComponent& operator=(const HPrimitiveComponent&) = delete;
    virtual ~HPrimitiveComponent();

public:
    virtual void update(const float deltaTime) override;
    virtual void render() override;

public:
    void setVisibility(bool isVisible);
    bool getVisibility();

protected:
    bool visibility = true;
};
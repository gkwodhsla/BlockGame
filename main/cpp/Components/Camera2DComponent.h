#pragma once
#include "HSceneComponent.h"
#include "../glm-master/glm/glm.hpp"

class Camera2DComponent: public HSceneComponent
{
public:
    Camera2DComponent() = delete;
    Camera2DComponent(const float left, const float right, const float bottom, const float top,
                      const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up, HActor* owner);
    Camera2DComponent(const Camera2DComponent&) = delete;
    Camera2DComponent&operator=(const Camera2DComponent&) = delete;
    virtual ~Camera2DComponent();

public:
    void setProgramViewProjectionMat(GLuint programID);
    void changeCameraInnerProperty(const float left, const float right, const float bottom, const float top);
    void changeCameraOuterProperty(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
    void activate();
    void setIsSightFixed(bool isFixed);
    //시선이 고정되면 카메라가 움직여도 AT만 바라보지만 고정X라면 EYE에 따라 at이 바뀐다.

private:
    bool isSightFixed = true;
    float left;
    float right;
    float bottom;
    float top;
    glm::vec3 eye = {0.0f,0.0f,0.0f};
    glm::vec3 at = {0.0f,0.0f,0.0f};
    glm::vec3 up = {0.0f,0.0f,0.0f};
};


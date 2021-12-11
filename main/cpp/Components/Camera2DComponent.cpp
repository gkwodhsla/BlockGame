#include "Camera2DComponent.h"
#include "../Common/Framework.h"
#include "../Common/Renderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>

GLuint Camera2DComponent::cameraLoc = -1;
GLuint Camera2DComponent::projLoc = -1;


Camera2DComponent::Camera2DComponent(const float left, const float right, const float bottom,
                                     const float top, const glm::vec3 &eye, const glm::vec3 &at,
                                     const glm::vec3 &up, HActor* owner):
left(left), right(right), bottom(bottom), top(top), eye(eye), at(at), up(up)
{
    setOwner(owner);
}

Camera2DComponent::~Camera2DComponent()
{

}

void Camera2DComponent::setProgramViewProjectionMat(GLuint programID)
{
    glm::mat4 cameraTransform = glm::mat4(1.0f);
    if(isSightFixed)
    {
        cameraTransform = glm::lookAt(eye, at, up);
    }
    else
    {
        cameraTransform = glm::lookAt(eye, glm::vec3{eye.x, eye.y, 0.0f}, up);
    }
    if(cameraLoc == -1)
    {
        cameraLoc = glGetUniformLocation(programID, "cameraTrans");
        projLoc = glGetUniformLocation(programID, "projTrans");
    }
    glUniformMatrix4fv(cameraLoc, 1, GL_FALSE, glm::value_ptr(cameraTransform));

    glm::mat4 projTransform = glm::ortho(left, right,bottom, top,1.0f,100.0f);

    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projTransform));
}

void Camera2DComponent::changeCameraInnerProperty(const float left, const float right,
                                                  const float bottom, const float top)
{
    this->left = left;
    this->right = right;
    this->bottom = bottom;
    this->top = top;
}

void Camera2DComponent::changeCameraOuterProperty(const glm::vec3 &eye, const glm::vec3 &at,
                                                  const glm::vec3 &up)
{
    this->eye = eye;
    this->at = at;
    this->up = up;
}

void Camera2DComponent::activate()
{
    frameworkInst->curRenderer->setCamera(this);
}

void Camera2DComponent::setIsSightFixed(bool isFixed)
{
    isSightFixed = isFixed;
}
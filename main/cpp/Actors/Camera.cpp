#include "Camera.h"
#include "../Components/Camera2DComponent.h"

Camera::Camera()
{
    cameraComp = createComponent<Camera2DComponent>(-400.0f,400.0f,-400.0f,400.0f,glm::vec3{0.0f,0.0f,10.0f},
                                                    glm::vec3{0.0f,0.0f,0.0f},glm::vec3{0.0f,1.0f,0.0f}, this);
    cameraComp->attachTo(rootComponent);
}

Camera::~Camera()
{

}

void Camera::activateCamera()
{
    cameraComp->activate();
}

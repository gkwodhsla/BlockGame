#include "Camera.h"
#include "../Components/Camera2DComponent.h"

Camera::Camera(float rendererSize)
{
    float halfSize = rendererSize / 2.0f;
    cameraComp = createComponent<Camera2DComponent>(-halfSize,halfSize,-halfSize,halfSize,glm::vec3{0.0f,0.0f,10.0f},
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

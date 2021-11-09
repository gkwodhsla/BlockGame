#include "Camera.h"
#include "../Components/Camera2DComponent.h"

Camera::Camera()
{
    cameraComp = new Camera2DComponent(-400.0f,400.0f,-400.0f,400.0f,{0.0f,0.0f,10.0f},
                                       {0.0f,0.0f,0.0f},{0.0f,1.0f,0.0f});
    cameraComp->attachTo(rootComponent);
    cameraComp->setOwner(this);
    cameraComp->activate();
}

Camera::~Camera()
{
    delete cameraComp;
    cameraComp = nullptr;
}
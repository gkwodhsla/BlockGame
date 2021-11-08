#include "HPrimitiveComponent.h"

HPrimitiveComponent::HPrimitiveComponent()
{

}

HPrimitiveComponent::~HPrimitiveComponent()
{

}

void HPrimitiveComponent::update(const float deltaTime)
{
    HSceneComponent::update(deltaTime);
}

void HPrimitiveComponent::render()
{
    HSceneComponent::render();
}

void HPrimitiveComponent::setVisibility(const bool isVisible)
{
    visibility = isVisible;
}

void HPrimitiveComponent::setScale(const std::pair<float, float>& scale)
{
    this->scale = scale;
}
std::pair<float, float> HPrimitiveComponent::getScale()
{
    return scale;
}

bool HPrimitiveComponent::getVisibility()
{
    return visibility;
}



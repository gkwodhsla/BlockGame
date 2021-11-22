#include "HSceneComponent.h"
#include "../Actors/HActor.h"

HSceneComponent::HSceneComponent()
{

}

HSceneComponent::~HSceneComponent()
{

}

void HSceneComponent::updateComponentWorldRotation()
{
    if(parent && isUsingParentRotation)
    {
        worldRotation = parent->getComponentWorldRotation() + localRotation;
    }
    else if(!parent || (parent && !isUsingParentRotation)) //부모가 없다면 루트 컴포넌트이다.
    {
        worldRotation = localRotation;
    }
    for(auto& child:children)
    {
        child->updateComponentWorldRotation();
    }
}

void HSceneComponent::updateComponentWorldLocation()
{
    if(parent && isUsingParentLocation)
    {
        auto parentLocalLocation = parent->getComponentWorldLocation();
        worldLocation = std::make_pair(parentLocalLocation.first + localLocation.first,
                                       parentLocalLocation.second + localLocation.second);
    }
    else if(!parent || (parent && !isUsingParentLocation)) //부모가 없다면 rootComponent이다. rootComponent는 월드와 로컬이 같다.
    {
        worldLocation = localLocation;
    }
    for(auto& child:children)
    {
        child->updateComponentWorldLocation();
    }
}

void HSceneComponent::render()
{
    for(auto& child:children)
    {
        child->render();
    }
}

void HSceneComponent::update(const float deltaTime)
{
    for(auto& child:children)
    {
        child->update(deltaTime);
    }
}

std::pair<float, float> HSceneComponent::getComponentWorldLocation() const
{
    return worldLocation;
}

float HSceneComponent::getComponentWorldRotation() const
{
    return worldRotation;
}

void HSceneComponent::setComponentLocalLocation(const std::pair<float, float>& loc)
{
    localLocation = loc;
    updateComponentWorldLocation();
}

void HSceneComponent::setComponentLocalRotation(const float degree)
{
    localRotation = degree;
    updateComponentWorldRotation();
}

void HSceneComponent::setOwner(HActor *owner)
{
    this->owner = owner;
}

std::pair<float, float> HSceneComponent::getComponentLocalLocation() const
{
    return localLocation;
}

float HSceneComponent::getComponentLocalRotation() const
{
    return localRotation;
}

HSceneComponent* HSceneComponent::getParentComponent() const
{
    return parent;
}

void HSceneComponent::setAffectRotationFromParent(const bool isAffect)
{
    isUsingParentRotation = isAffect;
}
bool HSceneComponent::getAffectRotationFromParent() const
{
    return isUsingParentRotation;
}

void HSceneComponent::setAffectLocationFromParent(const bool isAffect)
{
    isUsingParentLocation = isAffect;
}

bool HSceneComponent::getAffectLocationFromParent() const
{
    return isUsingParentLocation;
}

void HSceneComponent::attachTo(HSceneComponent* component, bool isAffectFromParent)
{
    this->parent = component;
    component->children.push_back(this);

    if(isAffectFromParent)
    {
        auto parentWorldLocation = component->getComponentWorldLocation();
        worldLocation = std::make_pair(parentWorldLocation.first + localLocation.first,
                                       parentWorldLocation.second + localLocation.second);

        worldRotation = component->getComponentWorldRotation() + localRotation;

        auto parentWorldScale = component->getComponentWorldScale();
        worldScale = std::make_pair(parentWorldScale.first * localScale.first,
                                    parentWorldScale.second * localScale.second);
    }
    else
    {
        worldLocation = std::make_pair(localLocation.first, localLocation.second);
        worldRotation = localRotation;
        worldScale = localScale;
    }
    setAffectLocationFromParent(isAffectFromParent);
    setAffectRotationFromParent(isAffectFromParent);
}

void HSceneComponent::updateComponentWorldScale()
{
    if(parent && isUsingParentScale)
    {
        worldScale.first = localScale.first * parent->getComponentWorldScale().first;
        worldScale.second = localScale.first * parent->getComponentWorldScale().second;
    }
    else if(!parent || (parent && !isUsingParentScale)) //부모가 없다면 루트 컴포넌트이다.
    {
        worldScale = localScale;
    }
    for(auto& child:children)
    {
        child->updateComponentWorldScale();
    }
}

std::pair<float, float> HSceneComponent::getComponentWorldScale() const
{
    return worldScale;
}

std::pair<float, float> HSceneComponent::getComponentLocalScale() const
{
    return localScale;
}

void HSceneComponent::setComponentLocalScale(const std::pair<float, float> &scale)
{
    localScale = scale;
    updateComponentWorldScale();
}

void HSceneComponent::setAffectScaleFromParent(const bool isAffect)
{
    isUsingParentScale = isAffect;
}

bool HSceneComponent::getAffectScaleFromParent() const
{
    return isUsingParentScale;
}


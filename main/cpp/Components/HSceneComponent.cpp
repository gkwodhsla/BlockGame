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

std::pair<float, float> HSceneComponent::getComponentWorldLocation()
{
    return worldLocation;
}

float HSceneComponent::getComponentWorldRotation()
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

std::pair<float, float> HSceneComponent::getComponentLocalLocation()
{
    return localLocation;
}

float HSceneComponent::getComponentLocalRotation()
{
    return localRotation;
}

HSceneComponent* HSceneComponent::getParentComponent()
{
    return parent;
}

void HSceneComponent::setAffectRotationFromParent(const bool isAffect)
{
    isUsingParentRotation = isAffect;
}
bool HSceneComponent::getAffectRotationFromParent()
{
    return isUsingParentRotation;
}

void HSceneComponent::setAffectLocationFromParent(const bool isAffect)
{
    isUsingParentLocation = isAffect;
}

bool HSceneComponent::getAffectLocationFromParent()
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
    }
    else
    {
        worldLocation = std::make_pair(localLocation.first, localLocation.second);
        worldRotation = localRotation;
    }
    setAffectLocationFromParent(isAffectFromParent);
    setAffectRotationFromParent(isAffectFromParent);
}


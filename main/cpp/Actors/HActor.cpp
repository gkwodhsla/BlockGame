#include "HActor.h"
#include "../Components/HSceneComponent.h"
#include "../Components/ImageComponent.h"
//#include "../Level/HLevelBase.h"
#include <cmath>
#include <android/log.h>

using namespace GlobalFunction;

HActor::HActor()
{
    rootComponent = new HSceneComponent();
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    testComponent = new ImageComponent("images/brick.png");
    testComponent->attachTo(rootComponent);
    //VAO가 바인딩 됐기 때문에 해당 액터의 컴포넌트에 VBO가 있다면 들러붙는다.

    //destroyAction = [this]()
    //{
        //GetLevel()->destroyActor(this);
    //};
}

HActor::~HActor()
{
    delete rootComponent;
    rootComponent = nullptr;
    for(auto& component : actorComponents)
    {
        if(component)
        {
            delete component;
            component = nullptr;
        }
    }
    if(VAO)
    {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    delete testComponent;
}

void HActor::moveTo(const std::pair<float, float> &loc)
{
    rootComponent->setComponentLocalLocation(loc);
}

void HActor::rotateActor(const float degree)
{
    rootComponent->setComponentLocalRotation(degree);
}

void HActor::setVisibility(bool isVisible)
{
    visibility = isVisible;
}

bool HActor::getVisibility()
{
    return visibility;
}

HSceneComponent* HActor::getRootComponent()
{
    return rootComponent;
}

glm::vec2 HActor::getActorDirectionalVector()
{
    return dirVec;
}

void HActor::setActorDirectionalVector(const glm::vec2& newDir)
{
    dirVec = newDir;
}


std::pair<float, float> HActor::getActorWorldLocation()
{
    return rootComponent->getComponentLocalLocation();
}

void HActor::setActorWorldLocation(float x, float y)
{
    rootComponent->setComponentLocalLocation({float(x), float(y)});
}

float HActor::getActorWorldRotation()
{
    return rootComponent->getComponentLocalRotation();
}

void HActor::setActorTickable(const bool isTickable)
{
    tickable = isTickable;
}

bool HActor::getActorTickable()
{
    return tickable;
}

void HActor::render()
{
    if(visibility)
    {
        glBindVertexArray(VAO); //액터의 VAO를 먼저 바인드해준다.
        rootComponent->render();
    }

}

void HActor::update(const float deltaTime)
{
    if(tickable)
    {
        rootComponent->update(deltaTime);

        if (isSetLifeTime)
        {
            lifeTime -= deltaTime;
            if (lifeTime <= 0.0f)
            {
                destroyAction();
            }
        }
    }
}

void HActor::setLifeTime(const float lifeTime)
{
    this->lifeTime = lifeTime;
    isSetLifeTime = true;
}

void HActor::setIsSetLifeTime(const bool isSetLifeTime)
{
    this->isSetLifeTime = isSetLifeTime;
}

void HActor::registerFuncWhenActorLifeTimeZero(std::function<void()> func)
{
    destroyAction = func;
}

bool HActor::getIsSetLifeTime()
{
    return this->isSetLifeTime;
}

void HActor::setPendingKill(bool newPendingKill)
{
    isPendingKill = newPendingKill;
}

bool HActor::getPendingKill()
{
    return isPendingKill;
}
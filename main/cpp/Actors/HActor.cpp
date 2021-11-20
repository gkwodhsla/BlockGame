#include "HActor.h"
#include "../Components/HSceneComponent.h"
#include "../Components/ImageComponent.h"
#include "../Levels/HLevelBase.h"
#include <cmath>
#include <android/log.h>

using namespace GlobalFunction;

HActor::HActor()
{
    rootComponent = new HSceneComponent();
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //VAO가 바인딩 됐기 때문에 해당 액터의 컴포넌트에 VBO가 있다면 들러붙는다.

    destroyAction = [this]()
    {
        isPendingKill = true;
        visibility = false;
        tickable = false;
    };
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
    PRINT_LOG("delete Actor", "%s");
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

bool HActor::getVisibility() const
{
    return visibility;
}

HSceneComponent* HActor::getRootComponent() const
{
    return rootComponent;
}

glm::vec2 HActor::getActorDirectionalVector() const
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

std::pair<float, float> HActor::getActorWorldScale()
{
    return rootComponent->getComponentLocalScale();
}

void HActor::setActorWorldLocation(float x, float y)
{
    rootComponent->setComponentLocalLocation({x, y});
}

void HActor::setActorWorldScale(const float x, const float y)
{
    rootComponent->setComponentLocalScale({x, y});
}

float HActor::getActorWorldRotation() const
{
    return rootComponent->getComponentLocalRotation();
}

void HActor::setActorTickable(const bool isTickable)
{
    tickable = isTickable;
}

bool HActor::getActorTickable() const
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

bool HActor::getIsSetLifeTime() const
{
    return this->isSetLifeTime;
}

void HActor::setPendingKill(bool newPendingKill)
{
    isPendingKill = newPendingKill;
}

bool HActor::getPendingKill() const
{
    return isPendingKill;
}
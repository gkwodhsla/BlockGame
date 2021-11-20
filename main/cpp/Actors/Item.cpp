#include "Item.h"
#include "../Levels/HLevelBase.h"
#include "../Components/ImageComponent.h"
#include "../Components/BoxCollisionComponent.h"
#include "../Components/MovementComponent.h"

const float Item::gravAcc = -9.8f;

Item::Item(const char* filePath, const whichItem& whatItem)
{
    setActorDirectionalVector(glm::vec2(0.0f, -1.0f));
    itemImg = createComponent<ImageComponent>(filePath, this);
    itemImg->attachTo(rootComponent);
    collisionComp = createComponent<BoxCollisionComponent>(1.0f,1.0f,this);
    collisionComp->attachTo(rootComponent);
    moveComp = createComponent<MovementComponent>(this);
    moveComp->setAcceleration(std::make_pair(0.0f, gravAcc));
    moveComp->setSpeed(initSpeed);
    switch (whatItem)
    {
        case whichItem::BALL:
            collisionComp->registerCollisionResponse([this](HActor*other)
            {
                this->destroyAction();
            });
            break;
        case whichItem::EXPAND:
            collisionComp->registerCollisionResponse([this](HActor*other)
            {
                this->destroyAction();
            });
            break;
        case whichItem::SHRINK:
            collisionComp->registerCollisionResponse([this](HActor*other)
            {
                this->destroyAction();
            });
            break;
    }
}

Item::~Item()
{

}

void Item::render()
{
    HActor::render();
}

void Item::update(const float deltaTime)
{
    HActor::update(deltaTime);
    moveComp->update(deltaTime);
}
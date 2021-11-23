#include "Item.h"
#include "../Levels/HLevelBase.h"
#include "../Components/ImageComponent.h"
#include "../Components/BoxCollisionComponent.h"
#include "../Components/MovementComponent.h"
#include "Bouncer.h"
#include "Ball.h"

const float Item::gravAcc = -9.8f;

Item::Item(const whichItem& whatItem)
{
    setActorDirectionalVector(glm::vec2(0.0f, -1.0f));
    collisionComp = createComponent<BoxCollisionComponent>(1.0f,1.0f,this);
    collisionComp->attachTo(rootComponent);
    moveComp = createComponent<MovementComponent>(this);
    moveComp->setMaxAcceleration(50.0f);
    moveComp->setMaxSpeed(initSpeed);
    switch (whatItem)
    {
        case whichItem::BALL:
            itemImg = createComponent<ImageComponent>("images/ballItem.png", this);
            collisionComp->registerCollisionResponse([this](HActor*other)
            {
                if(GlobalFunction::Cast<Bouncer>(other))
                {
                    auto ball = GlobalFunction::getLevel()->spawnActor<Ball>();
                    ball->setActorWorldScale(16.0f,16.0f);
                    ball->setActorWorldLocation(0.0f,-100.0f);
                    ball->setCollisionComp(10.0f);
                    this->destroyAction();
                }
            });
            break;
        case whichItem::EXPAND:
            itemImg = createComponent<ImageComponent>("images/expandItem.png", this);
            collisionComp->registerCollisionResponse([this](HActor*other)
            {
                auto bouncer = GlobalFunction::Cast<Bouncer>(other);
                if(bouncer)
                {
                    bouncer->beginExpandingBar();
                    this->destroyAction();
                }
            });
            break;
        case whichItem::SHRINK:
            itemImg = createComponent<ImageComponent>("images/shrinkItem.png", this);
            collisionComp->registerCollisionResponse([this](HActor*other)
            {
                auto bouncer = GlobalFunction::Cast<Bouncer>(other);
                if(bouncer)
                {
                    bouncer->beginShrinkingBar();
                    this->destroyAction();
                }
            });
            break;
    }
    itemImg->attachTo(rootComponent);
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
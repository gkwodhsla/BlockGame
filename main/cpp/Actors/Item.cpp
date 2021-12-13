#include "Item.h"
#include "../Levels/HLevelBase.h"
#include "../Components/ImageComponent.h"
#include "../Components/BoxCollisionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/WAVPlayerComponent.h"
#include "../Levels/MainLevel.h"
#include "Bouncer.h"
#include "Ball.h"

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
                    GlobalFunction::Cast<MainLevel>(GlobalFunction::getLevel())->spawnBall();
                    itemWAV->play();
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
                    itemWAV->play();
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
                    itemWAV->play();
                    this->destroyAction();
                }
            });
            break;
    }
    itemImg->attachTo(rootComponent);
    itemWAV = createComponent<WAVPlayerComponent>("audio/powerup.wav", this);
    itemWAV->attachTo(rootComponent);
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
    if(getActorWorldLocation().second < deadLine)
    {
        destroyAction();
    }
}
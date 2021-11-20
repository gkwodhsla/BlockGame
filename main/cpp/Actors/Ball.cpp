#include "Ball.h"
#include "../Components/ImageComponent.h"
#include "../Components/CircleCollisionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Levels/MainLevel.h"
#include "../Actors/Item.h"
#include "../Actors/BreakableBrick.h"

const float Ball::ballSpeed = 400.0f;

Ball::Ball()
{
    ballImg = createComponent<ImageComponent>("images/ball.png", this);
    ballImg->attachTo(rootComponent);

    collisionComp = createComponent<CircleCollisionComponent>(0.0f, this);
    collisionComp->attachTo(rootComponent);

    collisionComp->registerCollisionResponse([this](HActor* other)
    {
        auto level = GlobalFunction::Cast<MainLevel>(GlobalFunction::getLevel());
        auto block = GlobalFunction::Cast<BreakableBrick>(other);
        if(level && block && GlobalFunction::generateRandomBool(0.5f))
        {
            int which = GlobalFunction::generateRandomInt(0, 2);
            auto newItem = level->spawnActor<Item>((whichItem)which);
            auto thisCurLoc = this->getActorWorldLocation();
            newItem->setActorWorldLocation(thisCurLoc.first, thisCurLoc.second);
            newItem->setActorWorldScale(50.0f, 20.0f);
        }
    });

    ballMovement = createComponent<MovementComponent>(this);
    ballMovement->setSpeed(ballSpeed);
    this->setActorDirectionalVector(glm::vec2(0.0f,-1.0f));
}

Ball::~Ball()
{

}

void Ball::render()
{
    HActor::render();
}

void Ball::update(const float deltaTime)
{
    HActor::update(deltaTime);
    ballMovement->update(deltaTime);
}

void Ball::setCollisionComp(float rad)
{
    collisionComp->setRadius(rad);
}

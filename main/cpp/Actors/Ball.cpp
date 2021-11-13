#include "Ball.h"
#include "../Components/ImageComponent.h"
#include "../Components/CircleCollisionComponent.h"
#include "../Components/MovementComponent.h"

Ball::Ball()
{
    ballImg = createComponent<ImageComponent>("images/ball.png", this);
    ballImg->attachTo(rootComponent);

    collisionComp = createComponent<CircleCollisionComponent>(0.0f, this);
    collisionComp->attachTo(rootComponent);

    collisionComp->registerCollisionResponse([this](HActor*)
                                                     {
                                                         ballImg->setTintEnabled(true);
                                                         ballImg->setTintColor(0.0f,1.0f,0.0f);
                                                         PRINT_LOG("Collision!",%s);
                                                     });

    ballMovement = createComponent<MovementComponent>(this);
    ballMovement->setSpeed(300.0f);
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

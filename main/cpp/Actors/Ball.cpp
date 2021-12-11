#include "Ball.h"
#include "../Components/ImageComponent.h"
#include "../Components/CircleCollisionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/ParticleComponent.h"
#include "../Levels/MainLevel.h"
#include "../Actors/Item.h"
#include "../Actors/BreakableBrick.h"

const float Ball::ballSpeed = 350.0f;
const float Ball::deadLine = -500.0f;

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
        if(level && block && GlobalFunction::generateRandomBool(0.2f)) //20%확률로 아이템을 생성한다.
        {
            int which = GlobalFunction::generateRandomInt(0, 2);
            auto newItem = level->spawnActor<Item>((whichItem)which);
            auto thisCurLoc = this->getActorWorldLocation();
            newItem->setActorWorldLocation(thisCurLoc.first, thisCurLoc.second);
            newItem->setActorWorldScale(50.0f, 20.0f);
        }
    });

    ballMovement = createComponent<MovementComponent>(this);
    ballMovement->setMaxSpeed(ballSpeed);
    ballMovement->setDeltaAccel(100.0f);
    this->setActorDirectionalVector(glm::vec2(0.0f,-1.0f));

    /*ballParticle = createComponent<ParticleComponent>("images/ballParticle.png", this, true,
                                                      GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT);
    ballParticle->setRepeat(true);
    ballParticle->setLifeTime(1.5f);
    ballParticle->setParticleNum(15);
    ballParticle->setPosRange(std::make_pair(-5.0f, 5.0f), std::make_pair(-5.0f, 5.0f));
    ballParticle->setAccRange(std::make_pair(0.0f, 0.0f), std::make_pair(0.0f, 0.0f));
    ballParticle->setVelRange(std::make_pair(0.0f, 0.0f), std::make_pair(0.0f, 0.0f));
    ballParticle->attachTo(rootComponent);
    ballParticle->setComponentLocalScale(std::make_pair(15.0f, 15.0f));
    ballParticle->play();*/
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
    if(getActorWorldLocation().second <= deadLine && visibility)
    {
        GlobalFunction::Cast<MainLevel>(GlobalFunction::getLevel())->decBallCnt();
        destroyAction();
    }
    if(isDirVecChangedRecently)
    {
        isDirVecChangedRecently = false;
    }
    /*auto dirVec = getActorDirectionalVector() * -1.0f;

    ballParticle->setVelRange(std::make_pair(dirVec.x * 5.0f, dirVec.x * 30.0f),
                              std::make_pair(dirVec.y * 5.0f, dirVec.y * 30.0f));
    ballParticle->setAccRange(std::make_pair(dirVec.x, dirVec.x), std::make_pair(dirVec.y, dirVec.y));
*/
}

float Ball::getCollisionRad() const
{
    return collisionComp->getRadius();
}

void Ball::setCollisionComp(float rad)
{
    collisionComp->setRadius(rad);
}

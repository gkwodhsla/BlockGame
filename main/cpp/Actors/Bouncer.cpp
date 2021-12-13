#include "Bouncer.h"
#include "Ball.h"
#include "../Components/ImageComponent.h"
#include "../Components/BoxCollisionComponent.h"
#include "../Components/WAVPlayerComponent.h"
#include "../Common/Framework.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

const float Bouncer::maxRotDeg = 60.0f;

Bouncer::Bouncer()
{
    setActorDirectionalVector(glm::vec2(0.0f, 1.0f)); // 공 튕길 때 기준이 되는 벡터
    bouncerImage = createComponent<ImageComponent>("images/platform.png", this);
    bouncerImage->attachTo(rootComponent);

    auto imageScale = bouncerImage->getComponentWorldScale();
    boxCollisionComponent = createComponent<BoxCollisionComponent>(imageScale.first,
                                                                   imageScale.second, this);
    boxCollisionComponent->attachTo(rootComponent);
    boxCollisionComponent->registerCollisionResponse([this](HActor* other)
                                                     {
                                                            auto ball = GlobalFunction::Cast<Ball>(other);
                                                            if(ball)
                                                            {
                                                                ballHitSound->play();
                                                                auto ballLoc = ball->getActorWorldLocation();
                                                                auto bouncerLoc = getActorWorldLocation();
                                                                auto middleDir = getActorDirectionalVector();
                                                                float bouncerXScale = getActorWorldScale().first / 2.0f;
                                                                float distBouncerAndBall = bouncerLoc.first - ballLoc.first;
                                                                float rotDegree = maxRotDeg / (bouncerXScale/fabs(distBouncerAndBall));
                                                                if(distBouncerAndBall >= 0.0f)
                                                                {
                                                                    auto rotateMat =
                                                                            glm::rotate(glm::mat4(1.0f), glm::radians(-rotDegree),
                                                                                        glm::vec3(0.0f,0.0f,1.0f));
                                                                    auto ballNewDir=glm::vec4(middleDir.x,middleDir.y,0.0f,1.0f)*rotateMat;
                                                                    ball->setActorDirectionalVector(glm::vec2(ballNewDir.x, ballNewDir.y));
                                                                }
                                                                else
                                                                {
                                                                    auto rotateMat =
                                                                            glm::rotate(glm::mat4(1.0f), glm::radians(rotDegree),
                                                                                        glm::vec3(0.0f,0.0f,1.0f));
                                                                    auto ballNewDir=glm::vec4(middleDir.x,middleDir.y,0.0f,1.0f)*rotateMat;
                                                                    ball->setActorDirectionalVector(glm::vec2(ballNewDir.x, ballNewDir.y));
                                                                }
                                                            }
                                                     });
    ballHitSound = createComponent<WAVPlayerComponent>("audio/bleepPlatform.wav", this);
    ballHitSound->attachTo(rootComponent);
}

Bouncer::~Bouncer()
{

}

void Bouncer::render()
{
    HPawn::render();
}

void Bouncer::update(const float deltaTime)
{
    HPawn::update(deltaTime);
    auto curSize = getActorWorldScale();
    switch (curState)
    {
        case barState::STATIC:
            break;
        case barState::EXPAND:
            if(curSize.first < targetSize)
            {
                curSize.first += deltaTime * animSpeed;
                setActorWorldScale(curSize.first, curSize.second);
            }
            else
            {
                curSize.first = targetSize;
                curSize.first += deltaTime * animSpeed;
                setActorWorldScale(curSize.first, curSize.second);
                curState = barState::STATIC;
            }
            break;
        case barState::SHRINK:
            if(curSize.first > targetSize)
            {
                curSize.first -= deltaTime * animSpeed;
                setActorWorldScale(curSize.first, curSize.second);
            }
            else
            {
                curSize.first = targetSize;
                curSize.first -= deltaTime * animSpeed;
                setActorWorldScale(curSize.first, curSize.second);
                curState = barState::STATIC;
            }
            break;
    }
}

void Bouncer::handleEvent(const Event &e)
{
    switch (e.type)
    {
        case EVENT_TYPE::FINGER_DOWN:
            befPos.first = e.xPos;
            befPos.second = e.yPos;
            break;
        case EVENT_TYPE::FINGER_SWIPE:
        {
            float curX = e.xPos - befPos.first;
            //float curY = e.yPos - befPos.second;
            curX*=frameworkInst->rendererSize / 2.0f;
            //curY*=400.0f;
            auto curWorldLoc = getActorWorldLocation();
            if(curWorldLoc.first >= minBarPos && curWorldLoc.first<=maxBarPos)
            {
                setActorWorldLocation(curWorldLoc.first + curX, curWorldLoc.second);
            }
            else if(curWorldLoc.first < minBarPos && curX > 0.0f)
            {
                setActorWorldLocation(curWorldLoc.first + curX, curWorldLoc.second);
            }
            else if(curWorldLoc.first > maxBarPos && curX < 0.0f)
            {
                setActorWorldLocation(curWorldLoc.first + curX, curWorldLoc.second);
            }
            befPos.first = e.xPos;
            befPos.second = e.yPos;
            break;
        }
    }
}

void Bouncer::beginExpandingBar()
{
    float curSize = getActorWorldScale().first;
    if(curSize < 300.0f)
    {
        curState = barState::EXPAND;
        targetSize = curSize + barSizeDelta;
    }
}

void Bouncer::beginShrinkingBar()
{
    float curSize = getActorWorldScale().first;
    if(curSize > 100.0f)
    {
        curState = barState::SHRINK;
        targetSize = curSize - barSizeDelta;
    }
}

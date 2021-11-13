#include "Bouncer.h"
#include "Ball.h"
#include "../Components/ImageComponent.h"
#include "../Components/BoxCollisionComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

const float Bouncer::maxRotDeg = 45.0f;

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
            float curY = e.yPos - befPos.second;
            curX*=400.0f;
            curY*=400.0f;
            auto curWorldLoc = getActorWorldLocation();
            setActorWorldLocation(curWorldLoc.first+curX, curWorldLoc.second+curY);
            befPos.first = e.xPos;
            befPos.second = e.yPos;
            break;
        }
    }
}

#include "BrickParent.h"
#include "../Components/BoxCollisionComponent.h"
#include "Ball.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

std::random_device BrickParent::rd;
std::default_random_engine BrickParent::dre(BrickParent::rd());
std::uniform_real_distribution<> BrickParent::urd(0.0f, 5.0f);

BrickParent::BrickParent()
{
    collisionComp = createComponent<BoxCollisionComponent>(1.0f, 1.0f, this);
    collisionComp->attachTo(rootComponent);
}

void BrickParent::setCollisionBoxWidthAndHeight(float w, float h)
{
    collisionComp->setComponentLocalScale({w, h});
}

BrickParent::~BrickParent()
{

}

void BrickParent::changeBallDirVec(HActor* me, HActor* other)
{
    {
        auto ball = GlobalFunction::Cast<Ball>(other);
        if(ball)
        {
            bool isHitFlat = true;
            auto brickPos = me->getActorWorldLocation();
            auto brickScale = me->getActorWorldScale();
            float brickX1 = brickPos.first - brickScale.first/2.0f;
            float brickX2 = brickPos.first + brickScale.first/2.0f;
            float brickY1 = brickPos.second + brickScale.second/2.0f;
            float brickY2 = brickPos.second - brickScale.second/2.0f;
            glm::vec2 normalVec={0.0f,0.0f};
            auto ballPos = other->getActorWorldLocation();
            if(brickX1<ballPos.first && ballPos.first < brickX2 && brickY2>ballPos.second) //벽돌 아래쪽
            {
                normalVec = glm::vec2(0.0f, -1.0f);
            }
            else if(brickX1<ballPos.first && ballPos.first < brickX2 && brickY1<ballPos.second)// 벽돌 위쪽
            {
                normalVec = glm::vec2(0.0f, 1.0f);
            }
            else if(brickY1>ballPos.second && ballPos.second>brickY2 && brickX2<ballPos.first)// 벽돌 오른쪽
            {
                normalVec = glm::vec2(-1.0f, 0.0f);
            }
            else if(brickY1>ballPos.second && ballPos.second>brickY2 && ballPos.first<brickX1)// 벽돌 왼쪽
            {
                normalVec = glm::vec2(1.0f, 0.0f);
            }
            else if(brickX2 < ballPos.first && brickY2 > ballPos.second)
            {
                isHitFlat = false;
                auto rotateMat =
                        glm::rotate(glm::mat4(1.0f), glm::radians(135.0f + (float)BrickParent::urd(BrickParent::dre)),
                                    glm::vec3(0.0f,0.0f,1.0f));
                auto ballNewDir=glm::vec4(0.0f,1.0f,0.0f,1.0f)*rotateMat;
                ball->setActorDirectionalVector(glm::vec2(ballNewDir.x, ballNewDir.y));
            }
            else if((brickX2 < ballPos.first && brickY1 < ballPos.second))
            {
                isHitFlat = false;
                auto rotateMat =
                        glm::rotate(glm::mat4(1.0f), glm::radians(45.0f + (float)BrickParent::urd(BrickParent::dre)),
                                    glm::vec3(0.0f,0.0f,1.0f));
                auto ballNewDir=glm::vec4(0.0f,1.0f,0.0f,1.0f)*rotateMat;
                ball->setActorDirectionalVector(glm::vec2(ballNewDir.x, ballNewDir.y));
            }
            else if(brickX1 > ballPos.first && brickY2 > ballPos.second)
            {
                isHitFlat = false;
                auto rotateMat =
                        glm::rotate(glm::mat4(1.0f), glm::radians(-135.0f + (float)BrickParent::urd(BrickParent::dre)),
                                    glm::vec3(0.0f,0.0f,1.0f));
                auto ballNewDir=glm::vec4(0.0f,1.0f,0.0f,1.0f)*rotateMat;
                ball->setActorDirectionalVector(glm::vec2(ballNewDir.x, ballNewDir.y));
            }
            else if(brickX1 > ballPos.first && brickY1 < ballPos.second)
            {
                isHitFlat = false;
                auto rotateMat =
                        glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f + (float)BrickParent::urd(BrickParent::dre)),
                                    glm::vec3(0.0f,0.0f,1.0f));
                auto ballNewDir=glm::vec4(0.0f,1.0f,0.0f,1.0f)*rotateMat;
                ball->setActorDirectionalVector(glm::vec2(ballNewDir.x, ballNewDir.y));

                //ball->setActorDirectionalVector(glm::normalize(
                //      glm::vec2(ballPos.first - brickPos.first, ballPos.second -brickPos.second)));
            }
            if(isHitFlat)
            {
                auto ballDirVec = ball->getActorDirectionalVector();
                ball->setActorDirectionalVector(glm::reflect(ballDirVec, normalVec));
            }
            auto ballDirVec = ball->getActorDirectionalVector();
            ball->setActorWorldLocation(ballPos.first + ballDirVec.x * 5.0f, ballPos.second + ballDirVec.y * 5.0f);
        }
    }
}

BoxCollisionComponent* BrickParent::getCollisionComp()
{
    return collisionComp;
}
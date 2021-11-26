#include "BrickParent.h"
#include "../Components/BoxCollisionComponent.h"
#include "../Components/ParticleComponent.h"
#include "Ball.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

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
        if(ball && !ball->getIsDirVecChangedRecently())
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
            
            else if(brickX2 < ballPos.first && brickY2 > ballPos.second) //벽돌 오른쪽 아래 모서리
            {
                glm::vec2 bas{ballPos.first, ballPos.second};
                glm::vec2 brs{brickX2, brickY2};
                auto vecBallToBrick = glm::normalize(bas - brs);
                normalVec = vecBallToBrick;
                PRINT_LOG("right down", %s);
            }
            else if((brickX2 < ballPos.first && brickY1 < ballPos.second)) //벽돌 오른쪽 위 모서리
            {
                glm::vec2 bas{ballPos.first, ballPos.second};
                glm::vec2 brs{brickX2, brickY1};
                auto vecBallToBrick = glm::normalize(bas - brs);
                normalVec = vecBallToBrick;
                PRINT_LOG("right up", %s);
            }
            else if(brickX1 > ballPos.first && brickY2 > ballPos.second) //벽돌 왼쪽 아래 모서리
            {
                glm::vec2 bas{ballPos.first, ballPos.second};
                glm::vec2 brs{brickX1, brickY2};
                auto vecBallToBrick = glm::normalize(bas - brs);
                normalVec = vecBallToBrick;
                PRINT_LOG("left down", %s);
            }
            else if(brickX1 > ballPos.first && brickY1 < ballPos.second) //벽돌 왼쪽 위 모서리
            {
                glm::vec2 bas{ballPos.first, ballPos.second};
                glm::vec2 brs{brickX1, brickY1};
                auto vecBallToBrick = glm::normalize(bas - brs);
                normalVec = vecBallToBrick;
                PRINT_LOG("left up", %s);
            }

            if(isHitFlat)
            {
                auto ballDirVec = ball->getActorDirectionalVector();
                auto ref = glm::reflect(ballDirVec, normalVec);
                ball->setActorDirectionalVector(ref);
            }
            ball->setIsDirVecChangedRecently(true);
            //auto ballDirVec = ball->getActorDirectionalVector();
            //ball->setActorWorldLocation(ballPos.first + ballDirVec.x * 5.0f, ballPos.second + ballDirVec.y * 5.0f);



        }
    }
}

BoxCollisionComponent* BrickParent::getCollisionComp()
{
    return collisionComp;
}
#include "UnbreakableBrick.h"
#include "Ball.h"
#include "../Components/ImageComponent.h"
#include "../Components/BoxCollisionComponent.h"

UnbreakableBrick::UnbreakableBrick(const char *imgPath)
{
    brickImage = createComponent<ImageComponent>(imgPath, this);
    brickImage->attachTo(rootComponent);

    auto imgScale = brickImage->getComponentWorldScale();
    collisionComp->registerCollisionResponse([this](HActor* other)
    {
        auto ball = GlobalFunction::Cast<Ball>(other);
        if(ball)
        {
            auto brickPos = getActorWorldLocation();
            auto brickScale = getActorWorldScale();
            float brickX1 = brickPos.first - brickScale.first/2.0f;
            float brickX2 = brickPos.first + brickScale.first/2.0f;
            float brickY1 = brickPos.second + brickScale.second/2.0f;
            float brickY2 = brickPos.second - brickScale.second/2.0f;
            glm::vec2 normalVec={0.0f,0.0f};
            auto ballPos = other->getActorWorldLocation();
            if(brickX1<ballPos.first && ballPos.first < brickX2 && brickY2>ballPos.second)
            {
                normalVec = glm::vec2(0.0f, -1.0f);
            }
            else if(brickX1<ballPos.first && ballPos.first < brickX2 && brickY1<ballPos.second)
            {
                normalVec = glm::vec2(0.0f, 1.0f);
            }
            else if(brickY1>ballPos.second && ballPos.second>brickY2 && brickX2<ballPos.first)
            {
                normalVec = glm::vec2(-1.0f, 0.0f);
            }
            else if(brickY1>ballPos.second && ballPos.second>brickY2 && ballPos.first<brickX1)
            {
                normalVec = glm::vec2(1.0f, 0.0f);
            }
            auto ballDirVec = ball->getActorDirectionalVector();
            ball->setActorDirectionalVector(glm::reflect(ballDirVec, normalVec));
        }
    });
}

UnbreakableBrick::~UnbreakableBrick()
{

}

void UnbreakableBrick::render()
{
    HActor::render();
}

void UnbreakableBrick::update(const float deltaTime)
{
    HActor::update(deltaTime);
}

void UnbreakableBrick::setCollisionComp(float rad)
{

}

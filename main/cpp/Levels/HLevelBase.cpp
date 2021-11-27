#include "HLevelBase.h"
#include "../Actors/HActor.h"
#include "../Controllers/HPlayerController.h"
#include "../Components/CollisionParent.h"
#include <algorithm>

HLevelBase::HLevelBase()
{

}

HLevelBase::~HLevelBase()
{
    for(auto&actor:actors)
    {
        if(actor)
        {
            delete actor;
            actor = nullptr;
        }
    }
    if(curController)
    {
        delete curController;
        curController = nullptr;
    }
}

void HLevelBase::handleEvent(const Event& e)
{
    INPUT_MODE mode = curController->getInputMode();
    switch (mode)
    {
        case INPUT_MODE::BOTH:
            curController->handleEvent(e);
            //추후 UI 추가시 코드 삽입
            break;

        case INPUT_MODE::UI_ONLY:
            //추후 UI 추가시 코드 삽입
            break;

        case INPUT_MODE::GAME_ONLY:
            curController->handleEvent(e);
            break;
    }
}

void HLevelBase::update(const float deltaTime)
{
    curDeleteTime -= deltaTime;
    if(curDeleteTime<=0.0f)
    {
        destroyActors();
        curDeleteTime = maxDeleteTime;
    }

    for(auto&actor : actors)
    {
        if(actor && !actor->getEnableSubstepping())
        {
            actor->update(deltaTime);
        }
        else if(actor && actor->getEnableSubstepping())
        {
            float subStepTime = deltaTime / (float)actor->getSubsteppingNum();
            for(int i=0;i<actor->getSubsteppingNum();++i) //physics simulation 의 정확성을 위한 substepping이 켜져있다면 한 프레임 내에서
                //정해진 substep의 횟수만큼 물리 계산을 한다.
            {
                actor->update(subStepTime);
                for(int j = 0; j < (int)collisionObjects.size(); ++j)
                {
                    if(collisionObjects[j]->getOwner() == actor)
                    {
                        for(int k = 0; k < (int)collisionObjects.size(); ++ k)
                        {
                            if(j != k && collisionObjects[j]->getOwner()->getVisibility())
                            {
                                collisionObjects[i]->checkCollision(*collisionObjects[j]);
                            }
                        }
                        break;
                    }
                }
            }
        }
    }

    for(int i = 0; i < (int)collisionObjects.size() - 1; ++i)
    {
        if(collisionObjects[i]->getOwner()->getVisibility() && !collisionObjects[i]->getOwner()->getEnableSubstepping())
        {
            for(int j = i + 1; j < (int)collisionObjects.size(); ++j)
            {
                if(collisionObjects[j]->getOwner()->getVisibility())
                {
                    collisionObjects[i]->checkCollision(*collisionObjects[j]);
                }
            }
        }
    }
}

void HLevelBase::render()
{
    for(auto&actor : actors)
    {
        if(actor)
        {
            actor->render();
        }
    }
}

void HLevelBase::destroyActors()
{
    auto removedIter = std::remove_if(actors.begin(), actors.end(), [](HActor* actor)
    {
       return actor->getPendingKill();
    });

    actors.erase(removedIter, actors.end());
}

void HLevelBase::changeController(HPlayerController* newController)
{
    if(curController)
    {
        delete curController;
        curController = nullptr;
    }
    curController = newController;
}

void HLevelBase::addCollisionObject(CollisionParent* newObj)
{
    collisionObjects.emplace_back(newObj);
}
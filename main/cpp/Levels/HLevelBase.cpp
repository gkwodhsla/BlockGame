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
    for(int i = 0; i < (int)collisionObjects.size() - 1; ++i)
    {
        if(collisionObjects[i]->getOwner()->getVisibility())
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
    for(auto&actor : actors)
    {
        if(actor)
        {
            actor->update(deltaTime);
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
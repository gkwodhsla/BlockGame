#include "HLevelBase.h"
#include "../Actors/HActor.h"
#include "../Controllers/HPlayerController.h"
#include "../Components/CollisionParent.h"

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

bool HLevelBase::destroyActor(HActor* actor)
{
    for(auto iter = actors.begin(); iter != actors.end(); ++iter)
    {
        if(*iter == actor)
        {
            delete *iter;
            *iter = nullptr;
            actors.erase(iter);
            return true;
        }
    }
    return false;
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
#include "HLevelBase.h"
#include "../Actors/HActor.h"
#include "../Controllers/HPlayerController.h"

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
            break;

        case INPUT_MODE::UI_ONLY:
            break;

        case INPUT_MODE::GAME_ONLY:
            curController->handleEvent(e);
            break;
    }
}

void HLevelBase::update(const float deltaTime)
{
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
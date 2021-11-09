#pragma once
#include "../Common/HObject.h"
#include "../Common/Common.h"
#include <vector>
#include "../Common/EventQ.h"

class HActor;
class HPlayerController;

class HLevelBase : public HObject
{
public:
    HLevelBase();
    HLevelBase(const HLevelBase&) = delete;
    HLevelBase&operator=(const HLevelBase&) = delete;
    virtual ~HLevelBase();
    virtual void handleEvent(const Event& e);
    virtual void update(const float deltaTime);
    virtual void render();
    bool destroyActor(HActor* actor);
    void changeController(HPlayerController* newController);

    template<typename T, typename ...Types>
    T* spawnActor(Types ...args)
    {
        T* newItem = GlobalFunction::createNewObject<T>(args...);
        actors.emplace_back(newItem);
        return newItem;
    }


protected:
    std::vector<HActor*> actors;
    HPlayerController* curController = nullptr;
};
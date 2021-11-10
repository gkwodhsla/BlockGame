#pragma once
#include "../Common/HObject.h"
#include "../Common/Common.h"
#include <vector>
#include "../Common/EventQ.h"

class HActor;
class HPlayerController;
class CollisionParent;

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
    virtual void enterGameWorld() = 0;
    virtual void exitGameWorld() = 0;
    bool destroyActor(HActor* actor);
    void changeController(HPlayerController* newController);
    void addCollisionObject(CollisionParent* newObj);

    template<typename T, typename ...Types>
    T* spawnActor(Types ...args)
    {
        T* newItem = GlobalFunction::createNewObject<T>(args...);
        actors.emplace_back(newItem);
        return newItem;
    }


protected:
    std::vector<HActor*> actors;
    std::vector<CollisionParent*> collisionObjects;
    HPlayerController* curController = nullptr;
};
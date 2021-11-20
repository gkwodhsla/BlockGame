#pragma once
#include "HActor.h"

class ImageComponent;
class BoxCollisionComponent;
class MovementComponent;

enum class whichItem
{
    BALL = 0,
    EXPAND,
    SHRINK
};

class Item: public HActor
{
public:
    Item() = delete;
    Item(const Item&) = delete;
    Item&operator=(const Item&) = delete;
    Item(const whichItem& whatItem);
    virtual ~Item();

public:
    virtual void render() override;
    virtual void update(const float deltaTime) override;

public:
    BoxCollisionComponent* collisionComp = nullptr;

private:
    ImageComponent* itemImg = nullptr;
    MovementComponent* moveComp = nullptr;
    static const float gravAcc;
    static constexpr float initSpeed = 100.0f;
};
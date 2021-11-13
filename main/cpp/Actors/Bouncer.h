#pragma once
#include "HPawn.h"

class ImageComponent;
class BoxCollisionComponent;
class CircleCollisionComponent;

class Bouncer: public HPawn
{
public:
    Bouncer();
    Bouncer(const Bouncer&) = delete;
    virtual ~Bouncer();
    Bouncer&operator=(const Bouncer&) = delete;
    virtual void render() override;
    virtual void update(const float deltaTime) override;
    virtual void handleEvent(const Event& e) override;
private:
    ImageComponent* bouncerImage = nullptr;
    BoxCollisionComponent* boxCollisionComponent = nullptr;

    std::pair<float, float> befPos{0.0f, 0.0f};
    static const float maxRotDeg;
};
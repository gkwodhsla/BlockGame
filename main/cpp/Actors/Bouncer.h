#pragma once
#include "HPawn.h"

class ImageComponent;
class BoxCollisionComponent;
class CircleCollisionComponent;
class WAVPlayerComponent;

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

public:
    void beginExpandingBar();
    void beginShrinkingBar();

private:
    ImageComponent* bouncerImage = nullptr;
    BoxCollisionComponent* boxCollisionComponent = nullptr;
    WAVPlayerComponent* ballHitSound = nullptr;

    std::pair<float, float> befPos{0.0f, 0.0f};
    static const float maxRotDeg;
    static constexpr float animSpeed = 60.0f;
    static constexpr float barSizeDelta = 60.0f;
    static constexpr float minBarPos = -400.0f;
    static constexpr float maxBarPos = 400.0f;
    float targetSize = 0.0f;
    enum class barState
    {
        STATIC,
        EXPAND,
        SHRINK
    };
    barState curState = barState::STATIC;
};
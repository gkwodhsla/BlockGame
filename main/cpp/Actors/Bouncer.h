#pragma once
#include "HPawn.h"

class ImageComponent;

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
    ImageComponent* bouncerImage2 = nullptr;
    std::pair<float, float> befPos{0.0f, 0.0f};
    //나중에 바운딩 박스 추가
};
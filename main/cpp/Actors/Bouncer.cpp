#include "Bouncer.h"
#include "../Components/ImageComponent.h"

Bouncer::Bouncer()
{
    bouncerImage = new ImageComponent("images/brick.png");
    bouncerImage->attachTo(rootComponent);
    bouncerImage->setOwner(this);
}

Bouncer::~Bouncer()
{
    if(bouncerImage)
        delete bouncerImage;
}

void Bouncer::render()
{
    HPawn::render();
}

void Bouncer::update(const float deltaTime)
{
    HPawn::update(deltaTime);
}

void Bouncer::handleEvent(const Event &e)
{
    switch (e.type)
    {
        case EVENT_TYPE::FINGER_DOWN:
            befPos.first = e.xPos;
            befPos.second = e.yPos;
            break;
        case EVENT_TYPE::FINGER_SWIPE:
        {
            float curX = e.xPos - befPos.first;
            float curY = e.yPos - befPos.second;
            curX*=400.0f;
            curY*=400.0f;
            auto curWorldLoc = getActorWorldLocation();
            setActorWorldLocation(curWorldLoc.first+curX, curWorldLoc.second+curY);
            befPos.first = e.xPos;
            befPos.second = e.yPos;
            break;
        }
    }
}

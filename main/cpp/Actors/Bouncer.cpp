#include "Bouncer.h"
#include "../Components/ImageComponent.h"
#include "../Components/BoxCollisionComponent.h"

Bouncer::Bouncer()
{
    bouncerImage = createComponent<ImageComponent>("images/platform.png", this);
    bouncerImage->attachTo(rootComponent);

    auto imageScale = bouncerImage->getComponentWorldScale();
    boxCollisionComponent = createComponent<BoxCollisionComponent>(imageScale.first,
                                                                   imageScale.second, this);
    boxCollisionComponent->attachTo(rootComponent);
    boxCollisionComponent->registerCollisionResponse([this](HActor*)
                                                     {
                                                            bouncerImage->setTintEnabled(true);
                                                            bouncerImage->setTintColor(1.0f,0.0f,0.0f);
                                                            PRINT_LOG("Collision!",%s);
                                                     });
}

Bouncer::~Bouncer()
{

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

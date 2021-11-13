#include "MainLevel.h"
#include "../Controllers/HPlayerController.h"
#include "../Actors/Camera.h"
#include "../Actors/Bouncer.h"
#include "../Actors/Ball.h"
#include "../Components/CircleCollisionComponent.h"

MainLevel::MainLevel()
{

}

MainLevel::~MainLevel()
{

}

void MainLevel::enterGameWorld()
{
    Bouncer* bouncer = GlobalFunction::Cast<Bouncer>(spawnActor<Bouncer>());
    bouncer->setActorWorldScale(200.0f,30.0f);
    Ball* ball = GlobalFunction::Cast<Ball>(spawnActor<Ball>());
    ball->setActorWorldScale(30.0f,30.0f);
    ball->setActorWorldLocation(-300.0f,300.0f);
    ball->setCollisionComp(15.0f);

    this->curController = GlobalFunction::createNewObject<HPlayerController>(bouncer);
    Camera* camera = GlobalFunction::Cast<Camera>(spawnActor<Camera>());
    camera->activateCamera();
}

void MainLevel::exitGameWorld()
{

}
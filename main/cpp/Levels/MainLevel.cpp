#include "MainLevel.h"
#include "../Controllers/HPlayerController.h"
#include "../Actors/Camera.h"
#include "../Actors/Bouncer.h"
#include "../Actors/Ball.h"
#include "../Actors/UnbreakableBrick.h"
#include "../Components/CircleCollisionComponent.h"

MainLevel::MainLevel()
{

}

MainLevel::~MainLevel()
{

}

void MainLevel::enterGameWorld()
{
    HActor* leftWall = spawnActor<UnbreakableBrick>("images/brick.png");
    leftWall->setActorWorldScale(100.0f, 800.0f);
    leftWall->setActorWorldLocation(450.0f, 0.0f);

    HActor* rightWall = spawnActor<UnbreakableBrick>("images/brick.png");
    rightWall->setActorWorldScale(100.0f, 800.0f);
    rightWall->setActorWorldLocation(-450.0f, 0.0f);

    HActor* upWall = spawnActor<UnbreakableBrick>("images/brick.png");
    upWall->setActorWorldScale(800.0f, 100.0f);
    upWall->setActorWorldLocation(0.0f, 450.0f);


    Bouncer* bouncer = GlobalFunction::Cast<Bouncer>(spawnActor<Bouncer>());
    bouncer->setActorWorldScale(200.0f,30.0f);
    bouncer->setActorWorldLocation(0.0f, -100.0f);
    Ball* ball = GlobalFunction::Cast<Ball>(spawnActor<Ball>());
    ball->setActorWorldScale(30.0f,30.0f);
    ball->setActorWorldLocation(0.0f,300.0f);
    ball->setCollisionComp(15.0f);

    this->curController = GlobalFunction::createNewObject<HPlayerController>(bouncer);
    Camera* camera = GlobalFunction::Cast<Camera>(spawnActor<Camera>());
    camera->activateCamera();
}

void MainLevel::exitGameWorld()
{

}
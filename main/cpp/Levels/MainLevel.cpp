#include "MainLevel.h"
#include "../Common/Framework.h"
#include "../Controllers/HPlayerController.h"
#include "../Actors/Camera.h"
#include "../Actors/Bouncer.h"
#include "../Actors/Ball.h"
#include "../Actors/UnbreakableBrick.h"
#include "../Actors/BreakableBrick.h"
#include "../Actors/ScoreBoard.h"
#include "../Actors/StageManager.h"
#include "../Actors/Item.h"
#include "../Components/CircleCollisionComponent.h"


MainLevel::MainLevel()
{

}

MainLevel::~MainLevel()
{

}

void MainLevel::enterGameWorld()
{
    createBaseObject();

    board = spawnActor<ScoreBoard>();
    board->setActorWorldLocation(-100.0f, 0.0f);
    board->setActorWorldScale(1.0f,1.0f);
    board->setVisibility(false);

    stageManager = spawnActor<StageManager>();

    clearGameWorld();
}

void MainLevel::exitGameWorld()
{

}

void MainLevel::update(const float deltaTime)
{
    HLevelBase::update(deltaTime);
    if(isMsgTime)
    {
        if(stageStartCoolTime <= 0.0f)
        {
            isMsgTime = false;
            stageManager->setGameMap();
            Ball* ball = GlobalFunction::Cast<Ball>(spawnActor<Ball>());
            addBallCnt();
            ball->setActorWorldScale(16.0f,16.0f);
            ball->setActorWorldLocation(0.0f,-200.0f);
            ball->setCollisionComp(10.0f);
            board->setVisibility(false);
        }
        stageStartCoolTime -= deltaTime;
    }
}

void MainLevel::createBaseObject()
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
    bouncer->setActorWorldLocation(0.0f, -300.0f);


    this->curController = GlobalFunction::createNewObject<HPlayerController>(bouncer);
    Camera* camera = GlobalFunction::Cast<Camera>(spawnActor<Camera>(frameworkInst->rendererSize));
    camera->activateCamera();
}

void MainLevel::clearGameWorld()
{
    isMsgTime = true;
    for(auto&actor : actors)
    {
        if(GlobalFunction::Cast<Ball>(actor) ||
           GlobalFunction::Cast<Item>(actor))
        {
            actor->destroyAction();
        }
        auto block = GlobalFunction::Cast<BreakableBrick>(actor);
        if(block && block->getVisibility())
        {
            stageManager->returnToPool(block);
        }
    }//이전 스테이지의 아이템, 공들을 모두 제거한다.
    stageStartCoolTime = maxStageStartCoolTime;
    std::string temp = "Stage " + std::to_string(stageManager->getCurStage());
    board->changeContent(temp);
    board->setVisibility(true);
}

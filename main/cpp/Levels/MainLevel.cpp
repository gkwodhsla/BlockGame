#include "MainLevel.h"
#include "../Common/Framework.h"
#include "../Controllers/HPlayerController.h"
#include "../Actors/Camera.h"
#include "../Actors/Bouncer.h"
#include "../Actors/Ball.h"
#include "../Actors/UnbreakableBrick.h"
#include "../Actors/BreakableBrick.h"
#include "../Components/CircleCollisionComponent.h"
#include <random>

std::random_device rd;
std::default_random_engine dre(rd());
std::uniform_int_distribution<int> uid(0, 6);

const float MainLevel::blockBeginYPos = 350.0f;
const float MainLevel::blockXSize = frameworkInst->rendererSize / boardSize;
const float MainLevel::blockYSize = boardYSize / boardSize;
int MainLevel::gameBoard[boardSize][boardSize];

MainLevel::MainLevel()
{

}

MainLevel::~MainLevel()
{

}

void MainLevel::enterGameWorld()
{
    createBaseObject();

    for(int i = 0; i < boardSize; ++i)
    {
        for(int j = 0; j < boardSize; ++j)
        {
            gameBoard[i][j] = uid(dre);
        }
    }

    float rendererHalfSize = frameworkInst->rendererSize / 2.0f;
    for(int i = 0; i < boardSize; ++i)
    {
        for(int j = 0; j < boardSize; ++j)
        {
            if(gameBoard[i][j] == 1000)
            {
                UnbreakableBrick* brick = spawnActor<UnbreakableBrick>("images/unbreakable.png");
                brick->setActorWorldScale(blockXSize, blockYSize);
                brick->setActorWorldLocation(-rendererHalfSize + j*blockXSize + blockXSize/2.0f,
                                             blockBeginYPos - i*blockYSize - blockYSize/2.0f);
            }
            else if(gameBoard[i][j]==0)
            {

            }
            else if(gameBoard[i][j] == 2)
            {
                BreakableBrick* brick = spawnActor<BreakableBrick>("images/blueBlock.png");
                brick->setActorWorldScale(blockXSize, blockYSize);
                brick->setActorWorldLocation(-rendererHalfSize + j*blockXSize + blockXSize/2.0f,
                                             blockBeginYPos - i*blockYSize - blockYSize/2.0f);
            }
        }
    }
}

void MainLevel::exitGameWorld()
{

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
    Ball* ball = GlobalFunction::Cast<Ball>(spawnActor<Ball>());
    ball->setActorWorldScale(16.0f,16.0f);
    ball->setActorWorldLocation(0.0f,-200.0f);
    ball->setCollisionComp(10.0f);

    this->curController = GlobalFunction::createNewObject<HPlayerController>(bouncer);
    Camera* camera = GlobalFunction::Cast<Camera>(spawnActor<Camera>(frameworkInst->rendererSize));
    camera->activateCamera();

}
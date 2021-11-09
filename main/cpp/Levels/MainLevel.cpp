#include "MainLevel.h"
#include "../Controllers/HPlayerController.h"
#include "../Actors/Camera.h"

MainLevel::MainLevel()
{
    curController = new HPlayerController(nullptr);
    spawnActor<Camera>();
}

MainLevel::~MainLevel()
{

}

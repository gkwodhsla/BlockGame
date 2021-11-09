#include "MainLevel.h"
#include "../Controllers/HPlayerController.h"

MainLevel::MainLevel()
{
    curController = new HPlayerController(nullptr);
}

MainLevel::~MainLevel()
{

}

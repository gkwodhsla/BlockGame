#include "HPlayerController.h"
#include "../Actors/HPawn.h"
#include "../Common/Common.h"
#include "../Common/EventQ.h"

HPlayerController::HPlayerController(HPawn* controlledPawn)
{
    this->controlledPawn = controlledPawn;
}

HPlayerController::~HPlayerController()
{

}

void HPlayerController::possess(HPawn* pawn)
{
    controlledPawn = pawn;
}

void HPlayerController::unpossess()
{
    controlledPawn = nullptr;
}

void HPlayerController::changeInputMode(const INPUT_MODE inputMode)
{
    curInputMode = inputMode;
}

INPUT_MODE HPlayerController::getInputMode() const
{
    return curInputMode;
}

void HPlayerController::handleEvent(const Event& e)
{
    if(controlledPawn)
    {
        controlledPawn->handleEvent(e);
    }
}

HPawn* HPlayerController::getControlledPawn() const
{
    return controlledPawn;
}

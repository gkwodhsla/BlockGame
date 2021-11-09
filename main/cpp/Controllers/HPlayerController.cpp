#include "HPlayerController.h"
#include "../Actors/HPawn.h"
#include "../Common/Common.h"
#include "../Common/EventQ.h"

HPlayerController::HPlayerController(HPawn* controlledPawn)
{

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

INPUT_MODE HPlayerController::getInputMode()
{
    return curInputMode;
}

void HPlayerController::handleEvent(const Event& e)
{
    switch(e.type)
    {
        case EVENT_TYPE::FINGER_DOWN:
            PRINT_LOG("finger down");
            break;
        case EVENT_TYPE::FINGER_UP:
            PRINT_LOG("finger up");
            break;
        case EVENT_TYPE::FINGER_SWIPE:
            PRINT_LOG("finger swipe");
            break;
    }
    if(controlledPawn)
    {
        controlledPawn->handleEvent(e);
    }
}

HPawn* HPlayerController::getControlledPawn()
{
    return controlledPawn;
}

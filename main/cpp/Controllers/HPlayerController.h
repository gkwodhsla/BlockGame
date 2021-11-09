#pragma once

#include "../Common/HObject.h"
#include "../Common/EventQ.h"

class HPawn;

enum class INPUT_MODE
{
    UI_ONLY,
    GAME_ONLY,
    BOTH
};

class HPlayerController: public HObject
{
public:
    HPlayerController(HPawn* controlledPawn);
    HPlayerController() = delete;
    HPlayerController(const HPlayerController&) = delete;
    HPlayerController& operator=(const HPlayerController&) = delete;
    virtual ~HPlayerController();
    void possess(HPawn* pawn);
    void unpossess();
    void changeInputMode(const INPUT_MODE inputMode);
    INPUT_MODE getInputMode();
    void handleEvent(const Event& e);
    //컨트롤러는 자기가 조종중인 Pawn에게만 이벤트를 넘긴다.
    HPawn* getControlledPawn();

protected:
    HPawn* controlledPawn = nullptr;
    INPUT_MODE curInputMode = INPUT_MODE::GAME_ONLY;
};



#include "HLevelBase.h"


class MainLevel: public HLevelBase
{
public:
    MainLevel();
    MainLevel(const MainLevel&) = delete;
    MainLevel&operator=(const MainLevel&) = delete;
    virtual ~MainLevel();

public:
    void exitGameWorld() override;
    void enterGameWorld() override;
};

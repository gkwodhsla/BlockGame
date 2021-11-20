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


private:
    void createBaseObject();

private:
    static constexpr float boardYSize = 400.0f;
    static const float blockBeginYPos;
    static const float blockXSize;
    static const float blockYSize;
};

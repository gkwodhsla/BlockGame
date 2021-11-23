#include "HLevelBase.h"

class StageManager;
class ScoreBoard;
class MainLevel: public HLevelBase
{
public:
    MainLevel();
    MainLevel(const MainLevel&) = delete;
    MainLevel&operator=(const MainLevel&) = delete;
    virtual ~MainLevel();

public:
    void update(const float deltaTime) override;

public:
    void exitGameWorld() override;
    void enterGameWorld() override;

public:
    void clearGameWorld();

public:
    StageManager* stageManager = nullptr;
    ScoreBoard* board = nullptr;

private:
    void createBaseObject();

private:
    bool isMsgTime = false;
    const float maxStageStartCoolTime = 2.0f;
    float stageStartCoolTime = 2.0f;

private:
    static constexpr float boardYSize = 400.0f;
    static const float blockBeginYPos;
    static const float blockXSize;
    static const float blockYSize;
};

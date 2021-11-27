#pragma once
#include "HActor.h"
#include "../Common/ActorObjectPool.h"
#include <vector>

class BreakableBrick;

class StageManager: public HActor
{
public:
    StageManager();
    StageManager(const StageManager&) = delete;
    StageManager&operator=(const StageManager&) = delete;
    virtual ~StageManager();

public:
    virtual void render() override;
    virtual void update(const float deltaTime) override;
    void setGameMap();
    void returnToPool(BreakableBrick* brick);
    void decRestBrick();
    void setRestBrickToZero(){restBricks=0;}
    int getCurStage(){return curStage+1;}

private:
    static constexpr int maxStage = 10;
    static constexpr int mapSize = 15;
    static constexpr float boardYSize = 400.0f;
    static const float blockBeginYPos;
    static const float blockXSize;
    static const float blockYSize;
    size_t restBricks = 0;
    size_t curStage = 0;
    ActorObjectPool<BreakableBrick> brickPool;
    std::vector<std::vector<char>> mapData;
};

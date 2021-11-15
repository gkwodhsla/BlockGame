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

private:
    static constexpr int maxStage = 1;
    static constexpr int mapSize = 15;
    static constexpr float boardYSize = 400.0f;
    static const float blockBeginYPos;
    static const float blockXSize;
    static const float blockYSize;
    ActorObjectPool<BreakableBrick> brickPool;
    std::vector<std::vector<char>> mapData;
};

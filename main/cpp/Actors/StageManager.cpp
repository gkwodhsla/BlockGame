#include "StageManager.h"
#include "BreakableBrick.h"
#include "../Common/Common.h"
#include <string>
#include <iterator>
#include <sstream>

const float StageManager::blockBeginYPos = 350.0f;
const float StageManager::blockXSize = frameworkInst->rendererSize / mapSize;
const float StageManager::blockYSize = boardYSize / mapSize;

StageManager::StageManager(): brickPool(mapSize*mapSize)
{
    mapData.resize(maxStage);
    for(int i=0;i<maxStage;++i)
    {
        mapData[i].reserve(mapSize * mapSize);
        size_t fileSize;
        std::string fileName = "misc/stage" + std::to_string(i + 1 + 2) + ".txt";
        char *buffer = GlobalFunction::readFile(fileName.c_str(), fileSize);
        std::istringstream ss{buffer};
        std::string temp{std::istream_iterator<char>(ss), {}};
        mapData[i].assign(temp.begin(), temp.end());
    }
}

StageManager::~StageManager()
{

}

void StageManager::render()
{
    HActor::render();
}

void StageManager::update(const float deltaTime)
{
    HActor::update(deltaTime);
}

void StageManager::setGameMap()
{
    float rendererHalfSize = frameworkInst->rendererSize / 2.0f;
    for(int i = 0; i < mapSize; ++i)
    {
        for(int j = 0; j < mapSize; ++j)
        {
            if(mapData[0][i*mapSize + j] == '0')
            {

            }
            else if(mapData[0][i*mapSize + j] == '1')
            {
                auto* brick = brickPool.acquireObject();
                brick->setBlockToUse(BlockColor::BLUE);
                brick->setActorWorldScale(blockXSize, blockYSize);
                brick->setActorWorldLocation(-rendererHalfSize + j*blockXSize + blockXSize/2.0f,
                                             blockBeginYPos - i*blockYSize - blockYSize/2.0f);
            }
            else if(mapData[0][i*mapSize + j] == '2')
            {
                auto* brick = brickPool.acquireObject();
                brick->setBlockToUse(BlockColor::RED);
                brick->setActorWorldScale(blockXSize, blockYSize);
                brick->setActorWorldLocation(-rendererHalfSize + j*blockXSize + blockXSize/2.0f,
                                             blockBeginYPos - i*blockYSize - blockYSize/2.0f);
            }
            else if(mapData[0][i*mapSize + j] == '3')
            {
                auto* brick = brickPool.acquireObject();
                brick->setBlockToUse(BlockColor::GREEN);
                brick->setActorWorldScale(blockXSize, blockYSize);
                brick->setActorWorldLocation(-rendererHalfSize + j*blockXSize + blockXSize/2.0f,
                                             blockBeginYPos - i*blockYSize - blockYSize/2.0f);
            }
            else if(mapData[0][i*mapSize + j] == '4')
            {
                auto* brick = brickPool.acquireObject();
                brick->setBlockToUse(BlockColor::ORANGE);
                brick->setActorWorldScale(blockXSize, blockYSize);
                brick->setActorWorldLocation(-rendererHalfSize + j*blockXSize + blockXSize/2.0f,
                                             blockBeginYPos - i*blockYSize - blockYSize/2.0f);

            }
            else if(mapData[0][i*mapSize + j] == '5')
            {
                auto* brick = brickPool.acquireObject();
                brick->setBlockToUse(BlockColor::PURPLE);
                brick->setActorWorldScale(blockXSize, blockYSize);
                brick->setActorWorldLocation(-rendererHalfSize + j*blockXSize + blockXSize/2.0f,
                                             blockBeginYPos - i*blockYSize - blockYSize/2.0f);
            }
        }
    }
}

void StageManager::returnToPool(BreakableBrick* brick)
{
    brickPool.returnToPool(brick);
}
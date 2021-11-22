#include "Common.h"
#include "Framework.h"
#include "../Levels/HLevelBase.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

std::random_device GlobalFunction::rd;
std::default_random_engine GlobalFunction::dre(GlobalFunction::rd());

HLevelBase * GlobalFunction::getLevel()
{
    return Framework::curLevel;
}

char* GlobalFunction::readFile(const char* filePath, size_t& fileSize)
{
    AAsset* rawImage = AAssetManager_open(Framework::assetMng, filePath, AASSET_MODE_UNKNOWN);
    char* buffer = nullptr;
    fileSize = AAsset_getLength(rawImage);
    buffer = new char[fileSize + 1];
    memset(buffer,0,fileSize + 1);
    AAsset_read(rawImage, buffer, fileSize);
    buffer[fileSize] = '\0';
    AAsset_close(rawImage);

    return buffer;
}

int GlobalFunction::generateRandomInt(const int r1, const int r2)
{
    std::uniform_int_distribution<> uid(r1, r2);
    return uid(dre);
}

float GlobalFunction::generateRandomFloat(const float r1, const float r2)
{
    std::uniform_real_distribution<> urd(r1, r2);
    return (float)urd(dre);
}

bool GlobalFunction::generateRandomBool(float percentage)
{
    std::bernoulli_distribution bd(percentage);
    return bd(dre);
}

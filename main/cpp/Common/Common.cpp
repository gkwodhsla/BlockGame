#include "Common.h"
#include "Framework.h"
#include "../Levels/HLevelBase.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

HLevelBase * GlobalFunction::getLevel()
{
    return Framework::curLevel;
}

char* GlobalFunction::readFile(const char* filePath, size_t& fileSize)
{
    AAsset* rawImage = AAssetManager_open(Framework::assetMng, filePath, AASSET_MODE_UNKNOWN);
    char* buffer = nullptr;
    fileSize = AAsset_getLength(rawImage);
    buffer = new char[fileSize];
    memset(buffer,0,fileSize);
    AAsset_read(rawImage, buffer, fileSize);
    AAsset_close(rawImage);

    return buffer;
}

/*float GlobalFunction::generateRandomFloat(const float r1, const float r2)
{
    std::uniform_real_distribution<> urd(r1, r2);
    return urd(dre);
}

bool GlobalFunction::generateRandomBool(float percentage)
{
    std::bernoulli_distribution bd(percentage);
    return bd(dre);
}
 */
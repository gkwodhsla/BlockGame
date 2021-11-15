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
#include "Common.h"
#include "Framework.h"
#include "../Levels/HLevelBase.h"

#if defined(__ANDROID__) || defined(ANDROID)
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#endif

std::random_device GlobalFunction::rd;
std::default_random_engine GlobalFunction::dre(GlobalFunction::rd());

HLevelBase * GlobalFunction::getLevel()
{
    return Framework::curLevel;
}

char* GlobalFunction::readFile(const char* filePath, size_t& fileSize)
{
    #if defined(__ANDROID__) || (ANDROID)
    AAsset* rawImage = AAssetManager_open(Framework::assetMng, filePath, AASSET_MODE_UNKNOWN);
    char* buffer = nullptr;
    fileSize = AAsset_getLength(rawImage);
    buffer = new char[fileSize + 1];
    memset(buffer,0,fileSize + 1);
    AAsset_read(rawImage, buffer, fileSize);
    buffer[fileSize] = '\0';
    AAsset_close(rawImage);

    return buffer;

    #elif defined(IOS)
    std::stringstream ss(filePath);
    std::string fileName;
    std::string extension;
    std::getline(ss, fileName, '.');
    std::getline(ss, extension, '.');
    if(extension == "png")
    {
        extension = "bin";
    }
    NSString *filepath = [[NSBundle] mainBundle
                          pathForResource:[NSString
                          stringWithUTF8String:fileName.c_str()]
                          ofType:[NSString
                          stringWithUTF8String:extension.c_str()]];
    const char* cfileName = [filePath UTF8String];
    std::ifstream ifs(cfileName, std::ios::binary);
    if(ifs.is_open())
    {
        auto fs = std::filesystem::file_size(cfileName);
        fileSize = static_cast<size_t>(fs);
        std::string buffer{std::istreambuf_iterator<char>(ifs), {}};
        char* retBuffer = new char[fs + 1];
        memset(retBuffer, 0, fs + 1);
        memcpy(retBuffer, buffer.c_str(), fs + 1);
        retBuffer[fs] = '\0';
        ifs.close();
        return retBuffer;
    }
    return nullptr;
    #endif
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

#pragma once

#include <android/log.h>
#include <cstdlib>
#include <random>

#if defined(__ANDROID__) || defined(ANDROID)
#include "../oboe-main/include/oboe/Oboe.h"
#endif

#define PRINT_LOG(str, type) \
__android_log_print(ANDROID_LOG_INFO, "gles log" ,#type, str);

class HLevelBase;



namespace GlobalFunction
{
    extern std::random_device rd;
    extern std::default_random_engine dre;

    template<typename T>
    void* GetClassTypeUniqueID()
    {
        static int a = 0;
        return &a;
    }
    //타입을 입력받아 해당 타입의 고유 ID를 반환한다.

    template<typename To, typename From>
    To* Cast(From* src) //안전한 다운캐스팅을 지원하는 함수이다.
    {
        if(GetClassTypeUniqueID<To>() == src->getID())
        {
            return (To*)src;
        }
        else
        {
            if(src->getID() == nullptr)
            {
                __android_log_print(ANDROID_LOG_INFO, "Cast_Error",
                                    "Warning: Input Class has no unique ID Please Set Unique ID"
                                    " using setID(GlobalFunction::<ClassType>GetClassTypeUniqueID())");
                exit(1);
            }
            return nullptr;
        }
    }
    template<typename To, typename From>
    To* Cast(const From* src) //안전한 다운캐스팅을 지원하는 함수이다.
    {
        if(GetClassTypeUniqueID<To>() == src->getID())
        {
            return (To*)src;
        }
        else
        {
            if(src->getID() == nullptr)
            {
                __android_log_print(ANDROID_LOG_INFO, "Cast_Error",
                                    "Warning: Input Class has no unique ID Please Set Unique ID"
                                    " using setID(GlobalFunction::<ClassType>GetClassTypeUniqueID())");
                exit(1);
            }
            return nullptr;
        }
    }

    template<typename T, typename ...Types>
    static T* createNewObject(Types ...args)
    {
        T* newItem = new T(args...);
        newItem->setID(GlobalFunction::GetClassTypeUniqueID<T>());
        return newItem;
    }

    HLevelBase* getLevel();
    char* readFile(const char* filePath, size_t& fileSize);
    int generateRandomInt(const int r1, const int r2);
    float generateRandomFloat(const float r1, const float r2);
    bool generateRandomBool(float percentage); // 0.0f ~ 1.0f (0% ~ 100.0%)
}
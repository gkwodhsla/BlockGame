cmake_minimum_required(VERSION 3.4.1)

#Cmake에서 변수를 참조할 때 변수 앞에 $를 붙이거나 ${...}로 감싼다.
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall") #경고메시지를 출력한다. (wall)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fno-exceptions -Wall") #14버전, 예외처리 사용X
set(LLVM_ENABLE_RTTI) #rtti 활성화
#if (${ANDROID_PLATFORM_LEVEL} LESS 12)
#    message(FATAL_ERROR "OpenGL 2 is not supported before API level 11 \
#                      (currently using ${ANDROID_PLATFORM_LEVEL}).")
#    return()
#elseif (${ANDROID_PLATFORM_LEVEL} LESS 18)
#    add_definitions("-DDYNAMIC_ES3")
#    set(GL3STUB_SRC gl3stub.c)
#    set(OPENGL_LIB GLESv2)
#else ()
#    set(OPENGL_LIB GLESv3)
#endif (${ANDROID_PLATFORM_LEVEL} LESS 12)
set(OPENGL_LIB GLESv3) #버전3만 지원
add_subdirectory(glm-master) #재귀적으로 CMakeLists 사용
add_subdirectory(freetype)
add_subdirectory(oboe-main)
add_subdirectory(parselib)
add_subdirectory(iolib)

add_library(gles3jni SHARED
        Actors/HActor.cpp
        Actors/HPawn.cpp
        Actors/Camera.cpp
        Actors/Bouncer.cpp
        Actors/Ball.cpp
        Actors/BrickParent.cpp
        Actors/UnbreakableBrick.cpp
        Actors/BreakableBrick.cpp
        Actors/ScoreBoard.cpp
        Actors/StageManager.cpp
        Actors/Item.cpp
        Common/Common.cpp
        Common/HObject.cpp
        Common/program.cpp
        Common/renderer.cpp
        Common/framework.cpp
        Common/lodepng/lodepng.cpp
        Common/EventQ.cpp
        Components/HPrimitiveComponent.cpp
        Components/HSceneComponent.cpp
        Components/ImageComponent.cpp
        Components/Camera2DComponent.cpp
        Components/CollisionParent.cpp
        Components/BoxCollisionComponent.cpp
        Components/CircleCollisionComponent.cpp
        Components/MovementComponent.cpp
        Components/TTFComponent.cpp
        Components/ParticleComponent.cpp
        Components/WAVPlayerComponent.cpp
        Controllers/HPlayerController.cpp
        Levels/HLevelBase.cpp
        Levels/MainLevel.cpp
        )

# Include libraries needed for gles3jni lib
target_link_libraries(gles3jni
        ${OPENGL_LIB}
        glm
        freetype
        oboe
        parselib
        iolib
        android
        EGL
        log
        m)

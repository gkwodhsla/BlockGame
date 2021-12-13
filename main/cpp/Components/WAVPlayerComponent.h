#pragma once
#include "HSceneComponent.h"
#include "../parselib/stream/MemInputStream.h"
#include "../parselib/wav/WavStreamReader.h"
#include "../iolib/player/OneShotSampleSource.h"
#include "../iolib/player/SimpleMultiPlayer.h"

class HActor;

class WAVPlayerComponent: public HSceneComponent
{
public:
    WAVPlayerComponent() = delete;
    WAVPlayerComponent(const WAVPlayerComponent&) = delete;
    WAVPlayerComponent& operator=(const WAVPlayerComponent&) = delete;
    WAVPlayerComponent(const char* filePath, HActor* owner);
    virtual ~WAVPlayerComponent();

public:
    void update(const float deltaTime) override;

public:
    void setLooping(bool isLoop);
    void play();
    void stop();

private:
    void loadWav(const char* filePath);

private:
    bool isLooping = false;
    int index;
    bool isPlaying = false;
    static int globalIndex;
    static bool isSetsDTPlayer;
    static iolib::SimpleMultiPlayer sDTPlayer;
};
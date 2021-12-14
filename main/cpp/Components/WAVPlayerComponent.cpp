#include "WAVPlayerComponent.h"
#include "../Actors/HActor.h"

#if defined(__ANDROID__) || defined(ANDROID)
int WAVPlayerComponent::globalIndex = 0;
bool WAVPlayerComponent::isSetsDTPlayer = false;
iolib::SimpleMultiPlayer WAVPlayerComponent::sDTPlayer;

WAVPlayerComponent::WAVPlayerComponent(const char *filePath, HActor* owner)
{
    if(!isSetsDTPlayer)
    {
        isSetsDTPlayer = true;
        sDTPlayer.setupAudioStream(2);
        sDTPlayer.startStream();
    }
    index = globalIndex++;
    loadWav(filePath);
    setOwner(owner);
}

WAVPlayerComponent::~WAVPlayerComponent()
{

}

void WAVPlayerComponent::update(const float deltaTime)
{
    HSceneComponent::update(deltaTime);
    if(isLooping && isPlaying && !sDTPlayer.getIsPlaying(index))
    {
        sDTPlayer.triggerDown(index);
    }
}

void WAVPlayerComponent::setLooping(bool isLoop)
{
    isLooping = isLoop;
}

void WAVPlayerComponent::play()
{
    sDTPlayer.triggerDown(index);
    isPlaying = true;
}

void WAVPlayerComponent::stop()
{
    sDTPlayer.triggerUp(index);
    isPlaying = false;
}

void WAVPlayerComponent::loadWav(const char *filePath)
{
    size_t fileSize = 0;
    auto buffer = GlobalFunction::readFile(filePath, fileSize);
    parselib::MemInputStream stream((unsigned char*)buffer, fileSize);
    parselib::WavStreamReader reader(&stream);
    reader.parse();
    if(reader.getNumChannels() != 1)
    {
        PRINT_LOG("parse wav failed", %s)
    }
    iolib::SampleBuffer* sampleBuffer = new iolib::SampleBuffer();
    sampleBuffer->loadSampleData(&reader);

    iolib::OneShotSampleSource* source = new iolib::OneShotSampleSource(sampleBuffer, 0.0f);
    sDTPlayer.addSampleSource(source, sampleBuffer);
    delete[] buffer;
}
#endif
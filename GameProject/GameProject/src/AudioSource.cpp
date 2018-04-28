#include "AudioSource.h"
#include <iostream>
#include <GLScene.h>

using namespace std;
using namespace irrklang;

AudioSource::AudioSource()
{
}

AudioSource::AudioSource(string newFilePath, float newVolume, bool isLooping)
{
    filePath = newFilePath;
    volume = newVolume;
    loop = isLooping;
}

AudioSource::~AudioSource()
{
    sound->drop(); // drop sound when instance is deleted. Don't think this is necessary but doing it to be safe
}

void AudioSource::Play()
{
    sound = AudioEngine::engine->play2D(filePath.c_str(), false, true); // Tell engine to play sound. Starts paused
    SetVolume(volume); // set the volume of the sound
    sound->setIsPaused(false); // unpause sound
}

void AudioSource::PlayMusic()
{
    sound = AudioEngine::engine->play2D(filePath.c_str(), loop, true);
    SetVolume(volume);
    sound->setIsPaused(false);
}

void AudioSource::Stop()
{
    // kill all the sounds in the engine. This is not ideal but works for this project
    AudioEngine::engine->stopAllSounds();
}

void AudioSource::SetVolume(float newVal)
{
    // clamp newVal to a max of 1.0 and minimum of 0
    if(newVal > 1.0)
        newVal = 1.0;
    else if(newVal < 0)
        newVal = 0;

    sound->setVolume(newVal);
}

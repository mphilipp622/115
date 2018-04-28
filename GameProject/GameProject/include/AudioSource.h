#ifndef AudioSource_H
#define AudioSource_H

#include <string>
#include "irrKlang.h"
#include <windows.h>
#include <AudioEngine.h>

using namespace std;

// Handles the playback and settings of SFX and Music. ChordManager will use AudioSource to play chords
class AudioSource
{
    public:
        AudioSource();
        AudioSource(string newFilePath, float newVolume, bool isLooping);
        virtual ~AudioSource();

        // Plays the sound from the filepath of the object
        void Play();

        void PlayMusic();

        // Stops playing any currently playing sound
        void Stop();

        // Sets the volume of this audio source
        void SetVolume(float newVal);

    protected:

    private:
        string filePath;
        float volume;
        bool loop;

        ISoundSource* source;
        ISound* sound;
        vec3df* position;
};

#endif // AudioSource_H

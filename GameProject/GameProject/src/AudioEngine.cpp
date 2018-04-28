#include "AudioEngine.h"

ISoundEngine* AudioEngine::engine; // global accessor for the audio engine

AudioEngine::AudioEngine()
{
    // start the sound engine with default parameters
    if(!engine)
        engine = createIrrKlangDevice(); // initialize static engine if it doesn't exist already

    if (!engine)
    {
       cout << "Audio Engine Failed to Initialize" << endl;
       exit(-1); // error starting up the engine
    }
}

AudioEngine::~AudioEngine()
{
    engine->drop();
}

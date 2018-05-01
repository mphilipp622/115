#ifndef TIMER_H
#define TIMER_H

#include <time.h>

// Class that is used for tracking elapsed time in the game.
class Timer
{
    public:
        Timer();
        virtual ~Timer();

        // Returns true if the timer has been starts
        bool IsStarted();

        // Returns true if the timer has been stopped
        bool IsStopped();

        // Returns true if the timer has been paused
        bool IsPaused();

        // Pauses the timer
        void Pause();

        // Resumes the timer from a paused state
        void Resume();

        // Stops the timer
        void Stop();

        // Starts the timer
        void Start();

        // Resets the timer back to 0
        void Reset();

        // Gets the elapsed time between the last GetTicks() call and the current GetTicks() call
        clock_t GetTicks(); // milliseconds

        // Get the running time of the timer
        clock_t GetTime();

    protected:

    private:
        // Time the timer is started at
        clock_t startedAt;

        // Time the timer is paused at
        clock_t pausedAt;

        // States of the timer
        bool started;
        bool paused;
};

#endif // TIMER_H

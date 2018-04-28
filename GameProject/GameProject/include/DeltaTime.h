#ifndef DELTATIME_H
#define DELTATIME_H

/*
Delta time is used for smoothing animations/movements in the game. Instead of animations speeds
being modified by the speed of your CPU/GPU, DeltaTime smooths the animations using time
*/
class DeltaTime
{
    public:
        DeltaTime();
        virtual ~DeltaTime();

        // static global getter for delta time. Used by multiple other classes
        static double GetDeltaTime();

        // called inside GLScene to update delta time at the end of every frame update
        void UpdateDeltaTime();

    protected:

    private:
        double oldTime;
};

#endif // DELTATIME_H

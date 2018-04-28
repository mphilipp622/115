#include <DeltaTime.h>
#include <windows.h>
#include <glut.h>
#include <iostream>

double deltaTime = 0.0; // initialize deltaTime to be 0

DeltaTime::DeltaTime()
{
    oldTime = glutGet(GLUT_ELAPSED_TIME);
    UpdateDeltaTime(); // start updating delta time as soon as instance is created
}

DeltaTime::~DeltaTime()
{
    //dtor
}

void DeltaTime::UpdateDeltaTime()
{
    // Updates delta time. This is, essentially, the time that's elapsed since the last frame render to the current frame
    double time = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = (time - oldTime) / 1000.0;
    oldTime = time;
}

double DeltaTime::GetDeltaTime()
{
    return deltaTime;
}

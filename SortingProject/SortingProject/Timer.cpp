/*
Mark Philipp
CSCI 115
ID: 109941708
*/

#include "stdafx.h"
#include "Timer.h"

using namespace std;

namespace Timer 
{
	// Returns true if the current running time has exceeded int time
	// Note that the total running time of 100 iterations of sorting will be looking at a threshold of 2 hours (7200 seconds)
	// For each iteration of the sort, we will look at a time threshold of 5 minutes (300 seconds)
	bool HasExceededTimeThreshold(chrono::time_point<chrono::system_clock> start, int time)
	{
		// If any algorithm runs longer than 'time' minutes, than we will quit execution.
		// We will annotate this on our statistics as time > 'time'. 'time' becomes our max running time that we care about
		auto end = chrono::system_clock::now();
		chrono::duration<double> elapsed = end - start; // get the currently elapsed time.

		if (elapsed.count() >= time)
			return true;

		return false;
	}
}
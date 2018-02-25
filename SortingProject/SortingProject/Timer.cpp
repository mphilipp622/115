#include "stdafx.h"
#include "Timer.h"

using namespace std;

namespace Timer 
{
	bool HasExceededTimeThreshold(chrono::time_point<chrono::system_clock> start, int time)
	{
		// If any algorithm runs longer than 'time' minutes, than we will quit execution.
		// We will annotate this on our statistics as time > 'time'. 'time' becomes our max running time that we care about
		auto end = chrono::system_clock::now();
		chrono::duration<double> elapsed = end - start;

		if (elapsed.count() >= time)
			return true;

		return false;
	}
}
/*
Mark Philipp
Isaac Fielding
CSCI 115
*/

#pragma once
#include <chrono>

// Namespace for benchmark timer
namespace Timer
{
	// Returns true if the current running time has exceeded int time
	bool HasExceededTimeThreshold(std::chrono::time_point<std::chrono::system_clock> start, int time);
}


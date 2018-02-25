#pragma once
#include <chrono>

namespace Timer
{
	bool HasExceededTimeThreshold(std::chrono::time_point<std::chrono::system_clock> start, int time);
}


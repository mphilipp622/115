#pragma once
#include <string>
#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <chrono>
#include <ctime>
#include <fstream>

// Namespace for benchmarking sorting functions. Pass sizes to the functions and they'll call on
// Sorter.h to execute sorting and output times to a console window.
namespace Benchmarker
{

	// Returns the time it takes to run Bubble Sort on array arr of n = size. Runs 100 times.
	void Benchmark(std::string method, int size);
}
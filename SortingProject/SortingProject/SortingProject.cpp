#include "stdafx.h"
#include "Benchmarker.h"
#include <thread>
#include <iostream>
#include "Sorter.h"

using namespace std;
using namespace Benchmarker;
using namespace Sorter;

int main()
{
	// Bubble Sort a million. Other sizes already done
	thread thread0(BenchmarkBubbleSort, 100000);
	thread thread1(BenchmarkBubbleSort, 1000000);

	// Selection Sort Benchmarks
	/*thread thread2(BenchmarkSelectionSort, 10);
	thread thread3(BenchmarkSelectionSort, 1000);
	thread thread4(BenchmarkSelectionSort, 10000);*/
	thread thread5(BenchmarkSelectionSort, 100000);
	thread thread6(BenchmarkSelectionSort, 1000000);

	// InsertionSort Benchmarks
	/*thread thread7(BenchmarkInsertionSort, 10);
	thread thread8(BenchmarkInsertionSort, 1000);
	thread thread9(BenchmarkInsertionSort, 10000);*/
	thread thread10(BenchmarkInsertionSort, 100000);
	thread thread11(BenchmarkInsertionSort, 1000000);

	// wait for n^2 algo's to finish
	thread0.join();
	thread1.join();
	thread5.join();
	thread6.join();
	thread10.join();
	thread11.join();
	
	// Merge Sort Benchmarks
	//thread thread12(BenchmarkMergeSort, 10);
	//thread thread13(BenchmarkMergeSort, 1000);
	//thread13.join(); // wait for thread to finish so we don't overflow stack through recursion

	//thread thread14(BenchmarkMergeSort, 10000);
	//thread14.join();

	thread thread15(BenchmarkMergeSort, 100000);
	thread15.join();

	thread thread16(BenchmarkMergeSort, 1000000);
	thread16.join();

	//// Quick Sort Benchmarks
	//thread thread17(BenchmarkQuickSort, 10);
	//thread thread18(BenchmarkQuickSort, 1000);
	//thread18.join();

	/*thread thread19(BenchmarkQuickSort, 10000);
	thread19.join();*/

	thread thread20(BenchmarkQuickSort, 100000);
	thread20.join();

	thread thread21(BenchmarkQuickSort, 1000000);
	thread21.join();
	
	thread0.join();
	thread1.join();
	/*thread2.join();
	thread3.join();
	thread4.join();*/
	thread5.join();
	thread6.join();
	/*thread7.join();
	thread8.join();
	thread9.join();*/
	thread10.join();
	thread11.join();
	/*thread12.join();
	thread13.join();
	thread14.join();*/
	/*thread15.join();
	thread16.join();*/
	//thread17.join();

	return 0;
}

Mark Philipp
Isaac Fielding
CSCI 115

Updated: 2/25/18

To run the program, run the "SortingProject.exe" file found in the root folder "SortingProject".

You will be asked for user input, which will allow you to create multiple types of arrays and sort or benchmark them.

Be sure that there is a "Data" folder that exists in your root "SortingProject" folder. I included this folder with the zip file so it should exist by default. This folder will be written to by the program. All of the benchmarks you run will be saved to this directory as CSV files that are named appropriately.

Do note that the majority of the code is both defined and implemented inside of the header files. This is due to the issues the c++ linkers have with generic classes (templates). By combining declaration and implementation into the same .h file for the generic class, the linker is able to succeed.

int main() can be found in SortingProject.cpp

All the sorting functions can be found in Sort.h

The timer function can be found in Timer.h and implemented in Timer.cpp

Array.h serves as the base abstract class for the prototype design pattern.
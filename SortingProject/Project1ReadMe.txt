Mark Philipp
Isaac Fielding
CSCI 115

------------------------

Updated: 3/13/18

To run the program, run the "SortingProject.exe" file found in the root folder "SortingProject".

You will be asked for user input, which will allow you to create multiple types of arrays and sort or benchmark them.

Be sure that there is a "Data" folder that exists in your root "SortingProject" folder. I included this folder with the zip file so it should exist by default. This folder will be written to by the program. All of the benchmarks you run will be saved to this directory as CSV files that are named appropriately.

Do note that the majority of the code is both defined and implemented inside of the header files. This is due to the issues the c++ linkers have with generic classes (templates). By combining declaration and implementation into the same .h file for the generic class, the linker is able to succeed.

-------------------------

All source code can be found in the "SortingProject" folder.

int main() can be found in SortingProject.cpp

All the sorting functions can be found in Sort.h

The timer function can be found in Timer.h and implemented in Timer.cpp

Array.h serves as the base abstract class for the prototype design pattern.

If you wish to compile the project, you will need to open the SortingProject.sln file in Visual Studio and build the project and run it.

-------------------------
ERRORS
-------------------------

The only error that might happen during compilation in Visual studio is an error related to your Windows SDK version. To resolve this error, you will need to go to Project -> SortingProject Properties -> In the Configuration Propertes/General section, there's a section called "Windows SDK Version". Make sure it is set to 8.1. This should resolve the SDK error. If it does not, then try setting it to the other options listed, such as 10.0.16299.
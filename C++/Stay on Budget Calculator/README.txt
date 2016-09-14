README.txt


CS 315-001 Spring 2015
Program Assignment makeup program 1, Milestone 3

MArch, 2015

name: Carmon Zach Almon


Synopsis:

To compile: g++ --std=c++0x Source2.cpp

To run:

	./a.out < test1.in
	where test1.in can be replaced with any other text file.
or:
	./a.out [ENTER] N number for number of elments [ENTER] N elements [ENTER] Budget [ENTER]

 

Included Files: //adjust as necessary
README - current file
Source2.cpp - source code for milestone 3 algorithm with result and comparison
count output to console
tester.sh - shell script to generate and run tests for experimental analysis
Analysis.txt - txt file with experimental analysis report
Tests: in1, in2, in3, in4, in5, in6

Bugs and Extras:

	**Efficiency is slow because in the program the vectors are not passed by reference. It takes alot of compute cycles to copy the vectors, this was found but has not been implemented. If implemented efficiency would increase exponentially

Algorithm Description:

	There is a loop to read in numbers.
	
	There is a call to sort the vector of N elements.
	
	There is a loop to loop once over the N elements of the vector.
	
	Each loop there is a call to a binary search function to find if the value y, which equals M-x (where x is the vector indexed at current loop iterator 'i'), is in the vector.
	
	The binary search function takes the vector and searches over the index number, not the vector values.
	
	The algorithm indexes the vector at the current binary search value to check if it equals y.
	
	Returns true if the value is in the vector, and is not the same index as the for loop from before, or if it is, there is a duplicate number above or below the index value.

	Returns false for any and every other check and if the search reaches the end of the binary search.

	
	Algorithm Theoretical run time: O(nlogn)

	
Algorithm Example:

Consider the following input sequence.
4
1
5
7
3
9


Length is 4
Budget (M) is 9
3 and 5 are found to add to M-1, and has the lowest difference. 5 - 3 > 7 - 1









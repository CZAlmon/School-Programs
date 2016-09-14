CS 315-001 Spring 2015
Program Assignment 1, Milestone 3
January 29, 2015
name: Carmon Zachary Almon


Synopsis: 
To compile: g++ --std=c++0x pa1.cpp

Input for this program should follow the specs.

To run:
./a.out < test1.in

where test1.in can be replaced with any other text file. The only output that
will be presented is an integer which returns the smallest d such that the
sequence is d-smooth, followed by the number of comparisons for the test.

A typescript (generated with the UNIX script command) is provided to show use
of all included source files and executables

Included Files:

README			     - current file
pa1.cpp				 - source code for milestone 3 algorithm with result and comparison count output to console
script.txt			 - sample session showing commands, inputs, and outputs
pa1_exp_analsis.txt  - txt file with experimental analysis report
tests/scripts		 - tests directory has 2 sets of test files, and 2 scripts.
					 - one set of tests/script provided by professor
					 - one set provided by student
					 - Also comes with a.out file, so the scripts are ready to be run


Bugs and Extras:
No bugs have been found to date.

Algorithm Description:
a)use a binary search system to search for d-values within M, where M is the number of the sequence added up plus 50. This algorithm is O(log(M))
b)when given a individual d-value loop over the sequence adjusting values to make them strictly increasing. Also adjust each value so that it is the smallest value it can be, where it is still bigger then the value before it. 
c)b returns true or false, and the binary search system will remember the smallest true d-value.

The theoretical running time of my algorithm is O(nlog(M)), where n is the number of elements, and M is the sum of all elements plus 50.

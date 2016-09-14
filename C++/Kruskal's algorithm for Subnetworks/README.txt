README.txt

CS 315-001 Spring 2015
Program 2, Milestone 2

April, 20 2014

name: Carmon Zach Almon

Synopsis:

To compile: make #Run Makefile to compile all other object files and Source.cpp

To run:  

	./a.out [Filename.in]
	
 

Included Files: //adjust as necessary
README - current file
Makefile - Makefile to compile program
Source.cpp - C++ file 
graph.cpp - C++ File
edge.cpp - C++ File
unionfind.cpp - C++ File
graph.h - C++ File
edge.h - C++ File
unionfind.h - C++ File



Bugs and Extras:




Algorithm:

	Open File. Get Graph Size and Number of Required Links. (I Do Check Input for correctness here)
	
	Get city names into vector and their corresponding number (1 for first entry, 2 for second, etc)
	
	Open graph and make it from the in file. The in file will take the matrix from the in file and will leave the links (if any)
	
	If there are any links then for into a function to get the links and "convert" then from the city name to city number
		Get first and second of the pair
	
		Compare the numbers(cities) and set the lower city number first. Lower first Higher second. This will make sure its always in the upper right part of the matrix
	
		Make an edge of the pair of cities and push it to a priority queue.
		Set the edge weight to -1 after.
	
	Close the in file. 
	
	Open a graph for Kruskals tree.
	
	If Required links is more than 0 then loop over that priority queue and add every single required edge to the union.
	
	Make a priority queue of the rest of the edges.
	
	Loop over that till every vertex is in the graph, making sure there is no loop (Other than if there is from required links)
	This is the Kruskals Algorithm.
	
	Every Union (Both required links and the algorithm) Add up the weight for the total weight.
	
	
	
	
	
	
	
	
	

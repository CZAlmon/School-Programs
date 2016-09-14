# File: makefile
# Author: CS315 JWJ-CS-UK
# Task: pa2 - cs315s15 handout
# Description: makefile for building program "pa2m2cs315s15"

# Edited by Zach Almon, Edited places have comments with details
# Source.o and Source.cpp were main.o and main.cpp Simple name change is all that was done

pa2m2cs315s15: Source.o graph.o edge.o unionfind.o
	g++ -g -o pa2m2cs315s15 Source.o graph.o edge.o unionfind.o

Source.o:	Source.cpp
	g++ -g -c -Wall Source.cpp

graph.o: graph.h graph.cpp
	g++ -g -c -Wall graph.cpp

edge.o:	edge.h edge.cpp
	g++ -g -c -Wall edge.cpp

unionfind.o: unionfind.h unionfind.cpp
	g++ -g -c -Wall unionfind.cpp


clean:
	rm pa2m2cs315s15
	rm *.o

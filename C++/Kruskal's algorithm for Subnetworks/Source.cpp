#include <cstdlib>
#include <iostream>
#include <queue>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <stdlib.h>
#include <map>

#include "graph.h"
#include "edge.h"
#include "unionfind.h"

using namespace std;

int main(int argc, char *argv[]){

	//To make sure that only 1 thing has been passed
	// open text file for reading
	if(argc != 2)
	{
		// Hint to user about how to use command line
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		exit(-1);
	}

	ifstream in;
	in.open(argv[1]);  //open input stream.

	if (!in)         //check for open success.
	{
		cout << "Input File was not read in" << endl;
		exit(-1);
	}

	map<string, int> city_names_and_numbers;	//Get city names and corresponding number representation
	priority_queue<edge> Link_edges;				//Queue of Link edges
	priority_queue<edge> PQ_edges;					//Queue of edges
	int final_weight, kruskal_size;		//Final_weight = output to user; kruskal_size = number of edges
	int graph_size, number_links;		//Graph_size = the size of in; Number_links is number of required links
	char t;								//Char for making undirected graphs
	string temp;
	int i_temp, i_temp2, i_temp3;		//i_temp1 and i_temp2 are for city representaions. i_temp3 is:
									//In the Link Pairs, Lower city "number representaion" should always be first
	t = UNDIRECTED;
	//Make sure in correctly transfers into size and link size
	if ((in >> graph_size).fail()){
		cout << "Bad Graph Size name" << endl;
		return -3;
	}
	if ((in >> number_links).fail()){
		cout << "Bad Link Size name" << endl;
		return -4;
	}
	//Make sure Size and link are correct
	if (graph_size < 2 || graph_size > 1000){
		cout << "Incorrect Number of Cities. Must be between 2 and 1000" << endl;
		return -5;
	}
	if (number_links < 0 || number_links > 499500){
		cout << "Incorrect Number of Required Links. Must be between 0 and 500*999 (499500 Pairs of Cities)" << endl;
		return -6;
	}
	//Get city names
	for (int i = 0; i < graph_size; i++){
		if ((in >> temp).fail()){
			cout << "Bad city name" << endl;
			return -7;
		}
		city_names_and_numbers[temp] = i;

	}

	graph my_graph(graph_size, t);
	//In passed by reference, will Loop exactly Size times and extract Matrix from in leaving links if any.
	my_graph.read(in);
	//in at this point has only the link pairs left inside it.
	if (number_links > 0){
		for (int i = 0; i < number_links; i++){
			//FIRST Of the Pair
			if ((in >> temp).fail()){
				cout << "Bad Link city name" << endl;
				return -8;
			}

			map<string, int>::iterator it = city_names_and_numbers.find(temp);
			i_temp = it->second;
			
			//SECOND OF the Pair
			if ((in >> temp).fail()){
				cout << "Bad Link city name" << endl;
				return -8;
			}

			it = city_names_and_numbers.find(temp);
			i_temp2 = it->second;
			
			//Lower City representaion number should ALWAYS BE FIRST. Lower, then higher. i_temp should be lower then i_temp2
			//This will keep us in the upper half of the matrix all the time
			if (i_temp > i_temp2){
				i_temp3 = i_temp;
				i_temp = i_temp2;
				i_temp2 = i_temp3;
			}

			//Get edge, push it to queue, then change the weight.
			edge link_edge(i_temp+1, i_temp2+1, my_graph.edge_weight(i_temp+1, i_temp2+1));
			Link_edges.push(link_edge);
			my_graph.write(i_temp+1, i_temp2+1, -1);
		}
	}
	in.close();

	graph Kruskals_graph(graph_size, t);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Required City Links
	//First Goal for at Max 2 requred edges


	//Subnetwork Variables may be used for required edges
	edge edge_temp;
	unionfind un(my_graph.size() + 1);
	final_weight = 0;
	kruskal_size = 0;


	//Put required edges into union
	while (!Link_edges.empty()){
		edge_temp = Link_edges.top();

		un.unions(un.find(edge_temp.get_from()), un.find(edge_temp.get_to()));
		final_weight += edge_temp.get_weight();
		kruskal_size++;

		Link_edges.pop();
	}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Kruskal's Algorithm

	//set PQ_edges
	for (int i = 1; i <= graph_size; i++){
		for (int j = i; j <= graph_size; j++){
			if (my_graph.edge(i, j)){
				edge e(i, j, my_graph.edge_weight(i, j));
				PQ_edges.push(e);
			}
		}
	}

	//Build the subnetwork
	
	//Subnetwork Variables taken from here, and moved above
	while (!PQ_edges.empty()){
		edge_temp = PQ_edges.top();

		if (un.find(edge_temp.get_from()) == un.find(edge_temp.get_to()))
			PQ_edges.pop();
		else
		{
			un.unions(un.find(edge_temp.get_from()), un.find(edge_temp.get_to()));
			final_weight += edge_temp.get_weight();
			kruskal_size++;
		}
	}

	

	//Check to see if there is a cycle. Very rudimentary. Only checks if there was no union done. 
	//Unknown how to check if all vertices have been added or not.
	if (kruskal_size <= 0){
		cout << "IMPOSSIBLE" << endl;
	}
	else{
		cout << "Number of edges: " << kruskal_size;
		cout << " for a cost of: " << final_weight << endl;
	}




	





	return 1;
}



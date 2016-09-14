// File: graph.h
// Author: CS315 JWJ CS-UK
// Description: graph class provided by instructor


/* ----graph.h-------
	graph class for cs315 project 3
	given by instructor JWJ


	The graph class stores a matrix in incidence format.
	It is assumed that the size of the graph is < 1001.
	You can store  undirected graphs.
	For undirected graphs we just give the upper half of the matrix.
	Format for undirected graphs:

	3    		<---- size
	u   	 	<---- type
	0 20 30   	<---- first upper row
	   0 10   	<---- second upper row
	      0   	<---- third upper row

	which represents a 3 x 3  weighted undirected graph with
	the following matrix: 

	vertex  1       2       3        
	1       0       20      30        
	2       20       0      10        
	3       30      10       0        


	The methods edge, and edge_weight, allow you to see
	if there is a connection between the values.
*/

#include <iostream>
#include <fstream>

#define UNDIRECTED 1
#define DIRECTED 0

#define V_MAX 1000 //# vertices in G(V,E,w) represented with the matrix


class graph
{
public:
	// s is size, type is undirected or directed
	graph(int s, int type = UNDIRECTED);

	int write(int from, int to, int weight=1);	
	int read(void);
	int read(std::ifstream& in);
	void printer(void);
	int get_type(void);
	
	int any_edges(void);
	int any_from(int from);
	int any_to(int to);

	int num_vertices(void);

	int edge(int from, int to);
	int edge_weight(int x, int y);
	
	int inline size() {return _size;};

private:
	int m[V_MAX][V_MAX];
	int _size;
	bool _undirected;
};

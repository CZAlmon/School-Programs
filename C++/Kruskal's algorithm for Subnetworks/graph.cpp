// File: graph.cpp
// Description: implementation of graph class from graph.h
//cs315s15 pa2
//Spring 2015



/* ----graph.cpp-------
	graph class for cs315 project 3 Spring 2015
	given by instructor JWJ CS-UK
*/

#include <iostream>
#include "graph.h"

using namespace std;

#define UNDIRECTED 1
#define DIRECTED 0

graph::graph(int s, int type)
{
	_size=s;

	if (type == DIRECTED)
		_undirected=false;
	else
		_undirected=true;

	for (int i=0; i<s; i++)
		for (int j=0; j<s; j++)
			m[i][j]=0;
}

int graph::get_type(void)
{
	return (_undirected);
}

void graph::printer(void)
{
	for (int j=0; j<_size; j++)
	{
		for (int i=0; i<_size; i++)
			cout << m[j][i] << "\t";
		cout << endl;
	}
}

int graph::write(int from, int to, int weight)
{
	if ((from > 0) && (from <= _size))
	 if ((to > 0) && (to <= _size))
      if (from != to)
	  {
		m[from-1][to-1]=weight;
		if (_undirected)
			m[to-1][from-1]=weight;
		return 1;
	  }
	return 0;
}	

int graph::any_edges(void)
{
	for (int j=0; j<_size; j++)
		for (int i=0; i<_size; i++)
			if (m[i][j] != 0)
				return 1;

	return 0;
}

	
int graph::edge(int from, int to)
{
	if ((from > 0) && (from <= _size))
	 if ((to > 0) && (to <= _size))
	  if (m[from-1][to-1]!=0)
	   return 1;
	return 0;
}

int graph::edge_weight(int from, int to)
{
	if ((from > 0) && (from <= _size))
		if ((to > 0) && (to <= _size))
			return m[from-1][to-1];
	return 0;
}

int graph::read(void)
{
	for (int j=0; j<_size; j++)
	for (int i=j; i<_size; i++)
			cin >> m[j][i];

	return 1; 
}

int graph::read(ifstream& in)
{
	for (int j=0; j<_size; j++)
	for (int i=j; i<_size; i++)
			in >> m[j][i];

	return 1; 
}

int graph::any_from(int from)
{
	for(int j = 0; j < _size; j++)
		if ( m[from - 1][j] != 0 )
			return 1;

	return 0;
}

int graph::any_to(int to)
{
	for(int i = 0; i < _size; i++)
		if( m[i][to - 1] != 0 )
			return 1;
	return 0;
}

int graph::num_vertices(void)
{
	int count = 0;
	for(int i = 0; i < _size; i++)
		if( any_from(i + 1) )
			count++;

	return count;
}

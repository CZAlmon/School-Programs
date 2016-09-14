// File: edge.cpp
// Author: written for CS315 JWJ-CS-UK
// Description: a simple implementation of edge class from edge.h

#include "edge.h"

edge::edge()
{
	_from = -1;
	_to = -1;
	_weight = -1;
}
edge::edge(int from, int to, int weight)
{
	_from = from;
	_to = to;
	_weight = weight;
}

int edge::get_from(void) const
{
	return _from;
}

int edge::get_to(void) const
{
	return _to;
}

int edge::get_weight(void) const
{
	return _weight;
}

bool edge::operator<( const edge &e ) const
{
	if( _weight < e.get_weight() )
		return false;
	return true;
}

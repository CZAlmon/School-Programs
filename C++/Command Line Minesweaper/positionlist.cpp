// CS 215, Spring 2014
// Carmon Zachary Almon
// Programming assignment 4
// Last updated 23 April, 2014
#include <cstdlib>
#include "positionlist.h"
using namespace std;

// Initialize a node with no next node and the given position.
Node::Node(Position p)
	: next(NULL), pos(p)
{}

// Default constructor: initialize an empty list.

PositionList::PositionList()
{
	first = NULL;
}

// Initialize a copy of a list using the copy_nodes helper function.
PositionList::PositionList(const PositionList &original)
{
	first = copy_nodes(original.first);
}

// Store the contents of another list in this one, replacing the old
// contents of this list (and freeing those nodes).  Returns the
// implicit parameter by reference (return *this;)
//
// This method implements assignment:   poslist = otherposlist;
//
PositionList &PositionList::operator=(const PositionList &other) 
{
	if (this == &other)
		return *this;

	int size_here = size();

	for (int i=0; i < size_here; i++){
		pop_front();
	}
	
	first = copy_nodes(other.first);

	return *this;
}

// Calculate the size of the list.
int PositionList::size() const 
{
	int i = 0;
	for (Node *curr = first; curr != NULL; curr = curr->next) {
		i++;
	}
	return i;
}

// Test whether the list is empty.
bool PositionList::empty() const
{
	if (first == NULL){
		return true;
	}
	return false;
}

// Return the Position at the given index.  If the index is out of
// bounds, return Position(-1, -1).
Position PositionList::get(int index) const
{
	Node *curr = first;
	for (int i=0; i < index; i++){

		if (curr == NULL){
			return Position(-1, -1);
		}

		curr = curr->next;

	}

	if (curr == NULL){
			return Position(-1, -1);
	}
	return curr->pos;
}

// Add a new Position object to the beginning of the list.
void PositionList::push_front(Position pos)
{
	Node *to_insert = new Node(pos);
	to_insert->next = first;
	first = to_insert;
}

// Remove the first element, freeing its node.
void PositionList::pop_front()
{
	Node *to_del = first;
	first = to_del->next;
	delete to_del;
}

// Helper function: recursively copy "in" and all the nodes that follow.
// As a base case, "copying" NULL should return NULL (and not copy anything).
Node *PositionList::copy_nodes(const Node *in) const
{
	if (in == NULL){
		return NULL;
	}

	Node *copy = new Node(in->pos);
	copy->next = copy_nodes(in->next);

	return copy;

	//This was here before, Unknown if needed
	//return new Node(Position(-9, -9));
}

// Clean up this list by freeing all its nodes.
PositionList::~PositionList()
{
	int size_here = size();

	for (int i=0; i < size_here; i++){
		pop_front();
	}
}

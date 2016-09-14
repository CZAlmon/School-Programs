// CS 215, Spring 2014
// Carmon Zachary Almon
// Programming assignment 4
// Last updated 29 April, 2014
#ifndef POSITIONLIST_H_INCLUDED
#define POSITIONLIST_H_INCLUDED

#include "position.h"

// Class representing a node in a PostionList.  This class
// is intended to be used only by PositionList.
class Node
{
public:
	// Create a new node with no next node and position p.
	Node(Position p);
private:
	// A pointer to the next node in the linked list.
	Node *next;

	// The Position being stored in this node.
	Position pos;

	// The Node class is intended for the internal use of
	// PositionList, so give that class access to our
	// private data members.
	friend class PositionList;
};

// Class representing a position on a two-dimensional board.
// Stores an x and y coordinate, with methods to return and
// set each coordinate, and a method to test whether the
// position falls within a given width and height.
class PositionList
{
public:
	// Initialize an empty list.
/* positionlist() - make an empty list
 *
 * Description: 
 *		  Make an empty list
 *		  		  
 * Inputs:
 *		  None
 *
 * Outputs:
 *		  No outputs.		 
 *		
 * Side-Effects:
 *		 Changes the first node to NULL.
 *		   
 * Exceptions:		
 *		  None	  
 *	
 * Notes:  
 */
	PositionList();

	// Initialize a list as a deep copy of another.
/* PositionList(const PositionList &original) - Makes a copy of a different list
 *
 * Description: 
 *		  Runs through the parameter and makes a deep retained copy of that list.
 *		  Loops over the other list and makes a copy	  
 *		  
 * Inputs:
 *		  Positionlist object as parameter
 *
 * Outputs:
 *		  Returns the newly copied poistionlist object
 *
 * Side-Effects:
 *		 Makes a new object with its own member variables
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
	PositionList(const PositionList &original);

	// Clean up this list by freeing all its nodes.
/* ~PositionList() - Deleter
 *
 * Description: 
 *		  Runs over the size, deletes the list
 *		  		  
 * Inputs:
 *		  none  
 *
 * Outputs:
 *		  none
 *
 * Side-Effects:
 *		 	   
 * Exceptions:		
 *		  
 * Notes:  
 */
	~PositionList();

// Deep copy the contents of another list into this one.  Replace the old
// contents of this list, freeing those nodes.  Returns the implicit
// parameter by reference (return *this;)
//
// This method implements assignment:   poslist = otherposlist;
/* PositionList &operator=(const PositionList &other) -
 *
 * Description: 
 *		  
 *		  		  
 *		  
 *		  		  
 *		  
 *		  		  
 *
 * Inputs:
 *		  
 *
 * Outputs:
 *
 *
 * Returns an appointment with information from the line.		 
 *		
 * Side-Effects:
 *		 
 *		   
 * Exceptions:		
 *		  
 *		  
 *	
 * Notes:  
 */
	PositionList &operator=(const PositionList &other);

// Returns true if this list is empty.
/* empty() - returns true if empty, false if not
 *
 * Description: 
 *		  If first pointer is null, return true, else false
 *		  		  
 * Inputs:
 *		  N/A
 *
 * Outputs:
 *		  If first pointer is null, return true, else false
 *	
 * Side-Effects:
 *		 None
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
	bool empty() const;

// Calculate the size of the list (number of nodes).
/* size() - calculate size of list
 *
 * Description: 
 *		  Runs over each node, count 1, move to next node and repeat
 *		  Get total and return as int  
 *		  
 * Inputs:
 *		  None  
 *
 * Outputs:
 *		  Returns int number
 *
 * Side-Effects:
 *		 
 * Exceptions:		
 *		  
 * Notes:  
 */
	int size() const;
	
// Find and return the index-th element in the list, counting from 0.
// If the index was out of bounds, return the Position (-1, -1).
/* get() - get a certain value from list.
 *
 * Description: 
 *		  Set curr to first node. Run over each node till the index number
 *		  if a node is NULL return Position(-1,-1)  
 *		  Get index node, if index node is NULL return Position(-1,-1)
 *		  else return curr->pos (Curr node to Position Node)
 *
 * Inputs:
 *		  Index Value
 *
 * Outputs:
 *		  Position object
 *
 * Side-Effects:
 *		  None
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
	Position get(int index) const;

// Add a new Position object to the beginning of the list.
/* push_front(Position pos) - Add a new Position object to the beginning of the list.
 *
 * Description: 
 *		  Make new node for parameter.
 *		  Put new node in next.
 *		  Put new node in the position first.
 *		  Adding it to the front of the list.
 *		  
 * Inputs:
 *		  Position to be added
 *
 * Outputs:
 *		  None
 *
 * Side-Effects:
 *		  Adds a new position to the front of the list
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
	void push_front(Position pos);

// Remove the first element, freeing its node.
/* pop_front() - Remove the first element, freeing its node.
 *
 * Description: 
 *		  Make a new node for the first node in list
 *		  Assign first node pointer to next in list
 *		  Delete the node you made in the begining of this function
 *		  		  
 * Inputs:
 *		  None
 *
 * Outputs:
 *		  None
 *
 * Side-Effects:
 *		  Deletes current first node, assigns second node to first node position
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
	void pop_front();

private:
// Recursively make a deep copy of a node and all the nodes that follow.
	// Returns the copy.  The input may be NULL, in which case nothing is
	// copied and the function returns NULL.
	// This function will be used by the copy constructor and by operator= .
/* Node *copy_nodes(const Node *in) const - ^^^^^^^
 *
 * Description: 
 *		  If parameter is null, return Null
 *		  Make new node for parameter, put it in Node's pos.	  
 *		  copy that to next in nodes variables, then recursively call this function again.
 *		  return the copy	  
 *		  
 * Inputs:
 *		  Parameter is a Node
 *
 * Outputs:
 *		  Returns the copied node
 *
 * Side-Effects:
 *		  none
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
	Node *copy_nodes(const Node *in) const;

	Node *first;
};


/* main() -
 *
 * Description: 
 *		  
 *		  		  
 *		  
 *		  		  
 *		  
 *		  		  
 *
 * Inputs:
 *		  
 *
 * Outputs:
 *
 *
 * Returns an appointment with information from the line.		 
 *		
 * Side-Effects:
 *		 
 *		   
 * Exceptions:		
 *		  
 *		  
 *	
 * Notes:  
 */

#endif

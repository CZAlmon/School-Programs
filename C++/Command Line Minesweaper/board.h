// CS 215, Spring 2014
// Carmon Zachary Almon
// Programming assignment 4
// Last updated 29 April, 2014
#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "position.h"
#include "positionlist.h"
using namespace std;

class MineSweeperBoard
{
public:
// Initialize a board with a given width and height, containing the
// given number of randomly-placed mines.  Nothing should be revealed
// or flagged.  If there are more mines than spaces for them, fill
// the entire board with mines.
/* MineSweeperBoard(int board_width, int board_height, int mine_count) - constructor for the mine-board
 *
 * Description: 
 *		  Will start a 3 -2D array of arrays with pointers. One will be the mines, one will be flagged objects, the last will be
 *		  what has been revealed to the user. Each works similarly.
 *		  Make new* array. Loop for y arrays, then loop for the x arrays.
 *		  Inside y-loop make a new array for each y element.
 *		  Inside x-loop set each [i][m] element a pointer to false or true. 
 *        (All false for Flag and Revealed. Mined will have true for only places with mines, Make these places random, also dont go over user defined # of mines)
 *		  
 * Inputs:
 *		  Board height, width, number of mines
 *
 * Outputs:
 *		  None
 *	
 * Side-Effects:
 *		  Change member variables for Revealed, Mined, flagged
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
	MineSweeperBoard(int board_width, int board_height, int mine_count);

// Clean up the board, freeing any dynamically allocated memory.
/* ~MineSweeperBoard() - deconstructor
 *
 * Description: 
 *		  3 loops all similar.
 *		  Loop over the 2D array (flagged, mined, revealed) and delete each array inside the [i] element.
 *		  Then delete the main array. This will free everything properly.
 *		  Do this loop for each 2D array (or combine so there is only 1 loop, doesnt matter for such small arrays)
 *
 * Inputs:
 *		  None
 *
 * Outputs:
 *		  None
 *
 * Side-Effects:
 *		   Frees all allocated memory
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
	~MineSweeperBoard();

// Get the size of the board.
/* int get_width() const - get width of board
 *
 * Description: 
 *		  return width
 *		  		  
 * Inputs:
 *		  none
 *
 * Outputs:
 *		  returns width as an int
 *
 * Side-Effects:
 *		 none
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
	int get_width() const;
/* int get_height() const - get height of board
 *
 * Description: 
 *		  return height
 *		  		  
 * Inputs:
 *		  none
 *
 * Outputs:
 *		  returns height as an int
 *
 * Side-Effects:
 *		 none
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
	int get_height() const;

// Reveal a square.
// If this square wasn't already revealed, and if the number of
// adjacent mines equals the number of adjacent flags, recursively
// reveal all the surrounding squares that aren't flagged.
/* reveal(Position p) - reveals the position
 *
 * Description: 
 *		  Get the x and y value of point p (parameters)
 *		  One main if statement, if that point is not revealed, go into, else do nothing.
 *		  in main if statement, set point to true, then new if statement comparing adjacent flagged to adjacent mined
 *		  Inside new if statement:
 *		  Set new PositionList object equal to member function ajacent(p) (member function ajacent was given by professor)
 *		  Loop over PositionList Objects size, get position object of each part, get x and y values for each object
 *		  if this object is not flagged-- RECURSION CALL for this position
 *
 * Inputs:
 *		  Position object p.
 *
 * Outputs:
 *		  None
 *	
 * Side-Effects:
 *		 Changes revealed, and flagged 2D arrays approprietly.
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
	void reveal(Position p);

// Put a flag on a square, or remove a flag that is
// already there.  Returns true if we placed a flag, false if
// we removed one.
/* bool flag(Position p) - flags this point
 *
 * Description: 
 *		  Get x and y value of the parameter Position p.
 *		  if flagged[y][x] is true set to false and return false (Removes flag and returns false for no flag)
 *		  if flagged[y][x] is not true, set to true and return true (puts a flag at this spot and returns true for flag)
 *		  		  
 * Inputs:
 *		  Position p
 *
 * Outputs:
 *		  True for flag at this spot, false for not
 *
 * Side-Effects:
 *		  Changes flagged 2D array 
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
	bool flag(Position p);

// Return the appearance of the square (what will be
	// displayed to the player) as a single character.
	char appearance(Position p) const;

// Display the entire board to an output stream.  Prints
	// a header with the column numbers, and prints the row
	// number on each line.  For example,
	//     |  0  1  2  3  4
	//  ---+---------------
	//   0 |  1  /  .  .  .
	//   1 |  1  2  .  .  .
	//   2 |  0  1  .  .  .
	//   3 |  0  1  2  1  1
	//   4 |  0  0  0  0  0
/* void display(ostream &out) const - Displays the board to user
 *
 * Description: 
 *		  For apparence, set 2 loops for the first 2 lines of the board, mainly spaces and "-" and numbers "i" from 0 to to w (not included)
 *		  Next loop is the main loop, i for the rows, add a few spaces, print number then a loop inside for the columns
 *		  This loop will make a position object of [m][i] (x, y) then display apperence(position_object) with appropriate spaces
 *		  then end on a new line to start next interation of [i] loop.
 *		  
 * Inputs:
 *		  out going stream
 *
 * Outputs:
 *		  displays the board and its contents to user
 *
 * Side-Effects:
 *		 None
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
	void display(ostream &out) const;

// Returns true if the player won (every square with a mine
// is flagged, and every cell without a mine is revealed).
	bool won() const;

// Returns true if the player lost (there is a revealed
	// mine).
/* bool lost() const - tells weither user has lost.
 *
 * Description: 
 *		  Loop over rows, the loop over columns, if mined[m][i] is true then compare mined[m][i] to revealed[m][i]
 *		  if(mined[m][i] == revealed[m][i]) is true, then return true
 *		  
 *		  exit all ifs, and loops. return false if this point is reached.		  
 *		  
 * Inputs:
 *		  None
 *
 * Outputs:
 *		  returns true if user lost, false otherwise
 *
 * Side-Effects:
 *		 none
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
	bool lost() const;

// Reveal everything (losing the game in the process)
/* void give_up() - gives up game.
 *
 * Description: 
 *		  Loop over rows, loop over columns, set revealed[m][i] to true
 *		  set ALL revealed[m][i] to true.
 *		  This will trigger lost() and will lose the game ending it.
 *		  		  
 * Inputs:
 *		  None
 *
 * Outputs:
 *		  None
 *	
 * Side-Effects:
 *		  Sets all of revealed to true. Ending game, and displaying all the board.
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
	void give_up();

private:
	// Returns a list of all the positions adjacent to p.  If p
	// is in the middle of the board, it has eight neighbors,
	// but if it is on an edge or corner it will have fewer.
	PositionList adjacent(Position p) const;

	// Return the number of mines or flags adjacent to a square.
	int adjacent_mines(Position p) const;

/* int adjacent_flags(Position p) const - returns number of adjacent flagged objects
 *
 * Description: 
 *		  Make new PositionList with adjacent(p)
 *		  start an int variable for the count
 *		  one loop from 0 to PositionList.size()
 *		  make a Position object with PositionList.get(i)
 *		  if (flagged[position.y()][position.x()]) is true count++
 *		  return count
 *
 * Inputs:
 *		  Position p
 *
 * Outputs:
 *		  returns count of flagged objects 
 *
 * Side-Effects:
 *		 none
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
	int adjacent_flags(Position p) const;

	// Size of the board.
	int width;
	int height;
	int number_of_mines;

	// Dynamically allocated 2D arrays indicating which squares are
	// revealed, which are mined, and which are flagged.
	bool **revealed;
	bool **mined;
	bool **flagged;
};
#endif

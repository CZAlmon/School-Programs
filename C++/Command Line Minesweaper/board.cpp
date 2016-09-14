// CS 215, Spring 2014
// Carmon Zachary Almon
// Programming assignment 4
// Last updated 23 April, 2014
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "board.h"
using namespace std;

char MineSweeperBoard::appearance(Position p) const
{
	int x = p.x();
	int y = p.y();

	if (flagged[y][x]){
		return '/';
	} 
	else if (revealed[y][x]){
		if (mined[y][x]){
			// Boom!
			return '*';
		} 
		else{
			// At most 8 adjacent mines, so one digit.
			int adjmines = adjacent_mines(p);
			// Convert a number to a digit character.
			return '0' + adjmines;
		}
	} 
	else{
		// Unrevealed, unflagged.
		return '.';
	}
}
bool MineSweeperBoard::won() const
{
	// Check every square.  If we see a square that is mined but
	// not flagged, or unmined but not revealed, return false
	// immediately.  If we get to the end, every square is correct,
	// so the user won and we return true.
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (mined[y][x] && !flagged[y][x]) {
				return false;
			} else if (!mined[y][x] && !revealed[y][x]) {
				return false;
			}
		}
	}
	return true;
}
PositionList MineSweeperBoard::adjacent(Position p) const
{
	PositionList result;

	// Loop over the 3x3 block centered around p.
	for (int adj_y = p.y() - 1; adj_y <= p.y() + 1; adj_y++) {
		for (int adj_x = p.x() - 1; adj_x <= p.x() + 1; adj_x++) {
			// Make a position out of the new coordinates.
			Position adj(adj_x, adj_y);
			// Skip out-of-bounds squares
			if (!adj.in_bounds(width, height))
				continue;
			// Also skip the center.
			if (adj.x() == p.x() && adj.y() == p.y())
				continue;

			// If we get here, it's really adjacent, so add it to the list.
			result.push_front(adj);
		}
	}
	return result;
}
int MineSweeperBoard::adjacent_mines(Position p) const
{
	PositionList neighbors = adjacent(p);

	// Loop over the neighbors.
	int adjacent_count = 0;
	for (int i = 0; i < neighbors.size(); i++) {
		Position adj = neighbors.get(i);
		// If it's mined, increase the count.
		if (mined[adj.y()][adj.x()])
			adjacent_count++;
	}
	return adjacent_count;
}


//I have completed

MineSweeperBoard::~MineSweeperBoard(){
	//Revealed
	for (int i = 0; i < height; i++){
		delete[] revealed[i];
	}
	delete[] revealed;
	//mined
	for (int i = 0; i < height; i++){
		delete[] mined[i];
	}
	delete[] mined;
	//flagged
	for (int i = 0; i < height; i++){
		delete[] flagged[i];
	}
	delete[] flagged;

}
MineSweeperBoard::MineSweeperBoard(int board_width, int board_height, int mine_count){
	width = board_width;
	height = board_height;
	number_of_mines = mine_count;
	int num_mines_placed = 0;
	srand(time(NULL));

	revealed = new bool *[height];
	for (int i = 0; i < height; i++){
		revealed[i] = new bool [width];
		for (int m = 0; m < width; m++){
			revealed[i][m] = false;
		}
	}


	//NEED MORE RANDOMNESS
	mined = new bool *[height];
	for (int i = 0; i < height; i++){
		mined[i] = new bool [width];
		for (int m = 0; m < width; m++){
			if (num_mines_placed < number_of_mines && rand() % 2){
				if(rand() % 2){
					num_mines_placed++;
					mined[i][m] = true;
				}
				else{
					mined[i][m] = false;
				}
			}
			else{
				mined[i][m] = false;
			}
		}
	}

	flagged = new bool *[height];
	for (int i = 0; i < height; i++){
		flagged[i] = new bool [width];
		for (int m = 0; m < width; m++){
			flagged[i][m] = false;
		}
	}
}
int MineSweeperBoard::get_width() const{
	return width;
}
int MineSweeperBoard::get_height() const{
	return height;
}
int MineSweeperBoard::adjacent_flags(Position p) const
{
	PositionList neighbors = adjacent(p);

	// Loop over the neighbors.
	int adjacent_count = 0;
	for (int i = 0; i < neighbors.size(); i++) {
		Position adj = neighbors.get(i);
		// If it's flagged, increase the count.
		if (flagged[adj.y()][adj.x()])
			adjacent_count++;
	}
	return adjacent_count;
}
void MineSweeperBoard::reveal(Position p){
	int x = p.x();
	int y = p.y();

	if (!revealed[y][x]){
		revealed[y][x] = true;
		if (adjacent_flags(p) == adjacent_mines(p)){

			PositionList neighbors = adjacent(p);
			for (int i = 0; i < neighbors.size(); i++) {
				Position adj = neighbors.get(i);
				x = adj.x();
				y = adj.y();
				if (!flagged[y][x]){
					reveal(adj);
				}
			}
		}
	}
}


//ALL VERIFYS work, or look like they work
//Verify
bool MineSweeperBoard::flag(Position p){
	int x = p.x();
	int y = p.y();
	//if flag at p then remove flag and return flase
	if (flagged[y][x]){
		flagged[y][x] = false;
		return false;
	}

	//if no flag, then put on and return true
	if (!flagged[y][x]){
		flagged[y][x] = true;
		return true;
	}

}
//Verify
void MineSweeperBoard::display(ostream &out) const{
	//use appearence(p)
	//loop over number of points using width and height
	int w = width;
	int h = height;

	int total = w * h;

	//first 2 lines
	out << "    |";  
	for (int i = 0; i < w; i++){
		out << "  " << i;
	}
	out << endl;
	out << "----+";
	for (int i = 0; i < w; i++){
		if(i >= 10){
			out << "-";
		}
		out << "---";
	}
	out << endl;
	//end 2 lines

	for (int i = 0; i < h; i++){
		if (i < 10){
			out << " ";
		}
		out << " " << i << " |";
		for (int m = 0; m < w; m++){
			Position my_point(m,i);
			if(m >= 10){
				out << " ";
			}
			out << "  " << appearance(my_point);
		}
		out << endl;
	}


}
//Verify
bool MineSweeperBoard::lost() const{
	//if mined[y][x] == true and revealed[y][x] == true then player losses

	for (int i = 0; i < height; i++){
		for (int m = 0; m < width; m++){
			if (mined[i][m]){
				if (mined[i][m] == revealed[i][m]){
					return true;
				}
			}
		}
	}

	return false;


}
//Verify
void MineSweeperBoard::give_up(){
	//reveal entire board
	//quit game
	//lost() == true

	for (int i = 0; i < height; i++){
		for (int m = 0; m < width; m++){
			revealed[i][m] = true;
		}
	}


}



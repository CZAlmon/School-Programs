// CS 215, Spring 2014
// Carmon Zachary Almon
// Programming assignment 4
// Last updated 29 April, 2014
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "board.h"
//#include "high_score.h"


// NOTE TO GRADER!!!!!!!!!!!!!!!!!!!!!!!!
// I attempted the extra credit but it proved to difficult for me with errors and whatnot
// So i have commented all high_score list code out, you DO NOT have to worry about grading it.

using namespace std;

void pause_215(bool have_newline);

/* main() - Main driver of program, get users input call most functions on board.
 *
 * Description: 
 *		  Get user input for width and height (5 to 20 inclusive) and get # of mines (0 to width*height inclusive) Make board to this deminsions
 *		  Get time point here
 *		  Display board to user
 *		  start main while(!lost() && !win()) loop. Ask user for [R]eveal [F]lag [G]ive up
 *		  [R]eveal - ask for the coordinates from user, not going over bounds make a new position object with this coordinates then reveal(p) this object then board.display() to reveal board.
 *		  [F]lag - ask for the coordinates from user, not going over bounds make a new position object with this coordinates then flag(p) this object then board.display() to reveal board.
 *		  [G]ive up - call board.give_up() then board.display() to reveal board. give_up() will break loop automatically because .lost() will become true.
 *		  Out of loop - get time point
 *		  If won, tell user they won
 *		  if lost, tell user they lost
 *		  tell user thier time from timepoint 2 - timepoint 1 in seconds
 *		  
 * Inputs:
 *		  User input for:
 *				Width, Height, # of Mines
 *				[R] [F] [G] for reveal, flag or give up respectively
 *				X and Y value for revealed
 *				X and Y value for revealed
 *				
 *				
 *				
 * Outputs:
 *		  Displays to user the board, and directions on what to enter
 *
 * Side-Effects:
 *		 None
 *		   
 * Exceptions:		
 *		  
 * Notes:  
 */
int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	string name;
	int board_height;
	int board_width;
	int mines_number;
	string input;
	int pos_x;
	int pos_y;

	cout << "Welcome to MineSweeper 215!" << endl;

	//Board size loop
    cout << "The Height and Width must be at least 5 units and no more than 20" << endl;
	while (cin){
		cout << "How large should the board be (width height)? ";
        cin >> board_width >> board_height;

		
		if (cin.fail()){
			cin.clear();
			cout << "  Please enter two numbers separated by a space." << endl;
		}
		else if(board_height >= 5 && board_height <= 20 && board_width >= 5 && board_width <= 20){
			break;
		}
		else if(board_width < 5 || board_width > 20){
			cout << "Please enter the width between 5 and 20" << endl;
		}
		else if(board_height < 5 || board_height > 20){
			cout << "Please enter the height between 5 and 20" << endl;
		}
	}

	int total_board_size = board_height * board_width;



	//Mine number loop
	cout << "Enter the number of mines (between 0 and " << total_board_size << "): ";
	while (cin){
        cin >> mines_number;
	
		if (cin.fail()){
			cin.clear();
		}
		else if (mines_number >= 0 || mines_number <= total_board_size){
			break;
		}
		else{
			cout << "Please enter a number between 0 and " << total_board_size << ": ";
		}
	}


	// Create a board of that size.
	// TODO: change these numbers.
	MineSweeperBoard board(board_width, board_height, mines_number);

	// Compute and display how much time the game took.
	time_t start_time = time(NULL);

	cout << endl;
	board.display(cout);
	cout << endl;

	while (!board.lost() && !board.won()){

		// TODO: Ask the user to [R]eveal, [F]lag, or [G]ive up.
		// The first two commands also require a Position, so
		// you may need to ask for x and y coordinates as well.
		// TODO: Then perform that command by calling the appropriate
		// method.


		cout << "[R]eveal, [F]lag, or [G]ive up." << endl;
		cin >> input;
		if (input == "R" || input == "r"){
			
			while (cin){
				cout << "What position? (x y): ";
				cin >> pos_x >> pos_y;

		
				if (cin.fail()){
					cin.clear();
					cout << "  Please enter two numbers separated by a space." << endl;
				}
				else if(pos_x >= board_width || pos_x < 0){
					cout << "Please enter a x value between 0 and " << board_width - 1 << endl;
				}
				else if(pos_y >= board_height || pos_y < 0){
					cout << "Please enter a y value between 0 and "  << board_height - 1 << endl;
				}
				else{
					Position new_pos(pos_x, pos_y);
					board.reveal(new_pos);
					cout << endl;
					board.display(cout);
					cout << endl;
					break;
				}
			}

		}
		else if (input == "F" || input == "f"){
			
			while (cin){
				cout << "What position? (x y): ";
				cin >> pos_x >> pos_y;

		
				if (cin.fail()){
					cin.clear();
					cout << "  Please enter two numbers separated by a space." << endl;
				}
				else if(pos_x >= board_width || pos_x < 0){
					cout << "Please enter a x value between 0 and " << board_width - 1 << endl;
				}
				else if(pos_y >= board_height || pos_y < 0){
					cout << "Please enter a y value between 0 and "  << board_height - 1 << endl;
				}
				else{
					Position new_pos(pos_x, pos_y);
					board.flag(new_pos);
					cout << endl;
					board.display(cout);
					cout << endl;
					break;
				}
			}


		}
		else if(input == "G" || input == "g"){
			board.give_up();
			board.display(cout);
		}

		//Needed to repeat loop if one of these (or thier lower case) was not entered.
		else{
			cout << "Please input only [R], [F], or [G]" << endl;
		}



	}
	// Compute and display how much time the game took.
	time_t end_time = time(NULL);
	// Compute and display how much time the game took.
	time_t total_time = end_time - start_time;


	// TODO: Tell the user whether they won or lost.
	if (board.won()){
		cout << "You won" << endl;
		//cout << "Please enter your name: " << endl;
		//cin >> name;
		//cout << endl;

		////Reading in for High Score List. Seperated by #
		////Keep (name, time, size, and number of mines)
		////Organize by time

		//High_score score();

		//score.read_scores();

		//score.add_score(name, total_time, total_board_size, mines_number);

		//score.write_score();

		//cout << "Top 10 on the High Score List:" << endl;

		//score.display_score(cout);

	}
	else if(board.lost()){
		cout << "You lost" << endl << endl;
		board.give_up();
		board.display(cout);
	}
	cout << endl << "Your total time played was: " << total_time << endl;

	pause_215(true);
	return 0;
}

void pause_215(bool have_newline)
{
    if (have_newline) {
        // Ignore the newline after the user's previous input.
        cin.ignore(200, '\n');
    }

    // Prompt for the user to press ENTER, then wait for a newline.
    cout << endl << "Press ENTER to continue." << endl;
    cin.ignore(200, '\n');
}

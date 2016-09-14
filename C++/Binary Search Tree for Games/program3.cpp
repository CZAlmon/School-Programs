/*course: CS216-003 
  Project: Project 3
  Date: 11/10/2014 
  Purpose: To store a list of computer games using binary search trees
  Author: Carmon Zachary Almon 
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "search_tree.h"
#include "elements.h"
using namespace std;



/*
	argc is the amount of pieces of information passed to the program. purely an integar
	argv is the pieces of information passed to the program.
*/

int main(int argc, char *argv[]){

	//The user input for commands
	string user_input_commands;
	string user_input_string;
	int user_input_year;
	double user_input_score = 1;
	int sort_result;
	char a;

	//Input variables from the file to be used a few times to input from file to program
	string file_title_used_to_insert_from_file;
	int file_year_used_to_insert_from_file;
	double file_score_used_to_insert_from_file;

	

	//To make sure that only 1 piece of information has been passed to the program
	if(argc != 2){
		return -1;
	}

	fstream File_name;							//Variable for the file name
	
	File_name.open(argv[1]);				//Open the file name passed through argv[1]

	//Test to see if file was opened. If not then this will return -2 indicating the file cannot be opened, or was not opened.
	if(!File_name.is_open()){
		cout << argv[1] << "file cannot be opened" << endl;
		return -2;
	}

	
	//Open class element This is dynamically allocated internally
	Binary_tree game_of_trees;

	//Loop to bring lines in from the file and extract them to the program to add to or remove the lines
	while(!File_name.eof()){
		
		getline(File_name, file_title_used_to_insert_from_file, ':'); //get title minus the :
		
		File_name >> file_year_used_to_insert_from_file; // get the year minus the spaces

		File_name >> file_score_used_to_insert_from_file; // get the score minus the spaces

		game_of_trees.Insert_node(file_title_used_to_insert_from_file, file_year_used_to_insert_from_file, file_score_used_to_insert_from_file);
		
		File_name.ignore(); //leave off the new line character from the last part of the file line here
	}

	//File is no longer needed
	File_name.close();


	while(true){

		//User command.
		cout << " __________________________________________________ " << endl;
		cout << "|                                                  |" << endl;
		cout << "| 1. ---> Insert the game title, year, and score   |" << endl;
		cout << "| 2. ---> Search games, Case sensitive             |" << endl;
		cout << "| 3. ---> List all games, Choose the order         |" << endl;
		cout << "| 4. ---> Modify existing user scores              |" << endl;
		cout << "| 5. ---> Quit                                     |" << endl;
		cout << "|                                                  |" << endl;
		cout << " __________________________________________________ " << endl;
		
		cin >> user_input_commands;
		cin.ignore();

		if(user_input_commands == "1"){
			cout << "What game title: ";
			
			getline(cin, user_input_string); //get total line so multiple word titles are recieved
			cin.clear();
			cout << endl << "What is the year the game was made? ";
			cin >> user_input_year; //get year

			//Loop over till users score input is between 0.0 and 10.0
			while((user_input_score >= 0.0) && (user_input_score <= 10.0)){
				cout << endl << "What is the high score for the game? ";
				cin >> user_input_score;
				//checks for if the score is within parameters
				if(user_input_score <= 0.0){
					cout << endl << "Please enter a number greater or equal to 0" << endl;
				}
				else if(user_input_score >= 10.0){
					cout << endl << "Please enter a number less or equal to 10" << endl;
				}
				else{
					break;
				}

			}

			game_of_trees.Insert_node(user_input_string, user_input_year, user_input_score);
		}
		else if(user_input_commands == "2"){
			cout << "What to search? ";
			cin >> user_input_string; //Get user input string here
			sort_result = 0; //sort results get reset to 0
			//call tree search on that string and the sort results passed by reference
			game_of_trees.Tree_search(user_input_string, sort_result);
			//passed by reference the results get updated to come out here
			cout << endl << "There were " << sort_result << " matches found." << endl;
		}
		else if(user_input_commands == "3"){
			a = '1'; //for the switch statement/while loop to start
			while(a != '4'){

				cout << "1: Preorder" << endl;
				cout << "2: Postorder" << endl;
				cout << "3: Inorder" << endl;
				cout << "4: Back to main menu" << endl;
				//get user input here
				cin >> a;

				switch(a){
				case '1':
					//Preorder, list total number of games then print off the games from the member function/recursion, assign 4 to a so loop quits
					cout << "Total number of games: " << game_of_trees.get_number_of_nodes() << endl;
					cout << "Game list (preorder):" << endl << endl;
					a = '4';
					game_of_trees.preorder_print();
					break;
				case '2':
					//Postorder, list total number of games then print off the games from the member function/recursion, assign 4 to a so loop quits
					cout << "Total number of games: " << game_of_trees.get_number_of_nodes() << endl;
					cout << "Game list (postorder):" << endl << endl;
					a = '4';
					game_of_trees.postorder_print();
					break;
				case '3':
					//Inorder, list total number of games then print off the games from the member function/recursion, assign 4 to a so loop quits
					cout << "Total number of games: " << game_of_trees.get_number_of_nodes() << endl;
					cout << "Game list (inorder):" << endl << endl;
					game_of_trees.inorder_print();
					a = '4';
					break;

				case '4':
					break;
				default:
					cout << "Please enter 1,2,3, or 4" << endl;
				}
			}
		}

		else if(user_input_commands == "4"){
			cout << "What Title to Modify? ";
			//get title, full title multiple words are possible
			getline(cin, user_input_string);
			cin.clear();
			cout << endl << "What score to add? ";
			cin >> user_input_score; //get new score to add
			cout << endl;
			//call function with those 2 parameters
			game_of_trees.modify_user_scores(user_input_string, user_input_score);
			
		}
		else if(user_input_commands == "5"){
			//simply break from function
			break;
		}
		else{
			cout << "Please enter 1, 2, 3, 4, or 5 for your choice." << endl;
		}
	}
	//end program, can only get here from user command 5
	
	return 0;

}

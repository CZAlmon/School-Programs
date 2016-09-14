/*course: CS216-003 
  Project: Project 2
  Date: 10/5/2014 
  Purpose: To create and manage a linked list given
  Author: Carmon Zachary Almon 

  NOTE: Some code was used from .cpp files given by Yi Pike, CS 216 professor at UKY.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "program_2_header.h"
using namespace std;


/*
	argc is the amount of pieces of information passed to the program. purely an integar
	argv is the pieces of information passed to the program.
*/

int main(int argc, char *argv[]){

	//The user input for letters/commands
	string user_input;
	//Input string from the file to be used a few times to input from file to program
	string file_string_used_to_insert_from_file;
	//counter to use in the input from file to the program
	int counter_used_to_insert_from_file = 1;

	//The lines the user will input when thier choice is "I n"
	string user_input_lines;
	//The line number to determine where the line will go
	int user_input_line_number;



	//To make sure that only 1 piece of information has been passed to the program
	if(argc != 2){
		return -1;
	}

	fstream File_name;							//Variable for the file name
	
	File_name.open(argv[1]);				//Open the file name passed through argv[1]

	//Test to see if file was opened. If not then this will return -2 indicating the file cannot be opened, or was not opened.
	if(!File_name.is_open()){
		cout << argv[1] << " file cannot be opened" << endl;
		return -2;
	}

	//Linkedlist element
	My_Linked_List Program_2_link_list;

	//Loop to bring lines in from the file and extract them to the program to add to or remove the lines
	while(!File_name.eof()){
		//Get each line through each loop
		getline(File_name, file_string_used_to_insert_from_file);
		//Insert starting with 1 ending with the last line of file
		Program_2_link_list.Insert_line(file_string_used_to_insert_from_file, counter_used_to_insert_from_file);
		//counter to determine the line placement, which here will be in order of 1 to end of file.
		counter_used_to_insert_from_file++;
	}
	//File is no longer needed
	File_name.close();

	//User command.
	cout << " __________________________________________________ " << endl;
	cout << "|                                                  |" << endl;
	cout << "| I n ---> Insert the line of text to line n       |" << endl;
	cout << "| D n ---> Delete line n                           |" << endl;
	cout << "| L   ---> List all lines                          |" << endl;
	cout << "| Q   ---> Save into a file and quit               |" << endl;
	cout << " __________________________________________________ " << endl;

	//Loop over user input. Only break when user enters "Q"
	while(cin >> user_input){
		//If user enters I then
		if(user_input == "I"){
			//Get the number that was entered after the I. cin deleminates the space
			cin >> user_input_line_number;
			//Determine if line is too small or too big.
			if(user_input_line_number < 1){
				cout << "The line number is too small" << endl;
			}
			//If the line input is greater then the number of elements then do nothing.
			else if(Program_2_link_list.number_of_elements() < user_input_line_number){
				cout << "The line number is too big" << endl;
			}
			else{
				cout << "Next line of text to insert:" << endl;
				cin.get(); //Clear cin
				getline(cin, user_input_lines); //Getline the user inputs
				//insert
				Program_2_link_list.Insert_line(user_input_lines, user_input_line_number);
			}
		}
		else if(user_input == "D"){
			//Get the number that was entered after the D. cin deleminates the space
			cin >> user_input_line_number;
			//delete
			Program_2_link_list.Delete_line(user_input_line_number);

		}
		else if(user_input == "L"){
			//print the list out
			Program_2_link_list.Print_the_list();

		}
		else if(user_input == "Q"){
			break;
		}
		else{
			cout << "Please enter I n, D n, L, or Q exactly" << endl;
		}

	}

	//Open file to print to/export out to
	File_name.open(argv[1], ios::out);
	//Loop over the Linked list starting with the head element, ending when the element is NULL, each loop increasing through the linkedlist
	for(My_list_elements const* List_element = Program_2_link_list.get_head(); List_element != NULL; List_element = List_element->getNext()){
		//Get the line of each list element, and export to file, end with a new line
		File_name << List_element->Get_Line() << endl;

	}
	//close file and save
	File_name.close();

	return 0;
}





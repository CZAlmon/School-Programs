/*course: CS216-003 
  Project: Project 4
  Date: 12/8/2014 
  Purpose: To convert a infix expression to postfix notation
  Author: Carmon Zachary Almon 
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdio.h> // <------->
#include <string.h>//These two are needed for strspn()
#include "class.h"
using namespace std;

bool check_infix_expression(vector<string> infix_vector_here);
bool is_number(const string expressionPart);

/*
	argc is the amount of pieces of information passed to the program. purely an integar
	argv is the pieces of information passed to the program.
*/

int main(int argc, char *argv[]){

	//The user input for commands
	vector<string> infix_vector; 
	vector<string> postfix_vector;
	int user_number = 0;						//Number to either put infix, convert, evaluate or exit
	string user_input_string;					//string that should be an infix string
	string user_tokens;							//tokens that will be put into infix vector
	stringstream user_input;					//stringstream that converts infic string to vector
	string postfix_expression;					//will get postfix string to display

	int counter = 0;							//counter to make sure user has a infix vector, postfix vector to convert or evaluate respectively
	double my_value = 0;						//value for evaluating

	postfix_class my_postfix_expression;		//postfix class object
	

	//To make sure that nothing has been passed to the program
	if(argc != 1){
		return -1;
	}

	//while users input is 1, 2, 3, or 4 (0 is used to make sure loop iterates the first time)
	while(user_number >= 0 || user_number <= 4){

		cout << "*********************************************************" << endl;
		cout << "1. Read in an infix expression in infix notation.        " << endl << endl;
		cout << "2. Convert current infix expression to postfix notation. " << endl;
		cout << "   Won't work if no expression has been read in yet.     " << endl << endl;
		cout << "3. Evaluate the current postfix expression.              " << endl;
		cout << "   Won't work if no expression has been read in yet or   " << endl;
		cout << "   the current infix expression has not been converted.  " << endl << endl;
		cout << "4. Exit.                                                 " << endl;
		cout << "*********************************************************" << endl;

		//get user input for decision
		cin >> user_number;
		
		
		//first iteration, if they choose 0 again this will display nothing else
		if(user_number == 0){

			cout << "Please enter a number between 1 and 4" << endl;

		}
		else if(user_number == 1){ //first choice

			cout << "Please enter an infix expression" << endl;

			cin.ignore(500, '\n');				//Used for getline
			getline(cin, user_input_string);	//getline the infix string
			cin.clear();						//used for getline

			user_input.str(user_input_string);	//convert from string to stringstream

			while(!user_input.eof()){           //loop while stringstream isnt at end of file

				user_input >> user_tokens;		//parse on the spaces, put in tokens

				infix_vector.push_back(user_tokens);	//put tokens into vector

			}

			counter = 1;						//they have set a infix vector so set counter to 1

			if(!check_infix_expression(infix_vector)){     //check to make sure valid expression
				cout << "Please try again, your infix expression was not in infix notation" << endl;
				counter = 0;					//its not valid, set counter to 0.
			}
					
		}
		else if(user_number == 2){    // second choice
			//if counter is at 1, then there is a correct infix expression, otherwise go back
			if(counter == 1){
				//call postfix object, convert the vector into the class objects vector
				my_postfix_expression.convert_from_infix_to_postfix(infix_vector);
				//display string that was input (infix string from user directly)
				cout << "Infix Expression: " << user_input_string << endl;
				//get the string from postfix object, will be a postfix notation string
				postfix_expression = my_postfix_expression.get_postfix_string();
				//display
				cout << "Postfix Expression: " << postfix_expression << endl;
				//set counter to 2, since object is now in postfix notation we can move on.
				counter = 2;
			}
			else{                 // no infix expression, go back to 1
				cout << "Please enter an infix expression" << endl;
			}
		}
		else if(user_number == 3){              //third choice
			//if counter has been set to 2, go here otherwise go back
			if(counter == 2){
				//output infix
				cout << "Infix Expression: " << user_input_string << endl;
				//output postfix
				cout << "Postfix Expression: " << my_postfix_expression.get_postfix_string() << endl;
				//output evaluation of the postfix expression from "object.member function"
				cout << "Evaluation of Postfix Expression: " << my_postfix_expression.evaulte_postfix() << endl;

				//reset after this. clear old expression
				cout << "Either enter a new expression, Exit, or evaluate again" << endl;
				cout << "Old expression has now been cleared" << endl;
				
				//clear infix vector
				if(infix_vector.size() != 0){
					for(int m = infix_vector.size(); m > 0; m--){
						infix_vector.pop_back();
					}
				}
				//reset counter, string and stringstream
				counter = 0;
				user_input_string = "";
				user_input.str("");
				user_input.clear();

				//clear postfix object vector
				my_postfix_expression.clear_postfix();


			}
			else{ //if counter isnt set to 2, go back
				cout << "Please enter an infix expression and convert it to postfix" << endl;
			}
			
		}//at choice 4, exit program
		else if(user_number == 4){

			break;

		}
		else{
			//if anything other then 0-5 is input, output here
			cout << "Please enter a number between 1 and 4" << endl;

		}
		//clear cin error's
		cin.clear();
		cout << endl << endl;

	}

	
	return 0;

}

//Function to check for infix notation
//Her spec sheet only said to check for spaces, since we can assume currect notation other than spacing.
//this function only checks for spacing because of this.
bool check_infix_expression(vector<string> infix_vector_here){
	//vector size and a string to hold tokens
	int myvectorsize = infix_vector_here.size();
	string my_token;
	//loop over vector and get each token to check to make sure its valid
	for(int i = 0 ; i < myvectorsize ; i++){

		my_token = infix_vector_here[i];

		if(my_token == "("){
			//Do nothing if it is '(' only then go to next part of vector
		}
		else if(my_token == ")"){
			//Do nothing if it is ')' only then go to next part of vector
		}
		else if(my_token == "+"){
			//Do nothing if it is '+' only then go to next part of vector
		}
		else if(my_token == "-"){
			//Do nothing if it is '-' only then go to next part of vector
		}
		else if(my_token == "*"){
			//Do nothing if it is '*' only then go to next part of vector
		}
		else if(my_token == "/"){
			//Do nothing if it is '/' only then go to next part of vector
		}
		else if(is_number(my_token)){
			//Do nothing if it is '0123456789' ,(a number consisting of those digits only), only then go to next part of vector
		}
		else{
			return false;		//if this is reached, something is wrong, return false now
		}
	}
	//if loop passes, return true, the infix notation is currect.
	return true;


}
//Function to check if a string is a number.
bool is_number(const string expressionPart){
	//return true if this is a number 0-9 or any combination of those digits, false otherwise.
	bool check = strspn(expressionPart.c_str(), "0123456789") == expressionPart.size();

	return(check);

}
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "class.h"
using namespace std;


//declare vector is all.
postfix_class::postfix_class(){
	postfix_vector;
}

void postfix_class::convert_from_infix_to_postfix(vector<string> infix_vector){

	//vector to hold the tokens to be transfered to CLASS vector LATER, not now. Dont want to work on CLASS vector at the moment
	vector<string> new_postfix_vector;
	//standard variables to hold information (names)
	int tokensize;
	int mysize = infix_vector.size();
	string my_token;
	vector<string> token_operands_stack; //meant operators not operands. This vector is only for "( ) * - + /"
	//OPERANDS GO DIRECTLY TO new_postfix_vector
	
	//main loop. Loop over infix vector given in parameter
	for(int i = 0 ; i < mysize ; i++){
		//set each token as mytoken to operate on 
		my_token = infix_vector[i];

		// if token is ( then put it to the token
		if(my_token == "("){

			token_operands_stack.push_back(infix_vector[i]);

		}
		else if(my_token == ")"){
			//get token vector size
			tokensize = token_operands_stack.size() - 1;
			//loop over token vector from back to front pushing everything to the new vector while poping them back
			//at a ( then stop and pop the ( from the token vector
			while(token_operands_stack[tokensize] != "("){

				new_postfix_vector.push_back(token_operands_stack[tokensize]);


				tokensize--;
				token_operands_stack.pop_back();
			}
			token_operands_stack.pop_back();
			
			//end
		}
		else if(my_token == "+"){
			//Get token vector size
			tokensize = token_operands_stack.size() - 1;

			//If this is the first operator then push it onto the token vector
			if(tokensize == -1){
				token_operands_stack.push_back(my_token);
			}
			//if not then
			else{
				//if tokens are * or / then they need to be pushed onto the new vector first. So push ALL * or / onto new vector before we do anything
				//Loop over token vector at end to begining, if it is * or / then push it to vector, then pop
				while(token_operands_stack[tokensize] != "(" && token_operands_stack[tokensize] != "+" && token_operands_stack[tokensize] != "-"){
					if(token_operands_stack[tokensize] == "*"){
						new_postfix_vector.push_back(token_operands_stack[tokensize]);
						token_operands_stack.pop_back();
					}
					else if(token_operands_stack[tokensize] == "/"){
						new_postfix_vector.push_back(token_operands_stack[tokensize]);
						token_operands_stack.pop_back();
					}
					tokensize--;
				}
				//Now we know there arnt any * or / (They have higher precidence so they go first)
				//If there is a + or a - then push those onto the new vector since they come first, popback, then push the + token we have to token vector
				if(token_operands_stack[tokensize] == "+"){
					new_postfix_vector.push_back(token_operands_stack[tokensize]);
					token_operands_stack.pop_back();
					token_operands_stack.push_back(my_token);
				}
				//If there is a + or a - then push those onto the new vector since they come first, popback, then push the + token we have to token vector
				else if(token_operands_stack[tokensize] == "-"){
					new_postfix_vector.push_back(token_operands_stack[tokensize]);
					token_operands_stack.pop_back();
					token_operands_stack.push_back(my_token);
				}
				//If there is a ( then simply push the token onto the token vector. 
				else if(token_operands_stack[tokensize] == "("){
					token_operands_stack.push_back(my_token);
				}
			}
						
		}
		else if(my_token == "-"){
			//Get token vector size
			tokensize = token_operands_stack.size() - 1;

			//If this is the first operator then push it onto the token vector
			if(tokensize == -1){
				token_operands_stack.push_back(my_token);
			}
			//if not then
			else{
				//if tokens are * or / then they need to be pushed onto the new vector first. So push ALL * or / onto new vector before we do anything
				//Loop over token vector at end to begining, if it is * or / then push it to vector, then pop
				while(token_operands_stack[tokensize] != "(" && token_operands_stack[tokensize] != "+" && token_operands_stack[tokensize] != "-"){
					if(token_operands_stack[tokensize] == "*"){
						new_postfix_vector.push_back(token_operands_stack[tokensize]);
						token_operands_stack.pop_back();
					}
					else if(token_operands_stack[tokensize] == "/"){
						new_postfix_vector.push_back(token_operands_stack[tokensize]);
						token_operands_stack.pop_back();
					}
					tokensize--;
				}
				//Now we know there arnt any * or / (They have higher precidence so they go first)
				//If there is a + or a - then push those onto the new vector since they come first, popback, then push the - token we have to token vector
				if(token_operands_stack[tokensize] == "+"){
					new_postfix_vector.push_back(token_operands_stack[tokensize]);
					token_operands_stack.pop_back();
					token_operands_stack.push_back(my_token);
				}
				//If there is a + or a - then push those onto the new vector since they come first, popback, then push the - token we have to token vector
				else if(token_operands_stack[tokensize] == "-"){
					new_postfix_vector.push_back(token_operands_stack[tokensize]);
					token_operands_stack.pop_back();
					token_operands_stack.push_back(my_token);
				}
				//If there is a ( then simply push the token onto the token vector. 
				else if(token_operands_stack[tokensize] == "("){
					token_operands_stack.push_back(my_token);
				}
			}
					
		}

		//Since * and / are the highest precidence, they are a little simpler
		else if(my_token == "*"){
			//Get token vector size
			tokensize = token_operands_stack.size() - 1;
			//If first operator, push it to the token vector
			if(tokensize == -1){
				token_operands_stack.push_back(my_token);
			}
			//if there is a + or - or ( then simply push the * token onto the token vector
			else if(token_operands_stack[tokensize] == "+"){
				token_operands_stack.push_back(my_token);
			}
			//Same as before
			else if(token_operands_stack[tokensize] == "-"){
				token_operands_stack.push_back(my_token);
			}
			//same
			else if(token_operands_stack[tokensize] == "("){
				token_operands_stack.push_back(my_token);
			}
			//Since * and / have the same precidence, you will push the last token to the new vector, pop it from token vector
			//then push the * token to the token vector
			else if(token_operands_stack[tokensize] == "*"){
				new_postfix_vector.push_back(token_operands_stack[tokensize]);
				token_operands_stack.pop_back();
				token_operands_stack.push_back(my_token);
			}
			//Since * and / have the same precidence, you will push the last token to the new vector, pop it from token vector
			//then push the * token to the token vector
			else if(token_operands_stack[tokensize] == "/"){
				new_postfix_vector.push_back(token_operands_stack[tokensize]);
				token_operands_stack.pop_back();
				token_operands_stack.push_back(my_token);
			}
		}
		else if(my_token == "/"){

			//Get token vector size
			tokensize = token_operands_stack.size() - 1;
			//If first operator, push it to the token vector
			if(tokensize == -1){
				token_operands_stack.push_back(my_token);
			}
			//if there is a + or - or ( then simply push the * token onto the token vector
			else if(token_operands_stack[tokensize] == "+"){
				token_operands_stack.push_back(my_token);
			}
			//Same as before
			else if(token_operands_stack[tokensize] == "-"){
				token_operands_stack.push_back(my_token);
			}
			//same
			else if(token_operands_stack[tokensize] == "("){
				token_operands_stack.push_back(my_token);
			}
			//Since * and / have the same precidence, you will push the last token to the new vector, pop it from token vector
			//then push the / token to the token vector
			else if(token_operands_stack[tokensize] == "*"){
				new_postfix_vector.push_back(token_operands_stack[tokensize]);
				token_operands_stack.pop_back();
				token_operands_stack.push_back(my_token);
			}
			//Since * and / have the same precidence, you will push the last token to the new vector, pop it from token vector
			//then push the / token to the token vector
			else if(token_operands_stack[tokensize] == "/"){
				new_postfix_vector.push_back(token_operands_stack[tokensize]);
				token_operands_stack.pop_back();
				token_operands_stack.push_back(my_token);
			}
		}
		else{

			//This will only go if the token is a number. Simply push it to the new vector
			new_postfix_vector.push_back(my_token);

		}
		

	}

	//out of loop
	//After main loop, check to see if token vector is clear, if not push the contents back to new vector
	if(token_operands_stack.size() == 0){
		//done nothing to be done here.
	}
	else{
		tokensize = token_operands_stack.size() - 1;
		while(tokensize != -1){
			new_postfix_vector.push_back(token_operands_stack[tokensize]);
			tokensize--;
		}
	}
	//assign new vector to the postfix vector from class. DONE
	postfix_vector = new_postfix_vector;

}
double postfix_class::evaulte_postfix(){
	//standard variables. Names are what they are for.
	int mysize = postfix_vector.size();
	string my_token;
	
	string top_of_stack;
	int top_of_stack_num;
	string second_of_stack;
	int second_of_stack_num;

	int new_number_to_add_to_stack;
	string new_string_to_add_to_stack;

	vector<string> token_operands_stack;
	int tokensize;

	//Needs an intial value since it is being returned. -100000000 is a big random enough number it serves to be an error code.
	double postfix_value = -100000000;


	//Loop over postfix vector
	//Start at 0 and work up to size. Since it is stops at less then size, this works.
	//Here is how the loop works, as each if is the same except for the operator:
	//Loop over vector until an operator is encountered. Push all operands to the stack.
	//Get top of stack, and the second from the top of stack. they are what we need to operate on when we encounter a operator
	//pop back the operand stack twice for those 2 numbers.
	//convert the string numbers to ints
	//Add, subtract, Multiply, or Divide the numbers. THIS IS THE ONLY STEP THAT WILL VARY FROM THE IF STATEMENTS
	//convert the new int (from the old 2 and operator) to a string, and push it back on top of the stack of operands
	//contine with loop
	for(int i = 0 ; i < mysize ; i++){
		//get each token
		my_token = postfix_vector[i];
		//each if is the same except what operator they use (+ - * /)
		if(my_token == "+"){
		//Get token stack size. We can safely assume this will not be first since it will correctly be in postfix (from being in infix) notation
			tokensize = token_operands_stack.size() - 1;
			
			top_of_stack = token_operands_stack[tokensize];
			tokensize = tokensize - 1;
			second_of_stack = token_operands_stack[tokensize];

			token_operands_stack.pop_back();
			token_operands_stack.pop_back();

			top_of_stack_num = string_to_number(top_of_stack);
			second_of_stack_num = string_to_number(second_of_stack);

			new_number_to_add_to_stack = second_of_stack_num + top_of_stack_num;
			new_string_to_add_to_stack = number_to_string(new_number_to_add_to_stack);

			token_operands_stack.push_back(new_string_to_add_to_stack);

		}
		else if(my_token == "-"){
		//Get token stack size. We can safely assume this will not be first since it will correctly be in postfix (from being in infix) notation
			tokensize = token_operands_stack.size() - 1;

			top_of_stack = token_operands_stack[tokensize];
			tokensize = tokensize - 1;
			second_of_stack = token_operands_stack[tokensize];

			token_operands_stack.pop_back();
			token_operands_stack.pop_back();

			top_of_stack_num = string_to_number(top_of_stack);
			second_of_stack_num = string_to_number(second_of_stack);

			new_number_to_add_to_stack = second_of_stack_num - top_of_stack_num;
			new_string_to_add_to_stack = number_to_string(new_number_to_add_to_stack);

			token_operands_stack.push_back(new_string_to_add_to_stack);

		}
		else if(my_token == "*"){
		//Get token stack size. We can safely assume this will not be first since it will correctly be in postfix (from being in infix) notation
			tokensize = token_operands_stack.size() - 1;

			top_of_stack = token_operands_stack[tokensize];
			tokensize = tokensize - 1;
			second_of_stack = token_operands_stack[tokensize];

			token_operands_stack.pop_back();
			token_operands_stack.pop_back();

			top_of_stack_num = string_to_number(top_of_stack);
			second_of_stack_num = string_to_number(second_of_stack);

			new_number_to_add_to_stack = second_of_stack_num * top_of_stack_num;
			new_string_to_add_to_stack = number_to_string(new_number_to_add_to_stack);

			token_operands_stack.push_back(new_string_to_add_to_stack);

		}
		else if(my_token == "/"){
		//Get token stack size. We can safely assume this will not be first since it will correctly be in postfix (from being in infix) notation
			tokensize = token_operands_stack.size() - 1;

			top_of_stack = token_operands_stack[tokensize];
			tokensize = tokensize - 1;
			second_of_stack = token_operands_stack[tokensize];

			token_operands_stack.pop_back();
			token_operands_stack.pop_back();

			top_of_stack_num = string_to_number(top_of_stack);
			second_of_stack_num = string_to_number(second_of_stack);

			new_number_to_add_to_stack = second_of_stack_num / top_of_stack_num;
			new_string_to_add_to_stack = number_to_string(new_number_to_add_to_stack);

			token_operands_stack.push_back(new_string_to_add_to_stack);

		}
		//The only else that is different. This will only happen when the token is a number, push it to the stack of operands.
		else{
			token_operands_stack.push_back(my_token);
		}
		

	}
	//the last value in the operand stack is the value we want. convert to int and put it in the variable, return it. pop back the token operand stack
	postfix_value = string_to_number(token_operands_stack[0]);
	token_operands_stack.pop_back();

	return postfix_value;

}

//return postfix vector
vector<string> postfix_class::get_postfix(){
	return postfix_vector;
}
//loop over vector, store in a string, return string
string postfix_class::get_postfix_string(){

	string vector_string = "";
	int mysize_here = postfix_vector.size();
	//Loop over vector, add all tokens to string and add a space inbetween them
	for(int i = 0 ; i < mysize_here ; i++){

		vector_string.append(postfix_vector[i]);
		vector_string.append(" ");

	}
	//return string here
	return vector_string;
}
//return true if a number (string) consists only of digits 0-9
bool postfix_class::class_is_number(const string expressionPart){

	bool check = strspn(expressionPart.c_str(), "0123456789") == expressionPart.size();

	return(check);
}
//converts int to string, returns string
string postfix_class::number_to_string(int number){

	stringstream ss;
	ss << number;
	return ss.str();

}
//converts string to int, returns int
int postfix_class::string_to_number(string text){

	stringstream ss(text);
	int result;
	ss >> result;

	return result;

}
//loop over postfix vector, pop back clearing it all
void postfix_class::clear_postfix(){
	//loop over vector
	int mysize = postfix_vector.size();
	//popback every entry
	for(int i = mysize; i > 0; i--){
		postfix_vector.pop_back();
	}

}







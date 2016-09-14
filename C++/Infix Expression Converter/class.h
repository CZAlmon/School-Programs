#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
using namespace std;


class postfix_class
{
private:
	//vector
	vector<string> postfix_vector;

public:
	//constructor, declare vector only
	postfix_class();
	//convert infix vector to postfix vector
	void convert_from_infix_to_postfix(vector<string>);
	//evaluate vector here, return value
	double evaulte_postfix();
	//return postfix vector
	vector<string> get_postfix();
	//return postfix string here
	string get_postfix_string();
	//same as is_number function, but this is a member function. checks to make sure a string is a number
	bool class_is_number(const string expressionPart);
	//int to string converting function
	string number_to_string(int);
	//string to int converting function
	int string_to_number(string);
	//function to clear postfix vector.
	void clear_postfix();

};





#endif
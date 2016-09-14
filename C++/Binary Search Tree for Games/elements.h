#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <iostream>
#include <string>
using namespace std;

class Binary_tree;

class tree_node
{
private:
	string title;//title
	int year_made;//year
	double highest_score;//score

	tree_node* left;//left node pointer
	tree_node* right;//right node pointer

public:
	tree_node(string, int, double, tree_node*, tree_node*);//node maker

	string Get_title() const;//get title string
	int get_year_made() const;//get year made int
	double get_highest_score() const;//get score double

	void change_highest_score(double new_high_score); //change high score by modify function

    tree_node* getLeft() const; //get left node 
	tree_node* getRight() const;// get right node
	
	friend class Binary_tree;  // gives Binary_tree access
};



#endif
#include <iostream>
#include <string>
#include "elements.h"
using namespace std;
//assigns things to the nodes
tree_node::tree_node(string node_title, int year_game_made, double score_highest, tree_node* left_point, tree_node* right_point){

	title = node_title;
	year_made = year_game_made;
	highest_score = score_highest;

	left = left_point;
	right = right_point;

}
//returns title, year, and score respectively
string tree_node::Get_title() const{
	return title;
}
int tree_node::get_year_made() const{
	return year_made;
}
double tree_node::get_highest_score() const{
	return highest_score;
}
//change highest score
void tree_node::change_highest_score(double new_high_score){

	if(new_high_score > 10.0){
		new_high_score = 10.0;
	}

	highest_score = new_high_score;

}
//returns left and right respectively
tree_node* tree_node::getLeft() const{

	return left;

}
tree_node* tree_node::getRight() const{

	return right;

}
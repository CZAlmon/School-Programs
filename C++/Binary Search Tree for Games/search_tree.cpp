#include <iostream>
#include <string>
#include "search_tree.h"
#include "elements.h"
using namespace std;



Binary_tree::Binary_tree(){
	root = NULL; //start with root being null and number of nodes is 0
	number_of_nodes = 0;
}
Binary_tree::~Binary_tree(){
	//call the recursion on the start, the root
	delete_binary_tree(root);

}
void Binary_tree::delete_binary_tree(tree_node* node){
	//delete the tree recursion function
	if(node == NULL){return;}
	//move through
	delete_binary_tree(node->left);
	delete_binary_tree(node->right);
	//then delete node
	delete node;

}
   
void Binary_tree::Insert_node(string game_title, int year, double score){

	if(score > 10.0){
		score = 10.0;
	}
	//initalize node pointers and nodes found
	tree_node* newNodePtr;
	tree_node* tree_left = NULL;
	tree_node* tree_right = NULL;

	tree_node* previous = NULL;
	tree_node* current = root;
	//if root is null then there is no tree and assign the root. this wont change
	if(root == NULL){
		newNodePtr = new tree_node(game_title, year, score, tree_left, tree_right);
		root = newNodePtr;
	}
	//else 
	else{
		newNodePtr = new tree_node(game_title, year, score, tree_left, tree_right);
		//move through tree depending on the title, is less (before alphabetically) the go left or right for more (after alphabetically)
		while(current != NULL){
			//previous keeps the node to move back to to get the left and right pointer
			previous = current;
			//less
			if(game_title < current->Get_title()){
				current = current->getLeft();
			}
			//more/greater
			else{
				current = current->getRight();
			}
		}
		//get the mode that has the null pointers
		//if less go left and assign next node there
		if(game_title < previous->Get_title()){
			previous->left = newNodePtr;
			number_of_nodes++;
		}
		//if more go right and assign next node there
		else if(game_title > previous->Get_title()){
			previous->right = newNodePtr;
			number_of_nodes++;
		}
		else{
			//Do not assign if there is a game with same title here
			cout << "Same as a game already in tree, try again" << endl;
			return;
		}
	}



}
void Binary_tree::tree_search_rec(tree_node* search_node, string search_title_key, int &number_of_items){
	//Search in order
	//base case
	if(search_node == NULL){return;}
	//left recursion
	tree_search_rec(search_node->left, search_title_key, number_of_items);
	//print node off.
	if(search_title_key == search_node->Get_title().substr(0, search_title_key.length())){
		number_of_items++;
		cout << endl;
		cout << "Name: " << search_node->Get_title() << endl;
		cout << "Year: " << search_node->get_year_made() << endl;
		cout << "High Score: " << search_node->get_highest_score() << endl << endl;
	}
	//right recursion
	tree_search_rec(search_node->right, search_title_key, number_of_items);


}
void Binary_tree::Tree_search(string title_key, int &number_of_items){
	//call recursion on root with title key and pass by reference the number of items found
	tree_search_rec(root, title_key, number_of_items);
	
}

tree_node* Binary_tree::modify_node_finder(tree_node* modify_nodefinder_variable, string modify_title_key){
	//modify recursion finder returns node found to modify
	tree_node* check = NULL; 
	//base case, should never have to return NULL. There are checks before this function to check
	if(modify_nodefinder_variable == NULL){
		return NULL;
	}

	//recursion is preorder to find node the fastest
	//return node found that matches title key
	if(modify_title_key == modify_nodefinder_variable->Get_title().substr(0, modify_title_key.length())){
		return modify_nodefinder_variable;
	}
	//go left recursion
	check = modify_node_finder(modify_nodefinder_variable->left, modify_title_key);
	if(check != NULL){
		return check;
	}
	//go right recursion
	check = modify_node_finder(modify_nodefinder_variable->right, modify_title_key);
	if(check != NULL){
		return check;
	}

	return NULL;
}
void Binary_tree::tree_modify_rec(tree_node* modify_node, string search_title_key, int &number_of_items){
	//base case
	if(modify_node == NULL){return;}
	//in order recursion search
	//left recursion
	tree_modify_rec(modify_node->left, search_title_key, number_of_items);
	//at node if title matches, increase number of nodes found by 1
	if(search_title_key == modify_node->Get_title()){ 
		number_of_items++;
	}
	//right recursion
	tree_search_rec(modify_node->right, search_title_key, number_of_items);


}
void Binary_tree::modify_user_scores(string title_name, double new_game_score){

	//This function has multiple checks to see if only one node or multiple or no nodes found that matches title name given

	int numberof_items = 0;
	//first check, find number of nodes found
	tree_modify_rec(root, title_name, numberof_items);
	tree_node* modify_node;
	//checks here
	if(numberof_items == 0){
		cout << "Game cannot be found try again" << endl;
	}
	//good if this is hit
	else if(numberof_items == 1){
		//another check within this function
		modify_node = modify_node_finder(root, title_name);
		//change node here
		modify_node->change_highest_score(new_game_score);
		//output the nodes propertys
		cout << "Name: " << modify_node->Get_title() << endl;
		cout << "Year: " << modify_node->get_year_made() << endl;
		cout << "New High Score: " << modify_node->get_highest_score() << endl << endl;
		//successfully modified
		cout << "Game successfully modified" << endl;
	}
	//and checks here
	else{
		cout << "Multiple games found, try to be more specific" << endl;
	}


}				

//Print functions here. All work the same. The last 3 with no parameters are public which call the privite recursion
//ones with the root as a parameter which then print off the order.
//Inorder goes in the middle of the 2 recursion calls
//Pre order goes in front of the 2 recursion calls
//post order goes in behind the 2 recursion calls
void Binary_tree::inorder_print_rec(tree_node* in_node){

	if(in_node == NULL){return;}

	inorder_print_rec(in_node->left);
	cout << in_node->Get_title() << endl;
	cout << in_node->get_year_made() << endl;
	cout << in_node->get_highest_score() << endl << endl;
	inorder_print_rec(in_node->right);

}
void Binary_tree::preorder_print_rec(tree_node* pre_node){

	if(pre_node == NULL){return;}
	
	cout << pre_node->Get_title() << endl;
	cout << pre_node->get_year_made() << endl;
	cout << pre_node->get_highest_score() << endl << endl;
	inorder_print_rec(pre_node->left);
	inorder_print_rec(pre_node->right);

}
void Binary_tree::postorder_print_rec(tree_node* post_node){

	if(post_node == NULL){return;}

	inorder_print_rec(post_node->left);
	inorder_print_rec(post_node->right);
	cout << post_node->Get_title() << endl;
	cout << post_node->get_year_made() << endl;
	cout << post_node->get_highest_score() << endl << endl;

}
void Binary_tree::inorder_print(){

	inorder_print_rec(root);

}											
void Binary_tree::preorder_print(){

	preorder_print_rec(root);

}
void Binary_tree::postorder_print(){

	postorder_print_rec(root);

}
//get total number of games within tree. only increases if insert correctly inserts
int Binary_tree::get_number_of_nodes() const{
	return number_of_nodes;
}  




#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H

#include <iostream>
#include <string>
using namespace std;

class tree_node;

class Binary_tree
{
private:
   tree_node* root; 

   int number_of_nodes;

   //All these functions are recursion functions to be used by public functions and only those.
   void inorder_print_rec(tree_node*);//inorder print recursion
   void preorder_print_rec(tree_node*);//preorder print recursion
   void postorder_print_rec(tree_node*);//postorder recursion
   void delete_binary_tree(tree_node*);//delete the tree recursion
   void tree_search_rec(tree_node*, string, int &number_of_items);//search tree and print recursion
   void tree_modify_rec(tree_node*, string, int &number_of_items);//search tree and updated number of nodes found to modify recursion
   tree_node* modify_node_finder(tree_node*, string); //return tree node for modify function recursion

public:
   Binary_tree();
   ~Binary_tree();
   
   void Insert_node(string game_title, int year, double score);		  //insert node
   void Tree_search(string title_key, int &number_of_items);	     //Display all games whose titles match the key passed (Case matters)
   void modify_user_scores(string title_name, double new_game_score);		//Change the high score for a game found
   void inorder_print();											//Print list in order (Alphabetical)
   void preorder_print();										   //Print list preorder
   void postorder_print();										  //Print list post order
   									 

   int get_number_of_nodes() const;     //Number of nodes



};



#endif

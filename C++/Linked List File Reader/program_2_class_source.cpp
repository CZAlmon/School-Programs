//Class source for program_2_header


#include <iostream>
#include <string>
#include "program_2_header.h"



/*
*    My_list_elements Members
*/
//Construct the element
My_list_elements::My_list_elements(string line_element, My_list_elements* next_element){
	line = line_element;
	next = next_element;
}
//Get the line element
string My_list_elements::Get_Line() const{ 
   return line; 
}
//Get the next element in the series
My_list_elements const* My_list_elements::getNext() const{ 
   return next; 
}


/*
*    My_Linked_List Members
*/
//Construct the linkedlist
My_Linked_List::My_Linked_List (){
	head = NULL;
	element_counter = 0;
}
//Insert elements
void My_Linked_List::Insert_line(string line_to_insert, int I_line_number){
	//Counter used for comparison to determine when to quit
	int insert_counter = 1;
	//set of pointers to move through linkedlist and the new node to input in
	My_list_elements* currPtr = head;	
	My_list_elements* prevPtr = NULL;
	My_list_elements* newNodePtr;    
   //loop to move through list
	while(currPtr != NULL && I_line_number > insert_counter){			
		//moving through list
		prevPtr = currPtr;
		currPtr = currPtr->next;
		//counter to find out what line the loop is at
		insert_counter++;												//Counter
	}
	//make new node with line to insert and end at null
	newNodePtr = new My_list_elements(line_to_insert, NULL);
	if(prevPtr == NULL){
		//If this is at the start of the linked list then assign the new node to head
		head = newNodePtr;
	}
	else{
		//Else make the prev pointer point to new node
		prevPtr->next = newNodePtr;     
		//then make new node point to currPtr. increasing the linked list
		newNodePtr->next = currPtr;
	}
	//increase the value of the entire linked list counter by 1 for each call.
	element_counter++;
}
void My_Linked_List::Delete_line(int D_line_number){
	//set of pointers to move through linkedlist
	My_list_elements* currPtr = head;
	My_list_elements* prevPtr = NULL;
	//Counter used for comparison to determine when to quit
	int delete_counter = 1;
	//Loop over the linked list till we reach the line node we want to delete
	while(D_line_number != delete_counter){
		//move through list
		prevPtr = currPtr;
		currPtr = currPtr->next;
		//increase line node for each loop
		delete_counter++;
	}
	//Set the prevPtr to point to the next object bypassing the currPtr
	prevPtr->next = currPtr->next;
	//delete currPtr
	delete currPtr;


	//decrease the value of the entire linked list counter by 1 for each call.
	element_counter--;
}
void My_Linked_List::Print_the_list(){
	//set of pointers to move through linkedlist
	My_list_elements* currPtr = head;
	My_list_elements* prevPtr = NULL;

	//Loop to loop while currPtr is not at the end of the list
	while(currPtr != NULL){
		//moving through list
		prevPtr = currPtr;
		currPtr = currPtr->next;
		//print out the element here
		cout << prevPtr->line << endl; 

	}

}
//return size of linked list
int My_Linked_List::number_of_elements() const{
	return element_counter;
}
//Return head object/start of linkedlist
My_list_elements const*  My_Linked_List::get_head(){
	return head;
}




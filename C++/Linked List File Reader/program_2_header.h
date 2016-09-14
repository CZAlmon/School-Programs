//program_2_header.h

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <string>
using namespace std;

class My_list_elements;

class My_Linked_List
{
private:
   My_list_elements* head; 

   int element_counter;

public:
   My_Linked_List();
   
   void Insert_line(string line, int line_number);
   void Delete_line(int line_number);
   void Print_the_list();
   int number_of_elements() const;     //Number of elements
   My_list_elements const* get_head();


};

class My_list_elements
{
private:
	string line;
	My_list_elements* next;

public:
	My_list_elements(string, My_list_elements*);

	string Get_Line() const;
    My_list_elements const* getNext () const;

	
	friend class My_Linked_List;  // gives My_Link_List access to line and next
};


#endif
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

bool compare_two_values(int a, int b, int x, int y);

bool my_binary_search(vector<int> vec, int size, int number_check, int search_number);


int main(int argc, char *argv[]){

	//To make sure that nothing has been passed to the program
	if(argc != 1){
		return -1;
	}

	//Variables used
	vector<int> MySequence;
	vector<int> MySequence_test;
	int MySequence_Length;
	int placeholder;
	int budget;


	//Get length of sequence as first, and adjust it for the loop
	cin >> MySequence_Length;

	//Cant be more than a million numbers
	if(MySequence_Length < 1 || MySequence_Length > 1000000){
			cout << "Cannot use more than 1,000,000 numbers" << endl;
			return -2;
	}
		
	//loop to get sequence
	for(int i=0; i < MySequence_Length; i++){

		cin >> placeholder;

		//Cant have a number bigger than a billion
		if(placeholder < 1 || placeholder > 1000000000){
			cout << "Cannot use a number more than 1,000,000,000" << endl;
			return -3;
		}

		MySequence.push_back(placeholder);
		
		
	}
	
	//get budget
	cin >> budget;

	//Cant have a budget more than 2 billion and 2
	if(budget < 2 || budget > 2000000002){
			cout << "Cannot use a number more than 2,000,000,002" << endl;
			return -4;
	}

	MySequence_test = MySequence;

	sort(MySequence_test.begin(), MySequence_test.begin()+MySequence_Length);

	int budget_minus_1 = budget - 1;
	int budget_minus_2 = budget - 2;

	int flag = 0;
	bool flag_1 = false;
	int working_a;
	int working_b;

	int x;
	int y;
	

	for(int i = 0; i < MySequence_Length; i++){

		x = MySequence_test[i];
		y = budget - x;

		if(my_binary_search(MySequence_test, MySequence_Length, i, y)){
			if(flag == 1){
				if(compare_two_values(x, y, working_a, working_b)){
					working_a = x;
					working_b = y;

				}
				else{
					//Do nothing because current additions are lower than point currently at.
				}
			}
			else{
				flag = 1;
				working_a = x;
				working_b = y;
			}
		}
		else if(my_binary_search(MySequence_test, MySequence_Length, i, y-1)){
			if(flag == 1){
					//Do nothing, we already have 2 numbers to make m at least
			}
			else if(flag == 2){
				if(compare_two_values(x, y, working_a, working_b)){
					working_a = x;
					working_b = y-1;

				}
				else{
					//Do nothing because current additions are lower than point currently at.
				}
			}
			else{
				flag = 2;
				working_a = x;
				working_b = y-1;
			}
		}
		else if(my_binary_search(MySequence_test, MySequence_Length, i, y-2)){
			if(flag == 1){
					//Do nothing, we already have 2 numbers to make m at least
			}
			else if(flag == 2){
					//Do nothing, we already have 2 numbers to make m-1 at least
			}
			else if(flag == 3){
				if(compare_two_values(x, y, working_a, working_b)){
					working_a = x;
					working_b = y-2;

				}
				else{
					//Do nothing because current additions are lower than point currently at.
				}
			}
			else{
				flag = 3;
				working_a = x;
				working_b = y-2;
			}
		}

	}
	
	


	//OUTPUT Needs to be a + b = c, where a <= b
	//This if statement makes sure it is output correct.
	if(flag == 1 || flag == 2 || flag == 3){
		if(working_a <= working_b){
			//Do nothing, in correct order
		}
		else{
			//switch a to b and b to a.
			placeholder = working_a;
			working_a = working_b;
			working_b = placeholder;
		}
	}

	if(flag == 1){
		cout << working_a << " + " << working_b << " = " << budget << endl;
	}
	else if(flag == 2){
		cout << working_a << " + " << working_b << " = " << budget_minus_1 << endl;
	}
	else if(flag == 3){
		cout << working_a << " + " << working_b << " = " << budget_minus_2 << endl;
	}
	else{
		cout << "NO" << endl;
	}

	

	return 0;

}


/*

	Return true if a-b <= x-y
	This functions checks if a is bigger than b and x is bigger than y.

	it returns true if a-b (or b-a) is bigger than x-y (or y-x)
	The numbers it compares need to ALWAYS be positive. That is why you check which is bigger between the 2.
	In other words, order doesnt matter between a and b and x and y. You want the difference that is positive.

	It compares the ABSOLUTE VALUE of the difference to see which is smaller. That is what is compared.

*/
bool compare_two_values(int a, int b, int x, int y){

	if(a >= b){
		if(x >= y){
			if((a-b) <= (x-y)){
				return true;
			}
			else{
				return false;
			}
		}
		else{
			if((a-b) <= (y-x)){
				return true;
			}
			else{
				return false;
			}
		}
	}
	else{
		if(x >= y){
			if((b-a) <= (x-y)){
				return true;
			}
			else{
				return false;
			}
		}
		else{
			if((b-a) <= (y-x)){
				return true;
			}
			else{
				return false;
			}
		}
	}
	

}

//  Function not needed anymore. Used in the n^2 but not needed anymore.
//
//functions to check if 2 numbers are equal to some number c
//bool check_m(int a, int b, int c){
//
//	if((a+b)==c){
//		return true;
//	}
//	else{
//		return false;
//	}
//}

/*
	binary_search(MySequence_test.begin(), MySequence_test.end(), y)
	my_binary_search(My_sequence_test, My_sequence_length, i, y)


	This is my binary search algorithm.
	It takes the vector to search over, size, number I am at, and the number I am searching for.

	I set the min to 0 and the max to the max size of the vector (minus 1 because I will be indexing the vector)

	I perform a binary search over the size of the vector, not the vector itself.
	I check the number at the size (here is where I index) to compare it to the number I am searching for. 

	If the number is found I check to make sure the number I am at (mid the number of the size) is the same as the check.
	I check this because I do not want x+x=M because I only want 2 different number not the same number twice.

	Only return true or false if I found the number in the binary search. Thats all I need.


*/
bool my_binary_search(vector<int> vec, int size, int number_check, int search_number){

	int min = 0;
	int max = size-1;
	int mid = 0;
	
	while (max >= min){

		// calculate the midpoint for roughly equal partition
		mid = min + ((max - min) / 2);

		//If number is found
		if(vec[mid] == search_number){
			
			//check to see if number is same index as the for loop before.
			if(mid == number_check){
				//check if there is a duplicate number below index
				if(vec[mid-1] == search_number){
					return true;
				}
				//check if there is a duplicate number above index !!! Only when not at max, otherwise out of bounds!
				else if(mid != size-1){
					if(vec[mid+1] == search_number){
						return true;
					}
				}
				//Else false if there is no other number (no duplicate)
				else{
					return false;
				}

			}
			//Else true they arnt the same index
			else{
				return true;
			}

		}
		else if(vec[mid] > search_number){

			max = mid - 1;

		}
		//        ^^^^^^^^^^^^^^^^ Above is the lower array, check to see if a lower d will work
		// determine which subarray to search
		//        Below checks upper array because the sequence is not d-smooth for given d so check higher.
		else{

			// change min index to search upper subarray
			min = mid + 1;


		}
	}
	//if loop completes and has no numbers found, return false
	return false;

}

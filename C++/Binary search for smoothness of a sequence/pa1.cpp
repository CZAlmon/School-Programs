#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

int binary_search(vector<int> A, int imax);
bool is_num_d(vector<int> A, int my_d_value);



int main(int argc, char *argv[]){

	//To make sure that nothing has been passed to the program
	if(argc != 1){
		return -1;
	}

	//Variables used
	vector<int> MySequence;
	vector<int> MySequence_test;
	int MySequence_Length;
	int biggest;
	int placeholder;
	vector<int> MySequence_increasing;

	int the_d_value_output;

	//Get length of sequence as first, and adjust it for the loop
	cin >> MySequence_Length;
	MySequence_Length -= 1;

	//Get first value
	cin >> placeholder;
	MySequence.push_back(placeholder);
	//biggest is the value M
	biggest = placeholder;
	//loop to get sequence
	for(int i=0; i < MySequence_Length; i++){

		cin >> placeholder;

		MySequence.push_back(placeholder);
		
		//add the values up
		biggest += placeholder;
	}
	//add 50 to make M
	biggest += 50;

	MySequence_test = MySequence;

	//To get the time taken for the algorithm
	time_t time_1 = time(NULL);

	//Binary search returns d-value
	the_d_value_output = binary_search(MySequence_test, biggest);

	//To get the time taken for the algorithm
	time_t time_two = time(NULL);
	//To get the time taken for the algorithm
	double seconds = difftime(time_two, time_1);
	

	cout << the_d_value_output << endl;


	return 0;

}


int binary_search(vector<int> A, int imax)
{

	int imax_variable = imax;
	int imin = 1;
	int imid;
	int previous_d_that_worked;
	bool d_smoothness = false;
	
	
	// continue searching while [imin,imax] is not empty
	while (imax_variable >= imin){

		// calculate the midpoint for roughly equal partition
		imid = imin + ((imax_variable - imin) / 2);

		//Check if sequence is D-smooth, for given d
		d_smoothness = is_num_d(A, imid);
      
		//If it is, get the d-value to remember it as the smallest
		if(d_smoothness){
			previous_d_that_worked = imid;
			//Go to lower half of the array to check d-values
			imax_variable = imid - 1;
		}
		//        ^^^^^^^^^^^^^^^^ Above is the lower array, check to see if a lower d will work
		// determine which subarray to search
		//        Below checks upper array because the sequence is not d-smooth for given d so check higher.
		else{

			// change min index to search upper subarray
			imin = imid + 1;
		}
	}
	
	//once the binary search is complete, return the smallest d-value that worked.
	return previous_d_that_worked;
}


bool is_num_d(vector<int> A, int my_d_value){
	
	//B is acting as a stack, its not needed, only the previous and current 
	//values are needed, but I want to save entire new vector just in case I want to check

	vector<int> B;
	int f_value;
	int s_value;

	int difference;
 
	//Go ahead and set the very first value as low as it can go by subtract d from it
	f_value = A[0] - my_d_value;
	B.push_back(f_value);
	
	//start loop at 1 and go from second element to end of vector
	for(size_t i=1; i < A.size(); i+=1){
		//Get next value to work on
		s_value = A[i];
		//Get previous value to see how low to go
		f_value = B[i-1];
		
		if(s_value < f_value){
			//Return false if no matter how much of d you add to s, if f is still bigger, this is false.
			if((s_value + my_d_value) <= f_value){
				return false;
			}
			
			//get difference
			difference = f_value - s_value;
			/*
			add difference plus 1
			Difference will NEVER be equal or over d-value.
			because of the if statement above
			*/
			s_value += difference + 1;

			//pushback adjusted value
			B.push_back(s_value);

		}
		else if(s_value > f_value){
			//Get difference
			difference = s_value - f_value;
			//Difference plus 1 to adjust 1 above previous
			if(difference < my_d_value){
				s_value = (s_value - difference) + 1;
			}
			//difference will be lowest d-value
			else if(difference > my_d_value){
				s_value -= my_d_value;
			}
			//Subtract difference and add one, this is still within d, and will be one above previous
			else{
				s_value = (s_value - difference) + 1;
			}

			//pushback adjusted value
			B.push_back(s_value);

		}
		else{
			//d value will always be at least one, so if s = f then just add one and be done.
			s_value = s_value + 1;
			B.push_back(s_value);
		}
		
	}
	
	return true;
}






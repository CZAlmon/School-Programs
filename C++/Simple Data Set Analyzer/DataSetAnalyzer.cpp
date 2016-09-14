#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>
#include "DataSetAnalyzerHeader.h"

using namespace std;

/* Zach Almon
 * CS 215, Spring 2014
 * Programming assignment 2
 * 7 March, 2014
 *
 * Store a set of data points and compute some of their statistics.
 */


/* Main() - Main function to get user input and call functions/methods
 *
 * Description: 
 *		  Main will loop around getting user input until the user types quit.
 *		  If the input is anything other than numbers, the loop wont continue and will clear errors.
 *		  If the input is a number, the insert method will be called for that input value,
 *		  then the loop will repeat.
 *		  After the user typs "quit" the print method will be called to cout to display what it needs to. 
 *		  Will also print out the mean/median/max/min of the set using try/catch and throwing an
 *		  error when size is 0 or less.
 * Inputs:
 *		  User input for numbers and "quit" to quit loop
 * Outputs:
 *		  Telling user to input numbers and "quit" to quit loop.
 *		  calling print method to output from that function
 *		  Print mean/median/max/min methods of data set, or prints that empty/negative set is detected
 * Side-Effects:
 *		  Calls the insert method to change the array
 *        Calls the print method to output to screen
 * Exceptions:
 *		  When empty set is detected from mean/median/max/min methods print out that it is detected
 * Notes: N/A 
 */
int main()
{
    int failed = test_data_set();
	double input;
	string Line;

    // TODO: Read doubles in a loop and add them to a data set.  Repeat
    //   the loop on invalid input, then end when the user types "quit".
    //   Print the data set before each prompt.
	data_set Newarray;

	while (cin)
    {
        cout << "Enter a number, or \"quit\" to quit: ";
        cin >> input;
	
		if (cin.fail()){
			cin.clear();
			getline(cin, Line);
			if (Line == "quit")
				break;
		}
		else{
			Newarray.insert(input);
		}
	}


    // TODO: Print the final data set, and compute its statistics:
    //   size, mean, minimum, maximum, and median.

	Newarray.print(cout);

	try{
		cout << "This is the Mean: " << Newarray.mean() << endl;
	}
	catch(runtime_error){
		cout << "Empty Set Detected" << endl;
	}
	try{
		cout << "This is the median: " << Newarray.median() << endl;
	}
	catch(runtime_error){
		cout << "Empty Set Detected" << endl;
	}
	try{
		cout << "This is the Maximum: " << Newarray.maximum() << endl;
	}
	catch(runtime_error){
		cout << "Empty Set Detected" << endl;
	}
	try{
		cout << "This is the Minimum: " << Newarray.minimum() << endl;
	}
	catch(runtime_error){
		cout << "Empty Set Detected" << endl;
	}
	
	
	

    pause_215(false);
    return 0;
}


void pause_215(bool have_newline)
{
    if (have_newline) {
        // Ignore the newline after the user's previous input.
        cin.ignore(200, '\n');
    }

    // Prompt for the user to press ENTER, then wait for a newline.
    cout << endl << "Press ENTER to continue." << endl;
    cin.ignore(200, '\n');
}


// TODO: implement all these method stubs!

//DONE
data_set::data_set()
{
	curr_cap = 10;
	curr_size = 0;
	points = new double[curr_cap];
}

//DONE
data_set::data_set(int initial_capacity)
{
	if (initial_capacity < 0){
		throw runtime_error("negative size detected");
	}
	curr_cap = initial_capacity;
	curr_size = 0;
	points = new double[initial_capacity];
}

//DONE
data_set::data_set(const data_set &original)
{
	curr_cap = original.capacity();
	curr_size = original.size();

	points = new double[curr_cap];

	for (int i=0; i<curr_size; i++){
		points[i] = original.points[i];
	}
	

}

//DONE
data_set &data_set::operator=(const data_set &original)
{
	if (this == &original){
		return *this;
	}
	curr_cap = original.capacity();
	curr_size = original.size();

	points = new double[curr_cap];

	for (int i=0; i<curr_size; i++){
		points[i] = original.points[i];
	}

    
}

//DONE
data_set::~data_set()
{
	delete[] points;
}

//DONE
void data_set::insert(double value)
{
	if (curr_size == 0){
		points[curr_size] = value;
		curr_size++;
	}
	else if (curr_size < curr_cap){
		for (int i = 0; i <= curr_size; i++){
			if (i == curr_size){
				points[curr_size] = value;
			}
			else if (value < points[i]){
				for (int m = curr_size; m > i; m--){
					points[m] = points[m-1];
				}
				points[i] = value;
				break;
			}
		}
		curr_size++;
	}

	else{
		curr_cap = curr_cap * 2;
		double* newpoints = new double[curr_cap];

		for (int i = 0; i < curr_size; i++){
			 newpoints[i] = points[i];
		}
		
		delete[] points;
		points = newpoints;

		for (int i = 0; i <= curr_size; i++){
			if (i == curr_size){
				points[curr_size] = value;
			}
			else if (value < points[i]){
				for (int m = curr_size; m > i; m--){
					points[m] = points[m-1];
				}
				points[i] = value;
				break;
			}
		}
		curr_size++;
	}

}

//DONE
void data_set::print(ostream &out) const
{
	if (curr_size > 0){
		for (int i=0; i < curr_size; i++){
			if (i == curr_size - 1){
				out << points[i] << " }" << endl;
			}
			else if (i == 0){
				out << "{ " << points[i] << ", ";
			}
			else{
				out << points[i] << ", ";
			}
		}
	}
	else{
		out << " { } " << endl;
	}
}

//DONE
int data_set::size() const
{
    return curr_size;
}


//DONE
int data_set::capacity() const
{
    return curr_cap;
}

//DONE
double data_set::mean() const
{
	double temp = 0;

	if (curr_size <= 0){
		throw runtime_error("empty set");
	}
	// Loop over Array for Mean 
	
	else{
		for (int i = 0; i < curr_size; i++){
			temp = temp + points[i];	
		}
		temp = temp / curr_size;
	   return temp;
	}
}

//DONE
double data_set::median() const
{
	int temp = 0;
	int temp2 = 0;
	double finaltemp = 0;

	if (curr_size <= 0){
		throw runtime_error("empty set");
	}
	else if(curr_size % 2 == 1){
		temp = curr_size / 2;
		return points[temp];
	}
	else{
		temp2 = curr_size / 2;
		temp = temp2 - 1;
		finaltemp = (points[temp2] + points[temp]) / 2;
		return finaltemp;
	}
}

//DONE
double data_set::minimum() const
{
	if (curr_size <= 0){
		throw runtime_error("empty set");
	}
	else{
		return points[0];
	}
}

//DONE
double data_set::maximum() const
{
	if (curr_size <= 0){
		throw runtime_error("empty set");
	}
	else{
		return points[curr_size - 1];
	}
}

//DONE
int test_data_set()
{
    // Current test number.  Be sure to increment this before each test!
    int curr_test = 0;

    // Number of failed tests.
    int failed = 0;
    
    cerr << "Testing..." << endl;

    // Test 1: does the default constructor create an empty data set?
    //   Tests: default constructor, size method
    curr_test++;
    data_set empty;
    if (empty.size() != 0) {
        cerr << "Test " << curr_test << " failed: size is "
             << empty.size() << ", should be 0." << endl;
        failed++;
    }

    // Test 2: does the default constructor set the capacity correctly.
    //   Tests: default constructor, capacity method
    curr_test++;
    if (empty.capacity() != 10) {
        cerr << "Test " << curr_test << " failed: capacity is "
             << empty.capacity() << ", should be 10." << endl;
        failed++;
    }

    // Test 3: does the integer constructor work?
    //   Tests: int constructor, capacity method.
    curr_test++;
    data_set tiny(1);
    if (tiny.capacity() != 1) {
        cerr << "Test " << curr_test << " failed: capacity is "
             << tiny.capacity() << ", should be 10." << endl;
        failed++;
    }

    // Test 4: and is that data set empty, too?
    //   Tests: int constructor, size method.
    curr_test++;
    if (tiny.size() != 0) {
        cerr << "Test " << curr_test << " failed: size is "
             << tiny.size() << ", should be 0." << endl;
        failed++;
    }

    // Test 5: can we insert?
    //   Tests: int constructor, insert and size methods.
    curr_test++;
    data_set working(2);
    working.insert(4.5);
    if (working.size() != 1) {
        cerr << "Test " << curr_test << " failed: size is "
             << working.size() << ", should be 1." << endl;
        failed++;
    }

    // Test 6: can we insert over the current capacity?
    //   Tests: int constructor, insert and size methods.
    curr_test++;
    working.insert(5.5);
    working.insert(3.5);
    if (working.size() != 3) {
        cerr << "Test " << curr_test << " failed: size is "
             << working.size() << ", should be 3." << endl;
        failed++;
    }
    
    // Test 7: did that update the capacity?
    //   Tests: int constructor, insert and capacity methods.
    curr_test++;
    if (working.capacity() < 3) {
        cerr << "Test " << curr_test << " failed: capacity is "
             << working.capacity() << ", should be at least 3." << endl;
        failed++;
    }

    // Test 8: does the vector print in order and with the correct
    //         formatting?
    //   Tests: int constructor, insert and print methods.
    //   Uses an ostringstream to capture the output.
    curr_test++;
    ostringstream out;
    working.print(out);
    string expected = "{ 3.5, 4.5, 5.5 }\n";
    if (out.str() != expected) {
        cerr << "Test " << curr_test << " failed:" << endl;
        cerr << "Actual output:   " << out.str() << endl;
        cerr << "Expected output: " << expected << endl;
        failed++;
    }

    // Test 9: does the copy constructor faithfully copy?
    //   Tests: copy constructor and print methods.
    curr_test++;
    data_set copy(working);
    ostringstream out_copy;
    copy.print(out_copy);
    if (out_copy.str() != out.str()) {
        cerr << "Test " << curr_test << " failed:" << endl;
        cerr << "Original: " << out.str() << endl;
        cerr << "Copy:     " << out_copy.str() << endl;
        failed++;
    }
    
    // Test 10: did it do a deep copy?  Changing the copy shouldn't change
    //          the original.
    //   Tests: copy constructor, insert and print methods.
    curr_test++;
    copy.insert(2.0);
    
    ostringstream out_orig;
    working.print(out_orig);
    if (out_orig.str() != expected) {
        cerr << "Test " << curr_test << " failed:" << endl;
        cerr << "Actual output:   " << out_orig.str() << endl;
        cerr << "Expected output: " << expected << endl;
        failed++;
    }

    // Test 11: does the assignment operator change the size?
    //   Tests: assignment operator, size method.
    curr_test++;
    tiny = working;
    if (tiny.size() != 3) {
        cerr << "Test " << curr_test << " failed: size is "
             << tiny.size() << ", should be 3." << endl;
        failed++;
    }
    
    // Test 12: did the assignment operator copy the values?
    //   Tests: assignment operator, print method.
    curr_test++;
    ostringstream out_tiny;
    working.print(out_tiny);

    if (out_tiny.str() != out_orig.str()) {
        cerr << "Test " << curr_test << " failed:" << endl;
        cerr << "Original: " << out_orig.str() << endl;
        cerr << "Copy:     " << out_tiny.str() << endl;
        failed++;
    }
    
    // Test 13: did it do a deep copy?
    //   Tests: assignment operator, insert and print methods.
    curr_test++;
    tiny.insert(9.0);
    
    ostringstream out_orig2;
    working.print(out_orig2);

    if (out_orig2.str() != expected) {
        cerr << "Test " << curr_test << " failed:" << endl;
        cerr << "Actual output:   " << out_orig2.str() << endl;
        cerr << "Expected output: " << expected << endl;
        failed++;
    }
    
    // Test 14: does minimum() work?
    //   Tests: insert and minimum methods
    curr_test++;
    if (working.minimum() != 3.5) {
        cerr << "Test " << curr_test << " failed: got "
             << working.minimum() << ", expected 3.5." << endl;
        failed++;
    }
    
    // Test 15: does minimum throw an exception on an empty
    //          vector?
    //   Tests: empty constructor, minimum method
    curr_test++;
    bool caught = false;
    // We need a try/catch because we expect an exception.
    try {
        double x = empty.minimum();
    } catch (exception e) {
        caught = true;
    }
    if (!caught) {
        cerr << "Test " << curr_test << " failed: missing exception" << endl;
        failed++;
    }

	 // TODO: implement two tests each for mean, maximum, and median.
	// MY TESTS BELOW HERE




	//Test 16: Does mean throw an exception on an empty
    //          vector?
    curr_test++;
    caught = false;
    // We need a try/catch because we expect an exception.
    try {
        double tester = empty.mean();
    } catch (exception e) {
        caught = true;
    }
    if (!caught) {
        cerr << "Test " << curr_test << " failed: missing exception" << endl;
        failed++;
    }

	// Test 17: does mean() work?
    //   Tests: insert and mean methods
    curr_test++;
	data_set testing;
	testing.insert(1);
	testing.insert(2);
	testing.insert(3);
	testing.insert(4);
	testing.insert(5);
    if (testing.mean() != 3) {
        cerr << "Test " << curr_test << " failed: got "
             << testing.mean() << ", expected 3." << endl;
        failed++;
    }

	// Test 18: does max() work?
    //   Tests: insert and max methods
    curr_test++;
    if (testing.maximum() != 5) {
        cerr << "Test " << curr_test << " failed: got "
             << testing.maximum() << ", expected 5." << endl;
        failed++;
    }

	//Test 19: Does max throw an exception on an empty
    //          vector?
    curr_test++;
    caught = false;
    // We need a try/catch because we expect an exception.
    try {
        double tester = empty.maximum();
    } catch (exception e) {
        caught = true;
    }
    if (!caught) {
        cerr << "Test " << curr_test << " failed: missing exception" << endl;
        failed++;
    }

	// Test 20: does median() work for odd sets?
    //   Tests: insert and median methods
    curr_test++;
    if (testing.median() != 3) {
        cerr << "Test " << curr_test << " failed: got "
             << testing.median() << ", expected 3." << endl;
        failed++;
    }

	// Test 21: does median() work for odd sets?
    //   Tests: insert and median methods
    curr_test++;
	testing.insert(6);
    if (testing.median() != 3.5) {
        cerr << "Test " << curr_test << " failed: got "
             << testing.median() << ", expected 3.5." << endl;
        failed++;
    }




    if (failed == 0)
    {
        cerr << "All tests passed." << endl;
    }

    // Add an extra blank line after the tests.
    cerr << endl;

    return 0;
}


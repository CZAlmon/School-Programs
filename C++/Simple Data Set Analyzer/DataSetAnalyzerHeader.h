#ifndef DATASETANALZYERHEADER_H_INCLUDED
#define DATASETANALZYERHEADER_H_INCLUDED

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>

using namespace std;

/* pause_215() - Wait for the user to press ENTER.
 *
 * Description: 
 *   Optionally read and discard the remainder of the user's last
 *   line of input.  Then, prompt the user to press ENTER, then
 *   read and discard another line of input.
 *
 * Inputs:
 *   bool have_newline:
 *     True if the user has already entered a newline that the
 *     program has not yet read.  If true, this function first
 *     discards remaining input up to and including that newline.
 *
 * Outputs:
 *   No return value.
 *
 * Side-effects:
 *   Prints a prompt to standard output.  Reads one or two lines
 *   from standard input.
 *
 * Exceptions:
 *   None.
 *
 * Notes:
 *   This function is intended to be used at the end of a program,
 *   just before returning from main().  Reading another line of
 *   input prevents the console window from closing immediately.
 *
 *   In general, have_newline should be true if the last user input
 *   from cin used the extraction operator (>>), and false if there
 *   has been no user input or if the last input used getline().
 */
void pause_215(bool have_newline);

/* test_data_set() - Test the data_set class.
 *
 * Description: 
 *   Run a series of tests on the data_set class.  Prints an
 *   error message for each failed test.
 *
 * Inputs:
 *   None.
 *
 * Outputs:
 *   Returns the number of failed tests.
 *
 * Side-effects:
 *   Prints an error message to standard error for each test that
 *   fails.  Also prints a message at the end if all tests passed.
 *
 * Exceptions:
 *   If a called method unexpectedly throws an exception, it will
 *   be passed on (not caught).
 *
 */
int test_data_set();


class data_set
{
public:

 /* data_set() - Default constructor, sets capacity to 10 and size to 0 and array to curr_cap
 *
 * Description: 
 *		  This method is to reset the capacity and the size before any changes occur.
 *		  Capacity (curr_cap) is set to 10 as default, and size (curr_size) is set to 0.
 *		  The dynamically allocated array, points, is set to size curr_cap.
 * Inputs:
 *		  None
 * Outputs:
 *		  None
 * Side-Effects:
 *		  curr_cap is set to 10, and curr_size is set to 0
 *		  points is set to size curr_cap
 * Exceptions:		
 *		  None
 * Notes:
 */
    data_set();
 /* data_set(capacity) - Sets capacity to parameter, size to 0 and array to current capacity
 *
 * Description: 
 *		  This method is to reset the capacity and the size before any changes occur.
 *		  Capacity (curr_cap) is set to the parameter as default, and size (curr_size) is set to 0.
 *		  The dynamically allocated array, points, is set to size curr_cap.
 * Inputs:
 *		  The parameter intial_capacity
 * Outputs:
 *		  None
 * Side-Effects:
 *		  Changes curr_cap to the parameters value, curr_size to 0, and the array, points,
 *		  to curr_caps value.
 * Exceptions:		
 *		  Throws an error if capacity is 0
 * Notes:  
 */
    data_set(int initial_capacity);

/* data_set(const data_set &original) - Copy constructor to copy from another data_set
 *
 * Description: 
 *		  This method is to set the capacity and the size to the same values as the 
 *		  data_set in its parameter. It will then create a new dynamically allocated
 *		  array that will then loop over the parameter's array, copying everything to the new array.
 * Inputs:
 *		  Parameter that is a data_set
 * Outputs:
 *		  None
 * Side-Effects:
 *		  Changes curr_cap and curr_size to the parameters value, and the array, points,
 *		  to the parameters array.
 * Exceptions:		
 *		  None
 * Notes:  
 */
    data_set(const data_set &original);

/* data_set(capacity) - Assignment operator
 *
 * Description: 
 *		  This method is to copy everything from one data set to another.
 *		  If it is assigned to copy itself, it simply returns *this.
 *		  It will then set the capacity and the size to the same values as the 
 *		  data_set in its parameter. It will then create a new dynamically allocated
 *		  array that will then loop over the parameter's array, copying everything to the new array.
 * Inputs:
 *		  None
 * Outputs:
 *		  None
 * Side-Effects:
 *		  Changes curr_cap and curr_size to the parameters value, and the array, points,
 *		  to the parameters array.
 * Exceptions: None
 * Notes:  
 */
    data_set &operator=(const data_set &original);

/* ~data_set() - Destructor
 *
 * Description: 
 *		  Used to close allocated memory from class
 * Inputs:
 *		  None
 * Outputs:
 *		  None
 * Side-Effects:
 *		  Closes/Deletes memory from array, points, the dynamically allocated memory
 * Exceptions:		
 *		  None
 * Notes:
 */
    ~data_set();
    
/* size() - method to return the number of items in the array
 *
 * Description: 
 *		  Simply returns the number of items in the array, points, to the caller.
 * Inputs:
 *		  None
 * Outputs:
 *		  Returns value to caller
 * Side-Effects:
 *		  None, no changes, const
 * Exceptions:		
 *		  None
 * Notes:  
 */
    int size() const;
    
/* capacity() - method to return the current capacity of the array
 *
 * Description: 
 *		  Simply returns the current capacity of the array, points, to the caller.
 * Inputs:
 *		  None
 * Outputs:
 *		  Returns value to caller
 * Side-Effects:
 *		  None, no changes, const
 * Exceptions:		
 *		  None
 * Notes:  
 */
    int capacity() const;


/* insert(value) - method to insert values into the array set. 
 *
 * Description: 
 *		  Parameter is a value from the user's input in main. 
 *		  Puts value into the first spot if size is 0
 *		  Loops over array until it finds the spot it should go (maintaining order
 *		  from least to greatest), the will push everything back one spot and put
 *		  value in the correct spot.
 *		  If size is the same as capacity, it will create a new array with twice the 
 *		  capacity and will delete old array to free memory. Then will loop over 
 *		  and add the value to the correct spot, pushing anything and everything back one space
 * Inputs:
 *		  None
 * Outputs:
 *		  None
 * Side-Effects:
 *		  Size will always change by 1, for the value being brought in by the parameter
 *		  Capacity will change by (twice as much) when size = capacity
 *		  Dynamically Allocated array, points, will be added to everytime,
 *		    and will be increased in capacity when size = capacity
 * Exceptions:		
 *		  None
 * Notes:  
 */
    void insert(double value);

/* print(out) - prints values to screen
 *
 * Description: 
 *		  Loops over entire array. Detects if first or last element.
 *		  If first or last element prints specific thing.
 *		  Every other element will print same thing with spaces/commas
 * Inputs:
 *		  None
 * Outputs:
 *		  Outputs the array to screen with specific characters/spaces
 * Side-Effects:
 *		  None, Const
 * Exceptions:		
 *		  None
 * Notes:  
 */
    void print(ostream &out) const;

/* mean() - calculates and returns the average of the end set
 *
 * Description: 
 *		  Loops over the array, adding every number
 *		  Then divides by the size
 *		  Returns this value
 * Inputs:
 *		  None
 * Outputs:
 *		  None
 * Side-Effects:
 *		  None
 * Exceptions:		
 *		  Throws a runtime_error if the set is empty
 * Notes:	  
 */
    double mean() const;
/* minimum() - returns the first item of the array
 *
 * Description: 
 *		  Returns points[0]
 * Inputs:
 *		  None
 * Outputs:
 *		  None
 * Side-Effects:
 *		  None
 * Exceptions:		
 *		  Throws a runtime_error if the set is empty
 * Notes:	  
 */
    double minimum() const;
/* maximum() - returns the value at the end of the set
 *
 * Description: 
 *		  returns points[curr_size - 1]
 * Inputs:
 *		  None
 * Outputs:
 *		  None
 * Side-Effects:
 *		  None
 * Exceptions:		
 *		  Throws a runtime_error if the set is empty
 * Notes:	  
 */
    double maximum() const;
/* median() - calculates and returns the median number of the set
 *
 * Description: 
 *		  finds the median value. If set is empty, throws an runtime error.
 *		  if set is odd (5 % 2 = 1, if 1 is left over anytime) then it will take the
 *		  middle number (ceiling(5/2)
 *		  if set is even, then it will take the number the left and right of half
 *		  and add together, and divide by 2 (((6/2) + (6/2 +1)) / 2)
 * Inputs:
 *		  None
 * Outputs:
 *		  None
 * Side-Effects:
 *		  None
 * Exceptions:		
 *		  Throws a runtime_error if the set is empty
 * Notes:	  
 */
    double median() const;

private:
    // Current allocated capacity of the array.
    int curr_cap;

    // Number of elements in use.
    int curr_size;

    // Pointer to a dynamically-allocated array of points.
    double *points;
};

#endif



/* Main() - 
 *
 * Description: 
 *		  
 *		  
 *		   
 *		  
 *		  
 *		  
 *		  
 *		  
 *
 * Inputs:
 *		  
 *
 * Outputs:
 *		  
 *		 
 *		
 * Side-Effects:
 *		  
 *		   
 * Exceptions:		
 *		  
 *		   
 *	
 * Notes:
 *		  
 *		  
 *		   
 *		  
 */
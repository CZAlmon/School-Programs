#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

/* day_string_to_int - convert a day name in string to its corrisponding number.
 *
 * Description: 
 *		  Input is the string of the day name. if it is this, return day number, repeat for all 7 days.
 *		  Else throw runtime error, invalid day.
 *
 * Inputs:
 *		  String day name
 *
 * Outputs:
 *		  Day number, 0-6 Sunday- Saturday		 
 *		
 * Side-Effects:
 *		  No output, No variable changes, global or local. Only throws runtime error if invalid day.
 *		   
 * Exceptions:		
 *		  Throw runtime error if in valid day, Not Sunday or sunday for every day of the week
 *		   
 * Notes:
 */
int day_string_to_int(string day_of_week);
/* day_int_to_string - To convert from int number to full day name as a string.
 *
 * Description: 
 *		  input (parameter) is the day number, switch is used since its comparing numbers.
 *		  Case by case 0-6 returns coorisponding day as a string ("Sunday" or "Monday").
 *		  Makes user experience a bit better for visual appeal.
 *
 * Inputs:
 *		  Parameter is a number 0-6. If nonoe are hit, throws a runtime error.
 *
 * Outputs:
 *		  Returns a string for the day name corrisponding to the number given.		 
 *		
 * Side-Effects:
 *		  No output, No variable changes, global or local. Only throws runtime error if invalid day.
 *		   
 * Exceptions:		
 *		  Throw runtime error if in valid day, Not Sunday or sunday for every day of the week
 *		   
 * Notes:
 */
string day_int_to_string(int day_num);
/* new_day_prompt() - Prompts user for a day name. Accepts Sunday or sunday for every day. (All lower case or only 1st letter upper.)
 *
 * Description: 
 *		  loops over for users input. If the input is Sunday or sunday (but for one of the days of the week, all 7)
 *		  Then it returns "Sunday" or "Monday". Otherwise out << "Invalid day" and repeats the cycle.
 *		   
 * Inputs:
 *		  User input for a day of the week name.
 *
 * Outputs:
 *		  returns day of the week name as "Sunday" or "Monday"		 
 *		
 * Side-Effects:
 *		  outputs text to user prompting input. Nothing changes.
 *		   
 * Exceptions:		
 *		  No exceptions. Loops over until user types day in as lower case, or only 1st letter uppercase for day name.		   
 *	
 * Notes:
 *		 I wrote out this code first, before thinking of doing a function or method to make all letters lowercase to check for day name
 *		 so i stuck with this code as it would be too time consuming to change it before deadline is reached. Would probably be faster
 *		 and more user friendly to accept any input from user and make it all lower case and compare that and only that for the day names.
 */
string new_day_prompt(ostream &out);
//Function given by professor, No changes were made
//Inputs a string and outputs the number as a string.
//Throws a fail if string isnt a number
int string_to_int(string str);
//Function given by professor, No changes were made
//Takes a line and breaks it apart at the #.
//No exceptsions.
vector<string> split_string(string input);
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





//Global Variables; Constants used for the weekday Names/Numbers throughout the program
//NEVER CHANGED THROUGHOUT PROGRAM
const int SUNDAY = 0;
const string sunday = "Sunday";
const string sunday2 = "sunday";

const int MONDAY = 1;
const string monday = "Monday";
const string monday2 = "monday";

const int TUESDAY = 2;
const string tuesday = "Tuesday";
const string tuesday2 = "tuesday";

const int WEDNESDAY = 3;
const string wednesday = "Wednesday";
const string wednesday2 = "wednesday";

const int THURSDAY = 4;
const string thursday = "Thursday";
const string thursday2 = "thursday";

const int FRIDAY = 5;
const string friday = "Friday";
const string friday2 = "friday";

const int SATURDAY = 6;
const string saturday = "Saturday";
const string saturday2 = "saturday";

#endif
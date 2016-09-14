#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED

#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>



class appointment
{
public:

/* appointment() - Constructor for the basic appointment
 *
 * Description: 
 *		  accepts 2 parameters, labels and notes, and sets the private member variables as them (labels to labels and notes to notes).
 *		  
 * Inputs:
 *		  Labels and notes as parameters.
 *
 * Outputs:
 *		  No return value. Changes member variables.	 
 *		
 * Side-Effects:
 *		  Changes member variables value, nothing else.
 *		   
 * Exceptions:		
 *		  No exceptions.   
 *	
 * Notes:
 */
	appointment(string labels_here, string notes_here);
/* get_label() - Returns what the label variable is
 *
 * Description: 
 *		  simple accessor for the label variable of the appointment class. Returns the string value of label.		  
 *
 * Inputs:
 *		  None
 *
 * Outputs:
 *		  Returns the string value of the variable label of the appointment class.		 
 *		
 * Side-Effects:
 *		  Returns string value of label.
 *		   
 * Exceptions:		
 *		  No exceptions		   
 *	
 * Notes:
 */
	string get_label() const;
/* get_notes() - Returns what the notes variable is
 *
 * Description: 
 *		  simple accessor for the notes variable of the appointment class. Returns the string value of notes.		  
 *
 * Inputs:
 *		  None
 *
 * Outputs:
 *		  Returns the string value of the variable notes of the appointment class.		 
 *		
 * Side-Effects:
 *		  Returns string value of notes.
 *		   
 * Exceptions:		
 *		  No exceptions		   
 *	
 * Notes:
 */
	string get_notes() const;
/* print() - Appointment's virtual print method
 *
 * Description: 
 *		  prints out the label and notes in a fashion dictated by the example from the professor.
 *		  Needed to be able to print out the label and notes of any appointment, wether sub class or not.
 *		  virtual to make sure it prints it label and notes when needed to and sub class information when
 *		  that is required.
 *
 * Inputs:
 *		  None.
 *
 * Outputs:
 *		  Outputs information to the screen for the user, labels and notes in this case, in a fashion dictated by the example from the professor.
 *		
 * Side-Effects:
 *		  Outputs to the screen, not file.
 *		   
 * Exceptions:		
 *		  No exceptions.	   
 *	
 * Notes:
 */
	virtual void print(ostream &out) const;
/* occurs_on() - Pure virtual function
 *
 * Description: 
 *		  accepts int parameter. To be used to determine if an appointment happens on that day,
 *		  the one that coorisponds to the parameter.
 *		   
 *		  Pure virtual method, not used or implemeted for appointment base class.
 *
 * Inputs:
 *		  day integer as parameter.
 *
 * Outputs:
 *		  returns true if appointment happens on that day, or false if not.
 *		
 * Side-Effects:
 *		  No side effects
 *		   
 * Exceptions:		
 *		  No exceptions
 * Notes:  
 */
	virtual bool occurs_on(int day) const = 0;
/* print_appointment() - pure virtual method to print the appointment in plain text for an out going file
 *
 * Description: 
 *		  To be used in sub classes. Prints out in plain text the information of the appointment
 *		  seperated by #'s to be able to be read later by the reader.		  
 *
 * Inputs:
 *		  None
 *
 * Outputs:
 *		  Text in a format to be read in by the reader function of this program.
 *		 
 *		
 * Side-Effects:
 *		  No changes are made.
 *		   
 * Exceptions:		
 *		  No exceptions are thrown.		   
 *	
 * Notes:
 */
	virtual void print_appointments(ostream& out) const = 0;

private:
	string label;
	string notes;
};

class daily_app : public appointment
{
public:
/* daily_app() - Sub-class to appointment, for daily appointments
 *
 * Description: 
 *		  Calls the appointment constructor to set the labels and notes parameters (accessor will be able to get the info later)
 *		  Time and location are set by the constructor itself (daily_app)
 *
 * Inputs:
 *		  Parameter for Label, Notes, Time, and Location
 *
 * Outputs:
 *		  Changes variables for the 4 parameters of the appointment object itself
 *		 
 * Side-Effects:
 *		  None/Variables related to the appointment change but nothing else
 *		   
 * Exceptions:		
 *		  None
 *		   
 * Notes:
 */
	daily_app(string labels_here, string notes_here, string time_of_day, string location);
/* print() - Daily_app's printing function.
 *
 * Description: 
 *		  Calls the appointment's print function for the label and notes info
 *		  Prints out the time and location info in accordance to the example
 *		  provided by the professor.
 *		  
 * Inputs:
 *		  None
 *
 * Outputs:
 *		  Prints out the information related to the appointment (label, notes, time, location)
 *		 to the screen for the user.
 *		
 * Side-Effects:
 *		  None, nothing changes.
 *		   
 * Exceptions:		
 *		  None		   
 *	
 * Notes:
 */
	void print(ostream &out) const;
/* occurs_on() - Determines weither a given event occurs on the day inputed through parameter
 *
 * Description: 
 *		  returns true no matter what. Daily appointments are every day of the week, therefore
 *		  always occuring on every day. 
 *
 * Inputs:
 *		  Integer day.
 *
 * Outputs:
 *		  boolian true value. (Always true)		 
 *		
 * Side-Effects:
 *		  None.
 *		   
 * Exceptions:		
 *		  None.		   
 *	
 * Notes:  
 */
	bool occurs_on(int day) const;
/* print_appointments() - prints out plain text version of info seperated by #
 *
 * Description: 
 *		  prints out the type (daily) followed by #, calls the get_label for the label, followed by #,
 *		  thens get_notes, followed by #, then place - #, then time followed by a new line. The parameter out
 *		  will lead to an outgoing file, not the users screen, but that will be the function calling it, not
 *		  this function.
 *		  
 * Inputs:
 *		  out, parameter
 *
 * Outputs:
 *		  plain text of the information in the appointment.
 *		 
 * Side-Effects:
 *		  None, no changes to the data
 *		   
 * Exceptions:		
 *		  None.		   
 *	
 * Notes:

 */
	void print_appointments(ostream& out) const;
private:
	string daily_place;
	string daily_time;
};

class weekly_app : public appointment
{
public:
/* weekly_app() - Sub-class to appointment, for weekly appointments
 *
 * Description: 
 *		  Calls the appointment constructor to set the labels and notes parameters (accessor will be able to get the info later)
 *		  Day, Time and location are set by the constructor itself (weekly_app)
 *
 * Inputs:
 *		  Parameter for Label, Notes, Day, Time, and Location
 *
 * Outputs:
 *		  Changes variables for the 5 parameters of the appointment object itself
 *		 
 * Side-Effects:
 *		  None/Variables related to the appointment change but nothing else
 *		   
 * Exceptions:		
 *		  None
 *		   
 * Notes:
 */
	weekly_app(string labels_here, string notes_here, int day_of_week, string time_of_day, string location);
/* print() - weekly_app's printing function.
 *
 * Description: 
 *		  Calls the appointment's print function for the label and notes info
 *		  Prints out the day, time and location info in accordance to the example
 *		  provided by the professor.
 *		  
 * Inputs:
 *		  None
 *
 * Outputs:
 *		  Prints out the information related to the appointment (label, notes, day, time, location)
 *		 to the screen for the user.
 *		
 * Side-Effects:
 *		  None, nothing changes.
 *		   
 * Exceptions:		
 *		  None		   
 *	
 * Notes:
 */
	void print(ostream &out) const;
/* occurs_on() - determines if the appointment happens on the day specified.
 *
 * Description: 
 *		  Returns true if day == weekly_day (the variable for the day in weekly_app) 
 *		  They are both int's.		  
 *
 * Inputs:
 *		  integer day
 *
 * Outputs:
 *		  return true or false. Boolean.
 *		 
 *		
 * Side-Effects:
 *		  None
 *		   
 * Exceptions:		
 *		  None	   
 *	
 * Notes: 
 */
	bool occurs_on(int day) const;
/* print_appointments() - prints out plain text version of info seperated by #
 *
 * Description: 
 *		  prints out the type (weekly) followed by #, calls the get_label for the label, followed by #,
 *		  thens get_notes, followed by #, then place - #, then time - #, then day followed by a new line. The parameter out
 *		  will lead to an outgoing file, not the users screen, but that will be the function calling it, not
 *		  this function.
 *		  
 * Inputs:
 *		  out, parameter
 *
 * Outputs:
 *		  plain text of the information in the appointment.
 *		 
 * Side-Effects:
 *		  None, no changes to the data
 *		   
 * Exceptions:		
 *		  None.		   
 *	
 * Notes:

 */

	void print_appointments(ostream& out) const;
private:
	string weekly_place;
	string weekly_time;
	int weekly_day;
};

class task : public appointment
{
public:
/* task() - Sub-class to appointment, for task appointments
 *
 * Description: 
 *		  Calls the appointment constructor to set the labels and notes parameters (accessor will be able to get the info later)
 *		  day and duration are set by the constructor itself (task)
 *
 * Inputs:
 *		  Parameter for Label, Notes, day and duration
 *
 * Outputs:
 *		  Changes variables for the 4 parameters of the appointment object itself
 *		 
 * Side-Effects:
 *		  None/Variables related to the appointment change but nothing else
 *		   
 * Exceptions:		
 *		  None
 *		   
 * Notes:
 */
	task(string labels_here, string notes_here, int days, string dur);
/* print() - Task's printing function.
 *
 * Description: 
 *		  Calls the appointment's print function for the label and notes info
 *		  Prints out the day and duration info in accordance to the example
 *		  provided by the professor.
 *		  
 * Inputs:
 *		  None
 *
 * Outputs:
 *		  Prints out the information related to the appointment (label, notes, day, and duration)
 *		 to the screen for the user.
 *		
 * Side-Effects:
 *		  None, nothing changes.
 *		   
 * Exceptions:		
 *		  None		   
 *	
 * Notes:
 */	
	void print(ostream &out) const;
/* occurs_on() - determines if the appointment happens on the day specified.
 *
 * Description: 
 *		  Returns true if day == task_day_of_week (the variable for the day in task) 
 *		  They are both int's.		  
 *
 * Inputs:
 *		  integer day
 *
 * Outputs:
 *		  return true or false. Boolean.
 *		 
 *		
 * Side-Effects:
 *		  None
 *		   
 * Exceptions:		
 *		  None	   
 *	
 * Notes: 
 */	
	bool occurs_on(int day) const;
/* print_appointments() - prints out plain text version of info seperated by #
 *
 * Description: 
 *		  prints out the type (task) followed by #, calls the get_label for the label, followed by #,
 *		  thens get_notes, followed by #, then day - #, then duration followed by a new line. The parameter out
 *		  will lead to an outgoing file, not the users screen, but that will be the function calling it, not
 *		  this function.
 *		  
 * Inputs:
 *		  out, parameter
 *
 * Outputs:
 *		  plain text of the information in the appointment.
 *		 
 * Side-Effects:
 *		  None, no changes to the data
 *		   
 * Exceptions:		
 *		  None.		   
 *	
 * Notes:

 */

	void print_appointments(ostream& out) const;
private:
	int task_day_of_week;
	string task_duration;
};

class schedule
{
public:
/* schedule() - constructor for a schedule
 *
 * Description: 
 *		  Nothing needs to be set, simple makes a new schedule to be worked upon.
 *		  
 * Inputs:
 *		  None.
 *
 * Outputs:
 *		  None.		 
 *		
 * Side-Effects:
 *		  None.
 *		   
 * Exceptions:		
 *		  None.		   
 *	
 * Notes:
 */
	schedule();
/* ~schedule() - Deconstructor
 *
 * Description: 
 *		  Not a simple deconstructor. Needs to loop over the vector of appointments,
 *		  and delete every appointment in its data. Runs from 0 until size 
 *		  (That is 0 to size - 1 if you do not use the "<" symbol).
 *		   
 * Inputs:
 *		  None.
 *
 * Outputs:
 *		  None.		 
 *		
 * Side-Effects:
 *		  Deletes all appointment data in the vector of appointments after program terminates.
 *		   
 * Exceptions:		
 *		  None.
 *		  
 * Notes: 
 */	
	~schedule();
/* schedule_loader() - Loads schedule from a file to be worked upon
 *
 * Description: 
 *		  Loops over each line of the file, breaking when line == 0 (No more data in the lines)
 *		  Calls add appointment to add the appointment returned by the parse appointment function.
 *		  For each line of the file there will be an appointment added. 
 *		  
 * Inputs:
 *		  File is input. 
 *
 * Outputs:
 *		  No output.		 
 *		
 * Side-Effects:
 *		 Changes the vector of appointments for the schedule object. Adds appointments to it from the file. 
 *		   
 * Exceptions:		
 *		 None.		   
 *	
 * Notes:
 */	
	void Schedule_loader(istream& intput_file);
/* schedule_writer() - File parameter is the file to be written to
 *
 * Description: 
 *		  The file parameter is the file to be written too.
 *		  Goes from 0 until size (0 to size - 1), and 
 *		   schedule of appointments (vector of appointments) -> print_appointments function with the output file
 *		  will call each appointment with the "this" command (each appointment may be different (eg daily/task))
 *		  prints plain text of the appointments through print_appointment function, then writes that to the file.
*
 * Inputs:
 *		  File to overwritten
 *
 * Outputs:
 *		  None.
 *		 
 * Side-Effects:
 *		  over writes the file given as a parameter to adjust for appointment changes (add/remove)
 *		   
 * Exceptions:		
 *		  None.		   
 *	
 * Notes:
 */
	void Schedule_writer(ostream& output_file) const;
/* Add_Appointment() - Add the appointment to the vector
 *
 * Description: 
 *		  Adds the appointment pointer to the vector of appointments
 *		  Parameter is the pointer, only pushes back the vector.
 *		   
 * Inputs:
 *		  Appointment pointer
 *
 * Outputs:
 *		  Nothing.		 
 *		
 * Side-Effects:
 *		  Changes the vector of appointments. Pushes it back and adds the new pointer
 *		   
 * Exceptions:		
 *		  none.		   
 *	
 * Notes: 
 */	
	void Add_Appointment(appointment* a);
/* Remove Appointment() - Removes the appointment specificied by the parameter
 *
 * Description: 
 *		  Parameter is the number of the appointment that needs to be removed.
 *		  Remove it from the vector. I used the .erase method here, or you could move all appointments up, overwritting
 *		  the one to be erased and then use pop_back.
 *		 
 * Inputs:
 *		  Appointment number parameter
 *
 * Outputs:
 *		  None.	 
 *		
 * Side-Effects:
 *		 Changes the vector of appointments. Removes the user specfied app.
 *		   
 * Exceptions:		
 *		  None.	   
 *	
 * Notes:
 */	
	void Remove_Appointment(int App_Number);
/* print_schedule_day() - prints the schedule for the day specified.
 *
 * Description: 
 *		  Using the vector of appointments -> (this command) to occurs on, it will
 *		  determine if the appointment happens on the day needed. If true, it prints out the info
 *		  on that day. Loops over the entire vector of appointments checking for that day.
 *		  
 *		  Parameters are the out stream (user UI) and the day NUMBER info is needed on.	  
 *
 * Inputs:
 *		  Output stream (user screen), and day number as an int.
 *
 * Outputs:
 *		  outputs appointment info if there is any.		 
 *		
 * Side-Effects:
 *		  Nothing changes. accessor only.
 *		   
 * Exceptions:		
 *		  None.		   
 *	
 * Notes: 
 */	
	void print_Schedule_Day(ostream &out, int day) const;
/* print_schedule_week() - prints out the entire schedule for the week.
 *
 * Description: 
 *		  Loops over 0-6 (inclusive) for each day.
 *		  Prints out the day name (eg if 0, print Sunday)
 *		  calls print_schedule_day for the value of i currently on (calls for each day)
 *		  outputs to screen the info (user screen)
 *		  
 *		  parameter is only out. print_schedule_day's second parameter of a day number if the value of i. 0-6 inclusive.
 *		  
 * Inputs:
 *		  cout for user screen.
 *
 * Outputs:
 *		  prints out the entire schedule for the week.		 
 *		
 * Side-Effects:
 *		  None, no changes accessor only.
 *		   
 * Exceptions:		
 *		  None.	   
 *	
 * Notes:
 */	
	void print_Schedule_Week(ostream &out) const;
/* get_size() - Accessor to find the current size of the vector of appointments
 *
 * Description: 
 *		  Returns integer of the size of vector of appointments (.size())
 *		  
 * Inputs:
 *		  None.
 *
 * Outputs:
 *		  Returns int size of the vector		 
 *		
 * Side-Effects:
 *		  None, no changes only access.
 *		   
 * Exceptions:		
 *		  None.		   
 *	
 * Notes: 
 */
	int schedule::get_size() const;

private:
	vector<appointment*> schedule_of_appointments;
};

/* parse_appointment() - Read in lines from file, and return the appointment 
 *
 * Description: 
 *		  Parameter is a string with a line from the file.
 *		  Calls the string to vector function to seperate by #'s.
 *		  Tells from there which of the sub classes then goes to that and filles in the information, and returns an appointment with
 *		  the given information.
 *		  
 *		  Made to be called repeated from a loop.		  
 *
 * Inputs:
 *		  String line from a file
 *
 * Outputs:
 *		  Returns an appointment with information from the line.		 
 *		
 * Side-Effects:
 *		  Adds appointments, which changes each individual appointment variables.
 *		   
 * Exceptions:		
 *		  Throws runtime errors if not enough columns for a base appointment, or each sub class appointment.
 *		  Throws runtime error if in correct, or lacking appointment type.
 *	
 * Notes:  
 */
appointment *parse_appointment(string line);

#endif
Zach Almon (czal222)
CS 215 Lab 9 (Design document for program 3)
24 March 2014

Classes:

Appointment: Any given task or thing that must be done during a day of the week or month
	Data Members:
		string label: The name of the appointment
		string notes: Any notes for the appointment
	Methods:
		Appointment(String Labels, String Notes)
			Creates an Appointment with the specified label and notes
		Get_Label() const
			Simply returns what label is
		Get_Notes() const
			Simply returns what notes is
		Occurs_On(int day) const
			fully virtual, no implementation. to return true if the appointment happens on the given day.
		print(ostream &out) const
			writes the appointment to the outgoing stream, virtual, still prints out some.
		print_appointments(ostream& out) const
			fully virtual, used to print info to a file.



Daily_App:
Inherits from class Appointment.
	Data Members:
		string daily_Place: Where the Daily appointment is
		string daily_Time: What time the appointment is
	Methods:
		Daily_App(string labels_here, string notes_here, string time_of_day, string location)
			Constructor to create a Daily_appointment with given Time of day, location and also the Label and Notes from base class. calls appointment constructor for the label and notes part.
		print(ostream &out) const
			Writes the Daily Appointment to the outgoing stream
		Occurs_on(int day) const
			Returns True if a given appointment happens on the day, false if the appointment doesnt
		print_appointments(ostream& out) const
			used to print appointment info to a file. This is to print plain text so the program can read the file later.


Weekly_App:
Inherits from class Appointment.
	Data Members:
		string weekly_Place: Where the weekly appointment happens
		string weekly_Time: What time it happens
		string weekly_Day: What day of the week it happens on
	Methods:
		Weekly_App(string labels_here, string notes_here, int day_of_week, string time_of_day, string location)
			Constructor to create a Weekly Appointment with given day of the week, Time of day, location, and also the Label and Notes from base class. Calls the appointment constructor for the label and notes part.
		print(ostream &out) const
			Writes the Weekly Appointment to the outgoing stream
		Occurs_on(int day) const
			Returns True if a given appointment happens on the day, false if the appointment doesnt
		print_appointments(ostream& out) const
			used to print appointment info to a file. This is to print plain text so the program can read the file later.



Task:
Inherits from class Appointment.
	Data Members:
		int task_day_of_week
		int task_duration
	Methods:
		Task(string labels_here, string notes_here, int days, string dur)
			Constructor to create a Task with given day of the week, duration this task needs to be done and also the Label and Notes from base class. Calls the appointment constructor for the label and notes part.
		print(ostream &out) const
			Writes the Task to the outgoing stream
		Occurs_on(int day) const
			Returns True if a given appointment happens on the day, false if the appointment doesnt
		print_appointments(ostream& out) const
			used to print appointment info to a file. This is to print plain text so the program can read the file later.



Schedule:
Contains Appointment Objects
	Data Members:
		vector<Appointment*> schedule_of_Appointments: List of the appointments in this week/month/ FILE whichever it will be
	Methods:
		Schedule()
			No code, just makes the schedule to be worked on.
		~Schedule()
			deconstructor will loop over vector to delete its contents one at a time.
		Schedule_loader(istream& input_file)
			Will load the file into the Vector
		schedule_writer(ostream& output_file)
			will write the appointments to the file in plain text to be able to read and load from again.
		Add_Appointment(appointment* a)
			Will Add the appointment to the list of the appointments in the schedule vector
		Remove_Appointment(int App_Number)
			Will remove the appointment of the given number from the schedule
		Print_Schedule_Day(ostream &out, int day) const
			Writes the Appointments on a given day to the outgoing stream
		Print_Schedule_Week(ostream &out) const
			Writes the Schedule to the outgoing stream
		get_size() const
			returns the size of the vector of appointments as an integer.
		


Non-member Functions:


int day_string_to_int(string day_of_week);

	Returns an integer that represents the day 0-6. Parameter is the day of the week that is needed. 

string day_int_to_string(int day_num);

	Returns a string that contains the day name that coorisponds to the number in the parameter. 0 == "Sunday" for example.

string new_day_prompt(ostream &out);
	
	prompts for the day from the user. Returns a string. That will contain the day from the user. parameter is the out stream to the users screen.

int string_to_int(string str);

	given by the professor. parameter is a string, and the function will convert the string to an integer if possible. returns the int.

vector<string> split_string(string input);

	given by the professor. parameter is a string. it will take the string apart by the #'s and return them in a vector. Used solely by the next function.

appointment *parse_appointment(string line);

	parameter is a line. calls the split_string to seperate the line by #'s. Then takes each part and puts them into variables to read and interpret to put back together in an appointment. returns the pointer to said appointment. meant to be called in a loop to loop over each line in a file to add many appointments to a schedule.





int main(): Main Driver program
No parameters
Always returns 0, indicating no error

1: Create a Schedule
2: Ask user for input of the name,
2A: If user inputed nothing (Empty string/Enter without typeing) Exit loop and Proceed
2B: If user inputed a filename that works, exit loop and proceed
2C: If filename doesnt work, display a message that it didnt work, and return to top of loop
3: New Loop: Display the commands to Print Daily, Print Week, Add Appointment, Remove Appointment, Quit the Program, Save the File, Or save a NEW File.
4: Loop inside that Loop to take the Commands (D, W, A, R, Q, S, N or the lower case) if user inputs incorrectly
5:D - Loop again asking what day of week, then print the appointments on that day
6:W - Simply print all appointments on the schedule
7:A - Loop over asking for ([D]aily, [W]eekly, [T]ask) 
      Ask for Label         (All)
      Ask for Notes         (All)
      Ask for Location      (D, W)
      Ask for Time          (D, W)
      Ask for Day           (W, T)
      Ask for Duration      (T)
      Make Appointment, add to Schedule
8:R - Display List of Appointments in numbered form 0 - Last one
      Loop over the number of appointments in the list (Keep looping until its within definitions or -1 to cancel and leave loop)
      Remove Appointment from Schedule
9:Q - Quit the program, Leave the Main loop. End everything
10:S - Save the schedule FILE. Tell user file name.txt has saved
11:N - Prompt user for filename with extension, save the file with the given filename

















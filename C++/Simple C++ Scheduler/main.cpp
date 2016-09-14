#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "helpers.h"
#include "Classes.h"

using namespace std;

/* Zach Almon
 * CS 215, Spring 2014
 * Programming assignment 3
 * Last Updated: 6th April, 2014
 *
 * I DO have the code implemented for both sets of extra credit points (10 pts for Save/New File) (5 pts for Easy day names).
 *
 * Store a set appointments from a file, into a file, or make a new file.
 */

/* Main() - Main driver, gets user input
 *
 * Description: 
 *		  Create schedule, and get user input for a name to import a file, if nothing is entered (\n) then new file is created.
 *		  If name is correct and file is opened, load it into the new schedule. call the loader function then close file.
 *		  Loop over to get users input to View Daily, Weekly, Add, Remove, Save, create a New file, or Quit.
 *		  To view a daily record, ask for the day then display the day's record. To view a weekly record, then simply call
 *		  the weekly print function and it will show the entire week. For adding ask if its a Daily, Weekly, Task or Quit.
 *		  Ask for the label, notes, location (Daily/Weekly), time (Daily/Weekly), day (task/Weekly), duration (task) then
 *		  create a new appointment of that type, and add it with the adding function. To remove, ask for the number of which appointment
 *		  then call the remove function with that number. To save, simply call the writer function and overwrite the file, if 0 go to new file.
 *		  For a new file, ask for a name with extension, then write it. Quit simply breaks out of the loop and ends the program.
 *		  
 *		  
 * Inputs:
 *		  User inputs for File name, commands ([D], [W], [A], [R], [S], [N], or [Q]), sub-commands ([D], [W], [T], [Q], or -1), or new file name.
 *
 * Outputs:
 *		  prompt for user input, write to file, open new file and write to it. Return 0.
 *		
 * Side-Effects:
 *		  Calls multiple methods on the schedule class, and sub-appointment classes. Writes to files, and creates files
 *		   
 * Exceptions:		
 *		  Throws no exceptions, but handles different runtime errors.
 *	
 * Notes:
 *		  
 */
int main()
{
	//File name input
	string input;
	string Users_day;
	int Users_day_num;
	int flag = 0;
	//input for 2nd loop, used over and over
	string Next_line;
	//file object. used to open a file. and then open the file again or a new file.
	fstream file;

	string Remove_app_input;
	int remove_app_input_num;

	string Add_app;					//User input, D, W, T, Q
	string Add_app_type;			//Every App
	string Add_app_label;			//Every App
	string Add_app_notes;			//Every App
	string Add_app_location;		//Daily, Weekly
	string Add_app_time;			//Daily, Weekly
	string Add_app_day;				//Weekly, Tasks
	int Add_app_day_NUM;			//Weekly, Tasks (Number version)
	string Add_app_duration;		//Tasks Only

	//Create Schedule
	schedule New_Appointment;


	//Ask For File Name
    //A: If user inputed nothing (Empty string/Enter without typeing) Exit loop and Proceed
    //B: If user inputed a filename that works, exit loop and proceed
    //C: If filename doesnt work, display a message that it didnt work, and return to top of loop
	while (cin)
    {
        cout << "Please enter a File name with extension, or press enter for a new file: ";
        getline(cin, input);

		//If user enters nothing
		if (input.length() == 0){
			break;
		}
		
		else{
			file.open(input);
			//If file opened
			if (file.is_open()){
				New_Appointment.Schedule_loader(file);
				file.close();
				break;
			}
			cout << "Name did not work, please try again" << endl;
		}
		
	}

	cout << endl << endl;

	//Next Loop: Dislpay: 
	//You may view a [W]eekly or [D]aily schedule,
    //[A]dd a new appointment, [R]emove an appointment,
    //[S]ave the schedule, save as a [N]ew file, or [Q]uit.
	//Loop inside that Loop to take the Commands (D, W, A, R, Q, S, N or the lower case) if user inputs incorrectly
		//D - Loop again asking what day of week, then print the appointments on that day
		//W - Simply print all appointments on the schedule
		//A - Loop over asking for ([D]aily, [W]eekly, [T]ask) 
		//      Ask for Label         (All)
		//      Ask for Notes         (All)
		//      Ask for Location      (D, W)
		//      Ask for Time          (D, W)
		//      Ask for Day           (W, T)
		//      Ask for Duration      (T)
		//      Make Appointment, add to Schedule
		//R - Display List of Appointments in numbered form 0 - Last one
		//      Loop over the number of appointments in the list (Keep looping until its within definitions or -1 to cancel and leave loop)
		//      Remove Appointment from Schedule
		//Q - Quit the program, Leave the Main loop. End everything
		//S - Save the schedule FILE. Tell user file name.txt has saved
		//N - Prompt user for filename with extension, save the file with the given filename
	while(cin){
		cout << "You may view a [D]aily or [W]eekly schedule," << endl;
		cout << "[A]dd a new appointment, [R]emove an appointment, " << endl;
		cout << "[S]ave the schedule, save as a [N]ew file, or [Q]uit. " << endl;
		cin >> Next_line;

		if (Next_line == "D" || Next_line == "d"){
			//Prompts for the day name, Input will be returned as the day name, with 1st letter only captiolized.
			Users_day = new_day_prompt(cout);
			try{
				//Trys to convert day to numerical value.
				//Should always work theorically.
				Users_day_num = day_string_to_int(Users_day);
				flag = 1;
			}
			catch(runtime_error){
				//Should never happen here, Theorically (new day prompt should never return something other then whats expected)
				cout << "Invalid day please try again" << endl;
			}
			if (flag == 1){
				New_Appointment.print_Schedule_Day(cout, Users_day_num);
				cout << endl << endl;
				flag = 0;
			}
			else{
				cout << "There is nothing to display" << endl << endl;
			}
		}
		else if (Next_line == "W" || Next_line == "w"){
			//Prints out every appointment
			New_Appointment.print_Schedule_Week(cout);
			cout << endl << endl;
		}
		else if (Next_line == "A" || Next_line == "a"){
			//Needed a loop to find out which appointment type, or to quit
			while(cin){
				cout << "[D]aily, [W]eekly, [T]ask, or [Q]uit." << endl;
				cin >> Add_app;
				if (Add_app == "D" || Add_app == "d"){
					//Info asked in order of how the appointment's parameters go
					Add_app_type = "daily";
					cout << "What label should I give the appointment? ";
					cin >> Add_app_label;
					cout << "Enter notes: ";
					cin >> Add_app_notes;
					cout << "What time is the appointment? ";
					cin >> Add_app_time;
					cout << "Where is the appointment? ";
					cin >> Add_app_location;

					//New was needed as the add_appointment took only pointers
					New_Appointment.Add_Appointment(new daily_app(Add_app_label, Add_app_notes, Add_app_time, Add_app_location));
					break;
				}
				else if (Add_app == "W" || Add_app == "w"){
					//Info asked in order of how the appointment's parameters go
					Add_app_type = "weekly";
					cout << "What label should I give the appointment? ";
					cin >> Add_app_label;
					cout << "Enter notes: ";
					cin >> Add_app_notes;
					cout << "What time is the appointment? ";
					cin >> Add_app_time;
					cout << "Where is the appointment? ";
					cin >> Add_app_location;

					//Needed a specfic day, so had to loop over until user entered a correct day
					while(cin){
						cout << "What day is the appointment? ";
						cin >> Add_app_day;
						try{
							Add_app_day_NUM = day_string_to_int(Add_app_day);
							break;
						}
						catch(runtime_error){
							cout << "Invalid Day" << endl;
						}
					}

					//New was needed as the add_appointment took only pointers
					New_Appointment.Add_Appointment(new weekly_app(Add_app_label, Add_app_notes, Add_app_day_NUM, Add_app_time, Add_app_location));
					break;
					
				}
				else if (Add_app == "T" || Add_app == "t"){
					//Info asked in order of how the appointment's parameters go
					Add_app_type = "task";
					cout << "What label should I give the appointment? ";
					cin >> Add_app_label;
					cout << "Enter notes: ";
					cin >> Add_app_notes;

					//Needed a specfic day, so had to loop over until user entered a correct day
					while(cin){
						cout << "What day is the appointment? ";
						cin >> Add_app_day;
						try{
							Add_app_day_NUM = day_string_to_int(Add_app_day);
							break;
						}
						catch(runtime_error){
							cout << "Invalid Day" << endl;
						}
					}

					
					cout << "How long in minutes is the appointment going to be? ";
					cin >> Add_app_duration;

					//New was needed as the add_appointment took only pointers
					New_Appointment.Add_Appointment(new task(Add_app_label, Add_app_notes, Add_app_day_NUM, Add_app_duration));
					break;

				}
				else if(Add_app == "Q" || Add_app == "q"){
					break;
				}

				//Needed to repeat loop if one of these (or thier lower case) was not entered.
				else{
					cout << "Please input only [D], [W], [T], or [Q]" << endl;
				}

			}

			cout << endl << endl;
		}
		else if (Next_line == "R" || Next_line == "r"){

			//Outputs only if no appointments.
			if (New_Appointment.get_size() == 0){
				cout << "There are no appointments" << endl << endl;
			}

			//Will display 0-0 if only 1 appointment. 
			//As in, it displays numbers starting from 0 instead of 1. Did not have enough time to make this more user friendly.
			else{
				cout << "Remove which appointment? [0-" << New_Appointment.get_size() - 1 << ", -1 to cancel]" << endl;
				cin >> Remove_app_input;
				try{
					remove_app_input_num = string_to_int(Remove_app_input);
				}
				catch(runtime_error){
					cout << "Error was detected in Input, Please input only numbers 0-" << New_Appointment.get_size() - 1 << ", or -1 to cancel]" << endl;
				}
				New_Appointment.Remove_Appointment(remove_app_input_num);
			}

			cout << endl << endl;
		}
		else if (Next_line == "S" || Next_line == "s"){
			//Will tell user to pick N instead, as it doesnt have a name yet.
			if (input.length() == 0){
				cout << "File was not found, please choose [N] to make a new file instead" << endl;
			}
			//Will overwrite the file it was read from 
			else{
				file.open(input, fstream::out);
				New_Appointment.Schedule_writer(file);
				file.close();
				cout << "File saved Completely." << endl;
			}
			cout << endl << endl;
		}
		else if (Next_line == "N" || Next_line == "n"){
			//Asks for a new file name
			cout << "Please input a name for your file, With .txt extension: " << endl;
			cin >> input;
			//Saves to file.
			file.open(input, fstream::out);
			New_Appointment.Schedule_writer(file);
			file.close();
			cout << "File saved Completely." << endl << endl;
		}

		//Quits program
		else if (Next_line == "Q" || Next_line == "q"){
			break;
		}
		//Tells user to enter only these letters for commands, if the [N] boxed letters above didnt give them a hint.
		else{
			cout << "Please input only [D], [W], [A], [R], [S], [N], or [Q]" << endl << endl;
		}
	}



	pause_215(true);
	return 0;
}


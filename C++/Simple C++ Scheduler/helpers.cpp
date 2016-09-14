#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "helpers.h"
#include "Classes.h"
using namespace std;

//Unneeded functions that profressor provided. I dont use them at all.
//
//day_name function could have been used, but I had went another direction before i realized i could utilize it.
//
//string day_name(int day)
//{
//	if (day == SUNDAY)
//		return "Sunday";
//	else if (day == MONDAY)
//		return "Monday";
//	else if (day == TUESDAY)
//		return "Tuesday";
//	else if (day == WEDNESDAY)
//		return "Wednesday";
//	else if (day == THURSDAY)
//		return "Thursday";
//	else if (day == FRIDAY)
//		return "Friday";
//	else if (day == SATURDAY)
//		return "Saturday";
//
//	throw logic_error("invalid day");
//}
//
//prompt_day could not be used, i created my own for easier to read day names.
//
//int prompt_day()
//{
//	int day = -1;
//	do {
//		cout << "What day? [0 = Sunday, 6 = Saturday] ";
//		cin >> day;
//		if (cin.fail()) {
//			cin.clear();
//			cout << "Invalid day." << endl;
//		} else if (day < SUNDAY || day > SATURDAY) {
//			cout << "Day out of range." << endl;
//		}
//		// Throw away the rest of the line.
//		cin.ignore(200, '\n');
//	} while (day < SUNDAY || day > SATURDAY);
//
//	return day;
//}

//Asks for new day. Accepts all lower case or first uppercase letetr and rest lower. Returns first uppercase letetr and rest lower.
string new_day_prompt(ostream &out){
	string new_input;

	while(cin){
		out << "What day? (e.g. accepts \"Sunday\" or \"sunday\")" << endl;
		cin >> new_input;
		
		if (new_input == sunday || new_input == sunday2) {
			return sunday;
		}
		else if (new_input == monday || new_input == monday2) {
			return monday;
		}
		else if (new_input == tuesday || new_input == tuesday2) {
			return tuesday;
		}
		else if (new_input == wednesday || new_input == wednesday2) {
			return wednesday;
		}
		else if (new_input == thursday || new_input == thursday2) {
			return thursday;
		}
		else if (new_input == friday || new_input == friday2) {
			return friday;
		}
		else if (new_input == saturday || new_input == saturday2) {
			return saturday;
		}
		else{
			out << "Invalid Day" << endl;
		}
	}
}

//converts day number to day name in string. 0 == "Sunday" Type conversion.
string day_int_to_string(int day_num){
	switch(day_num){
	case SUNDAY:
		return sunday;
	case MONDAY:
		return monday;
	case TUESDAY:
		return tuesday;
	case WEDNESDAY:
		return wednesday;
	case THURSDAY:
		return thursday;
	case FRIDAY:
		return friday;
	case SATURDAY:
		return saturday;
	default:
		throw runtime_error("day out of range");
	}
}

//converts day string name to day number as an int. 0 == "Sunday" Type conversion.
int day_string_to_int(string day_of_week){

	if (day_of_week == sunday || day_of_week == sunday2) {
		return SUNDAY;
		}
	else if (day_of_week == monday || day_of_week == monday2) {
		return MONDAY;
	}
	else if (day_of_week == tuesday || day_of_week == tuesday2) {
		return TUESDAY;
	}
	else if (day_of_week == wednesday || day_of_week == wednesday2) {
		return WEDNESDAY;
	}
	else if (day_of_week == thursday || day_of_week == thursday2) {
		return THURSDAY;
	}
	else if (day_of_week == friday || day_of_week == friday2) {
		return FRIDAY;
	}
	else if (day_of_week == saturday || day_of_week == saturday2) {
		return SATURDAY;
	}
	else{
		throw runtime_error("Invalid day");
	}
}

// Convert a numeric string to an integer.  Throws an exception if it is not a number.
int string_to_int(string str)
{
	int num;
	istringstream instr(str);
	instr >> num;
	if (instr.fail())
		throw runtime_error("invalid number " + str);

	// Check for junk after the number.
	string remaining = "junk";
	getline(instr, remaining);

	// End of file or an empty string means there was no junk.
	if (instr.eof() || remaining == "")
		return num;
	else
		throw runtime_error("garbage after number " + str);
}

//Given function that seperates a file input line by #/
vector<string> split_string(string input)
{
	vector<string> pieces;

	// Start of the current field
	int field_start = 0;

	// Location of the next at sign.
	int next_at;
	do {
		// Find the #.  Returns the index, or string::npos if it wasn't
		// found.
		next_at = input.find('#', field_start);

		// If it wasn't found, add the last piece.
		if (next_at == string::npos)
			pieces.push_back(input.substr(field_start));
		// Or it was found, so add this piece
		else
			pieces.push_back(input.substr(field_start, next_at - field_start));

		// The next field starts just after the # 
		field_start = next_at + 1;

		// If there was no #, we're done.
	} while(next_at != string::npos);

	return pieces;
}

//function to parse the line and return a appointment to be added to a schedule
appointment *parse_appointment(string line)
{
	vector<string> columns = split_string(line);
	if (columns.size() < 3)
		throw runtime_error("not enough columns in: " + line);

	// Columns 1-3: type, label, notes
	string type = columns[0];
	string label = columns[1];
	string notes = columns[2];

	if (type == "weekly") {
		if (columns.size() < 6){
			throw runtime_error("not enough columns in: " + line);
		}
		string place = columns[3];
		string time = columns[4];
		int day = string_to_int(columns[5]);
		if (day < SUNDAY || day > SATURDAY){
			throw runtime_error("day out of range");
		}
		// Adjust this to match your class name and parameters.
		return new weekly_app(label, notes, day, time, place);
	}
	if (type == "daily"){
		if (columns.size() < 5){
			throw runtime_error("not enough columns in: " + line);
		}
		string place = columns[3];
		string time = columns[4];

		return new daily_app(label, notes, time, place);
	}
	if (type == "task"){
		if (columns.size() < 5){
			throw runtime_error("not enough columns in: " + line);
		}
		int day_of_the_week = string_to_int(columns[3]);
		string duration = columns[4];

		return new task(label, notes, day_of_the_week, duration);
	}


	// If we got here, we didn't handle the appointment type.
	throw runtime_error("unknown appointment type " + type);
}

//Given function to pause the output screen
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

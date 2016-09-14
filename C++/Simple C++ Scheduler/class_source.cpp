#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "helpers.h"
#include "Classes.h"
using namespace std;

//Done
appointment::appointment(string labels_here, string notes_here){
	label = labels_here;
	notes = notes_here;
}
string appointment::get_label() const{
	return label;
}
string appointment::get_notes() const{
	return notes;
}
void appointment::print(ostream &out) const{
	out << label;
	if (notes.length() != 0){
		out << " (" << notes << ")" << endl;
	}
	else{
		out << endl;
	}
}




//Done
daily_app::daily_app(string labels_here, string notes_here, string time_of_day, string location)
	: appointment(labels_here, notes_here){
	daily_time = time_of_day;
	daily_place = location;
}
void daily_app::print(ostream &out) const{
	appointment::print(out);
	out << "\tWhere: " << daily_place << endl;
	out << "\tWhen: " << daily_time << endl;

}
bool daily_app::occurs_on(int day) const{
	return true;
}
void daily_app::print_appointments(ostream& out) const{
	out << "daily#" << get_label() << "#" << get_notes() << "#" << daily_place << "#" << daily_time << endl;
}




//Done
weekly_app::weekly_app(string labels_here, string notes_here, int day_of_week, string time_of_day, string location)
	: appointment(labels_here, notes_here){
	weekly_day = day_of_week;
	weekly_time = time_of_day;
	weekly_place = location;
}
void weekly_app::print(ostream &out) const{
	appointment::print(out);
	out << "\tWhere: " << weekly_place << endl;
	out << "\tWhen: " << weekly_time << endl;

}
bool weekly_app::occurs_on(int day) const{

	if (day == weekly_day){
		return true;
	}
	else{
		return false;
	}

}
void weekly_app::print_appointments(ostream& out) const{
	out << "weekly#" << get_label() << "#" << get_notes() << "#" << weekly_place << "#" << weekly_time << "#" << weekly_day << endl;
}




//Done
task::task(string labels_here, string notes_here, int days, string dur)
	: appointment(labels_here, notes_here){
	task_day_of_week = days;
	task_duration = dur;
}
void task::print(ostream &out) const{
	appointment::print(out);
	out << "\tWhen: any time on " << day_int_to_string(task_day_of_week) << endl;
	out << "\tFor" << task_duration << " minutes" <<endl;

}
bool task::occurs_on(int day) const{
	if (day == task_day_of_week){
		return true;
	}
	else{
		return false;
	}
}
void task::print_appointments(ostream& out) const{
	out << "task#" << get_label() << "#" << get_notes() << "#" << task_day_of_week << "#" << task_duration << endl;
}



//Done
schedule::schedule(){

}
schedule::~schedule(){
	for (unsigned int i = 0; i < schedule_of_appointments.size(); i++){
		delete schedule_of_appointments[i];
	}
}
void schedule::Schedule_loader(istream& input_file){

	string lines;

	while(input_file){
		getline(input_file, lines);
		if (lines.length() == 0){
			break;
		}

		try{
			Add_Appointment(parse_appointment(lines));
		}
		catch(runtime_error err){
			cerr << err.what() << endl;
		}

	}
}
void schedule::Schedule_writer(ostream& output_file) const{
	for (unsigned int i = 0; i < schedule_of_appointments.size(); i++){
		schedule_of_appointments[i]->print_appointments(output_file);
	}
}
void schedule::Add_Appointment(appointment* a){
	schedule_of_appointments.push_back(a);
}
void schedule::Remove_Appointment(int App_Number){

	//Un-needed. Found the .erase(.begin + app_number) method to be easier
	//for (int i = App_Number; i < get_size(); i++){
	//	schedule_of_appointments[i - 1] = schedule_of_appointments[i];
	//}
	//schedule_of_appointments.pop_back();
	schedule_of_appointments.erase(schedule_of_appointments.begin() + App_Number);
}
void schedule::print_Schedule_Day(ostream &out, int day) const{
	for (unsigned int i = 0; i < schedule_of_appointments.size(); i++){
		if (schedule_of_appointments[i]->occurs_on(day)){
			schedule_of_appointments[i]->print(out);
		}
	}
}
void schedule::print_Schedule_Week(ostream &out) const{
	for (int i = 0; i < 7; i++){
		if (i == SUNDAY){
			out << sunday << ":" << endl;
		}
		if (i == MONDAY){
			out << monday << ":" <<  endl;
		}
		if (i == TUESDAY){
			out << tuesday << ":" <<  endl;
		}
		if (i == WEDNESDAY){
			out << wednesday << ":" <<  endl;
		}
		if (i == THURSDAY){
			out << thursday << ":" <<  endl;
		}
		if (i == FRIDAY){
			out << friday << ":" <<  endl;
		}
		if (i == SATURDAY){
			out << saturday << ":" <<  endl;
		}
		print_Schedule_Day(out, i);
	}
}
int schedule::get_size() const{
	int mysize;
	mysize = schedule_of_appointments.size();

	return mysize;
}


//#include <iostream>
//#include <fstream>
//#include <string>
//#include <sstream>
//#include <cstdlib>
//#include <vector>
//#include "high_score.h"
//using namespace std;
//
//High_score::High_score(){
//
//}
//
//void High_score::read_scores(){
//	string lines;
//	fstream file;
//
//	file.open("High_score_List.txt");
//	//If file opened
//	if (file.is_open()){
//		while(file){
//			getline(file, lines);
//			if (lines.length() == 0){
//				break;
//			}
//			score_list.push_back(lines);
//		}
//		file.close();
//	}
//}
//void High_score::add_score(string name, time_t time, int size, int mines){
//
//	long int t = static_cast<long int> (time);
//
//	string my_time;
//	string my_size;
//	string my_mines;
//	int counter = 0;
//	int top_counter = 0;
//	time_t each_time;
//
//	stringstream buffer;
//
//	string my_str1;
//	string my_str2;
//	
//	vector<string> score_broken_down;
//
//	//Need to convert time_t and int's to strings here
//
//
//	string new_score = name + "#" + my_time + "#" + my_size + "#" + my_mines;
//	//Need to convert from string to time_t also
//
//
//	for (int i = 0; i < score_list.size(); i++){
//		split_string(score_list[i], score_broken_down);
//	}
//
//	for (int i = 0; i < score_broken_down.size(); i++){
//		if (counter == 0){
//			top_counter++;
//			counter++;
//		}
//		else if (counter == 1){
//			counter++;
//			buffer = score_broken_down[i];
//
//			if(time < each_time){
//				for (int i = score_list.size() - 1; i != top_counter ; i--){
//					if(i == score_list.size() - 1){
//						score_list.push_back(score_list[i]);
//					}
//					else{
//						my_str1 = score_list[i];
//						score_list[i] = score_list[i-1];
//						score_list[i-1]= my_str1;
//
//					}
//
//				}
//				break;
//
//			}
//		}
//		else if (counter == 2){
//			counter++;
//		}
//		else if (counter == 3){
//			counter = 0;
//		}
//	}
//
//
//
//
//}
//void High_score::write_scores(){
//	string lines;
//	fstream file;
//
//	file.open("High_score_List.txt");
//	//If file opened
//	if (file.is_open()){
//		for (int i = 0; i < score_list.size(); i++){
//			file << score_list[i];
//		}
//	}
//}
//void High_score::display_scores(ostream &out){
//	int counter = 0;
//	int top_number_counter = 1;
//	vector<string> score_broken_down;
//
//	for (int i = 0; i < score_list.size(); i++){
//		split_string(score_list[i], score_broken_down);
//	}
//
//	//Score_broken_down is now 4x as big as score list
//
//	
//
//	for(int i = 0; i < 40; i++){
//		
//		if (counter == 0){
//			out << top_number_counter << ". " << score_broken_down[i];
//			top_number_counter++;
//			counter++;
//
//		}
//		else if (counter == 1){
//			out << " time: " << score_broken_down[i] << "seconds";
//			counter++;
//		}
//		else if (counter == 2){
//			out << " size: " << score_broken_down[i];
//			counter++;
//		}
//		else if (counter == 3){
//			out << " number of mines: " << score_broken_down[i];
//			counter = 0;
//			out << endl;
//		}
//	}
//}
//
////Saved as  name#time#size#number_of_mines
////Updates &Score_lister 4 times for each line
//void High_score::split_string(string input, vector<string> &Score_lister){
//
//	// Start of the current field
//	int field_start = 0;
//
//	// Location of the next at sign.
//	int next_at;
//	do {
//		// Find the #.  Returns the index, or string::npos if it wasn't
//		// found.
//		next_at = input.find('#', field_start);
//
//		// If it wasn't found, add the last piece.
//		if (next_at == string::npos)
//			Score_lister.push_back(input.substr(field_start));
//		// Or it was found, so add this piece
//		else
//			Score_lister.push_back(input.substr(field_start, next_at - field_start));
//
//		// The next field starts just after the # 
//		field_start = next_at + 1;
//
//		// If there was no #, we're done.
//	} while(next_at != string::npos);
//}

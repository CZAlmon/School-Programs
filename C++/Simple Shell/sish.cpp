#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <wait.h>
#include <iomanip>

using namespace std;

vector<string> scanner(string file, vector<string> &vect);
vector<string> parser(vector<string> &token, vector<string> &v1, vector<string> &v2, int &parameter_numbers);
int shell(vector<string> token, vector<string> &LP, vector<pid_t> &LP_pid);
int assignshell(vector<string> token, string &output);

int main(){
	
	string prompt = ">";
	string command = "";

	cout << "sish " << prompt << " ";
	getline(cin, command);
	//If no input (just hits enter), then loop until you get something or the user hits ctrl+d (the if statement)
	while(command == ""){
		cout << "empty string" << endl;
        cout << "sish " << prompt << " ";
		getline(cin,command);
		
		if (cin.eof()){
			command = "bye";
		}
	}
	
	
	// Used for variable declaration for built in command
	vector<string> variable;
	// Used to store the value for the declared variable in the built in command
	vector<string> value;
	
	variable.push_back("PATH");
	value.push_back("/bin:/usr/bin");
	

	// Used to store type for token
	vector<string> type;
	// Used to store the token
	vector<string> token;

	// Used to tell the usage for the token in the shell		
	vector<string> usage;
	
	//Listprocs vectors. One for command string name, other for PID
	vector<string> list_processes;
	vector<pid_t> list_processes_pid;
	int status;
	pid_t result;
	
	
	//To know how many PM to run or assignto
	int number_of_parameters = 0;

	int ShowTokens = 0;
	int Result = 0;

	while (command != "bye"){
		// Returns token vector
		token = scanner(command, type);
		// Returns usage vector
		usage = parser(token, variable, value, number_of_parameters);


		//If statement if user changes showtokens
		if (token[0] == "ShowTokens" && usage[0] != "WRONG_COMMAND"){

			stringstream convert(token[2]); // stringstream used for the conversion initialized with the contents of Text

			if (!(convert >> Result)){  //give the value to Result using the characters in the string
				Result = 0;
			}

			ShowTokens = Result;
			Result = 0;

		}
		else{
			// Error occured in parser
			if (usage[0] == "WRONG_COMMAND"){
				cout << "Invalid command" << endl;
			}
			else{
				//Special if statement to print stuff out.
				if (ShowTokens == 1){
					if (token[0] == "#"){}
					else{
						for (size_t i = 0; i < token.size(); i++){
							// Format for column printing
						        string column1 = "Token type = ";
   						     	string column2 = "Token = ";
        						string column3 = "Usage = ";

							column1 += type[i];
							column2 += token[i];
							column3 += usage[i];
							cout << left << setw(22) << column1;
							cout << left << setw(20) << column2;
							cout << left << setw(20) << column3  << endl;}
					}
				}

				if (token[0] == "#"){
					//Do nothing for this command
				}
				//defprompt only changes the output prompt
				if (token[0] == "defprompt"){
					prompt = token[1];
				}
				//cd calls the chdir function which changes the current working directory
				if (token[0] == "cd"){
					
					if(chdir(token[1].c_str()) != 0){
				
						perror("sish");
					
					}
				
					
				}
				//Listprocs displays the current processes
				if (token[0] == "listprocs"){
					
					if(list_processes.size() == 0){
						
						cout << "No Processes at this time" << endl;
						
					}
					else{
						for(size_t i = 0; i < list_processes.size(); i++){
				
							cout << "Process " << i << ": "<< list_processes[i] << endl;
						}	
					}
					
					
				}
				//runs a command
				if(token[0] == "run"){
					//run function
					
					int run_out = shell(token, list_processes, list_processes_pid);
					if (run_out != 0){
						perror("sish");
					}
					
				}
				if(token[0] == "assignto"){
					// string to catch assignto
					string output;
					int assign = assignshell(token, output);
					// If assignto had error
					if (assign != 0)
						perror("sish");
					else{
						// Pushes back variable entered by user to variable and stores output to value
						variable.push_back(token[1]);
						value.push_back(output);
						}
										
				}
			}
		}
		
		for(size_t i = 0; i < list_processes.size(); i++){
		
			result = waitpid(list_processes_pid[i], &status, WNOHANG);
			if (result == 0) {
			  // Child still alive
			} 
			else if (result == -1) {
			  // Error 
			} 
			else {
				list_processes.erase(list_processes.begin()+i);
				list_processes_pid.erase(list_processes_pid.begin()+i);
			}
		}
		
		
		
		token.clear();
		type.clear();
		usage.clear();
		cout << endl << "sish " << prompt << " ";
		
		getline(cin, command);
		//If no input (just hits enter), then loop until you get something or the user hits ctrl+d (the if statement)
		while(command == ""){
			cout << "empty string" << endl;
			cout << "sish " << prompt << " ";
			getline(cin,command);
			
			if (cin.eof()){
				command = "bye";
			}
	}
	}
	return 0;
}

vector<string> scanner(string input, vector<string> &type){
	string keyword = "defprompt cd listprocs bye run assignto <bg>";
	vector<string> token;
	size_t found = 0;
	
	for(size_t i = 0; i < input.size(); i++){
		if(input[i] == '"'){
			input.erase(input.begin()+i);
		}
	}
	
	// Loops through string and places contents into vector
	while (input != ""){
		// searches for space
		found = input.find(" ", 0);
		// searches for string
		if (input.compare(0, 1, "\"") == 0){
			// Places word inside quote in vector
			size_t nextq = input.find("\"", 1);
			string quote = input.substr(0, nextq + 1);
			token.push_back(quote);
			input = input.substr(nextq + 2, input.length());
		}
		else{
			if (found > 256){
				token.push_back(input);
				break;
			}
		string newstr = input.substr(0, found);
		token.push_back(newstr);
		input = input.substr(found + 1, input.length());
		}
	}
	// Loop to see what type each token is
	for (size_t i = 0; i < token.size(); i++){
		// If token is a variable
		if (token[i].compare(0, 1, "$") == 0){
			type.push_back("variable");
			continue;
		}
		// if token is a character
		if (token[i] == "=" || token[i] == "#"){
			type.push_back("metachar");
			continue;
		}
		// if toke is inside a quote
		if (token[i].compare(0, 1, "\"") == 0){
			type.push_back("string");
			continue;
		}
		// if token is a special keyword
		if (keyword.find(token[i], 0) != string::npos){
			type.push_back("keyword");
			continue;
		}
		else
			type.push_back("word");
	}
	return token;
}

vector<string> parser(vector<string> &token, vector<string> &variable, vector<string> &value, int &parameter_numbers){
	//To tell main how many parameters there are
	parameter_numbers = 0;
	

	vector<string> usage;
	
	if (token[0] == "#"){
		return usage;
	}
	// Check for invalid statement
	if (token.size() == 1 && token[0] != "bye" && token[0] != "listprocs"){
		usage.push_back("WRONG_COMMAND");
		return usage;
	}
	
	
	if (token[0] == "listprocs"){
		//List all processes

		if (token.size() != 1){
			usage[0] = "WRONG_COMMAND";
			return usage;
		}

		usage.push_back("keyword/command");
		return usage;
	}
	
	// for variable statement
	if (token[1] == "="){
		char *buffer = (char*)token[0].c_str();
		
		// user wants to change showtokens
		if (token[0] == "ShowTokens"){
			
			usage.push_back("variable");
			usage.push_back("assignment");
			usage.push_back("variableDef");	
			return usage;
		}
		// check size of 3 and first character not a number
		if (token.size() != 3 || !(isalpha(buffer[0]))){
			usage.push_back("WRONG_COMMAND");
			return usage;
		}
		usage.push_back("variable");
		usage.push_back("assignment");
		usage.push_back("variableDef");	
		
		
		// Check if variable is already in vector
		for (size_t i = 0; i < variable.size(); i++){
			if (token[0] == variable[i]){
				value[i] = token[2];
				return usage;
			}
		}
		
		// Create new variable by storing contents from another variable
		for (size_t i = 0; i < variable.size(); i++){
			if (token[2] == variable[i]){
				variable.push_back(token[0]);
				value.push_back(value[i]);
				return usage;
			}
		}
		
		//New variable and value
		variable.push_back(token[0]);
		value.push_back(token[2]);

		
		return usage;
	}

	if (token[0] == "defprompt"){

		if (token.size() < 2 || token.size() > 2){
			usage.push_back("WRONG_COMMAND");
			return usage;
		}
		usage.push_back("keyword/command");
		usage.push_back("Prompt/parameter");
		return usage;

	}

	if (token[0] == "cd"){

		if (token.size() < 2 || token.size() > 2){
			usage[0] = "WRONG_COMMAND";
			return usage;
		}

		usage.push_back("keyword/command");
		usage.push_back("Directory/parameter");
		return usage;

	}

	// assignto function
	if (token[0] == "assignto"){
		if (token.size() < 3){
			usage[0] = "WRONG_COMMAND";
			return usage;
		}

		usage.push_back("assignto");
		usage.push_back("variable");
		usage.push_back("cmd");
		
		// List parmaters for assignto
		for (size_t i = 3; i < token.size(); i++){
			// checks for variable in loop
			if (token[i].compare(0, 1, "$") == 0){
				string newstr = token[i].substr(1, token[i].length() - 1);
				vector<string>::iterator it;
				it = find(variable.begin(), variable.end(), newstr);
				if (it != variable.end()){
					int pos = it - variable.begin();
					token[i] = value[pos];
					}
				}

			int num = i - 2;
			stringstream ss;
			ss << num;
			usage.push_back("parameter " + ss.str());
			parameter_numbers++;
		}

		return usage;

	}

	if (token[0] == "run"){
		if (token.size() < 2){
			usage[0] = "WRONG_COMMAND";
			return usage;
		}

		usage.push_back("run");
		usage.push_back("cmd");
		// checks for variable in loop
		for (size_t i = 2; i < token.size(); i++){
			if (token[i].compare(0, 1, "$") == 0){
				string newstr = token[i].substr(1, token[i].length() - 1);
				vector<string>::iterator it;
				it = find(variable.begin(), variable.end(), newstr);
				if (it != variable.end()){
					int pos = it - variable.begin();
					token[i] = value[pos];
					cout << token[i] << value[pos] << endl;
				}
			}
			
			int num = i - 1;
			stringstream ss;
			ss << num;
			usage.push_back("parameter " + ss.str());
			parameter_numbers++;
		}
		
		return usage;
	}
	else{
		usage[0] = "WRONG_COMMAND";
		return usage;
	}
}

int shell(vector<string> token, vector<string> &LP, vector<pid_t> &LP_pid){
    pid_t pid;
	pid_t wpid;
    int status;
	bool background;

	token.erase(token.begin());
       // Iterator to check for background
	vector<string>:: iterator it;
	it = find(token.begin(), token.end(), "<bg>");
	
	if(it != token.end()){
		background = true;
	}
	else{
		background = false;
	}
	
	

	// convert vector to char*
	vector<char*> argv(token.size()+1);
	for(size_t i = 0; i < token.size(); i++){
		//If bg is present then make the argv point to NULL. bg is not for the program to run
		if(token[i] == "bg"){
			argv[i] = NULL;
		}
		else{
			argv[i] = &token[i][0];
		}
	}

	
	
    pid = fork();
	
	if(background){
		LP.push_back(token[1]);
		LP_pid.push_back(pid);
	}
		
    if (pid == 0){
            if (execvp(argv[0],argv.data())  == -1){
                perror("sish");
			}
            exit(EXIT_FAILURE);
    }
    else if (pid < 0){
            return -1;
    }
    else{
		// if background found dont wait
		if(background){}
		else{
			// wait for child to finish
			do{
				wpid = waitpid(pid, &status, WUNTRACED);
				if(wpid == 1){}
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
	}
    return 0;
}


int assignshell(vector<string> token, string &output){
	int pipe2ch[2], child2pip[2], read_bytes;
	pid_t childpid;
	char readbuffer[256];

	// vector to char*
	vector<char*> argv(token.size() + 1);
	for (size_t i = 0; i < token.size(); i++)
		argv[i] = &token[i][0];

	if (pipe(pipe2ch) != 0 || pipe(child2pip) != 0){
		cerr << "Failed to pipe\n";
		exit(1);
		}
	childpid = fork();

	// Error checking
	if (childpid < 0){
		cout << "Fork failed" << endl;
		exit(-1);
		}
	else if (childpid == 0){
		if (dup2(pipe2ch[0], 0) != 0 || close(pipe2ch[0]) != 0 || close(pipe2ch[1]) != 0){
			cerr << "Child: failed to set up standard input\n";
			exit(1);
			}
		if (dup2(child2pip[1], 1) != 1 || close(child2pip[1]) != 0 || close(child2pip[0]) != 0)
			{
			cerr << "Child: failed to set up standard output\n";
			exit(1);
			}

		if (execvp(argv[0], argv.data()) == -1){
			cerr << "Failed to execute " << endl;
			exit(1);
			}
		}
	else{
		close(pipe2ch[0]);
		close(child2pip[1]);

		int nbytes = argv.size();
		if (write(pipe2ch[1], argv.data(), nbytes) != nbytes){
			cerr << "Parent: short write to child\n";
			exit(1);
			}
		close(pipe2ch[1]);
		while (1){
			read_bytes = read(child2pip[0], readbuffer, sizeof(readbuffer) - 1);
			if (read_bytes <= 0)
				break;
			readbuffer[read_bytes] = '\0';
			output += readbuffer;
			}
		close(child2pip[0]);
		}
	return 0;
	}


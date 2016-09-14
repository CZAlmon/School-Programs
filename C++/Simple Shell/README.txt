Program 4
CS 485G
Carmon Zachary Almon 
Ronnel Turner 

Files included:

	README.txt
	Makefile
	sish.cpp


Description of Program:
	
	Get input From user;
	Main while loop:
		Enter while loop, if command doesn't equal "bye" then continue to loop;
		In the loop, first run the command string through the scanner, which returns a vector of the tokens/keywords/commands;
			Scanner:
				Takes a string input and a vector passed by reference. returns a vector
				The vector passed by reference is the type detected by the scanner for each token scanned from string
				The string is broken into different tokens and put into a new vector. 
				Each token is parsed to tell what type of token it is (this is pushed onto the vector passed by ref.)
				The new vector of tokens is returned
		After the scanner, the vector is sent through parser with the variables, their values, and an int to determine number of parameters.
			Parser:
				Takes 3 vectors and an int passed by reference. returns a vector
				The first vector is the token vector that holds only the tokens, not the type.
				The second vector is a variable vector.
				The third vector is a value vector for the values of variables given in the second vector 
					( These 2 vectors are tied together that is to say.)
				The integer is to tell the main program how many parameters there are in the command.
				The parser then checks for "#" character, if so then do nothing.
				The parser then checks for number of tokens given.
				The parser then checks for each command and whether there is enough tokens for that command or
					not enough.
				In each command statement, a new usage vector is then created by pushing back whether a token is
					a command/keyword/token/parameter/variable/directory/prompt
				The usage vector is returned.				
		Back in the while loop, the return vector of the parser is the usage of each token/keyword/command
		After the parser if Showtokens is the first part of the token vector, convert the value that should be assigned to it to 
			an integer and assign it to Showtokens.
		Else we go to the next set of commands. Check if usage indexed at 0 is "WRONG_COMMAND" then display invalid command
			and go to end of loop
		If usage[0] isn't "WRONG_COMMAND" then go on to:
			If Showtokens = 1 then Loop over the size of token (and usage they are same size) and print off each token and its usage
			If token[0] = # then do nothing
			If token[0] = defprompt then change the prompt to whatever token[1] is.
			If token[0] = listprocs then loop over listprocesses vector and output its contents to user.
			If token[0] = cd calls the chdir command on token[1].c_str() then display the current working directory.
			If token[0] = run calls the shell function to perform its process:
				Shell:
					Takes 3 vectors (the last 2 passed by reference)
					The first is the token vector.
					The second is a vector of ongoing processes.
					The third is the vector of each of those process' pid_t's.
					
					The function checks to see if bg is within the token vector. It sets a bool to be used later.
					The function then changes the vector of string tokens to a vector of char* tokens.
						If bg is present then don't put bg into the new vector of char *. Set it equal to NULL here.
					Then fork.
					Here if bg is set then push the command into the vector of ongoing processes.
					Then push the child's pid_t (which is what the pid_t variable is set to in the parent process)
						onto the vector of pid_t's
					Child process will make the exec run command and its parameters. Then will exit.
					Parent will wait unless the bg bool is true then will just continue on.
				
				
			If token[0] = assignto calls the assigntoshell function to preform its process:
				assigntoshell:
				
				
				
		After the commands have been checked(or performed) then loop over the Listprocesses vector to check if the processes
			may still be running. If one has ended then erase the info and its pid_t (you know by the pid_t vector)
		
		clear all vectors (token, type, usage)
		display sish and prompt and get next command line. if eof is detected (ctrl+d) then also exit loop.
		The main while loop is now looped over as long as ctrl+d or "bye" has not be entered.
	return 0 on successful completion. 
	
	
	
Limitations:
	
1.	Sometimes after using the run command it takes up to 2 tries to exit the program. 
		eg:      
			sish > run cmd
			(Now for some reason it takes 2 "bye"s to exit the program)
			sish > bye
			sish > bye
			regular-shell-prompt > 
		
2.	Sometimes when input is "run echo $(Variable)" the value for said variable will print off 3 times like so:
			MyVar = Foobar      (Already defined within program)
			
			sish > run echo $MyVar
			FoobarFoobar
			Foobar
			
		Unknown cause. Have checked with gdb and ddd and it only prints off one time for them.
			I suspect it has something to do with the fork, exec, and/or child process.

3.	ShowTokens cannot be shown with echo. It is a stand-alone variable from the other values.
		You can still change its value and have the instructions printed off, but it's value cannot be shown.
		
4.	
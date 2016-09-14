README.txt

Program 5: MyCloud Server and It's clients


In this project we made our own server/cloud file storage and management service called MyCloud

	MyCloud server: Accepts requests to store a file, retrieve a file, delete a file, and list the files stored on the server. 
					Must Provide a correct Secret Key and Request Type
	
	MyCloud clients: Four client MyCloud applications that will store, retrieve, delete, and list files on the MyCloud server.

This project was written in C++ and utilized the RIO library calls provided by the textbook (in csapp.c and csapp.h) to create and manage the TCP/IP socket interface.


CS 485G
Carmon Zachary Almon 	
Ronnel Turner 			

Files included:

	README.txt
	DOC.txt 
	Makefile
	mcdel.cpp
	mcget.cpp
	mclist.cpp
	mcput.cpp
	Server.cpp
	client.h
	
Files from TextBook companion website, http://csapp.cs.cmu.edu/public/code.html:
	csapp.h
	csapp.c


/***************
 * Algorithms  *
 ***************/
 
	Server:
		To run the server pass the Port name/number then a arbitrary secret key for client access.
		
		The Server will start to listen for connections, and inside an infinite while loop will start to accept them.
		
		The server will accept the connection, and get the struct object that contains the data from client.
		
		The server will check the secret key. If it is not correct it will display an error and Will not send anything back to client
		
		If the secret key is correct the server will check the request type (put,get,del,list), if this is wrong send the client an error
		
		If the request type is valid:
			For put:
				Open a file with the filename given from the struct, write the contents of the struct there.
				Close the file.
				Save the filename in the Server.
				
				Send back: 0 for success -1 for error
				
			For get:
				Open the file with the filename given from the struct, write the contents of it to the struct.
				Close the file.
				Save the number of bytes of the message into the struct.
				
				Send back: 0 for success -1 for error, size of the file of the message, the message of 100k Max.
				
			For delete:
				Check for Filename in list.
				Delete it from the list and move the list up.
				
				Send back: 0 for success -1 for error
				
			for list:
				Copy contents of the Filename List into the message of the struct to send back
				Get the size of this and put into struct.
				
				Send back: 0 for success -1 for error, size of file list, file list.
				
				
		
	mcput Client:
		To run the put client, pass the MachineName, Port name/number, the secret key the server requires, and a filename.
			The File to put on the server must be read in from the user and stored to be sent.
		
		Write the message from stdin to the struct to send to server.
		Send to server.
		Get response. 
		Display Success or failure.
		

	mcget Client:
		To run the get client, pass the MachineName, Port name/number, the secret key the server requires, and a filename.
		
		Write the message to the struct to send to server.
		Send to server.
		Get response. 
		Display contents to client.
		Display Success or failure.
		

	mcdel Client:
		To run the delete client, pass the MachineName, Port name/number, the secret key the server requires, and a filename.
		
		Write the message to the struct to send to server.
		Send to server.
		Get response. 
		Display Success or failure.
		
	
	mclist Client:
		To run the put client, pass the MachineName, Port name/number, and the secret key the server requires.
	
		Write the message to the struct to send to server.
		Send to server.
		Get response. 
		Display contents to client.
		Display Success or failure.

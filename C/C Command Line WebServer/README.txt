==============
TCP GET Server
==============

Zip Contents:

	AcceptTCPConnection.c		Supplied Code										--Supplied from: http://cs.ecs.baylor.edu/~donahoo/practical/CSockets/textcode.html
	CreatTCPServerSocket.c		Supplied Code										--Supplied from: http://cs.ecs.baylor.edu/~donahoo/practical/CSockets/textcode.html
	DieWithError.c				Supplied Code										--Supplied from: http://cs.ecs.baylor.edu/~donahoo/practical/CSockets/textcode.html
	TCPEchoServer.h				Supplied Code										--Supplied from: http://cs.ecs.baylor.edu/~donahoo/practical/CSockets/textcode.html
	TCPEchoServer.c				Supplied Code										--Supplied from: http://cs.ecs.baylor.edu/~donahoo/practical/CSockets/textcode.html
	TCPEchoServer-Fork.c		Supplied, but modified Code.						--Supplied from: http://cs.ecs.baylor.edu/~donahoo/practical/CSockets/textcode.html
	HandleTCPClient.c			Supplied, but modified Code.						--Supplied from: http://cs.ecs.baylor.edu/~donahoo/practical/CSockets/textcode.html
	index.html					Self-created HTML file to test imbedded images.
	

This TCP Server is a Server that will take a GET request from a browser and return back the file requested.

Description and Usage
=====================

This program is a modified server that will process a GET request from a browser and send back a request file of the type .txt, .html, .jpg, or .gif. This server is modified from code that originally just echoed back the GET request to the browser. The files modified are TCPEchoServer-Fork.c and HandleTCPClient.c, with a majority in HandleTCPClient.c.

To run the program, download the zip, unzip the zip, run the Makefile and then use the command:

./TCPEchoServer-Fork <Port Number> <Root Directory of Files to be sent>

Where <Port Number> is the port number to be listening on.
Where <Root Directory of Files to be sent> is the absolute path to the directory in which the files that you want to supply to whatever browser makes requests reside in.


Code Description
================

TCPEchoServer-Fork.c is the main file that gets called. It will check for the 2 parameters, this is one change from the original, as the original only took a port number. The second change is where HandleTCPClient is called. A second parameter of the Root Directory was added to be able to search for files specified by the user of the server.

HandleTCPClient is the main file that does work. It is significantly change from the original. Pseudocode lays below of its process.

HandleTCPClient.c Pseudocode:
	
	Create variables needed later on, define a buffer of 1024 to be used.
	Receive message from client, store in buffer of size 1024, even if all of GET request does not fit, the part (GET [File] HTTP/1.1) we need will be in the first few indices. 
	Check if GET Request. IF it is we will continue, if not ignore and close the socket and child process.
		Get the characters from the 4th index (The index after 'GET ' which is the start of the file requested).
		If the Filename size is less than 2, we know the only character sent is / which we need to respond with index.html
			Set absolute path name from the supplied Root directory plus index.html.
			Try to open index.html.
			If it fails send back to the browser that 404 Index could not be found.
			Else index was found and opened.
				Create header with 200 message, set its length since it is a static header.
				Send header to browser.
				Start loop which will read in chunks of the file at a time and send the data to the browser.
					Read file up to buffer size
					Check to make sure something was read; else we are done.
					Error Check Read
					Make a pointer to the buffer
					Start a loop to send data so that all data may be sent.
						Send data and get the bytes written back
						Error check send
						Subtract bytes written from bytes’ read
						Add bytes written to Pointer so it knows what was sent and keeps track
						Repeat till bytes read is 0
		Else the Filename was given so we should do more work.
			Set absolute path name with the given root directory plus the File name extracted before.
			Try to open file. If the file could not be opened, send back 404 File not found to browser.
				If file was opened then:
				Check to see what type of file was requested.
				In the absolute path string, search for '.', get the index.
				Search index+1, check if t,T,h,H,j,J,g,G and set which type is requested depending on content.
				Set the header depending on what type of file is requested and set the header length.
				Send header to browser. 
				Start loop which will read in chunks of the file at a time and send the data to the browser.
					Read file up to buffer size
					Check to make sure something was read; else we are done.
					Error Check Read
					Make a pointer to the buffer
					Start a loop to send data so that all data may be sent.
						Send data and get the bytes written back
						Error check send
						Subtract bytes written from bytes’ read
						Add bytes written to Pointer so it knows what was sent and keeps track
						Repeat till bytes read is 0
				
	Close socket
	Void function so no return value to main.
	

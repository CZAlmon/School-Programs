#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define RCVBUFSIZE 32   /* Size of receive buffer */

#define DIRECTORYBUFFSIZE 1024   /* Max Size of my Buffer for storing the Directory String */

void DieWithError(char *errorMessage);  /* Error handling function */

void HandleTCPClient(int clntSocket, char *RootDirectory)
{
    char echoBuffer[DIRECTORYBUFFSIZE];        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */
	
	char GETVariable[DIRECTORYBUFFSIZE];	//Buffer for Filename String from GET Request
	
	const char Char_G = 'G';
	const char Char_E = 'E';
	const char Char_T = 'T';
	const char Char_Space = ' ';
	
	int FilenameSize = 0;
	
	
	//printf("%s was the given Root Directory\n", RootDirectory);

    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, DIRECTORYBUFFSIZE, 0)) < 0)
        DieWithError("recv() failed");

	//Check if GET Request
	if (echoBuffer[0] == Char_G && echoBuffer[1] == Char_E && echoBuffer[2] == Char_T){
		
		//printf("If Statement Worked\n");
		
		//printf("%s\n", echoBuffer);
		//Get The filename, 'GET ' is given and static, get Everything from there to the next space
		while (echoBuffer[FilenameSize+4] != Char_Space){
			GETVariable[FilenameSize] = echoBuffer[FilenameSize+4];
			FilenameSize++;
		}
		
		//printf("%s\n", GETVariable);
		//printf("\n\n\n\n\n\n\n\n");
		//If Filename is less than 2, nothing but / was given, send back index.html
		if (FilenameSize < 2){
			
			//No Filename Sent, send back index.html, set absolutepath to index.html
			char absolutePath[DIRECTORYBUFFSIZE];
			char Indexpath[11] = "index.html";
			char * i;
			int j = 0;
			for (i=RootDirectory; *i; i++){
				absolutePath[j] = *i;
				j++;
			}
			int m = 0;
			int k = 0;
			for(k = j; k < j+11; k++){
				absolutePath[k] = Indexpath[m];
				m++;
			}
			absolutePath[k+1] = '\0';
			//printf("%s\n", absolutePath);
			
			//printf("No File Given\n");
			
			//Try to open file.
			FILE *FilePointer;
			FilePointer = fopen(absolutePath, "r");
			
			if (FilePointer == 0){
				//File Not Found
				//Send:
				
				//printf("File Not Opened Successfully\n");
				
				char FourZeroFour[DIRECTORYBUFFSIZE] = "HTTP/1.0 404 Not Found\nContent-Type: text/html\n\n404 Index File Not Found"; //Content-Length: 1024
				
				if (send(clntSocket, FourZeroFour, 72, 0) < 0)
					DieWithError("send() failed");

			}
			else{
				//File Found and opened successfully
				//printf("Index Found and Opened\n");
				
				//Create Header and Its size
				char *HeaderString;
				int myBuffSize;
				
				HeaderString = "HTTP/1.0 200 OK\nContent-Type: text/html\n\n";
				myBuffSize = 41;
				
				
				//Send header to browser
				if (send(clntSocket, HeaderString, myBuffSize, 0) < 0)
					DieWithError("send() failed");
				
				char MediaBuff[DIRECTORYBUFFSIZE];
				int FilePointerDescriptor = fileno(FilePointer);
				//Loop over file reading some data, and trying to send it, then repeat till it is done.
				while (1) {
					//Read data from File, into buff, size 1024
					int bytes_read = read(FilePointerDescriptor, MediaBuff, DIRECTORYBUFFSIZE);
					if (bytes_read == 0) // We're done reading from the file
						break;
					if (bytes_read < 0) {
						DieWithError("read() failed");
					}
					
					//Pointer to buff to keep track of what has been written
					void *TempPoint = MediaBuff;
					//Write in a loop in case a portion needs to be sent again
					while (bytes_read > 0) {
						int bytes_written = send(clntSocket, TempPoint, DIRECTORYBUFFSIZE, 0);
						if (bytes_written <= 0) {
							DieWithError("send() failed");
						}
						bytes_read -= bytes_written;
						TempPoint += bytes_written;
					}
				}
				
				
			}
				
		
		}
		//Filename is bigger then 1. Something of a filename may have been given.
		else{
			//Make Absolute path to whatever filename/path was given
			char absolutePath[DIRECTORYBUFFSIZE];
			char * i;
			int j = 0;
			for (i=RootDirectory; *i; i++){
				absolutePath[j] = *i;
				j++;
			}
			//printf("%s\n", absolutePath);
			
			int m = 1;
			int k = 0;
			for(k = j; k < j+FilenameSize; k++){
				absolutePath[k] = GETVariable[m];
				m++;
			}
			absolutePath[k+1] = '\0';
			//printf("%s\n", absolutePath);
			
			//Try to open file
			FILE *FilePointer;
			FilePointer = fopen(absolutePath, "r");
			
			
			if (FilePointer == 0){
				//File Not Found
				//Send:
				
				//printf("File Not Opened Successfully\n");
				
				char FourZeroFour[DIRECTORYBUFFSIZE] = "HTTP/1.0 404 Not Found\nContent-Type: text/html\n\n404 File Not Found"; //Content-Length: 1024
				
				if (send(clntSocket, FourZeroFour, 66, 0) < 0)
					DieWithError("send() failed");

			}
			else{
				//File opened successfully
				
				//printf("File Opened Successfully\n");
				
				//Get What Type
				char TextType = 't';
				char HTMLType = 'h';
				char ImgType = 'j';
				char GifType = 'g';
				int WhatType = 0;
				
				int IndexForChar = 0;
				
				//printf("Here?");
				
				/*
					This next part is a good algorithm I think.
					Check to see what type of file was requested.
					In the absolute path string, search for '.', get the index.
					Search index+1, check if t,T,h,H,j,J,g,G and set which type is requested depending on content.
				*/
				while (absolutePath[IndexForChar] != '\0'){
					if(absolutePath[IndexForChar] == '.'){
						break;
					}
					IndexForChar++;
				}
				
				//Set What type to send back based on whats given
				//I dont have to handle anything but those four types, error handling for anything but that is not given
				if(absolutePath[IndexForChar+1] == TextType || absolutePath[IndexForChar+1] == toupper(TextType)){
					WhatType = 1;
				}
				else if(absolutePath[IndexForChar+1] == HTMLType || absolutePath[IndexForChar+1] == toupper(HTMLType)){
					WhatType = 2;
				}
				else if(absolutePath[IndexForChar+1] == ImgType || absolutePath[IndexForChar+1] == toupper(ImgType)){
					WhatType = 3;
				}
				else if(absolutePath[IndexForChar+1] == GifType || absolutePath[IndexForChar+1] == toupper(GifType)){
					WhatType = 4;
				}
				else{
					DieWithError("type error");
				}
				
				//Create Header and its size based on what is requested
				char *HeaderString;
				int myBuffSize = 0;
				
				if (WhatType == 1){
					HeaderString = "HTTP/1.0 200 OK\nContent-Type: text/plain\n\n";
					myBuffSize = 42;
				}
				else if (WhatType == 2){
					HeaderString = "HTTP/1.0 200 OK\nContent-Type: text/html\n\n";
					myBuffSize = 41;
				
				}
				else if (WhatType == 3){
					HeaderString = "HTTP/1.0 200 OK\nContent-Type: image/jpeg\n\n";
					myBuffSize = 42;
				}
				else if (WhatType == 4){
					HeaderString = "HTTP/1.0 200 OK\nContent-Type: image/gif\n\n";
					myBuffSize = 41;
				}
				
				//printf("%s This is the HeaderString\n", HeaderString);
				
				//Send Header
				if (send(clntSocket, HeaderString, myBuffSize, 0) < 0)
					DieWithError("send() failed");
				
				char MediaBuff[DIRECTORYBUFFSIZE];
				int FilePointerDescriptor = fileno(FilePointer);
				
				//Same as above, Read a portion and send it, multiple times if needed.
				//	When there are no bytes left to read left break and finish.
				while (1) {
					
					int bytes_read = read(FilePointerDescriptor, MediaBuff, DIRECTORYBUFFSIZE);
					if (bytes_read == 0) // We're done reading from the file
						break;

					if (bytes_read < 0) {
						DieWithError("read() failed");
					}

					void *TempPoint = MediaBuff;
					
					while (bytes_read > 0) {
						int bytes_written = send(clntSocket, TempPoint, DIRECTORYBUFFSIZE, 0);
						if (bytes_written <= 0) {
							DieWithError("send() failed");
						}
						bytes_read -= bytes_written;
						TempPoint += bytes_written;
					}
				}
				
				
			}
			
			
		}
		
		
	}
	else{
		//Not a Get Request, Ignore
	}
	
	
	//printf("%d\n", Loopcounter);

    close(clntSocket);    /* Close client socket */
}

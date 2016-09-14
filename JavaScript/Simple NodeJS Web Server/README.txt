### NodeJS Web Server


The components:
	1.	Command Window
	2.	Server-side Program
	3.	readFile()  - Server Initialization Function
	4.	onRequest() - Server Function
	5.	User-side Browser
	6.	Parameter File
	7.	Log File

The interfaces:
	1.	Nodejs is used to start the server.
	2.	The server uses readFile() to search for and read parameters from the parameter file.
	3.	Server displays in the command window whether or not it was successfully initialized and on what port.
	4.	The browser issues a request to the server.
	5.	The server uses onRequest() to process a request.
	6.	The requested data or an error message is returned to the browser.
	7.	A log entry for a request and its status is recorded in the log file.
	8.	The request and its status is reported in the command window.





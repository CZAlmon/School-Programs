### Simple PHP Web Program


##### Purpose:

Provide a web program consisting of  a web page with JavaScript and corresponding PHP server program to handle requests for race track data. The request web page has the following fields in a form:

##### Preconditions:

An HTML Webpage containing javascript code that invokes/calls the php file.

##### Postconditions:

The expected HTML page is returned the browser with all specified messages and data in their specified formats. If there are javascript errors, appropriate error boxes will pop up.


###### JavaScript:

The Javascript code does what processing it can before passing the request to the php code. The javascript code will pull information from the form data and parse it, making sure the month, day, year are all within bounds (1-12, 1-31, 2010-2015, respectively), as well as parsing the abbreviation for the track code (must be 2 or 3 alphabetic characters only), and the race number (1-15). Display errors one at a time, but all of them. Do not invoke the php program until every bit of data is good.


###### PHP:

Opens a .csv file and reads in data about horse races and stats. When invoked by the javascript program, it will assume good data being sent to it, then try to find the information in the csv file. IT will do calculations and display something on the screen. If the race/track/date combination does not produce results (not in file) for any reason then it will display any and all errors from the given data (Bad race number, bad track number, bad date, etc etc). It will display every error on the returned HTML page. If something is found (a race matches with input) then the program will display a table with information from the csv file. 


![Image of Workflow](https://github.com/CZAlmon/School-Programs/blob/master/PHP/Simple%20PHP%20Web%20Program/Graphic.png)

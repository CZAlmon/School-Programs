<?php
		// program3.php
		// Author: Carmon Zachary Almon
		// Date: 10-18-2015
		// Purpose:
			//  This program parses requests for race data, attempts to locate the requested race in cs316raceresults.csv, and 
			//  returns results of that race to the requesting browser. 
			//  If the requested race cannot be found, the program returns appropriate error messages to the browser.
		// Preconditions:
			//  Request queries are received with five fields: day, month, year, track, and race number. 
			//  Race results are contained in cs316raceresults.csv. Each entry in the results file should contain 10 fields: 
			//  	The date of the race, the abbreviated name of the racetrack, the race number, 
			//		the name of a competing horse, its finishing placement in the race, the distance the horse won or lost by, 
			//		its speed rating, its final odds, its morning odds, and its expected speed rating.
		// Postconditions:
			//  If cs316raceresults.csv cannot be opened, the server returns “Error opening file cs316raceresults.csv” to the browser. 
			//  Otherwise, the specified date, track, and race number are displayed on the browser. 
			//  If there are entries in the results file that match the specified data, then each entry is displayed in a table, 
			//  	ordered by finishing placement according to the example.
			//  If no entries can be found which contain the specified date, track, and race number, 
			//		then the message “Requested race not found” is also returned to the browser. 
			//  Additionally, if no entries exist for the specified date at all, the message “No races on this date” is also returned 
			//		to the browser. 
			//	Additionally, if no entries exist for the specified track at all, the message “No races on this track” is also returned 
			//		to the browser. 
			//	Additionally, if no entries exist for the specified race number at all, the message “No races for this race number” 
			//		is also returned to the browser.
			
	$Month = $_POST['month'];
	$Day = $_POST['day'];
	$Year = $_POST['year'];
	$Track_before = $_POST['track'];
	$Race = $_POST['raceNum'];
	//$Race = "$Race";
	$Track = "\"$Track_before\"";
	
	//Add the 0 onto the month and day if they are only one digit
	if($Month < 10){
		$Month = "0$Month";
	}
	if($Day < 10){
		$Day = "0$Day";
	}
	//Compile the ISO date
	$Complete_Date = "$Month/$Day/$Year";
	
	// Start of error handler code
	error_reporting(E_ALL);   // Enable all error checking
	$return = set_error_handler("MyError");  // set error handling function
	// Error handler function, called when PHP runtime error detected
	function MyError($errno,$errstr,$errfile,$errline) {
		print ("(ERR: $errno) ($errstr) ($errfile) (Line: $errline) <br>");
		return true;
	}
	//End of error handling
	
	//File Variable Names:
	$How_Many_Horses = 0;
	$Horse = array();
	$Finish = array();
	$LenAdj = array();
	$MSpeed = array();
	$PostOdds = array();
	$MlOdds = array();
	$ESpeed = array();
	
	$myfile = fopen("cs316raceresults.csv", "r") or die("Error opening file cs316raceresults.csv");
	//$Filecontents = fread($myfile,filesize("cs316raceresults.csv"));
	
	//race results cannot be found in the race results file for the date/track/race combination, but there were race results for that date, track, and race number for other races
	//"Requested Race Not Found"
	$Race_Not_Found = false;
	
	//there are no race requests for this date for any race display:
	//"Requested Race Not Found" && "No Races on this date"
	$No_Races_On_This_Date = false;
	
	//No race results for this track
	//"Requested Race Not Found" && "No races on this track"
	$No_Races_On_This_Track = false;
	
	//No race results for this race number for any date and track
	//"Requested Race Not Found" && "No races for this race number"
	$Race_Number_Not_In_File = false;
	
	//If there is an error, $Race_Not_Found will always be displayed. 
	//Display any and all errors!!
	
	//Temp Variables
	$Temp_Date = false;
	$Temp_Track = false;
	$Temp_Race = false;
	$Temp_Found = false;
	
	//read first line
	$line = explode(',',fgets($myfile, 1024));
	
	//Read line by line the file and print it
	while(! feof($myfile)){
		
		//First checks to see if its found. If something is found then set the temp variable
		//		and the permenant variable as true. The temp will get reset while the permenant will not,
		//			The permenant variable is to send back error data, if it is still false then it will get sent back as an error
		if($line[0] == $Complete_Date){
			$Temp_Date = true;
			$No_Races_On_This_Date = true;
		}
		if($line[1] == $Track){
			$Temp_Track = true;
			$No_Races_On_This_Track = true;
		}
		if($line[2] == $Race){
			$Temp_Race = true;
			$Race_Number_Not_In_File = true;
		}
		
		//If all 3 TEMP VARIABLES were found (This is important to distinguish between different lines)
		//	Then set race is found, and the temp variable.
		if($Temp_Date && $Temp_Track && $Temp_Race){
			$Temp_Found = true;
			$Race_Not_Found = true;
		}
		
		if($Race_Not_Found && $Temp_Found){
			$How_Many_Horses = $How_Many_Horses + 1;
			array_push($Horse, "$line[3]");
			array_push($Finish, "$line[4]");
			array_push($LenAdj, "$line[5]");
			array_push($MSpeed, "$line[6]");
			array_push($PostOdds, "$line[7]");
			array_push($MlOdds, "$line[8]");
			array_push($ESpeed, "$line[9]");
		}
		
		$Temp_Date = false;
		$Temp_Track = false;
		$Temp_Race = false;
		$Temp_Found = false;
		
		//read next line
		$line = explode(',',fgets($myfile, 1024));
	}
		
	//Print off table of data
	if($Race_Not_Found){
		
		print("<h1>Date: $Complete_Date <br> Track: $Track_before <br> Race Number: $Race");
		
		print("<table border=\"1\"");
		print("<tr>");
		print("<td>Finish</td><td>Name</td><td>Length</td><td>Speed Rating</td><td>Post Odds</td><td>Morning Odds</td><td>Expert Rating</td>");
		print("</tr>");
		for($i = 0; $i < $How_Many_Horses; $i++){
			print("<tr>");
			print("<td>$Finish[$i]</td><td>$Horse[$i]</td><td>$LenAdj[$i]</td><td>$MSpeed[$i]</td><td>$PostOdds[$i]</td><td>$MlOdds[$i]</td><td>$ESpeed[$i]</td>");
			print("</tr>");
		}
		print("</table>");
		
		/*
		 <table border="1">
			 <tr>
				 <td></td>
			 </tr>
		 </table>
		 */
	}
	//Print off error's
	else{
		print("<h1>Date: $Complete_Date <br> Track: $Track_before <br> Race Number: $Race");
		print("<br>Requested Race Not Found");
		
		if(!$No_Races_On_This_Date){
			print("<br>No Races on this date");
		}
		if(!$No_Races_On_This_Track){
			print("<br>No Races on this Track");
		}
		if(!$Race_Number_Not_In_File){
			print("<br>No Races for this race number");
		}
		print("</h1>");
	}
		
	
	//Close file
	fclose($myfile);
	
	//$teststring = "<h2>This is working</h2>";
	//print($Month . ", " . $Day . ", " . $Year . ", " . $Track . ", " . $Race . ", " . $Complete_Date);
	//print($teststring);
	//Return to browser.
	return true;
	
	
?>
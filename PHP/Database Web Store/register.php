<!--

File: products.php
Author: Carmon Zachary Almon, Dylan Wise
Date: 4/25/2016
Course: CS 405G - Database Systems - University of Kentucky
Description: See README.txt
Usage: Made to be used in conjuction with functioning database and other webpage files. See README.txt

-->

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<html>
<style>

body {
    background-color: rgb(0,93,170);
} 

h1 {
	color: white;
	text-align: center;
}
h2 {
	color: white;
}
h3 {
	color: white;
}
h4 {
	color: white;
}

p {
	color: white;
	text-align: center;
}


ul {
    list-style-type: none;
    margin: 0;
    padding: 0;
    overflow: hidden;
    background-color: #333;
}

li {
    float: left;
}

li a {
    display: inline-block;
    color: white;
    text-align: center;
    padding: 14px 16px;
    text-decoration: none;
}

li a:hover {
    background-color: #111;
}

li {
    border-right: 1px solid #bbb;
}


span {
	color: white;
}

legend {
	color: white;
}


<!--Links for menu -->
</style>

<head> 
<title>Database Store Products</title>
</head>

<h1>Welcome to the Database Store, Registration Page</h1>

<ul>
<li><a href = "http://www.cs.uky.edu/~czal222/CS405G/index.php">Home</a></li>
<li><a href = "http://www.cs.uky.edu/~czal222/CS405G/products.php">Products Page</a></li>
<li><a href = "http://www.cs.uky.edu/~czal222/CS405G/customer.php">Customer Page</a></li>
<li><a href = "http://www.cs.uky.edu/~czal222/CS405G/employee.php">Employee Page</a></li>
<li><a href = "http://www.cs.uky.edu/~czal222/CS405G/register.php">Registration Page</a></li>
<li><a href = "http://www.cs.uky.edu/~czal222/CS405G/login.php"><?php

$CookiesEnabled = true;
$CustLoggedIn = false;

$CustName = "";

if(count($_COOKIE) > 0) {
    $CookiesEnabled = true;
} 
else {
    $CookiesEnabled = false;
	print "<script type='text/javascript'>alert('Cookies need to be enabled to log in to add to basket and order.')</script>";
	print "Please enable Cookies and Login.";
}

$cookie_name = "DatabaseStore-CZADMW405G";


if(isset($_COOKIE[$cookie_name]) && $CookiesEnabled) {
    $CustLoggedIn = true;
	$CustName = $_COOKIE[$cookie_name];
	print "You are logged in as: $CustName";
} 
elseif (!isset($_COOKIE[$cookie_name]) && $CookiesEnabled) {
    $CustLoggedIn = false;
	print "Login";
}

?></a></li>
<li><a href = "http://www.cs.uky.edu/~czal222/CS405G/logout.php">Log Out</a></li>
</ul>




<?php

//Contains Servername, the username, and the pasword of the MySQL server we will use
$UK_servername = "delphi.cs.uky.edu";
$My_username = "czal222";
$My_password = "u0613596";

//connection string
$connection = new mysqli($UK_servername, $My_username, $My_password);

//If failed, show error
if ($connection->connect_error) {
        die("Connection failed: " . $connection->connect_error);
}

//select database to use
$connection->select_db("czal222");

//    ----Database Data

$string_query = "select Username from Staff";

//prepare the query
$report_query = $connection->prepare("$string_query");

//Execute, if there was an error, tell the user
if(!$report_query->execute()){
	$errormessage = $report_query->error;
	echo "$errormessage <br >";
	echo "Try again";
	exit();
}

//Get our results, put them into a 2dimensional array
$report_query->bind_result($Username);
$Staff_Array = array();
while($report_query->fetch()){
	$values = Array($Username);
	array_push($Staff_Array, $values);
}

////////////Above is Staff Array, Below is Customer Array

$string_query = "select Username, UserIDNum from Customers";

//prepare the query
$report_query = $connection->prepare("$string_query");

//Execute, if there was an error, tell the user
if(!$report_query->execute()){
	$errormessage = $report_query->error;
	echo "$errormessage <br >";
	echo "Try again";
	exit();
}


//Get our results, put them into a 2dimensional array
$report_query->bind_result($Username, $UserIDNum);
$Customers_Array = array();
while($report_query->fetch()){
	$values = Array($Username, $UserIDNum);
	array_push($Customers_Array, $values);
}

// ---- End of Database Data


//print_r($Customers_Array);
//print "<br>";
//print_r($Staff_Array);



//RIGHT HERE. If User is logged in, even if they hit the submit button, the POST execution will NEVER HAPPEN. Because it is stuck inside the else statement, it will never hit unless they log out.
//			The submit button will not work if the user is logged in!

if ($CustLoggedIn){
	
	print "<p>You are already logged in as: $CustName</p>";
	
}
else{
	
	if ($_SERVER["REQUEST_METHOD"] == "POST") {
		
		$NewUserID = 00000000;
		
		//Validation
		if (empty($_POST["name"])) {
			$nameErr = "Name is required";
		} 
		else {
			
			$name = test_input($_POST["name"]);
			
			// check if name only contains letters and whitespace
			if (!preg_match("/^[a-zA-Z\d]*$/",$name)) {
				$nameErr = "Only letters and Numbers allowed";
			}
			
			//Given Username is acceptable by definition, now to check if it already exists
			if ($nameErr == ""){
				
				//print "This was Reached as well 123!";
				
				
								
				$usernameMatch = false;
				$MyCounter = 0;
				$counter = 0;
				
				foreach($Staff_Array as $innerArray){
					//print $innerArray[0];
					//print "  $name <br>";
					//print $innerArray[1];
					//print "  $password<br>";
					
					if ($innerArray[0] == $name){
						$usernameMatch = true;
						$MyCounter = $counter;
					}
					
					$counter++;

				}
				
				$counter = 0;
				
				foreach($Customers_Array as $innerArray){
					//print $innerArray[0];
					//print "  $name <br>";
					//print $innerArray[1];
					//print "  $password<br>";
					
					if ($innerArray[0] == $name){
						$usernameMatch = true;
						$MyCounter = $counter;
					}
					
					$counter++;

				}
				
				if ($usernameMatch){
					$nameErr = "That username already exists! Please try another username.";
				}
				
				//Get random number and make sure it is unique against other user ID numbers
				//Random Number:
				$num = str_pad(mt_rand(1,99999999),8,'0',STR_PAD_LEFT);
				
				//print "<p>$num<br></p>";
				
				$NumberIsNotUnique = false;
				
				while(!$NumberIsNotUnique){
					
					$didanumbermatch = false;
					
					foreach($Customers_Array as $innerArray){
						if ($innerArray[1] == $num){
							$didanumbermatch = true;
						}
					}
					
					if ($didanumbermatch){
						$num = str_pad(mt_rand(1,99999999),8,'0',STR_PAD_LEFT);
						$didanumbermatch = false;
					}
					else{
						$NumberIsNotUnique = true;
						$NewUserID = $num;
					}
					
				}
				
			}
			
		}

		if (empty($_POST["password"])) {
			$passwordErr = "password is required";
			} 
		else {
			$password = test_input($_POST["password"]);
			// check if name only contains letters and whitespace
			if (!preg_match("/^[a-zA-Z\d]*$/",$password)) {
				$passwordErr = "Only letters and Numbers allowed";
			}
		}
		
		
		//print "This was reached.";
		//print "<br>$passwordErr<br>$nameErr";
		
		
		//Given Username and password are acceptable by definition, and no Username exists 	
		
		if ($nameErr == "" && $passwordErr == ""){
			
			
			$CleanName = test_input($_POST["name"]);
			$CleanPassword = test_input($_POST["password"]);
			$IsVIPCustomer = 0;
			
			//print "<p>ADDED:<br>$name<br>$password<br>$NewUserID</p>";
			
			//String insert method didnt work. Had to prepare and then bind to work
			//$String_Insert = "INSERT INTO Customers(Username, Password, UserIDNum, IsVIPCustomer) VALUES ($name, $password, $NewUserID, FALSE)";
			//$Insert_report = $connection->prepare("$String_Insert");
			
			
			$Resgitration_query = $connection->prepare("INSERT INTO Customers(Username, Password, UserIDNum, IsVIPCustomer) VALUES(?, ?, ?, ?)");
			
			//Bind the parameters to the query
			$Resgitration_query->bind_param("ssss", $CleanName, $CleanPassword, $NewUserID, $IsVIPCustomer);
			
			//Execute the query, if an error, print that to the user, otherwise tell them they were successful
			if(!$Resgitration_query->execute()){
				$errormessage = $actor_query->error;
				echo "$errormessage";
				echo "<br >";
				echo "<p>Go back and retry your registration again, something went wrong.</p>";
				return;
			}
			
			echo "<p>You are now a Customer, $name, Thank you. Please <b>login</b> and visit our product page.</p>";
			
		}
		
		//$_POST["name"] = "";
		//$_POST["password"] = "";
		
		
	}
	
}


function test_input($data) {
$data = trim($data);
$data = stripslashes($data);
$data = htmlspecialchars($data);
return $data;
}

?>


<h2>Register:</h2>
<h4>Please enter a username and password to use. Usernames and password must be shorter than 20 characters and can only contain Alphabetic and Numeral characters.</h4>
<span class="error">* required field.</span><br>
<span>Username and Password can not be longer than 20 characters</span><br><br>
<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
	<fieldset>
	<legend>User Information:</legend>
   <span>Username: <input type="text" name="name" value="<?php echo $name;?>" maxlength="20"></span>
   <span class="error">* <?php echo $nameErr;?></span>
   <br><br>
    <span>Password:  <input type="password" name="password" value="" maxlength="20"></span>
   <span class="error">* <?php echo $passwordErr;?></span></textarea>
   <br><br>
   <span>First Name:  <input type="text" name="FirstName" value="" maxlength="30"></span>
   <br><br>
   <span>Last Name:  <input type="text" name="LastName" value="" maxlength="30"></span>
   <br><br>
   <span>Physical Address:  <input type="text" name="Address" value="" maxlength="30"></span>
   <br><br>
   <span>Email Address:  <input type="text" name="Email" value="" maxlength="30"></span>
   <br><br> 
   <input type="submit" name="submit" value="Submit">
   </fieldset>
</form>








</html>
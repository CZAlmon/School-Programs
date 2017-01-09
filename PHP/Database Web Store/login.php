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

<h1>Welcome to the Database Store, Login Page</h1>

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

//If user already logged in, redirect back to index page
if ($CustLoggedIn){
	print "<script type='text/javascript'>alert('You are already logged in as $CustName')</script>";
	print "<meta http-equiv=\"refresh\" content=\"0;url= index.php\">";
}


//Contains Servername, the username, and the pasword of the MySQL server we will use
$UK_servername = "";
$My_username = "";
$My_password = "";

//connection string
$connection = new mysqli($UK_servername, $My_username, $My_password);

//If failed, show error
if ($connection->connect_error) {
        die("Connection failed: " . $connection->connect_error);
}

//select database to use
$connection->select_db("");


//    ----Database Data

$string_query = "select Username, Password from Staff";

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
$report_query->bind_result($Username, $Password);
$Staff_Array = array();
while($report_query->fetch()){
	$values = Array($Username, $Password);
	array_push($Staff_Array, $values);
}

////////////Above is Staff Array, Below is Customer Array

$string_query = "select Username, Password from Customers";

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
$report_query->bind_result($Username, $Password);
$Customers_Array = array();
while($report_query->fetch()){
	$values = Array($Username, $Password);
	array_push($Customers_Array, $values);
}

// ---- End of Database Data





// define variables and set to empty values
$nameErr = $passwordErr = "";
$name = $password = "";

//Handle POST
if ($_SERVER["REQUEST_METHOD"] == "POST") {

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
	
	$usernameMatch = false;
	$passwordMatch = false;
	$MyCounter = 0;
	$counter = 0;
	
	if ($nameErr == "" && $passwordErr == ""){
		//We know that each element in innerarray is 2 items long. Check innerarray[0]
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
		
		
		//print $counter;
		//print "<br>";
		//print $MyCounter;
		
		//If Found, else not found
		if ($usernameMatch){
			
			if ($Staff_Array[$MyCounter][1] == $password){
				$passwordMatch = true;
			}
			elseif ($Customers_Array[$MyCounter][1] == $password){
				$passwordMatch = true;
			}
			else{
				$nameErr = "Username/Password does not exist/match";
			}
			
		}
		else{
			$nameErr = "Username/Password does not exist/match";
			$passwordErr = "Username/Password does not exist/match";
		}
		
		if ($usernameMatch && $passwordMatch){
			//Success, Logged in
			$cookie_name = "DatabaseStore-CZADMW405G";
			setcookie($cookie_name, $name, time() + (86400 * 30), '/');
			
			print "<script type='text/javascript'>alert('You are now logged in $name')</script>";
			print "<meta http-equiv=\"refresh\" content=\"0;url= index.php\">";
			
		}
		
	}
	
}


function test_input($data) {
$data = trim($data);
$data = stripslashes($data);
$data = htmlspecialchars($data);
return $data;
}

?>


<h2>Login</h2>
<span class="error">* required field.</span><br>
<span>Username and Password can not be longer than 20 characters</span>
<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
	<fieldset>
	<legend>User Information:</legend>
   <span>Username: <input type="text" name="name" value="<?php echo $name;?>" maxlength="20"></span>
   <span class="error">* <?php echo $nameErr;?></span>
   <br><br>
    <span>Password: <input type="password" name="password" value="" maxlength="20"></span>
   <span class="error">* <?php echo $passwordErr;?></span></textarea>
   <br><br>
   <input type="submit" name="submit" value="Submit">
   </fieldset>
</form>















</html>

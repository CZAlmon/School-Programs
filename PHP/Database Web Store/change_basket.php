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
	text-align: center;
}
h3 {
	color: white;
	text-align: center;
}
h4 {
	color: white;
	text-align: center;
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


<!--Links for menu -->
</style>

<head> 
<title>Database Store Products</title>
</head>

<h1>Welcome to the Database Store, Customer Page</h1>

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

function test_input($data) {
	$data = trim($data);
	$data = stripslashes($data);
	$data = htmlspecialchars($data);
	return $data;
}

//reset($_POST);

$Keys = array_keys($_POST);

//print_r($Keys);
//print $_POST["New_Quantity"];

$StringGiven = $Keys[1];
$NewArray = explode("-", $StringGiven);

//print_r($NewArray);

$Users_ID_Number = $NewArray[0];
$ItemNumbertoChange = $NewArray[1];
$ItemsNewQuantity = $_POST["New_Quantity"];


//Checks for login ------------------------------------------
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
$connection->select_db("czal222");


//    ----Database Data

//Below is Customer Array

$string_query = "select Username from Customers";

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
$Customers_Array = array();
while($report_query->fetch()){
	$values = Array($Username);
	array_push($Customers_Array, $values);
}

// ---- End of Database Data

$IsCustomerNotStaff = false;
if ($CustLoggedIn){
		
	foreach($Customers_Array as $UserNameTemp){
		//print "$UserNameTemp[0] : $CustName <br>";
		if($CustName == $UserNameTemp[0]){
			$IsCustomerNotStaff = true;
		}
	}	
}


if(!$IsCustomerNotStaff){
	print "<script type='text/javascript'>alert('You need to be a Customer to view this page!!')</script>";
	print "<meta http-equiv=\"refresh\" content=\"0;url= index.php\">";
}
//End checks for login ----------------------------------------------


if ($ItemsNewQuantity == "") {
	
} 
else {
	//print $ItemsNewQuantity;
	$NewQuantity = test_input($ItemsNewQuantity);
	//print $NewQuantity;
	
	// check if name only contains letters and whitespace
	if (!preg_match("/^[\d]*$/", $NewQuantity)) {
		print "<script type='text/javascript'>alert('Only the number Zero or Positive Numbers allowed')</script>";
		print "<meta http-equiv=\"refresh\" content=\"0;url= customer.php\">";
	}
	else{
		//print $NewQuantity;
		
		if ($NewQuantity == 0){
			//print "Zero";
			
			$DeleteString = "DELETE FROM Baskets WHERE UserIDNum='$Users_ID_Number' and ItemNum='$ItemNumbertoChange'";
			
			//print "$DeleteString";
			
			$DeleteReport = $connection->prepare("$DeleteString");
		
			//Execute, if there was an error, tell the user
			if(!$DeleteReport->execute()){
				$errormessage = $DeleteReport->error;
				echo "$errormessage <br >";
				echo "Try again";
				exit();
			}
			
			print "<script type='text/javascript'>alert('Item has been removed from your Cart.')</script>";
			print "<meta http-equiv=\"refresh\" content=\"0;url= customer.php\">";
			
		}
		else{
			//print "More Than Zero";
			
			$updateString = "UPDATE Baskets SET Quantity='$NewQuantity' WHERE UserIDNum='$Users_ID_Number' and ItemNum='$ItemNumbertoChange'";
			
			$UpdateReport = $connection->prepare("$updateString");
			
			//Execute, if there was an error, tell the user
			if(!$UpdateReport->execute()){
				$errormessage = $UpdateReport->error;
				echo "$errormessage <br >";
				echo "Try again";
				exit();
			}
			
			print "<script type='text/javascript'>alert('Item has been updated in your Cart.')</script>";
			print "<meta http-equiv=\"refresh\" content=\"0;url= customer.php\">";
			
			
		}
		
		
	}
}




?>




</html>

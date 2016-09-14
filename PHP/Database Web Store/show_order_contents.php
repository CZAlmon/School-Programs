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


th {
	color: white;
}

td {
	color: white;
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

reset($_POST);

$OrderNumberToShow = key($_POST);

//print_r($_POST);
//print "<br>";
//print empty($_POST);
//print "<br>$OrderNumberToShow";




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

//If POST is not Empty, meaning we got some POST Data
if(!empty($_POST)){
	
	$string_query = "select ItemNum, CostAtPOS, Quantity from Orders where OrderNum='$OrderNumberToShow'";

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
	$report_query->bind_result($ItemNum, $CostAtPOS, $Quantity);
	$OrderArray = array();
	$OrderItems = array();
	while($report_query->fetch()){
		$values = Array($ItemNum, $CostAtPOS, $Quantity);
		$anotherValues = $ItemNum;
		array_push($OrderItems, $anotherValues);
		array_push($OrderArray, $values);
	}
	
	//print_r($OrderArray);
	//print_r($OrderItems);
	
	$ItemNumandValues = array();
	
	foreach($OrderItems as $ItemValue){
		
		$tempString = "select ItemName, ItemNum, ItemPictureURL from Inventory where ItemNum='$ItemValue'";
		
		$tempQuery = $connection->prepare("$tempString");
		
		if(!$tempQuery->execute()){
			$errormessage = $tempQuery->error;
			echo "$errormessage <br >";
			echo "Try again";
			exit();
		}
		
		$tempQuery->bind_result($ItemName, $ItemNumber, $ItemPictureURL);
		while($tempQuery->fetch()){
			$values = Array($ItemNumber, $ItemPictureURL, $ItemName);
			array_push($ItemNumandValues, $values);
		}
		
		
	}
	
	//print_r($ItemNumandValues);
	
	//Print table of order contents
	echo "<center>";
	echo "<h2>Order Number $OrderNumberToShow:</h2>";
	echo "<table border='5'>";
	echo "<tr><th>Item Picture</th><th>Item Name</th><th>Item Number</th><th>Item Cost</th><th>Quantity</th>";
	$counter = 0;
	$totalCost = 0;
	foreach($OrderArray as $innerArray){
		if(is_array($innerArray)){
			
			if ($innerArray[0] = $ItemNumandValues[$counter][0]){
				echo "<tr>";
				
				print "<td><img src=\"/~czal222/CS405G/Images/".$ItemNumandValues[$counter][1]."\" alt=\"".$ItemNumandValues[$counter][1]."Image\" width=\"128\" height=\"128\"/></td>";
				
				print "<td>".$ItemNumandValues[$counter][2]."</td>";
				
				print "<td>$innerArray[0]</td>";
				
				print "<td>$innerArray[1]</td>";
				
				print "<td>$innerArray[2]</td>";
				
				
				echo "</tr>";
			}
			else{
				print "<script type='text/javascript'>alert('Something Went Wrong! Please try again')</script>";
				print "<meta http-equiv=\"refresh\" content=\"0;url= index.php\">";
			}
		}
		$totalCost = $totalCost + ($innerArray[2] * $innerArray[1]);
		$counter++;
	}
	echo "</table></center>";
	
	print "<h4>Total Cost for This Order: $$totalCost</h4>";
	

	
}
else{
	
}












?>





<br>
<br>
<br>
<br>
<br>
<br>

</html>
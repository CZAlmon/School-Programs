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

<h1>Welcome to the Database Store, Products Page</h1>

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

//Check if cookies are enabled.
if(count($_COOKIE) > 0) {
    $CookiesEnabled = true;
} 
else {
    $CookiesEnabled = false;
	print "<script type='text/javascript'>alert('Cookies need to be enabled to log in to add to basket and order.')</script>";
	print "Please enable Cookies and Login.";
}

//Our Unique cookie name
$cookie_name = "DatabaseStore-CZADMW405G";

//Check if there is a cookie set, if so they are logged in, display thier name.
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

<p> If you arn't logged in, you wont have access to add to baskets or order anything, but feel free to browse our products.</p><br >


</html>

<p>This search function is not working as of now. We did not have enough time to implement it.</p>
<center>
 <form action="productSearch.php" method="post">
  <p>Search Products: <input type="text" name="Search" value="Search Terms" maxlength="30" size="30"><input type="submit" value="Submit"></p>
</form> 
</center>

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

//CHECK IF A LOGGED IN AS CUSTOMER/LOGGED IN AT ALL
$IsCustomerNotStaff = false;
if ($CustLoggedIn){
		
	foreach($Customers_Array as $UserNameTemp){
		//print "$UserNameTemp[0] : $CustName <br>";
		if($CustName == $UserNameTemp[0]){
			$IsCustomerNotStaff = true;
			break;
		}
	}
	
	//$IsCustomerNotStaff = in_array($CustName, $Customers_Array);
	
}



//Create a string for our query and append the sortby variable to the end since ? cannot be used after ORDER BY
$string_query = "select ItemName, ItemNum, ItemPictureURL, Quantity, ItemCost, IsonSale, SalePrice from Inventory";

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
$report_query->bind_result($ItemName, $ItemNum, $ItemPictureURL, $Quantity, $ItemCost, $IsonSale, $SalePrice);
$table = array();
while($report_query->fetch()){
	$values = Array($ItemPictureURL, $ItemName, $ItemNum, $Quantity, $ItemCost, $IsonSale, $SalePrice);
	array_push($table, $values);
}

//$CurrentWorkingDir = getcwd();

//Loop through our array and its arrays to present the results of the query in a table for the user
echo "<center>";
echo "<table border='5'>";
echo "<tr><th>Item Picture</th><th>Item Name</th><th>UPC Number</th><th>Quantity</th><th>Promotion</th><th>Item Cost</th><th>Add to Basket</th></tr>";
foreach($table as $innerArray){
	if(is_array($innerArray)){
		echo "<tr>";
		$counter = 0;
		foreach($innerArray as $value){
			if($counter == 0){
				//CURRENT DIRECTORY OF FILES
				//For UKY CS Multilab the format is /<~Name>/Path/To/$value
				//For your own purposes change src to your local URL
				print "<td><img src=\"/~czal222/CS405G/Images/$value\" alt=\"$value Image\" width=\"128\" height=\"128\"/></td>";
			}
			elseif($counter == 4){
				
				if ($innerArray[5]){
					print "<td>Promotional Price!</td>";
					print "<td>\$$innerArray[6]</td>";
				}
				else{
					print "<td>Not on Sale</td>";
					print "<td>\$$value</td>";
				}
				
				//Button command, only for customers logged in
				if ($CustLoggedIn && $IsCustomerNotStaff){
					print "<td><form method=\"post\" action=\"add_to_basket.php\"><input type=\"submit\" name=\"$innerArray[2]\" value=\"Add to Basket\"></form></td>";
				}
				elseif ($CustLoggedIn && !$IsCustomerNotStaff){
					print "<td><p>Only Customers Can Add to Basket</p></td>";
				}
				else{
					print "<td><p>Please Login to Add to Basket</p></td>";
				}
			}
			elseif($counter >= 5){
				//Do nothing
			}
			else{
				echo "<td>$value</td>";
			}
			$counter++;
		}
		echo "</tr>";
	}
}
echo "</table></center>";

echo "<br><br><br><br><br><br>";






?>





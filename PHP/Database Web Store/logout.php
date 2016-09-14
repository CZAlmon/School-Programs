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

<h1>Welcome to the Database Store, Logout Page</h1>

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

//DELETE COOKIE HERE. When you set cookie to time() - 3600, this sets a cookie to expire and hour ago, this deletes the cookie
if(count($_COOKIE) > 0) {
    $CookiesEnabled = true;
	
	$cookie_name = "DatabaseStore-CZADMW405G";
	$cookie_value = "testUser";
	setcookie($cookie_name, $cookie_value, time() - 3600, '/');
	
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

if ($CustLoggedIn){
	print "<script type='text/javascript'>alert('You have logged out!')</script>";
	//header("Location: index.php");
	print "<meta http-equiv=\"refresh\" content=\"0;url= index.php\">";
}
else{
	print "<script type='text/javascript'>alert('You must be logged in to log out!')</script>";
	//header("Location: index.php");
	print "<meta http-equiv=\"refresh\" content=\"0;url= index.php\">";
}

//<p>You have successfully logged out!</p><br >

?>



</html>




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

<h1>Welcome to the Database Store, Staff Page</h1>

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

$string_query = "select Username, IsManager from Staff";

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
$report_query->bind_result($Username, $IsManager);
$Staff_Array = array();
while($report_query->fetch()){
	$values = Array($Username, $IsManager);
	array_push($Staff_Array, $values);
}
	
$isStaffMember = false;
$isManagerVar = false;

//If not logged in
if (!$CustLoggedIn){
	print "<p>You have to be logged in to view this page!</p>";
	print "<p>Please <a href = \"http://www.cs.uky.edu/~czal222/CS405G/login.php\">login</a>.</p>";
	
}
else{
	
	//Check for staff login
	foreach($Staff_Array as $innerArray){
		//print $innerArray[0];
		//print "<br> True or False: $usernameMatch <br>";
		//print $innerArray[1];
		//print "<br> Cust Name:  $CustName <br>";
		
		if ($innerArray[0] == $CustName){
			$isStaffMember = true;
			$isManagerVar = $innerArray[1];
		}
	}
	
	//Table Variable Initialzation ------------------------------------------------------------------------------------------------------------
	
	$InventoryString = "select ItemName, ItemNum, ItemPictureURL, Quantity, ItemCost, SalesThisWeek, SalesThisMonth, SalesThisYear, IsonSale, SalePrice from Inventory";

	//prepare the query
	$InventoryQuery = $connection->prepare("$InventoryString");

	//Execute, if there was an error, tell the user
	if(!$InventoryQuery->execute()){
		$errormessage = $InventoryQuery->error;
		echo "$errormessage <br >";
		echo "Try again";
		exit();
	}

	//Get our results, put them into a 2dimensional array
	$InventoryQuery->bind_result($ItemName, $ItemNum, $ItemPictureURL, $Quantity, $ItemCost, $SalesThisWeek, $SalesThisMonth, $SalesThisYear, $IsonSale, $SalePrice);
	$StaffInventoryTable = array();
	$ManagerSalesInfoTable = array();
	//$ManagerInventoryTable = array();
	while($InventoryQuery->fetch()){
		//$Allvalues = Array($ItemPictureURL, $ItemName, $ItemNum, $Quantity, $ItemCost, $IsonSale, $SalePrice);
		$SalesValues = Array($ItemPictureURL, $ItemName, $ItemNum, $ItemCost, $Quantity, $SalesThisWeek, $SalesThisMonth, $SalesThisYear, $IsonSale, $SalePrice);
		$StaffValues = Array($ItemPictureURL, $ItemName, $ItemNum, $ItemCost, $Quantity);
		
		array_push($StaffInventoryTable, $StaffValues);
		array_push($ManagerSalesInfoTable, $SalesValues);
		//array_push($ManagerInventoryTable, $Allvalues);
	}
	
	//InventoryTable = 0=Picture, 1=Name, 2=Number, 3=Quantity, 4=Cost, 5=Weekly, 6=Monthly, 7=Yearly, 8=Sale, 9=SalePrice
	
	//print_r($InventoryTable);
	
	
	$CustomerOrdersString = "select C.Username, C.UserIDNum, O.UserIDNum, O.OrderNum, O.HasShipped from Customers C join CustomerOrders O on C.UserIDNum = O.USerIDNum;";

	//prepare the query
	$CustomerOrderQuery = $connection->prepare("$CustomerOrdersString");

	//Execute, if there was an error, tell the user
	if(!$CustomerOrderQuery->execute()){
		$errormessage = $CustomerOrderQuery->error;
		echo "$errormessage <br >";
		echo "Try again";
		exit();
	}

	//Get our results, put them into a 2dimensional array
	$CustomerOrderQuery->bind_result($CustUserName, $CustID, $OrderCustID, $OrderNum, $HasShipped);
	$CustomerOrderTable = array();
	while($CustomerOrderQuery->fetch()){
		$values = Array($CustUserName, $CustID, $OrderNum, $HasShipped);
		array_push($CustomerOrderTable, $values);
	}
	
	//CustomerOrderTable = 0=Cust ID, 1=Order ID, 2=Shipped
	
	//print_r($CustomerOrderTable);
	
	
	
	$OrdersString = "select OrderNum, ItemNum, CostAtPOS, Quantity from Orders";

	//prepare the query
	$OrderQuery = $connection->prepare("$OrdersString");

	//Execute, if there was an error, tell the user
	if(!$OrderQuery->execute()){
		$errormessage = $OrderQuery->error;
		echo "$errormessage <br >";
		echo "Try again";
		exit();
	}

	//Get our results, put them into a 2dimensional array
	$OrderQuery->bind_result($OrderNum, $ItemNum, $CostAtPOS, $Quantity);
	$OrderTable = array();
	while($OrderQuery->fetch()){
		$values = Array($OrderNum, $ItemNum, $CostAtPOS, $Quantity);
		array_push($OrderQuery, $values);
	}
	
	//OrderTable = 0=Order ID, 1=Item ID, 2=Cost of Item at POS, 3=Quantity
	
	//print_r($OrderTable);
	
	
	//End Table Variable Initialzation --------------------------------------------------------------------------------------------------------
	
	
	
	//Place Order ---------------------------------------------------------------
		
	if ($_SERVER["REQUEST_METHOD"] == "POST") {
		
		//Multi Use Post
		//Parse what type of POST it is
		
		$WhatMethodToCall = key($_POST);
		//print_r($_POST);
		//print "<p>We are going to: $WhatMethodToCall</p>";
		
		//Update Inventory
		
		//On Error:
		//print "<script type='text/javascript'>alert('')</script>";
		//print "<meta http-equiv=\"refresh\" content=\"0;url= index.php\">";
		
		
		if ($WhatMethodToCall == "ChangeQuantity"){
			
			$ItemNumberToChangePrice = $_POST["ChangeQuantity"];
			$NewQuantitytoSet = $_POST["New_Quantity"];
			
			if ($NewQuantitytoSet == "" || $NewQuantitytoSet == " " || $NewQuantitytoSet == "  " || $NewQuantitytoSet == "   " || $NewQuantitytoSet == "    " || $NewQuantitytoSet == "     " ){
				print "<script type='text/javascript'>alert('Error! Quantity box can not be empty.')</script>";
				print "<meta http-equiv=\"refresh\" content=\"0;url= employee.php\">";
			}
			else{
				
				$CleanedQuantity = test_input($NewQuantitytoSet);
				
				if (!preg_match("/^[\d]*$/", $CleanedQuantity)) {
					print "<script type='text/javascript'>alert('Only the number Zero or Positive Numbers allowed')</script>";
					print "<meta http-equiv=\"refresh\" content=\"0;url= employee.php\">";
				}
				else{
					//print "<p>This Here: $CleanedQuantity</p>";
					$UpdateInventoryString = "UPDATE Inventory SET Quantity=$CleanedQuantity WHERE ItemNum='$ItemNumberToChangePrice'";
					
					$UpdateInventoryReport = $connection->prepare("$UpdateInventoryString");
					
					//Execute, if there was an error, tell the user
					if(!$UpdateInventoryReport->execute()){
						$errormessage = $UpdateInventoryReport->error;
						echo "$errormessage <br >";
						print "<script type='text/javascript'>alert('Something went wrong with the Request, please try again.')</script>";
						exit();
					}
					
					print "<meta http-equiv=\"refresh\" content=\"0;url= employee.php\">";
					
				}
			}			
		}
		
		
		//Ship Pending Orders
		
		elseif ($WhatMethodToCall == "ShipOrder"){
			
			$OrderNumbertoShip = $_POST["OrderNumber"];
			
			//print "Setup : $OrderNumbertoShip";
			
			$ShipOrderString = "UPDATE CustomerOrders SET HasShipped=1 WHERE OrderNum='$OrderNumbertoShip'";
			
			$ShipOrderReport = $connection->prepare("$ShipOrderString");
			
			//Execute, if there was an error, tell the user
			if(!$ShipOrderReport->execute()){
				$errormessage = $ShipOrderReport->error;
				echo "$errormessage <br >";
				echo "Try again";
				exit();
			}
			
			print "<script type='text/javascript'>alert('Order Successfull Shipped!')</script>";
			print "<meta http-equiv=\"refresh\" content=\"0;url= employee.php\">";
			
		}
		
		
		//Manager only Option:
		//	Set Sale promo and price
		
		elseif ($WhatMethodToCall == "ChangePrice"){
			
			$ItemNumberToChangePrice = $_POST["ChangePrice"];
			$NewPrice = $_POST["NewPrice"];
			
			if (preg_match("/^[ .]*$/", $NewPrice)){
				print "<script type='text/javascript'>alert('Error! Price box must contain a number.')</script>";
				print "<meta http-equiv=\"refresh\" content=\"0;url= employee.php\">";
			}
			else{
				
				$CleanedNewPrice = test_input($NewPrice);
				
				if (!preg_match("/^[\d.]*$/", $CleanedNewPrice)) {
					print "<script type='text/javascript'>alert('Only the number Zero or Positive Numbers allowed')</script>";
					print "<meta http-equiv=\"refresh\" content=\"0;url= employee.php\">";
				}
				else{
					
					//print "<p>This Here: $CleanedNewPrice</p>";
					
					$UpdateInventoryPrice = "UPDATE Inventory SET ItemCost=$CleanedNewPrice WHERE ItemNum='$ItemNumberToChangePrice'";
					
					$UpdateInventoryPriceReport = $connection->prepare("$UpdateInventoryPrice");
					
					//Execute, if there was an error, tell the user
					if(!$UpdateInventoryPriceReport->execute()){
						$errormessage = $UpdateInventoryPriceReport->error;
						echo "$errormessage <br >";
						print "<script type='text/javascript'>alert('Something went wrong with the Request, please try again.')</script>";
						exit();
					}
					
					print "<meta http-equiv=\"refresh\" content=\"0;url= employee.php\">";
					
				}
			}
		}
		elseif ($WhatMethodToCall == "ChangeSale"){
			
			$ItemNumberToChangePrice = $_POST["ChangeSale"];
			$NewSalePrice = $_POST["New_Sale_Price"];
			$OnSaleVar = $_POST["OnSale"];
			
			if ($OnSaleVar == "YesOnSale" || $OnSaleVar == "NotOnSale"){
				
				$BoolOfOnSale = 0;
				
				if ($OnSaleVar == "YesOnSale"){
					$BoolOfOnSale = 1;
				}
				else{
					$BoolOfOnSale = 0;
				}
				
				if (preg_match("/^[ .]*$/", $NewSalePrice)){
					print "<script type='text/javascript'>alert('Error! Sale Price box must contain a number.')</script>";
					print "<meta http-equiv=\"refresh\" content=\"0;url= employee.php\">";
				}
				else{
					
					$CleanedSalePrice = test_input($NewSalePrice);
					
					if (!preg_match("/^[\d.]*$/", $CleanedSalePrice)) {
						print "<script type='text/javascript'>alert('Only the number Zero or Positive Real Numbers allowed')</script>";
						print "<meta http-equiv=\"refresh\" content=\"0;url= employee.php\">";
					}
					else{
						
						//print "<p>This Here: $CleanedSalePrice</p>";
						
						$UpdateInventorySalePrice = "UPDATE Inventory SET SalePrice=$CleanedSalePrice, IsOnSale=$BoolOfOnSale WHERE ItemNum='$ItemNumberToChangePrice'";
						
						$UpdateInventorySalePriceReport = $connection->prepare("$UpdateInventorySalePrice");
						
						//Execute, if there was an error, tell the user
						if(!$UpdateInventorySalePriceReport->execute()){
							$errormessage = $UpdateInventorySalePriceReport->error;
							echo "$errormessage <br >";
							print "<script type='text/javascript'>alert('Something went wrong with the Request, please try again.')</script>";
							exit();
						}
						
						print "<meta http-equiv=\"refresh\" content=\"0;url= employee.php\">";
						
					}
				}
				
				
				
			}
			else{
				print "<script type='text/javascript'>alert('You must select whether the item is on sale or not.')</script>";
				print "<meta http-equiv=\"refresh\" content=\"0;url= employee.php\">";
			}
			
			
			
			
			
		}
		
		
		else{
			
			print "<p>There was an error with your Form input. Please contact the Network Admin<p>";
			
		}
		
		
	}
	
	//End Post-----------------------------------------------------------------------
	
	
	
	//StaffInventoryTable
	//ManagerInventoryTable
	//ManagerSalesInfoTable
	//CustomerOrderTable
	//OrderTable
	
	
	
	if(!$isStaffMember){
		print "<p>You have to be logged in as an employee to view this page!</p>";
	}
	else{
		
		//Intro for Employees. Shows Inventory table with inventory info. Shows sale stats for managers.
		if (!$isManagerVar){
			//Not a manager -- Employee intro
			
			print "<h2>Welcome $CustName!</h2>";
			print "<p>Using this page will allow you to view all inventory, adjust stock, and ship any pending orders.</p>";
			
			print "<h3>Change Inventory on current Stock:</h3>";
			echo "<center>";
			echo "<table border='5'>";
			echo "<tr><th>Item Picture</th><th>Item Name</th><th>UPC Number</th><th>Item Cost</th><th>Quantity</th><th>Change Quantity</th></tr>";
			foreach($StaffInventoryTable as $innerArray){
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
							
							echo "<td>$value</td>";
							//print "<td><form method=\"post\" action=\"change_quantity.php\"><input type=\"submit\" name=\"$innerArray[2]\" value=\"Add to Basket\"></form></td>";
							print "<td><center><form method=\"post\" action=\"employee.php\"><input type=\"hidden\" name=\"ChangeQuantity\" value=\"$innerArray[2]\">New Amount:<br> <input type=\"text\" name=\"New_Quantity\" value=\"$value\" maxlength=\"5\" size=\"5\"><br><input type=\"submit\" name=\"SubmitButton\" value=\"Submit\"></form></center></td>";
							
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
			print "<br>
			<br>
			<br>";
			
		}
		else{
			//Manager intro
			
			print "<h2>Welcome $CustName!</h2>";
			print "<p>Using this page will allow you to view all inventory, adjust stock, and ship any pending orders. You may also see the sales statistics for all inventory and set sales promotions and prices.</p>";
			
			print "<h3>Change Inventory on current Stock:</h3>";
			echo "<center>";
			echo "<table border='5'>";
			echo "<tr><th>Item Picture</th><th>Item Name</th><th>UPC Number</th><th>Item Cost</th><th>Change Item Cost</th><th>Quantity</th><th>Change Quantity</th><th>Sales This Week</th><th>Sales This Month</th><th>Sales This Year</th><th>Sale</th><th>Sale Price</th><th>Change Sale Information</th></tr>";
			foreach($ManagerSalesInfoTable as $innerArray){
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
						elseif($counter == 3){
							
							echo "<td>$value</td>";
							print "<td><center><form method=\"post\" action=\"employee.php\"><input type=\"hidden\" name=\"ChangePrice\" value=\"$innerArray[2]\">New Amount:<br> <input type=\"text\" name=\"NewPrice\" value=\"$value\" maxlength=\"5\" size=\"5\"><br><input type=\"submit\" name=\"SubmitButton\" value=\"Submit\"></form></center></td>";
							
						}
						elseif($counter == 4){
							
							echo "<td>$value</td>";
							print "<td><center><form method=\"post\" action=\"employee.php\"><input type=\"hidden\" name=\"ChangeQuantity\" value=\"$innerArray[2]\">New Amount:<br> <input type=\"text\" name=\"New_Quantity\" value=\"$value\" maxlength=\"5\" size=\"5\"><br><input type=\"submit\" name=\"SubmitButton\" value=\"Submit\"></form></center></td>";
							
						}
						elseif($counter == 8){
							
							if ($value){
								print "<td>On Sale Currently</td>";
							}
							else{
								print "<td>Not On Sale Currently</td>";
							}
							
						}
						elseif($counter == 9){
							
							echo "<td>$value</td>";
							print "<td><center><form method=\"post\" action=\"employee.php\"><input type=\"hidden\" name=\"ChangeSale\" value=\"$innerArray[2]\">New Amount:<br> <input type=\"text\" name=\"New_Sale_Price\" value=\"$value\" maxlength=\"5\" size=\"5\"><br><select name=\"OnSale\"><option value=\"Select\" selected=\"true\">Select Here</option><option value=\"YesOnSale\">On Sale</option><option value=\"NotOnSale\">Not On Sale</option></select><br><input type=\"submit\" name=\"SubmitButton\" value=\"Submit\"></form></center></td>";
							
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
			print "<br>
			<br>
			<br>";
			
			
		}
		
		//All Employee Things
		//  See and Ship pending Orders
		
		
		//Pending orders ----------------------------------------------------------------------------------------------
		
		
	
		print "<br><br><br><h3>Ship Pending Orders:</h3>";
		echo "<center>";
		echo "<table border='5'>";
		echo "<tr><th>Customer Username</th><th>Customer ID</th><th>Order Number</th><th>Has it Shipped</th><th>Ship</th></tr>";
		foreach($CustomerOrderTable as $innerArray){
			if(is_array($innerArray) && !$innerArray[3]){
				echo "<tr>";
				$counter = 0;
				foreach($innerArray as $value){
					if($counter == 3){
						
						echo "<td>Order has not Shipped</td>";
						print "<td><center><form method=\"post\" action=\"employee.php\"><input type=\"hidden\" name=\"ShipOrder\" value=\"$innerArray[1]\"><input type=\"hidden\" name=\"OrderNumber\" value=\"$innerArray[2]\"><br><input type=\"submit\" name=\"SubmitButton\" value=\"Ship Order\"></form></center></td>";
					
					}
					else{
						echo "<td>$value</td>";
					}
					$counter++;
				}
				echo "</tr>";
			}
			else{
				//Already Shipped, dont display
			}
		}
		echo "</table></center>";	
		print "<br>
		<br>
		<br>
		<br>
		<br>";
		
		
		//End Pending orders ------------------------------------------------------------------------------------------
		
		
		/*
		//Old code
		if ($isManagerVar){
			//Manager only option
			//  See sales promotions, set promotion (Yes on sale or no) and Sale Price
			
			print "<h3>Manager Only: Change Inventory Prices and Sales:</h3>";
			echo "<center>";
			echo "<table border='5'>";
			echo "<tr><th>Item Picture</th><th>Item Name</th><th>UPC Number</th><th>Quantity</th><th>Price</th><th>Change Price</th><th>Sale</th><th>Sale Price</th><th>Change Sale Information</th></tr>";
			foreach($ManagerInventoryTable as $innerArray){
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
							
							echo "<td>$value</td>";
							//print "<td><form method=\"post\" action=\"change_quantity.php\"><input type=\"submit\" name=\"$innerArray[2]\" value=\"Add to Basket\"></form></td>";
							print "<td><center><form method=\"post\" action=\"employee.php\"><input type=\"hidden\" name=\"ChangePrice\" value=\"$innerArray[2]\">New Amount:<br> <input type=\"text\" name=\"NewPrice\" value=\"$value\" maxlength=\"5\" size=\"5\"><br><input type=\"submit\" name=\"SubmitButton\" value=\"Submit\"></form></center></td>";
							
						}
						elseif($counter == 5){
							
							if ($value){
								print "<td>On Sale Currently</td>";
							}
							else{
								print "<td>Not On Sale Currently</td>";
							}
							
						}
						elseif($counter == 6){
							
							echo "<td>$value</td>";
							//print "<td><form method=\"post\" action=\"change_quantity.php\"><input type=\"submit\" name=\"$innerArray[2]\" value=\"Add to Basket\"></form></td>";
							print "<td><center><form method=\"post\" action=\"employee.php\"><input type=\"hidden\" name=\"ChangeSale\" value=\"$innerArray[2]\">New Amount:<br> <input type=\"text\" name=\"New_Sale_Price\" value=\"$value\" maxlength=\"5\" size=\"5\"><br><select name=\"OnSale\"><option value=\"Select\" selected=\"true\">Select Here</option><option value=\"YesOnSale\">On Sale</option><option value=\"NotOnSale\">Not On Sale</option></select><br><input type=\"submit\" name=\"SubmitButton\" value=\"Submit\"></form></center></td>";
							
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
			print "<br>
			<br>
			<br>";
			
			
		}	
		*/
		
	}
	
	
	
	
}


	
	



?>











<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>


</html>

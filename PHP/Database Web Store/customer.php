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

//Create a new order number that is not in the array between those numbers (must be a 10-digit number)
function createOrderNumber($FunctionOrdersArray){
	
	$num = str_pad(mt_rand(1000000000,9999999999),10,'0',STR_PAD_LEFT);
	$NewOrderNum = 0;

	//print "<p><br>$num<br></p>";

	$NumberIsNotUnique = false;

	while(!$NumberIsNotUnique){

		$didanumbermatch = false;

		foreach($FunctionOrdersArray as $innerArray){
			if ($innerArray[1] == $num){
				$didanumbermatch = true;
			}
		}

		if ($didanumbermatch){
			$num = str_pad(mt_rand(1000000000,9999999999),8,'0',STR_PAD_LEFT);
			$didanumbermatch = false;
		}
		else{
			$NumberIsNotUnique = true;
			$NewOrderNum = $num;
		}

	}
	
	return $NewOrderNum;
	
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

$usernameMatch = false;
$Users_ID_Number = 0;

$BasketHasItems = false;

if (!$CustLoggedIn){
	
	print "<p>You have to be logged in to view this page!</p>";
	print "<p>Please <a href = \"http://www.cs.uky.edu/~czal222/CS405G/login.php\">login</a> or visit our <a href = \"http://www.cs.uky.edu/~czal222/CS405G/register.php\">Registration Page</a> to sign up as a customer.</p>";
	
}
else{
	
	//print_r($Customers_Array);
	
	foreach($Customers_Array as $innerArray){
		//print $innerArray[0];
		//print "<br> True or False: $usernameMatch <br>";
		//print $innerArray[1];
		//print "<br> Cust Name:  $CustName <br>";
		
		if ($innerArray[0] == $CustName){
			$usernameMatch = true;
			$Users_ID_Number = $innerArray[1];
		}
	}
	
	if(!$usernameMatch){
		print "<p>You have to be logged in as a customer to view this page!</p>";
	}
	else{
		
		//First Display Basket + Basket button to order everything
		//print "Display Basket Here with button to above<br>";
		
		$CustomerBasket = "select ItemNum, Quantity from Baskets where UserIDNum='$Users_ID_Number'";
		
		$BasketReport = $connection->prepare("$CustomerBasket");
		
		//Execute, if there was an error, tell the user
		if(!$BasketReport->execute()){
			$errormessage = $BasketReport->error;
			echo "$errormessage <br >";
			echo "Try again";
			exit();
		}

		//Get our results, put them into a 2dimensional array
		$BasketReport->bind_result($ItemNum, $Quantity);
		$BasketTable = array();
		$BasketItems = array();
		while($BasketReport->fetch()){
			$BasketHasItems = true;
			$values = Array($ItemNum, $Quantity);
			$anotherValues = $ItemNum;
			array_push($BasketItems, $anotherValues);
			array_push($BasketTable, $values);
		}
		
		
		//Place Order ---------------------------------------
		
		if ($_SERVER["REQUEST_METHOD"] == "POST") {
			
			//print_r($BasketTable);
			
			$Post_Users_ID_Number = $Users_ID_Number;
			$PostBasketTable = $BasketTable;
			$PostBasketItems = $BasketItems;
			$BasketItemNumsCostsandQuantity = array();
			$PostInventoryTable = array();
			
			//Get item information for each basket item from inventory list
			foreach($PostBasketItems as $ItemValue){
				
				$Post_tempString = "select ItemNum, Quantity, ItemCost from Inventory where ItemNum='$ItemValue'";
				
				$Post_tempQuery = $connection->prepare("$Post_tempString");
				
				if(!$Post_tempQuery->execute()){
					$errormessage = $Post_tempQuery->error;
					echo "$errormessage <br >";
					echo "Try again";
					exit();
				}
				
				//push all information to the array
				$Post_tempQuery->bind_result($Post_ItemNumber, $Post_Quantity, $Post_ItemCost);
				while($Post_tempQuery->fetch()){
					$Post_values = Array($Post_ItemNumber, $Post_Quantity);
					$OtherValues = Array($Post_ItemNumber, $Post_ItemCost, $Post_Quantity);
					array_push($PostInventoryTable, $Post_values);
					array_push($BasketItemNumsCostsandQuantity, $OtherValues);
					
				}
				
			}
			
			//print_r($PostBasketTable);
			//print "<br>";
			//print_r($PostInventoryTable);
			//print "<br>";
			//print_r($BasketItemNumsCostsandQuantity);
			
			//Check to make sure enough of items exist in stock (inventory quantity) compared to basket quantity
			$ItemsNotInInventory = array();
			$CountOfItemsNotInInven = 0;
			$Post_counter = 0;
			foreach ($PostInventoryTable as $ItemList){
				
				$ItemNumFromList = $ItemList[0];
				$ItemNumFromTable = $PostBasketTable[$Post_counter][0];
				
				//print "<br> $ItemNumFromList - $ItemNumFromTable";
				
				if ($ItemNumFromList == $ItemNumFromTable){
					
					$inventoryCount = $ItemList[1];
					$BasketCount = $PostBasketTable[$Post_counter][1];
					
					if($inventoryCount < $BasketCount){
						$CountOfItemsNotInInven++;
						array_push($ItemsNotInInventory, $ItemList[0]);
					}
					else{
						//Do nothing
					}
				}
				else{
					print "<script type='text/javascript'>alert('Something Went Wrong! Please try again')</script>";
					print "<meta http-equiv=\"refresh\" content=\"0;url= index.php\">";
				}
				$Post_counter++;
			}
			
			//If there are not enough of some items, print this message off and do nothing else.
			if ($CountOfItemsNotInInven > 0){
				foreach($ItemsNotInInventory as $MissingItems){
					print "<p>There are not enough of item number: $MissingItems, in stock. Please reduce the quantity to order, take it out of your basket, or wait until it is back in stock.</p>";
				}
			}
			else{
				
				//Create 10-digit unique Order Number
				//Insert Each Item Num, Individual Cost, Quantity to Orders
				//  Update Inventory Stock Amounts
				//Insert Order to Customer Orders with Customer ID
				//Clear Basket for CustID
				
				//Get all previous order numbers
				$OrdersString = "select OrderNum from CustomerOrders";
				
				$OrderQuery = $connection->prepare("$OrdersString");
				
				if(!$OrderQuery->execute()){
					$errormessage = $OrderQuery->error;
					echo "$errormessage <br >";
					echo "Try again";
					exit();
				}
				
				$OrderQuery->bind_result($OrderNum);
				$AllOrdersNum = array();
				while($OrderQuery->fetch()){
					array_push($AllOrdersNum, $OrderNum);
				}
				
				//Make new order number that is unique to all previous order numbers
				//print_r($AllOrdersNum);
				$NewOrderNumber = createOrderNumber($AllOrdersNum);
				//print "<p>Your new Order Number is: $NewOrderNumber</p>";
				
				//print_r($BasketItemNumsCostsandQuantity);
				
				//Insert New Order Num, then basket item + cost + Quantity to orders
				
				//Take each item, and push it into the orders table
				$OrdersCounter = 0;
				foreach ($BasketItemNumsCostsandQuantity as $InsertArray){
					
					$BasketQuantity = $PostBasketTable[$OrdersCounter][1];
					
					$InsertOrdersString = "INSERT INTO Orders(OrderNum, ItemNum, CostAtPOS, Quantity) VALUES ($NewOrderNumber, $InsertArray[0], $InsertArray[1], $BasketQuantity)";
					
					//print "<br> - $InsertOrdersString<br>";
					
					$InsertOrders_report = $connection->prepare("$InsertOrdersString");
					if(!$InsertOrders_report->execute()){
						$errormessage = $InsertOrders_report->error;
						echo "<br><p>$errormessage</p>";
						echo "<br >";
						echo "<p>Go back and retry your query again, or visit the Customer tab to update your basket</p>";
						return;
					}
					
					$OrdersCounter++;
				}
				
				//  Update Inventory Stock Amounts for each item
				//		Update SALES For Each Item
				foreach ($PostBasketTable as $UpdateArray){
					
					$TempQuantity = $UpdateArray[1];
					$TempItemNum = $UpdateArray[0];
					//print "<br> $TempQuantity - $TempItemNum";
					
					//Make Strings
					$UpdateInventoryString = "UPDATE Inventory SET Quantity=Quantity-$TempQuantity WHERE ItemNum='$TempItemNum'";
					
					$UpdateInventoryWeek = "UPDATE Inventory SET SalesThisWeek=SalesThisWeek+$TempQuantity WHERE ItemNum='$TempItemNum'";
					
					$UpdateInventoryMonth = "UPDATE Inventory SET SalesThisMonth=SalesThisMonth+$TempQuantity WHERE ItemNum='$TempItemNum'";
					
					$UpdateInventoryYear = "UPDATE Inventory SET SalesThisYear=SalesThisYear+$TempQuantity WHERE ItemNum='$TempItemNum'";
					
					
					
					//Prepare and then Execute all of them
					$UpdateInventoryReport = $connection->prepare("$UpdateInventoryString");
					
					//Execute, if there was an error, tell the user
					if(!$UpdateInventoryReport->execute()){
						$errormessage = $UpdateInventoryReport->error;
						echo "$errormessage <br >";
						echo "Try again";
						exit();
					}
					
					$UpdateInventoryWeekReport = $connection->prepare("$UpdateInventoryWeek");
					
					//Execute, if there was an error, tell the user
					if(!$UpdateInventoryWeekReport->execute()){
						$errormessage = $UpdateInventoryWeekReport->error;
						echo "$errormessage <br >";
						echo "Try again";
						exit();
					}
					
					$UpdateInventoryMonthReport = $connection->prepare("$UpdateInventoryMonth");
					
					//Execute, if there was an error, tell the user
					if(!$UpdateInventoryMonthReport->execute()){
						$errormessage = $UpdateInventoryMonthReport->error;
						echo "$errormessage <br >";
						echo "Try again";
						exit();
					}
					
					$UpdateInventoryYearReport = $connection->prepare("$UpdateInventoryYear");
					
					//Execute, if there was an error, tell the user
					if(!$UpdateInventoryYearReport->execute()){
						$errormessage = $UpdateInventoryYearReport->error;
						echo "$errormessage <br >";
						echo "Try again";
						exit();
					}				
					
				}		
				
				
				
				//Insert CustID and New Order Num (False Shipping) into customer orders
				//$HasShippedVar = false;
				
				//print "$Post_Users_ID_Number  -  $NewOrderNumber  -  $HasShippedVar";
				
				$InsertCustomerOrdersString = "INSERT INTO CustomerOrders(UserIDNum, OrderNum, HasShipped) VALUES ('$Post_Users_ID_Number', '$NewOrderNumber', '0')";
				
				$InsertCustOrders_report = $connection->prepare("$InsertCustomerOrdersString");
				if(!$InsertCustOrders_report->execute()){
					$errormessage = $InsertCustOrders_report->error;
					echo "<br><p>$errormessage</p>";
					echo "<br >";
					echo "<p>Go back and retry your query again, or visit the Customer tab to update your basket</p>";
					return;
				}
				
				
				
				//Clear Basket for CustID
				$DeleteString = "DELETE FROM Baskets WHERE UserIDNum='$Post_Users_ID_Number'";
			
				//print "$DeleteString";
				
				$DeleteReport = $connection->prepare("$DeleteString");
			
				//Execute, if there was an error, tell the user
				if(!$DeleteReport->execute()){
					$errormessage = $DeleteReport->error;
					echo "$errormessage <br >";
					echo "Try again";
					exit();
				}
				
				print "<script type='text/javascript'>alert('You have Sucessfully placed your Order. Your new Order Number is: $NewOrderNumber')</script>";
				print "<meta http-equiv=\"refresh\" content=\"0;url= customer.php\">";
				
				
				
			}
			
			
			
			//If successful Redirect to This page
			
			//If not successful dont do anything
			
			
		}
		//End of Place Order --------
		
		
		
		
		
		//get basket items
		$ItemNumandValues = array();
		foreach($BasketItems as $ItemValue){
			
			$tempString = "select ItemName, ItemNum, ItemPictureURL, ItemCost from Inventory where ItemNum='$ItemValue'";
			
			$tempQuery = $connection->prepare("$tempString");
			
			if(!$tempQuery->execute()){
				$errormessage = $tempQuery->error;
				echo "$errormessage <br >";
				echo "Try again";
				exit();
			}
			
			$tempQuery->bind_result($ItemName, $ItemNumber, $ItemPictureURL, $ItemCost);
			while($tempQuery->fetch()){
				$values = Array($ItemNumber, $ItemPictureURL, $ItemName, $ItemCost);
				array_push($ItemNumandValues, $values);
			}
			
		}
		
		//Print off basket
		echo "<center>";
		echo "<h2>Current Basket:</h2>";
		echo "<table border='5'>";
		echo "<tr><th>Item Picture</th><th>Item Name</th><th>Item Number</th><th>Item Cost</th><th>Quantity</th><th>Change Quantity</th>";
		$counter = 0;
		$CustBasketTotalCost = 0;
		foreach($BasketTable as $innerArray){
			if(is_array($innerArray)){
				
				if ($innerArray[0] = $ItemNumandValues[$counter][0]){
					echo "<tr>";
					
					print "<td><img src=\"/~czal222/CS405G/Images/".$ItemNumandValues[$counter][1]."\" alt=\"".$ItemNumandValues[$counter][1]."Image\" width=\"128\" height=\"128\"/></td>";
					
					print "<td>".$ItemNumandValues[$counter][2]."</td>";
					
					print "<td>$innerArray[0]</td>";
					
					print "<td>".$ItemNumandValues[$counter][3]."</td>";
					
					print "<td>$innerArray[1]</td>";
					
					print "<td><center><form method=\"post\" action=\"change_basket.php\">New Amount:<br> <input type=\"text\" name=\"New_Quantity\" value=\"$innerArray[1]\" maxlength=\"5\" size=\"5\"><br><input type=\"submit\" name=\"$Users_ID_Number-$innerArray[0]\" value=\"Submit\"></form></center></td>";
					
					echo "</tr>";
					
					$CustBasketTotalCost = $CustBasketTotalCost + ($innerArray[1] * $ItemNumandValues[$counter][3]);
					
				}
				else{
					print "<script type='text/javascript'>alert('Something Went Wrong! Please try again')</script>";
					print "<meta http-equiv=\"refresh\" content=\"0;url= index.php\">";
				}
			}
			$counter++;
		}
		echo "</table></center>";	
		
		print "<h4>Total Cost for This Order: $$CustBasketTotalCost</h4>";
		
	}	
}
?>






<?php if ($CustLoggedIn && $usernameMatch && $BasketHasItems) {?>
<center>
<form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
   <input type="submit" name="submit" value="Place Order">
</form>
</center>
<?php } 

//THE ABOVE FORM IS FOR PLACING ORDERS. DO NOT SHOW THE BUTTON UNLESS THE PERSON IS LOGGED IN, IS A CUSTOMER, AND THE BASKET HAS ITEMS IN IT

?>

<br>
<br>

<?php

if (!$CustLoggedIn){
	
}
else{
	if(!$usernameMatch){
	
	}
	else{
		//Display all past orders --------------------------------------------------
		//print "Display Past Order here.<br>";
		
		//print "$Users_ID_Number";
		
		$Customer_Query = "select OrderNum, HasShipped from CustomerOrders where UserIDNum='$Users_ID_Number'";

		//prepare the query
		$ConnectionReport_Query = $connection->prepare("$Customer_Query");

		//Execute, if there was an error, tell the user
		if(!$ConnectionReport_Query->execute()){
			$errormessage = $ConnectionReport_Query->error;
			echo "$errormessage <br >";
			echo "Try again";
			exit();
		}

		//Get our results, put them into a 2dimensional array
		$ConnectionReport_Query->bind_result($OrderNum, $HasShipped);
		$table = array();
		while($ConnectionReport_Query->fetch()){
			$values = Array($OrderNum, $HasShipped);
			array_push($table, $values);
		}
		
		echo "<center>";
		echo "<h2>All Past Orders:</h2>";
		echo "<table border='5'>";
		echo "<tr><th>Order Number</th><th>Shipped</th><th>See This Order</th>";
		foreach($table as $innerArray){
			if(is_array($innerArray)){
				echo "<tr>";
				$counter = 0;
				foreach($innerArray as $value){
					if($counter == 0){
						print "<td>$value</td>";
					}
					elseif($counter == 1){
						
						if ($value){
							print "<td>Order has been Shipped</td>";
						}
						else{
							print "<td>Order has not been Shipped</td>";
						}
						
						print "<td><form method=\"post\" action=\"show_order_contents.php\"><input type=\"submit\" name=\"$innerArray[0]\" value=\"View Entire Order\"></form></td>";
					}
					else{
						//do nothing
					}
					$counter++;
				}
				echo "</tr>";
			}
		}
		echo "</table></center>";
	}
}


?>


<br>
<br>
<br>
<br>
<br>
</html>











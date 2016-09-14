/*
	
	MySQL Database initialization for CS405G Program 10
	Created by Carmon Zachary Almon and Dylan Wise
	
	Data was created randomly by the group using ourselves and website: http://www.generatedata.com/
		Website was used only for inventory numbers, eg. ItemNum, Quantity, Sales, Price, etc.
	
	Only to be used in conjection with our own PHP and HTML Programs accessing the SQL Database.
	
	This file is GNU-licensed.
	
*/

/*
	USAGE:

		Have Database created;
									[or use the ones provided]
		Use Database_Name;
		
		Source ECOMMERCE.SQL;

		to Drop tables use:
		
*/

/*
CREATE DATABASE ECOMMERCE;
USE ECOMMERCE;
*/


CREATE TABLE Staff
(
        Username VARCHAR(20) NOT NULL,
		Password VARCHAR(20) NOT NULL,
		IsManager BOOLEAN NOT NULL,
		UNIQUE (Username),
		PRIMARY KEY (Username)
);
 
CREATE TABLE Customers
(
        Username VARCHAR(20) NOT NULL,
		Password VARCHAR(20) NOT NULL,
		UserIDNum BIGINT(8) NOT NULL,
		IsVIPCustomer BOOLEAN NOT NULL,
		UNIQUE (Username),
		UNIQUE (UserIDNum),
		PRIMARY KEY (Username)
);

CREATE TABLE Inventory
(
		ItemName VARCHAR(100) NOT NULL,
        ItemNum BIGINT(12) NOT NULL,
		ItemPictureURL VARCHAR(255) NOT NULL,
		Quantity INT NOT NULL,
		ItemCost DECIMAL(10,2) NOT NULL,
		SalesThisWeek INT NOT NULL,
		SalesThisMonth INT NOT NULL,
		SalesThisYear INT NOT NULL,
		IsonSale BOOLEAN NOT NULL,
		SalePrice DECIMAL(10,2) NOT NULL,
		UNIQUE (ItemNum)
);
 
CREATE TABLE Baskets
(
        UserIDNum BIGINT(8) NOT NULL,
		ItemNum BIGINT(12) NOT NULL,
		Quantity INT NOT NULL,
		UNIQUE (UserIDNum, ItemNum),
		FOREIGN KEY (UserIDNum) REFERENCES Customers(UserIDNum),
		FOREIGN KEY (ItemNum) REFERENCES Inventory(ItemNum)
);

CREATE TABLE Orders
(
        OrderNum BIGINT(10) NOT NULL,
		ItemNum BIGINT(12) NOT NULL,
		CostAtPOS DECIMAL(10,2) NOT NULL,
		Quantity INT NOT NULL,
		UNIQUE (OrderNum, ItemNum),
		FOREIGN KEY (ItemNum) REFERENCES Inventory(ItemNum)
);
 
CREATE TABLE CustomerOrders
(
        UserIDNum BIGINT(8) NOT NULL,
		OrderNum BIGINT(10) NOT NULL,
		HasShipped BOOLEAN NOT NULL,
		UNIQUE (UserIDNum, OrderNum),
		FOREIGN KEY (UserIDNum) REFERENCES Customers(UserIDNum),
		FOREIGN KEY (OrderNum) REFERENCES Orders(OrderNum)
);
 



/*
		
		Above are the tables for regular use 
		
		UserIDNum is 8-digits
		OrderNum is 10-digits
		ItemNum is 12-digits
		
*/



INSERT INTO Staff(Username, Password, IsManager) VALUES
("JohnDoe", "Thisisunsecure1", FALSE), 
("JaneDoe", "SomeOther123", FALSE), 
("MarcoPhoenix", "AceIsCool123", TRUE),
("JoeBadGuy", "SomeRandomPW123", FALSE),
("HelloWorld", "HelloWorld1", FALSE),
("Dylan", "12345", TRUE),
("Zach", "54321", FALSE);

INSERT INTO Customers(Username, Password, UserIDNum, IsVIPCustomer) VALUES
("WhatIsLove", "BabyDontHurtMe", 50000011, FALSE), 
("HelloWorld1", "HelloWorld54", 50002201, FALSE), 
("360NoScope", "YeaBoi12", 50003301, FALSE), 
("CustDylan", "12345", 90000001, TRUE),
("CustZach", "54321", 90000002, TRUE);

INSERT INTO Inventory(ItemName, ItemNum, ItemPictureURL, Quantity, ItemCost, SalesThisWeek, SalesThisMonth, SalesThisYear, IsonSale, SalePrice) VALUES
("Original Pokemon Red", 120987654321, "PokRed.png", 30, 29.99, 35, 65, 1098, FALSE, 19.90),
("Original Pokemon Blue", 120987654322, "PokBlue.gif", 30, 29.99, 25, 69, 1200, FALSE, 19.90),
("Monopoly", 422434101533, "Mono.png", 92, 38.85, 19, 161, 700, TRUE, 24.19),
("Call of Duty: Black Ops", 209070799546, "COD.jpg", 112, 98.09, 14, 130, 360, TRUE, 39.73),
("Cards Against Humanity", 889987442083, "CAH.png", 117, 38.00, 33, 85, 391, TRUE, 22.05),
("Jenga", 896935616526, "Jenga.jpg", 58, 73.86, 1, 161, 383, FALSE, 17.37),
("Connect 4", 515580737637, "Connect4.png", 231, 82.97, 40, 154, 720, FALSE, 10.25),
("Giant Jenga", 792213676916, "GJenga.jpg", 181, 97.91, 19, 196, 375, FALSE, 87.73),
("Rubix's Cube", 754665634082, "Rubixs.png", 50, 79.31, 48, 106, 975, FALSE, 42.94),
("Uno", 814769206522, "Uno.png", 132, 58.03, 21, 54, 406, FALSE, 15.25),
("Lego MineCraft Playset", 522431035758, "MineLego.jpg", 83, 32.49, 3, 126, 385, TRUE, 17.46),
("Nerf N-Strike Elite: Blaster", 561427688552, "Nerf.jpg", 244, 18.23, 46, 131, 329, TRUE, 14.33),
("Mini Basketball Hoop and Ball", 570411861641, "BBall.jpg", 135, 51.50, 37, 138, 953, TRUE, 20.55),
("Sword Handle Umbrella", 708490545488, "SwordUm.jpg", 104, 62.63, 4, 169, 278, TRUE, 26.81),
("Oreo Dunking Spoon", 348110652575, "OreoSpoon.jpg", 167, 72.26, 44, 199, 766, FALSE, 52.64),
("4 Color Laser Pointer", 621234471630, "LaserPoint.jpg", 222, 83.12, 41, 119, 784, TRUE, 18.60),
("Remote Control Quadrocopter", 375841022934, "QuadCopt.jpg", 221, 33.96, 12, 133, 371, TRUE, 25.71),
("Suit Panjamas", 966830556513, "SuitP.jpg", 14, 61.51, 3, 125, 950, TRUE, 46.75),
("Three Player Chess", 155538114486, "3PChess.jpg", 171, 48.88, 27, 142, 803, FALSE, 38.71),
("Mini Wooden Ballista", 658402433292, "Ballista.jpg", 67, 60.39, 18, 102, 657, FALSE, 44.63),
("Titanic Ice Cube Mold", 951058183051, "Titan.jpg", 210, 99.65, 21, 143, 314, FALSE, 76.19),
("Transformer USB Flash Drive", 351401490019, "TransformerFlash.jpg", 87, 83.31, 6, 93, 682, TRUE, 58.83),
("Snow Globe", 936029407614, "SnowG.png", 137, 53.83, 17, 170, 628, FALSE, 31.03),
("Checkers Game Board", 457737193675, "Checkers.png", 234, 69.60, 14, 121, 349, FALSE, 30.08),
("Connect 4 Tetris Combo Game", 230889591714, "ConnTetris.png", 1, 11.41, 23, 135, 507, TRUE, 5.53),
("Mass Water Balloon Loader", 410021146247, "WaterBal.jpg", 24, 36.54, 31, 153, 908, TRUE, 32.31),
("Giant Gummy Bear", 898833716940, "Gummy.jpg", 59, 37.67, 26, 108, 474, TRUE, 36.55),
("Mario Kart for Wii", 910985848773, "MK8.png", 198, 43.04, 12, 120, 731, FALSE, 39.00);

INSERT INTO Orders(OrderNum, ItemNum, CostAtPOS, Quantity) VALUES
(1234567890, 754665634082, 13.50, 1),
(1234567890, 708490545488, 12.45, 1),
(1234567890, 410021146247, 8.99, 2),
(1234568900, 351401490019, 12.00, 3),
(1234789000, 754665634082, 14.70, 1), 
(1234789000, 708490545488, 24.99, 4), 
(1234000000, 966830556513, 7.86, 1),
(1234000000, 658402433292, 6.33, 1),
(1234000000, 410021146247, 14.43, 1),
(1234000000, 910985848773, 17.65, 1),
(1234000000, 120987654322, 2.78, 1),
(1234000000, 422434101533, 4.88, 1),
(1000987654, 754665634082, 7.66, 2),
(1000987654, 966830556513, 13.78, 1),
(1000987654, 351401490019, 18.90, 1),
(1000987654, 910985848773, 20.65, 1),
(1000603459, 708490545488, 9.15, 2),
(1000603459, 658402433292, 6.98, 1),
(1000603459, 410021146247, 6.77, 1),
(1000603459, 348110652575, 15.65, 2),
(1000603459, 120987654322, 4.45, 1);

INSERT INTO Baskets(UserIDNum, ItemNum, Quantity) VALUES
(50000011, 375841022934, 1),
(50000011, 561427688552, 2),
(50000011, 708490545488, 1),
(90000001, 708490545488, 1),
(90000001, 570411861641, 1), 
(90000001, 155538114486, 2), 
(90000002, 120987654321, 1);

INSERT INTO CustomerOrders(UserIDNum, OrderNum, HasShipped) VALUES
(50000011, 1234567890, FALSE),
(50000011, 1234568900, FALSE),
(90000001, 1234789000, TRUE),
(90000001, 1234000000, FALSE), 
(90000002, 1000987654, FALSE), 
(90000002, 1000603459, TRUE);







### Command Line Minesweeper


##### Purpose:

Simple minesweeper game, executed via command line.


##### Description: 
		
		Get user input for width and height (5 to 20 inclusive) and get # of mines (0 to widthheight inclusive) Make board to this deminsions
		
		Get time point here
		
		Display board to user
		
		start main while(!lost() && !win()) loop. Ask user for [R]eveal [F]lag [G]ive up
		
		[R]eveal - ask for the coordinates from user, not going over bounds make a new position object with this coordinates then reveal(p) this object then board.display() to reveal board.
		
		[F]lag - ask for the coordinates from user, not going over bounds make a new position object with this coordinates then flag(p) this object then board.display() to reveal board.
		
		[G]ive up - call board.give_up() then board.display() to reveal board. give_up() will break loop automatically because .lost() will become true.
		
		Out of loop - get time point
		
		If won, tell user they won
		
		if lost, tell user they lost
		
		tell user thier time from timepoint 2 - timepoint 1 in seconds
 		  
##### Inputs:

		User input for:
			Width, Height, # of Mines
			[R] [F] [G] for reveal, flag or give up respectively
			X and Y value for revealed
			X and Y value for revealed
			
			
			
##### Outputs:

 		Displays to user the board, and directions on what to enter
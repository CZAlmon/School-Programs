#Carmon Zachary Almon
#11-1-13
#z.almon@yahoo.com
#section 14

#Purpose: Play the game of "Don't Match!!"

#Preconditions: user is given initial roll and asked if they desire to continue
#Postconditions: The game continues until either the user quits or matches the first roll

#Import random library
#Import graphics library
    
#get_a_roll
#Purpose: Get a random number and return an integer between 1 and 6 inclusive
#Preconditions: First roll it is automatic following rolls depend on user entering "y"
#postconditions: Return an integer between 1 and 6 inclusive
    #Step 1: From random number library receive a number from 1 and 6 inclusive
    #Step 2: return this digit to the main function

#display_die
#Purpose: Receive an integer between 1 and 6 inclusive if integer matches the number on the die, display the die
#Preconditions: Receive integer between 1 and 6 inclusive
#Postconditions: Display the correct die for the corresponding numberdef display_die4(roll):
    #Step 1: if roll digit corresponds to die face
    #Step 2: call corresponding die face function

#die_face(number)
#Purpose: Draw the corresponding die face for the roll
#Preconditions: Receive integer between 1 and 6 inclusive
#Postconditions: Draw die face and output it to the shell
    #Step 1: Draw corresponding die face 

#imputfromUser
#Purpose: to recive input from user on the graphics window to advance game
#Preconditions: Mouse click from user
#Post conditions: Yes or N returned for the loop control
    #Step 1: get mouse click
    #step 2: assign X and Y coords to seperate varibles
    #step 3: if statements to compare with boxes made for yes or no input to X and Y value of mouse click

#main function
    #Step 1: Open graphics window
    #Step 2: Display introductory message
    #Step 3: Call get_a_roll automatically
    #Step 4: Call display_die function and dispaly proper die face
    #Step 5: Display rules of the game
    #Step 6: Display user's score
    #Step 7: Ask if user wants to roll again
    #Step 8: Display two buttons for user to click, "yes" if they want to roll, "no" if they do not
    #Step 9: If user clicks "yes"
         #Step 9.1: get_a_roll is called, dice is rolled again
         #Step 9.2: call display_die function, display roll directly under first roll
         #Step 9.3: If first roll matches the current roll
              #Step 9.31: Display flag
              #Step 9.32: Game is over proceed to step 11
         #Step 9.4: If roll does not match first roll
              #Step 9.41: Display the users current winnings
         #Step 9.5: Return to Step 8
    #Step 10: If user clicks "no"
         #Step 10.1: Display the user's winnings
         #Step 10.2: Proceed to step 12
    #Step 11: Display that the user matched and lost all their winnings
    #Step 12: Display "Click to exit"
    #Step 13: User clicks mouse and ends program
    

#End of main function




from random import *
from graphics import *

def get_a_roll():
    random_num = randrange(1, 7) #Random number 1-6 does not include 7
    return random_num 

def display_die(Number, display_time, window): #Number is the Random number, display_time is for the first picture(First roll) versus subsequent rolls, win is for the graphics window.
    
    first_point = Point(125, 400) #first roll point
    second_point = Point(125, 150) #second roll point
    display = Number
    gif = ""    
    
    if display == 1:           #Number/x will always be 1-6, never aything else
        gif = "one.gif"
    if display == 2:           #No need for else statements here
        gif = "two.gif"
    if display == 3:
        gif = "three.gif"
    if display == 4:
        gif = "four.gif"
    if display == 5:
        gif = "five.gif"
    if display == 6:
        gif = "six.gif"

    if display_time == True:
        pic = Image(first_point, gif) #displays the first roll image
    else:
        pic = Image(second_point, gif) #displays the subsequent roll images
    
    pic.draw(window) #draws whatever image to the graphics window. images are solid not transparent and wont overlap so no need to undraw.


def inputfromUser(window):
    p1 = window.getMouse()                       #gets mouse click to determine user input
    x_area = p1.getX()                        #gets x value to compare user input
    y_area = p1.getY()                        #gets y value to compare user input
    
    users_input = ""                           #Assigns empty string so loop wont crash if user clicks on the window other then areas in boxes.
    if x_area >= 300 and x_area <= 375:       #If click is within x values of yes box
        if y_area >= 200 and y_area <= 250:   #if click is within y values of yes box
            users_input = "Yes"                #user clicked yes
    if x_area >= 425 and x_area <= 500:       #If click is within x values of no box
        if y_area >= 200 and y_area <= 250:   #If click is within y values of no box
            users_input = "N"                  #user clicked no      
            
    return users_input


def main():
    
    win = GraphWin("Don't Match!", 600, 600)    #limit of hight and width of my screen
    win.setCoords(0,0,599,599)    
    title = Text(Point(300, 550), "The game of 'Don't Match'")
    title.draw(win)    
    
    win_or_lose_FLAG = True                  #Flag to determine if user has lost and will be used to exit window in that case.
    total = 0        
    x = get_a_roll()                         #Calls the random roll function, assigns to x
    First_roll = x                           #holds the very first roll, used when comparing to new rolls for losing roll
    total += x
    first_time = True                        #Assigns value to the first picture being drawn. First roll
    
    normalText = Text(Point(400,450), "Your first roll is "+ str(x))    
    normalText2 = Text(Point(400,400), "You can continue to roll as long as you dont roll a "+str(x))
    totalText = Text(Point(400, 350), "You have $"+str(total))
    InputText = Text(Point(400,300), "Do you want to roll again? (y/n)") 
    
    normalText.draw(win)                     #Draws the 4 lines above for the text in window
    normalText2.draw(win)
    totalText.draw(win)
    InputText.draw(win)
    
    Yesbox = Rectangle(Point(375,250),Point(300,200))
    Nobox = Rectangle(Point(425,250),Point(500,200))
    YesText = Text(Point(336,225), "Yes")
    NoText = Text(Point(463,225), "No")
    
    YesText.draw(win)                        #Draws boxes and Text inside it
    NoText.draw(win)
    Yesbox.draw(win)
    Nobox.draw(win)
    
    display_die(x, first_time, win)           #Calls to draw the die face based on the roll value, x, if it is the first time, which it is here, first_time, and drawn to graphics window, win.
    first_time = False                        #assigns from here on that all rolls will be put in the second place maintaining the first on the window


    user_input = inputfromUser(win)          #Call user input returns with yes or N for loop
       
              
    while user_input != "N" and win_or_lose_FLAG != False:
        x = get_a_roll()                        #New roll every start of loop
        display_die(x, first_time, win)         #display with the new roll, same position, and window parameter
        total += x

        totalText.undraw()                      #undraws the users total otherwise screen gets messy
        InputText.undraw()                      #undraws input text if user wants to input or not
        
        if First_roll == x:                     #determines if user has matched or no
            win_or_lose_FLAG = False            #based on next if statement this will stop the loop if user has matched
        
        if win_or_lose_FLAG == True:            #Main statement if user didnt match
               
            totalText = Text(Point(400, 350), "You have $"+str(total))
            InputText = Text(Point(400,300), "Do you want to roll again? (y/n)")    
            
            totalText.draw(win)                 #draws new total text
            InputText.draw(win)                 #draws new input text
            
                           
            user_input = inputfromUser(win)      #Calls the user input function returns yes or no
                                   
    
    if win_or_lose_FLAG == False:             #takes value of flag if user lost or quit and left with money
        totalText.undraw()                   #Next unndraws undraw the text in place of the lost text below.
        InputText.undraw()
        YesText.undraw()
        NoText.undraw()
        Yesbox.undraw()
        Nobox.undraw() 
        
        sorry_lost = Text(Point(400,250), "Sorry!")          #displays to user that they lost
        Matched_lost = Text(Point(400,200), "You Matched! You lost all of your money!") #lost money
        sorry_lost.draw(win)
        Matched_lost.draw(win)
        
    else:
        totalText.undraw()                #undraws the next text to make room for user to know how much money they left with.
        InputText.undraw()
        YesText.undraw()
        NoText.undraw()
        Yesbox.undraw()
        Nobox.undraw() 
        
        Won_left = Text(Point(400,150), "You left with $"+str(total))   #shows user how much money they made off this game
        Won_left.draw(win)
    
    close = Text(Point(300, 50), "Click to Close Window")    #tells user to click to close window
    close.draw(win) 
    win.getMouse()
    win.close()            


main()

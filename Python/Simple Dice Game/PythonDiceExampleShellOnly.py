#Carmon Zachary Almon
#11-1-13
#z.almon@yahoo.com
#section 14

from random import *
from graphics import *

def get_a_roll():
    random_num = randrange(1, 7)
    return random_num

def display_die(Number):
    x = Number
    if x == 1:
        die_1()
    if x == 2:
        die_2()
    if x == 3:
        die_3()
    if x == 4:
        die_4()
    if x == 5:
        die_5()
    if x == 6:
        die_6()
    
def die_1():
    print("+---+"), print("|   |"), print("| * |"), print("|   |"), print("+---+")
def die_2():
    print("+---+"), print("|*  |"), print("|   |"), print("|  *|"), print("+---+")
def die_3():
    print("+---+"), print("|*  |"), print("| * |"), print("|  *|"), print("+---+")
def die_4():
    print("+---+"), print("|* *|"), print("|   |"), print("|* *|"), print("+---+")
def die_5():
    print("+---+"), print("|* *|"), print("| * |"), print("|* *|"), print("+---+")
def die_6():
    print("+---+"), print("|* *|"), print("|* *|"), print("|* *|"), print("+---+")

def main():
    
    win_or_lose_FLAG = True       
    user_input = ""               
    total = 0
    
    print("The game of 'Don't Match'")
    x = get_a_roll()
    First_roll = x
    print("Your First Roll is ", x)
    display_die(x)
    print("You can roll as long as you dont roll another ", x)
    total += x
    print("You have $", total, sep="")
    user_input = input("Do you want to roll again? (y/n) ")
        
    while user_input != "N" and user_input != "n" and win_or_lose_FLAG != False:
        x = get_a_roll()        
        display_die(x)
        total += x
        
        if First_roll == x:                     
            win_or_lose_FLAG = False                   
        
        if win_or_lose_FLAG == True:
            print("You won $", x) #How do you tab over at the start pf print
            print("\t You have $", total, sep="")
            print()
            user_input = input("Do you want to roll again? (y/n) ")

    if win_or_lose_FLAG == False:
        print("You matched! You lost all your money!")
        print("Sorry!")
    else:
        print("You left with $", total, sep="")
    

main()

# pic = Image(Point(100,100), "gifsmall.gif") 
# pic.draw(wn)
# 
# win = GraphWin("Don't Match!", 500, 500)
# win.setCoords(0,0,499,499)
# 
# title = Text(Point(250, 450), "Click 2 Points")
# title.draw(win)
# 
# Text(Point(,), "Your first roll is", x, "the number")    #how do add in a varible in text object
# Text(Point(,), "You can continue to roll as long as you dont roll")
# Text(Point(,), "You rolled a")
# Text(Point(,), "Do you want to roll again? (y/n)")
# 
# Text(Point(,), "Yes")
# Text(Point(,), "No")
# 
# rectangle = rectangle(Point(,), Point(,)
# rectangle2 = rectangle(Point(,), Point(,)
# 
# mouse_click = win.getMouse()                       #how do you compare these points
# if mouse_click == rectangle
# 
# 
# Text(Point(250, 50), "Click to Close Window")


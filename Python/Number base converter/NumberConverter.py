# Carmon Zachary Almon
# Section 14
# 10-14-13
# z.almon@yahoo.com
#
# Purpose of program: To use and understand the concepts of designing pseudocode, out of labels with proper spacing in both dimenstions, using the math and graphics library correctly, using assignment statements to do integer arithmatic, to test with valid and invalid inputs, and to document everything correctly within code.
#
# Preconditions: User inputs Number and base
# Post-Conditions: Program generates number in new base and displays on the graphics window
# 
# 1. Import math library. Use * for everything
# 2. Import Graphics Library
# 3. Create Graphics window
# 4. Display "Big Blue Base Conversion"
# 5. Get user input in the Graphics Window for the decimal number
# 6. Get user input in the graphics window for the desired base convert
# 7. Calaulate the varible numOfDigits as int(log(Userinput1)/log(userinput2) 
# 8. Use the numOfDigits to create a for loop
# 9. In loop will run from the numOfDigits number to 0
# 10. The for loop will not handle numbers bigger than 10
# 11. The for loop will not handle 0, or 1
# 12. For loop will take number inputed and divide by base number with exponent of numOfDigits
# 13. Some varibles will collect every whole number from every division statement
# 14. Accumilater will decrease numOfdigits by 1 each time.
# 15. Accumilater will decrase the number inputed. It will take the remainder of each division and apply it as the new number.
# 16. These varibles will come together as the new number with the users inputed base. The "calculated number"
# 17. Output "(Input Decimal number) converted to base (input base number) is (Calculated number)"
# 18. Display "Click mouse to Close"
# 19. Close window with mouse click in code


from graphics import *         #For graphics throughout
from math import *             #For logs in calculations

def main():
    win = GraphWin("Big Blue Base Converter", 500, 550)
    win.setCoords(0,0, 499, 549) #Lower corner, upper corner
    title = Text(Point(250, 525),"Big Blue Base Converter")
    title.setStyle('bold')
    title.setTextColor("blue") #color needs ""
    title.draw(win)
    #above is the Title at the top
    number_convert = Text(Point(250, 475),"Enter a number")
    number_convert.setStyle('bold')
    number_convert.draw(win)
    #Above is the text object for number input
    input1 = Entry(Point(250, 450),5)
    input1.setText("  ")
    input1.draw(win)
    #Above is the input object for number input
    base_convert = Text(Point(250, 375),"Enter a Base to convert to")
    base_convert.setStyle('bold')
    base_convert.draw(win)
    #Above is the text object for base number input
    input2 = Entry(Point(250, 350),5)
    input2.setText("  ")
    input2.draw(win)
    #Above is the input object for base input
    user_input = Text(Point(250, 300),"Click to enter Numbers") # alert user to input numbers. Hitting enter is common error
    
    user_input.draw(win)    # drawing said alert
    win.getMouse()      # Wait for mouse click
    user_input.undraw() # undrawing alert after click to enter number, will still create everything else
    
    Inputed_Number = int(input1.getText())                #Number inputed, for the End Output
    Inputed_Number2 = Inputed_Number                              #Number inputed, for the Loop
    Inputed_Base = int(input2.getText())                  #Base input will always stay the same
    Number_of_Digits = int(log(Inputed_Number)/log(Inputed_Base))            #Number of Digits Always the same
    String_digit = ""
    
    for i in range(Number_of_Digits, -1, -1):             #Loop works
        Converted_Number = Inputed_Number2 // Inputed_Base ** i      #Converted_Number is each digit of the New Number in new Base 
        Inputed_Number2 = Inputed_Number2 % Inputed_Base **i          #Accumulator
        
        String_digit = String_digit + str(Converted_Number)         #Strings can be accumulators too. This adds the strings together one at a time next to each other with no spaces.
                 
        
    String = "The number " + str(Inputed_Number) + " converted to base " + str(Inputed_Base) + " is " + String_digit #String Varible for output Text
    Output = Text(Point(250, 150), String)    #Output on Window. String is the varible holds the text
    Output.draw(win)

    close_window = Text(Point(250, 50), "Click to Close Window") #alert user to close window
    close_window.draw(win)
    win.getMouse()
    win.close()    
main()
    
    
    
    
### Prisoners Dilemma in HTML and JavaScript

HTML Page with boxes showing output, and control buttons at the bottom. 

When an individual box is clicked on, that boxes score is updated.

When Run all is clicked, all boxes are updated.

When reset is clicked, all boxes will be zeroed out.



Algorithm:

	function coinFlip()
	•	Multiply 2 by a random number between 0 and 1 resulting in a random number between 0 and 2
	•	Calculate the floor of that number
	•	If the floor is 0, cooperate, otherwise, defect

	function run( strategy1, strategy2, penalty )
	•	Default penalty to false if not passed
	•	Initialize local history variables
		 •	my cooperation count
		 •	my defect count
		 •	my history
		 •	opponent's cooperation count
		 •	opponent's defect count
		 •	opponent's history
	•	Loop for 1000 times
		 •	If we are in a penalty state
		 •	If my cooperations exceed 600, defect
		 •	If my defections exceed 600, cooperate
		 •	If my opponent's cooperations exceed 600, they defect
		 •	If my opponents defections exceed 600, they cooperate
		 •	If either strategy is “Random”, determine choice with flipCoin
		 •	If either strategy is “My plan”, determine choice with myPlan
		 •	If we both cooperate, increment score by 3 and update histories
		 •	If I cooperate and opponent defects, update histories
		 •	If I defect and opponent cooperates, increment score by 5 and update histories
		 •	If we both defect, increment score by 1 and update histories
	•	If in a penalty state and my defections are over 500, subtract from my score the number of defections over 500
	•	Set the corresponding box in the HTML table with my score
	•	Increment the total box in the row by my score
	•	Reset the local variable values

	function run1( strategy1, strategy2 )
	•	This is a convenience function that calls the run function with a penalty true parameter value

	function myplan( count, myhistory, ophistory, mydefect, opdefect )
	•	If I can defect without earning a penalty, defect.
	•	If my opponent has not defected yet, cooperate.
	•	If my opponent has defected, reply randomly, but influenced proportionally by my opponents past behavior, moving in the direction of cooperation by the proportion of cooperations my opponent has chosen, but also in the direction of defections by the proportion of defections my opponent has chosen.

	function resetAll()
	•	Reset the HTML form

	function runAll()
	•	For my strategy each of Random, Cooperate, Defect, and My plan
		 •	For my opponent's strategy each of Random, Cooperate, Defect, and My plan
		 •	For each penalty value of true and false
	•	call run() with my strategy, my opponent's strategy, and penalty value





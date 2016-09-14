All python scripts need to be ran with Python 2.7 and require numpy and scikit learn to be installed.

The scripts must be ran in the sequence

ShelterPreProcess.py
convertIntoNumerical.py
NaiveBayesPrediction.py


ShelterPreProcess.py requires that you have the file called 'train.csv' in the directory
It expects this file to be the animal shelter dataset.

convertIntoNumerical.py will then use the 'filterPass4.txt' file generated from the preprocess script
to convert the file into numerical data that is useable in the scikit learn naive bayes function then
save that file as 'numericalDataTrain.txt'

NaiveBayesPrediction.py will then use 'numericalDataTrain.txt' to train 80 and test 20 of its own
data using the naive bayes classifier. 


The Rules folder contains the files necessary to run the GUI rules program we used for HW 1.
The actual programs are omitted because they are unable to mailed due to being .exe and .jar
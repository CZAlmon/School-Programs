from __future__ import division
import numpy as np
from sklearn.naive_bayes import GaussianNB
from random import shuffle
from math import ceil

dataVectors = []

#take the numerical version of the data and open
file = open('numericalDataTrain.txt','r')
for line in file:
    dataVectors.append(line.strip().split(','))

file.close

#shuff the data
shuffle(dataVectors)

#divide data 80/20
eightyPercent = len(dataVectors)*0.8

eightyPercent = int(ceil(eightyPercent))
testSize = len(dataVectors) - eightyPercent

outcomes = []
dataPredictive = dataVectors

#remove outcomes from data and put it into predictive vector
for i in range(len(dataVectors)):
    outcomes.append(dataVectors[i][3])
    dataPredictive[i].pop(3)

for i in range(len(dataVectors)):
    dataPredictive[i].pop(3)

#drop color and breed
for i in range(len(dataVectors)):
    dataPredictive[i].pop(7)

for i in range(len(dataVectors)):
    dataPredictive[i].pop(6)

#drop name
for i in range(len(dataVectors)):
    dataPredictive[i].pop(0)


#put training and testing dta into respective containers
dataTrain = dataPredictive[:eightyPercent]
trainingOutcomes = outcomes[:eightyPercent]

dataTest = dataPredictive[eightyPercent:]
testingOutcomes = outcomes[eightyPercent:]


#convert all lists into numpy arrays
dataTrain = np.array(dataTrain, dtype=int)
trainingOutcomes = np.array(trainingOutcomes, dtype=int)
dataTest = np.array(dataTest, dtype=int)
testingOutcomes = np.array(testingOutcomes, dtype=int)

#use naive bayes and gather score
clf = GaussianNB()
clf.fit(dataTrain, trainingOutcomes)

prediction = clf.predict_proba(dataTest)

NBScore = clf.score(dataTest, testingOutcomes)

print NBScore
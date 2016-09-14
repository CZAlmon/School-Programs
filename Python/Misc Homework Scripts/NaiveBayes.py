#Dylan Wise
#Naive Bayes
#4/3/16

#takes only one parameter, the file name.
#expects last attribute to be the one being predicted

from collections import Counter
import sys
from random import shuffle

#calculate naive bayes probabilty 
def calculateProbability(attributeName,attributeType,classType, attributeCounter, uniqueAttributes, classCounter):
    attribute = (attributeName, attributeType, classType)

    if attribute in uniqueAttributes:
        return attributeCounter[attribute]/classCounter[classType]

    else:
        return 1/(classCounter[classType]+1)

def main():
    #initilize vector for each line in file
    dataVectors = []

    file = open(sys.argv[1],'r')
    for line in file:
        dataVectors.append(line.strip().lower().split(','))

    #shuffle(dataVectors)
    trainingData = dataVectors[0:1000]
    testData = dataVectors[1000:]

    attributeOccurances = []
    attributeName = ''
    attributeType = ''
    classType = ''

    classOccurances = []

    #create count database for probabilities
    for dataLine in trainingData:
        for k in range(len(dataLine)-1):
            attributeNum = str(k)
            attributeType = dataLine[k]
            classType = dataLine[-1]

            attributeOccurances.append(tuple([attributeNum, attributeType, classType]))

        classOccurances.append(dataLine[-1])

    #use counters to count unique combinations
    attributeCounter = Counter(attributeOccurances)
    uniqueAttributes = list(set(attributeOccurances))

    classCounter = Counter(classOccurances)
    uniqueClasses = list(set(classOccurances))

    listOfProbabilities = [[] for i in range(len(uniqueClasses))]
    correctCounter = 0

    #now to see if our predictions are accurate
    for dataLine in testData:
        finalProbabilities = [1 for i in range(len(uniqueClasses))]
        for k in range(len(dataLine)-1):
            for j in range(len(finalProbabilities)):
                #create probabilities for P(x/c)
                listOfProbabilities[j].append(calculateProbability(str(k),dataLine[k],uniqueClasses[j],attributeCounter, uniqueAttributes, classCounter))
        
        #multiply P(x/c) probabilities
        for i in range(len(finalProbabilities)):
            for k in range(len(listOfProbabilities)):
                finalProbabilities[i] *= listOfProbabilities[i][k]

        #multiply P(c) with calculated probabilities 
        for i in range(len(uniqueClasses)):
            finalProbabilities[i] *= (classCounter[uniqueClasses[i]]/len(testData))

        #determine which class has the highest probability
        largestProbability = finalProbabilities.index(max(finalProbabilities))
        classDecision = uniqueClasses[largestProbability]

        #report if model was accurate
        if classDecision == dataLine[-1]:
            print(classDecision, end=' ')
            print("was the correct assumption.")
            correctCounter += 1

        else:
            print(classDecision, end=' ')
            print("was the incorrect assumption.")
        
        listOfProbabilities = [[] for i in range(len(uniqueClasses))]

    print()
    print("The model created is correct ", end='')
    print(round((correctCounter/len(testData))*100, 2), end='')
    print("% of the time.")
main()
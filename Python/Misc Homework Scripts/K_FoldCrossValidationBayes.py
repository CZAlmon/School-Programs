#Dylan Wise
#K-Fold Cross Validation Using Naive Bayes
#4/3/16

#takes two parameters, the file name and the amount of "folds"
#expects last attribute to be the one being predicted

from collections import Counter
from math import ceil, floor
from random import shuffle
import sys

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
    kFolds = int(sys.argv[2])

    kFoldData  = [[] for i in range(kFolds)]

    file = open(sys.argv[1],'r')
    for line in file:
        dataVectors.append(line.strip().lower().split(','))

    #randomize data
    #shuffle(dataVectors)

    dataSize = len(dataVectors)
    dataStep = dataSize/kFolds
    dataStepInt = 0
    unevenIterator = 0

    #If the data splits evenly into k-folds
    if dataSize % kFolds == 0:
        dataStepInt = int(dataStep)
        for i in range(kFolds):
            for k in range(dataStepInt):
                kFoldData[i].append(dataVectors[dataStepInt*i+k])

    #if the data does not split evenly into k-folds
    else:
        for i in range(kFolds-1):
            #alternate between rounding down and rounding up
            if i % 2 == 0:
                dataStepInt = int(ceil(dataStep))

            else:
                dataStepInt = int(floor(dataStep))

            for k in range(dataStepInt):
                kFoldData[i].append(dataVectors[unevenIterator])
                unevenIterator += 1

        for i in range(dataSize - unevenIterator):
            kFoldData[-1].append(dataVectors[unevenIterator])
            unevenIterator += 1
      
    listOfTrainers = [[] for i in range(kFolds)] 
    listOfClassOccurances = [[] for i in range(kFolds)] 
    listOfAttributeCounters = [[] for i in range(kFolds)]
    listOfUniqueAttributes = [[] for i in range(kFolds)]
    listOfClassCounters = [[] for i in range(kFolds)]
    listOfUniqueClasses = [[] for i in range(kFolds)]
                  
    attributeName = ''
    attributeType = ''
    classType = ''

    #create count database for probabilities
    for i in range(kFolds):
        for dataLine in kFoldData[i]:
            for k in range(len(dataLine)-1):
                attributeNum = str(k)
                attributeType = dataLine[k]
                classType = dataLine[-1]

                for j in range(kFolds):
                    if j != i:
                        listOfTrainers[j].append(tuple([attributeNum, attributeType, classType]))

            for j in range(kFolds):
                if j != i:
                    listOfClassOccurances[j].append(dataLine[-1])

    #use counters to count unique combinations
    for i in range(kFolds):
        listOfAttributeCounters[i] = Counter(listOfTrainers[i])
        listOfUniqueAttributes[i] = list(set(listOfTrainers[i]))

    for i in range(kFolds):
        listOfClassCounters[i] = Counter(listOfClassOccurances[i])
        listOfUniqueClasses[i] = list(set(listOfClassOccurances[i]))

    listOfProbabilities = [[list() for j in range(len(listOfUniqueClasses[i]))] for i in range(kFolds)]
    correctCounters = [0 for i in range(kFolds)] 

    #now to see if our predictions are accurate
    for o in range(len(kFoldData)):
        for dataLine in kFoldData[o]:
            finalProbabilities = [1 for i in range(len(listOfUniqueClasses[o]))]
            for k in range(len(dataLine)-1):
                for j in range(len(finalProbabilities)):
                    #create probabilities for P(x/c)
                    listOfProbabilities[o][j].append(calculateProbability(str(k),dataLine[k],listOfUniqueClasses[o][j],listOfAttributeCounters[o], listOfUniqueAttributes[o], listOfClassCounters[o]))
        
            #multiply P(x/c) probabilities
            for i in range(len(finalProbabilities)):
                for k in range(len(listOfProbabilities[o])):
                    finalProbabilities[i] *= listOfProbabilities[o][i][k]

            #multiply P(c) with calculated probabilities 
            for i in range(len(listOfUniqueClasses[o])):
                finalProbabilities[i] *= (listOfClassCounters[o][listOfUniqueClasses[o][i]]/(dataSize - (len(kFoldData[o]))))

            #determine which class has the highest probability
            largestProbability = finalProbabilities.index(max(finalProbabilities))
            classDecision = listOfUniqueClasses[o][largestProbability]

            #report if model was accurate
            if classDecision == dataLine[-1]:
                print(classDecision, end=' ')
                print("was the correct assumption.")
                correctCounters[o] += 1

            else:
                print(classDecision, end=' ')
                print("was the incorrect assumption.")
                pass

            #could improve this...
            listOfProbabilities = [[list() for j in range(len(listOfUniqueClasses[i]))] for i in range(kFolds)]

    listOfPercentCorrect = []
    for i in range(kFolds):
        print()
        print("Model #", end='')
        print(i+1, end='')
        print(" is correct ", end='')
        print(round((correctCounters[i]/len(kFoldData[i]))*100, 2), end='')
        listOfPercentCorrect.append((correctCounters[i]/len(kFoldData[i]))*100)
        print("% of the time.")

    print()
    print("The average correctness of the models created is ", end='')
    print(round(sum(listOfPercentCorrect)/len(listOfPercentCorrect), 2), end='%\n')

    print()
    print("The best model was model #", end='')
    print(listOfPercentCorrect.index(max(listOfPercentCorrect)) + 1)
main()
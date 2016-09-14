#Carmon Zachary Almon
#Naive Bayes algorithm, problem number 2, homework number 3
#4/1/2016

#Takes one parameter, the file name of the dataset.
#The data set must be >1000 data entries.
#The data set must be of form "1,2,3,4,5,6,7", with numbers being:

#   1. buying                  v-high, high, med, low
#   2. maint                   v-high, high, med, low
#   3. doors                   2, 3, 4, 5-more
#   4. persons                 2, 4, more
#   5. lug_boot                small, med, big
#   6. safety                  low, med, high
#   7. Class Distribution      unacc, acc, good, v-good

import sys
from collections import Counter
from math import ceil, floor

#naive bayes probabilty calculator
def calculateProbability(attributeName, attributeType, classType, attributeCounter, uniqueAttributes, classCounter):
    
    attribute = (attributeName, attributeType, classType)

    if attribute in uniqueAttributes:
        return attributeCounter[attribute]/classCounter[classType]

    else:
        return 1/(classCounter[classType]+1)

    pass


def main(filename):

    ListofLineTokens = []

    #Read File
    Givenfile = open(filename, 'r')
    for line in Givenfile:
        ListofLineTokens.append(line.strip().lower().split(','))    
        pass
    
    #Seperate Data
    trainingLines = ListofLineTokens[0:1000]
    TestLines = ListofLineTokens[1000:]

    OccurancesofAttributes = []
    AttName = ''
    AttType = ''
    classType = ''

    OccurancesofClass = []

    #Create Count Data List based on training set
    for lineData in trainingLines:
        for token in range(len(lineData)-1):
            
            AttNum = str(token)
            AttType = lineData[token]
            classType = lineData[-1]

            OccurancesofAttributes.append(tuple([AttNum, AttType, classType]))

            pass

        OccurancesofClass.append(lineData[-1])

        pass

    attCounter = Counter(OccurancesofAttributes)
    uniqueAtt = list(set(OccurancesofAttributes))

    ClassCounter = Counter(OccurancesofClass)
    uniqueClass = list(set(OccurancesofClass))

    listOfProbabilities = [[] for i in range(len(uniqueClass))]
    correctCounter = 0


    #Calculator for probabilities and predictions on TEST SET
    for lineData in TestLines:

        finalProbabilities = [1 for i in range(len(uniqueClass))]

        #Create All Probabilities
        for k in range(len(lineData)-1):
            for j in range(len(finalProbabilities)):
                listOfProbabilities[j].append(calculateProbability(str(k), lineData[k], uniqueClass[j], attCounter, uniqueAtt, ClassCounter))
                pass
            pass

        #Multiply Probabilities
        for i in range(len(finalProbabilities)):
            for k in range(len(listOfProbabilities)):
                finalProbabilities[i] *= listOfProbabilities[i][k]
                pass
            pass

        for i in range(len(uniqueClass)):
            finalProbabilities[i] *= (ClassCounter[uniqueClass[i]] / len(TestLines))
            pass

        #Determine Highest Chance
        BestChance = finalProbabilities.index(max(finalProbabilities))
        classDecision = uniqueClass[BestChance]

        #report if model was accurate
        if classDecision == lineData[-1]:
            print(classDecision, end=' ')
            print("was the correct assumption.")
            correctCounter += 1
            pass
        else:
            print(classDecision, end=' ')
            print("was the incorrect assumption.")
            pass
        
        listOfProbabilities = [[] for i in range(len(uniqueClass))]
        pass

    print()
    print("The model created is correct ", end='')
    print(round((correctCounter/len(lineData)), 2), end='')
    print("% of the time.")




    
    pass


if __name__ == "__main__":

    if len(sys.argv) != 1:
        print("The only argument should be the file name!")
        os._exit(1)

    main(sys.argv[1])

    #main('carRandom1.data')

    pass








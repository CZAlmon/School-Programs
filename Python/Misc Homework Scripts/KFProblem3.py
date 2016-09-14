#Carmon Zachary Almon
#K-Fold Cross Validation using Naive Bayes algorithm, problem number 3, homework number 3
#4/1/2016

#Takes two parameters, the file name of the dataset, and k-fold number
#The data set can be any number of data entries.
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

#naive bayes probabilty calculator, from NBProblem2.py
def calculateProbability(attributeName, attributeType, classType, attributeCounter, uniqueAttributes, classCounter):
    
    attribute = (attributeName, attributeType, classType)

    if attribute in uniqueAttributes:
        return attributeCounter[attribute]/classCounter[classType]

    else:
        return 1/(classCounter[classType]+1)

    pass


def main(filename, String_kfolds):

    try:
        kfolds = int(String_kfolds)
    except:
        print("Parameter 2 must be an integar!")
        return 1

    ListofLineTokens = []
    kFoldData  = [[] for i in range(kfolds)]
    
    #Read File
    Givenfile = open(filename, 'r')
    for line in Givenfile:
        ListofLineTokens.append(line.strip().lower().split(','))    
        pass
    
    SizeofSet = len(ListofLineTokens)
    SizeofFolds = SizeofSet / kfolds

    foldStepInt = 0
    unevenIterator = 0

    #If K-folds can be made evenly
    if SizeofSet % kfolds == 0:
        foldStepInt = int(SizeofFolds)
        for i in range(kfolds):
            for k in range(foldStepInt):
                kFoldData[i].append(ListofLineTokens[foldStepInt*i+k])
                pass
            pass
        pass

    #If The K-folds has a remainder
    else:
        for i in range(kfolds-1):
            if i % 2 == 0:
                foldStepInt = int(ceil(SizeofFolds))
                pass

            else:
                foldStepInt = int(floor(SizeofFolds))
                pass

            for k in range(foldStepInt):
                kFoldData[i].append(ListofLineTokens[unevenIterator])
                unevenIterator += 1
                pass
            pass

        for i in range(SizeofFolds - unevenIterator):
            kFoldData[-1].append(ListofLineTokens[unevenIterator])
            unevenIterator += 1
            pass

        pass
    #___________________Data_Distribution_Is_Done________________________________________


    listOfTrainers = [[] for i in range(kfolds)] 
    listOfClassOccurances = [[] for i in range(kfolds)] 
    listOfAttributeCounters = [[] for i in range(kfolds)]
    listOfUniqueAttributes = [[] for i in range(kfolds)]
    listOfClassCounters = [[] for i in range(kfolds)]
    listOfUniqueClasses = [[] for i in range(kfolds)]
                  
    attributeName = ''
    attributeType = ''
    classType = ''

    #Create Count Data List based on training set
    #Refer to Line 56 in NBProblem2.py
    for i in range(kfolds):
        for dataLine in kFoldData[i]:
            for k in range(len(dataLine)-1):
                attributeNum = str(k)
                attributeType = dataLine[k]
                classType = dataLine[-1]

                for j in range(kfolds):
                    if j != i:
                        listOfTrainers[j].append(tuple([attributeNum, attributeType, classType]))
                        pass
                    pass
                pass

            for j in range(kfolds):
                if j != i:
                    listOfClassOccurances[j].append(dataLine[-1])
                    pass
                pass

            pass

    #Refer to line 72 in NBProblem.py
    for i in range(kfolds):
        listOfAttributeCounters[i] = Counter(listOfTrainers[i])
        listOfUniqueAttributes[i] = list(set(listOfTrainers[i]))
        pass

    for i in range(kfolds):
        listOfClassCounters[i] = Counter(listOfClassOccurances[i])
        listOfUniqueClasses[i] = list(set(listOfClassOccurances[i]))
        pass

    listOfProbabilities = [[list() for j in range(len(listOfUniqueClasses[i]))] for i in range(kfolds)]
    correctCounters = [0 for i in range(kfolds)] 

    #Calculator for probabilities and predictions on TEST SET
    #Refer to line 82 in NBProblem2.py
    for o in range(len(kFoldData)):
        for dataLine in kFoldData[o]:

            finalProbabilities = [1 for i in range(len(listOfUniqueClasses[o]))]

            #Create All Probabilities
            for k in range(len(dataLine)-1):
                for j in range(len(finalProbabilities)):
                    listOfProbabilities[o][j].append(calculateProbability(str(k),dataLine[k],listOfUniqueClasses[o][j],listOfAttributeCounters[o], listOfUniqueAttributes[o], listOfClassCounters[o]))
                    pass
                pass
                   
            #Multiply Probabilities 
            for i in range(len(finalProbabilities)):
                for k in range(len(listOfProbabilities[o])):
                    finalProbabilities[i] *= listOfProbabilities[o][i][k]
                    pass
                pass

            for i in range(len(listOfUniqueClasses[o])):
                finalProbabilities[i] *= (listOfClassCounters[o][listOfUniqueClasses[o][i]]/(SizeofSet - (len(kFoldData[o]))))
                pass

            #Determine Highest Chance
            largestProbability = finalProbabilities.index(max(finalProbabilities))
            classDecision = listOfUniqueClasses[o][largestProbability]

            #report if model was accurate
            if classDecision == dataLine[-1]:
                print(classDecision, end=' ')
                print("was the correct assumption.")
                correctCounters[o] += 1
                pass

            else:
                print(classDecision, end=' ')
                print("was the incorrect assumption.")
                pass


            listOfProbabilities = [[list() for j in range(len(listOfUniqueClasses[i]))] for i in range(kfolds)]
            
            pass
        pass

    listOfPercentCorrect = []

    for i in range(kfolds):
        print()
        print("Model #", end='')
        print(i+1, end='')
        print(" is correct ", end='')
        print(round((correctCounters[i]/len(kFoldData[i]))*100, 2), end='')
        listOfPercentCorrect.append((correctCounters[i]/len(kFoldData[i]))*100)
        print("% of the time.")
        pass

    print()
    print("The average correctness of the models created is ", end='')
    print(round(sum(listOfPercentCorrect)/len(listOfPercentCorrect), 2), end='%\n')

    print()
    print("The best model was model #", end='')
    print(listOfPercentCorrect.index(max(listOfPercentCorrect)) + 1)


    
    pass


if __name__ == "__main__":

    #if len(sys.argv) != 3:
    #    print("The only arguments should be the file name then the k number!")
    #    print("Usage:\n\tpython programName FileDataName KFoldNumber")
    #    os._exit(1)

    #main(sys.argv[1], sys.argv[2])

    main('carRandom1.data', 4)

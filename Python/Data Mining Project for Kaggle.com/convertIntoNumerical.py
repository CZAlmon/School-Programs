dataVectors = []

#open the final pass of filtered data
file = open('filterPass4.txt','r')
for line in file:
   dataVectors.append(line.strip().split(','))

file.close()

listOfUniqueElements = [[] for i in range(10)]

#create a list of all unique elements
for i in range(len(dataVectors)):
   for k in range(len(dataVectors[i])):
       if dataVectors[i][k] not in listOfUniqueElements[k]:
           listOfUniqueElements[k].append(dataVectors[i][k])

#use the index of those elements to assign an int for the numerical data	   
listOfNumericalElements = [[] for i in range(10)]
for i in range(len(dataVectors)):
   for k in range(len(dataVectors[i])):
       listOfNumericalElements[k].append(listOfUniqueElements[k].index(dataVectors[i][k]))

#write all the data to a file
f = open('numericalDataTrain.txt', 'w')
for i in range(len(listOfNumericalElements[0])):
   for k in range(len(listOfNumericalElements)):
       f.write(str(listOfNumericalElements[k][i]))
       if k != len(listOfNumericalElements) - 1:
           f.write(',')

   f.write('\n')

f.close()
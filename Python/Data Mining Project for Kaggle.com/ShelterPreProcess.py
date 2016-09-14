from __future__ import division
import sys
import numpy as np
import matplotlib.pyplot as plt
from sklearn import preprocessing
from sklearn import svm
import re

dataVectors = []

#the file train.csv is expected
file = open('train.csv','r')
for line in file:
    dataVectors.append(line.strip().split(','))

file.close

#find the attribute names
attributes = dataVectors[0]

dataVectors = dataVectors[1:]
data=np.array(np.genfromtxt('train.csv',dtype=('S32','S32','S32','S32','S32','S32','S32',int,'S32','S32'),delimiter=',',names=True))
data.shape

#lets first convert all ages into days

#this code was meant to convert all data into days, we found out that was not going to work
#dateByDaysVec = []

#for i in range(len(dataVectors)):
#    if "year" in dataVectors[i][7]:
#        num = [int(s) for s in dataVectors[i][7].split() if s.isdigit()]
#        dateByDaysVec.append(365*num[0])

#    elif "month" in dataVectors[i][7]:
#        num = [int(s) for s in dataVectors[i][7].split() if s.isdigit()]
#        dateByDaysVec.append(30*num[0])

#    elif "week" in dataVectors[i][7]:
#        num = [int(s) for s in dataVectors[i][7].split() if s.isdigit()]
#        dateByDaysVec.append(7*num[0])

#    elif "day" in dataVectors[i][7]:
#        num = [int(s) for s in dataVectors[i][7].split() if s.isdigit()]
#        dateByDaysVec.append(num[0])

#    else:
#        dateByDaysVec.append(0)

yearsAlive = []
#assign number based on year
#less than a year 0
#every year after is another int

#convert all age data into yearly ints
for i in range(len(dataVectors)):
    if "year" in dataVectors[i][7]:
        num = [int(s) for s in dataVectors[i][7].split() if s.isdigit()]
        yearsAlive.append(num[0])
        data['AgeuponOutcome'][i] = num[0]

    else:
        yearsAlive.append(0)
        data['AgeuponOutcome'][i] = 0

#used to show the age dataskew uncomment to see
#plt.hist(data['AgeuponOutcome'],4)
#plt.show()

#seperate age data into 3 distinct categories
idx_age_0=data['AgeuponOutcome']<5
idx_age_1=(data['AgeuponOutcome']>=5) & (data['AgeuponOutcome']<10)
idx_age_2=data['AgeuponOutcome']>=10

#save new data and reopen data with years now as strings instead of ints 
np.savetxt('filterPass1.txt',data,fmt="%s",delimiter=',')
data=np.array(np.genfromtxt('filterPass1.txt',dtype=('S32','S32','S32','S32','S32','S32','S32','S32','S32','S32'),delimiter=',',names=attributes))

dataLen = len(dataVectors)
dataVectors = []

file = open('filterPass1.txt','r')
for line in file:
    dataVectors.append(line.strip().split(','))

file.close()

dataLen2 = len(dataVectors)

#save new year data as easy to read strings
data['AgeuponOutcome'][idx_age_0]='<5years'
data['AgeuponOutcome'][idx_age_1]='>=5and<10years'
data['AgeuponOutcome'][idx_age_2]='>=10years'

#so seperating the animals by pairs of 5 years could work

#now we have defined two different ways to look at the amount of time the pets have been alive
#decide later what is more appropriate

#next step is to take the animals with no names and assign them "NoName"
#I will also keep track of unnamed pets vs named

listOfAnimalNames = []
unnamedVsNamed = []

for i in range(len(dataVectors)):
    if dataVectors[i][1] != '':
        listOfAnimalNames.append(dataVectors[i][1])
        unnamedVsNamed.append('Named')

    else:
        listOfAnimalNames.append('NoName')
        unnamedVsNamed.append('NoName')

idx_name_0 = data['Name'] != ''
idx_name_1 = data['Name'] == ''

data['Name'][idx_name_0] = "Named"
data['Name'][idx_name_1] = "NoName"


#now that names are taken care of we need to handle the DateTime data
listOfSeasons = []
listOfTimeOfDays = []

#use a simple regular expression to grab distinct parts of th date data
for i in range(len(dataVectors)):
    getMonthAndTime = re.findall('\d+-(\d+)-\d+ (\d+):\d+:\d+',dataVectors[i][2])

    month = int(getMonthAndTime[0][0])
    time = int(getMonthAndTime[0][1])

    season = ''
    timeOfDay = ''

    if month >= 3 and month <= 5:
        season = 'Spring'

    if month >= 6 and month <= 8:
        season = 'Summer'

    if month >= 9 and month <= 11:
        season = 'Fall'

    if month == 12:
        season = 'Winter'

    if month >= 1 and month <= 2:
        season = 'Winter'


    if time >= 1 and time <= 6:
        timeOfDay = 'Morning'

    if time >= 7 and time <= 12:
        timeOfDay = 'Morning'

    if time >= 13 and time <= 18:
        timeOfDay = 'Afternoon'

    if time >= 19 and time <= 23:
        timeOfDay = 'Night'

    if time == 0:
        timeOfDay = 'Night'

    listOfSeasons.append(season)
    listOfTimeOfDays.append(timeOfDay)

#save new data with name modified
np.savetxt('filterPass2.txt',data,fmt="%s",delimiter=',')

dataVectors = []

file = open('filterPass2.txt','r')
for line in file:
    dataVectors.append(line.strip().split(','))

file.close()

dataLen3 = len(dataVectors)

#get rid of animalID and datetime and add timeOfDay and Seasons
for i in range(dataLen3):
    dataVectors[i].pop(2)
    dataVectors[i].pop(0)

    dataVectors[i].insert(1, listOfSeasons[i])
    dataVectors[i].insert(2, listOfTimeOfDays[i])

#save data with new timeOfDay and Seasons attributes
data2 = np.array(dataVectors)
np.savetxt('filterPass3.txt',data2,fmt="%s",delimiter=',')

#generate new data array
data=np.array(np.genfromtxt('filterPass3.txt',dtype=('S32','S32','S32','S32','S32','S32','S32','S32','S32','S32'),delimiter=',',names=attributes))

dataVectors = []

file = open('filterPass3.txt','r')
for line in file:
    dataVectors.append(line.strip().split(','))

file.close

isMixOrNot = []

#determine if an animal is a mix or not
for i in range(len(dataVectors)):
    if 'Mix' in data[i][8]:
        isMixOrNot.append('Mix')

    else:
        isMixOrNot.append('Purebred')

for i in range(len(dataVectors)):
    data[i][8] = isMixOrNot[i]

#np.savetxt('filterPass4.txt',data,fmt="%s",delimiter=',')
#data=np.array(np.genfromtxt('filterPass4.txt',dtype=('S32','S32','S32','S32','S32','S32','S32','S32','S32','S32'),delimiter=',',names=attributes))

#dataVectors = []

#file = open('filterPass4.txt','r')
#for line in file:
#    dataVectors.append(line.strip().split(','))

#file.close

mixedColorOrNot = []

for i in range(len(dataVectors)):
    if '/' in data[i][9]:
        mixedColorOrNot.append('MixedColor')

    else:
        mixedColorOrNot.append('SolidColor')

for i in range(len(dataVectors)):
    data[i][9] = mixedColorOrNot[i]

#get rid of the rest of the whitespace in the data so it can be used with Association Rules
idx_subtype_0 = data['OutcomeSubtype'] == ''
idx_subtype_1 = data['OutcomeSubtype'] == 'At Vet'
idx_subtype_2 = data['OutcomeSubtype'] == 'Foster'
idx_subtype_3 = data['OutcomeSubtype'] == 'In Foster'
idx_subtype_4 = data['OutcomeSubtype'] == 'In Kennel'
idx_subtype_5 = data['OutcomeSubtype'] == 'In Surgery'
idx_subtype_6 = data['OutcomeSubtype'] == 'Rabies Risk'

data['OutcomeSubtype'][idx_subtype_0] = "NoSubtype"
data['OutcomeSubtype'][idx_subtype_1] = "AtVet"
data['OutcomeSubtype'][idx_subtype_2] = "Foster"
data['OutcomeSubtype'][idx_subtype_3] = "Foster"
data['OutcomeSubtype'][idx_subtype_4] = "Kennel"
data['OutcomeSubtype'][idx_subtype_5] = "Surgery"
data['OutcomeSubtype'][idx_subtype_6] = "RabiesRisk"


idx_sex_0 = data['SexuponOutcome'] == ''

idx_sex_1 = data['SexuponOutcome'] == 'Intact Male'
idx_sex_2 = data['SexuponOutcome'] == 'Intact Female'
idx_sex_3 = data['SexuponOutcome'] == 'Spayed Female'
idx_sex_4 = data['SexuponOutcome'] == 'Neutered Male'

data['SexuponOutcome'][idx_sex_1] = "IntactMale"
data['SexuponOutcome'][idx_sex_2] = "IntactFemale"
data['SexuponOutcome'][idx_sex_3] = "SpayedFemale"
data['SexuponOutcome'][idx_sex_4] = "NeuteredMale"

data['SexuponOutcome'][idx_sex_0] = "Unknown"

np.savetxt('filterPass4.txt',data,fmt="%s",delimiter=',')

#dataVectors = []

#file = open('filterPass5.txt','r')
#for line in file:
#    dataVectors.append(line.strip().split(','))

#file.close()

#newData = np.array(dataVectors)
#np.savetxt('filterPass6.txt',newData,fmt="%s",delimiter=',')

#listOfUniqueElements = [[] for i in range(10)]

#for i in range(len(dataVectors)):
#    for k in range(len(dataVectors[i])):
#        if dataVectors[i][k] not in listOfUniqueElements[k]:
#            listOfUniqueElements[k].append(dataVectors[i][k])

#listOfNumericalElements = [[] for i in range(10)]
#for i in range(len(dataVectors)):
#    for k in range(len(dataVectors[i])):
#        listOfNumericalElements[k].append(listOfUniqueElements[k].index(dataVectors[i][k]))

#dataVectorsTest = []

#file = open('filterPass6.txt','r')
#for line in file:
#    dataVectorsTest.append(line.strip().split(','))

#file.close()

#listOfNumericalElementsTest = [[] for i in range(10)]
#for i in range(len(dataVectorsTest)):
#    for k in range(len(dataVectorsTest[i])):
#        listOfNumericalElementsTest[k].append(listOfUniqueElements[k].index(dataVectorsTest[i][k]))


#f = open('numericalDataTrain.txt', 'w')

#for i in range(len(listOfNumericalElements[0])):
#    for k in range(len(listOfNumericalElements)):
#        f.write(str(listOfNumericalElements[k][i]))
#        if k != len(listOfNumericalElements) - 1:
#            f.write(',')

#    f.write('\n')

#f.close()


#f = open('numericalDataTest.txt', 'w')

#for i in range(len(listOfNumericalElementsTest[0])):
#    for k in range(len(listOfNumericalElementsTest)):
#        f.write(str(listOfNumericalElementsTest[k][i]))
#        if k != len(listOfNumericalElementsTest) - 1:
#            f.write(',')

#    f.write('\n')

#f.close()


#everything below this point was the code to produce those bar graphs that were in the presentation
#there was a lot of tedious and copy pasted probability calculation in it
#however all the code is down there so you can see, just uncomment if you wish to run yourself

#mixDogsAdopted = 0
#mixDogsDied = 0
#mixDogsTransfered = 0
#mixDogsReturnedToOwners = 0
#mixDogsEuthanized = 0

#purebredDogsAdopted = 0
#purebredDogsDied = 0
#purebredDogsTransfered = 0
#purebredDogsReturnedToOwners = 0
#purebredDogsEuthanized = 0


#mixCatsAdopted = 0
#mixCatsDied = 0
#mixCatsTransfered = 0
#mixCatsReturnedToOwners = 0
#mixCatsEuthanized = 0

#purebredCatsAdopted = 0
#purebredCatsDied = 0
#purebredCatsTransfered = 0
#purebredCatsReturnedToOwners = 0
#purebredCatsEuthanized = 0


#for i in range(len(dataVectors)):
#    if data[i][5] == 'Dog' and data[i][3] == 'Adoption' and data[i][8] == 'Mix':
#        mixDogsAdopted += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Died' and data[i][8] == 'Mix':
#        mixDogsDied += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Transfer' and data[i][8] == 'Mix':
#        mixDogsTransfered += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Return_to_owner' and data[i][8] == 'Mix':
#        mixDogsReturnedToOwners += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Euthanasia' and data[i][8] == 'Mix':
#        mixDogsEuthanized += 1



#    if data[i][5] == 'Dog' and data[i][3] == 'Adoption' and data[i][8] == 'Purebred':
#        purebredDogsAdopted += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Died' and data[i][8] == 'Purebred':
#        purebredDogsDied += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Transfer' and data[i][8] == 'Purebred':
#        purebredDogsTransfered += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Return_to_owner' and data[i][8] == 'Purebred':
#        purebredDogsReturnedToOwners += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Euthanasia' and data[i][8] == 'Purebred':
#        purebredDogsEuthanized += 1


#    if data[i][5] == 'Cat' and data[i][3] == 'Adoption' and data[i][8] == 'Mix':
#        mixCatsAdopted += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Died' and data[i][8] == 'Mix':
#        mixCatsDied += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Transfer' and data[i][8] == 'Mix':
#        mixCatsTransfered += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Return_to_owner' and data[i][8] == 'Mix':
#        mixCatsReturnedToOwners += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Euthanasia' and data[i][8] == 'Mix':
#        mixCatsEuthanized += 1


#    if data[i][5] == 'Cat' and data[i][3] == 'Adoption' and data[i][8] == 'Purebred':
#        purebredCatsAdopted += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Died' and data[i][8] == 'Purebred':
#        purebredCatsDied += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Transfer' and data[i][8] == 'Purebred':
#        purebredCatsTransfered += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Return_to_owner' and data[i][8] == 'Purebred':
#        purebredCatsReturnedToOwners += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Euthanasia' and data[i][8] == 'Purebred':
#        purebredCatsEuthanized += 1


#nummixDogs = 0
#numpurebredDogs = 0

#nummixCats = 0
#numpurebredCats = 0

#for i in range(len(dataVectors)):

#    if data[i][5] == 'Dog' and data[i][8] == 'Mix':
#        nummixDogs += 1

#    if data[i][5] == 'Dog' and data[i][8] == 'Purebred':
#        numpurebredDogs += 1


#    if data[i][5] == 'Cat' and data[i][8] == 'Mix':
#        nummixCats += 1

#    if data[i][5] == 'Cat' and data[i][8] == 'Purebred':
#        numpurebredCats += 1


#percentagemixDogsAdopted = mixDogsAdopted/nummixDogs*100
#percentagemixDogsDied = mixDogsDied/nummixDogs*100
#percentagemixDogsTransfered = mixDogsTransfered/nummixDogs*100
#percentagemixDogsReturnToOwners = mixDogsReturnedToOwners/nummixDogs*100
#percentagemixDogsEuthanized = mixDogsEuthanized/nummixDogs*100
#percentagemixDogsOutcomes = [percentagemixDogsAdopted, percentagemixDogsDied, percentagemixDogsTransfered, percentagemixDogsReturnToOwners, percentagemixDogsEuthanized]

#percentagepurebredDogsAdopted = purebredDogsAdopted/numpurebredDogs*100
#percentagepurebredDogsDied = purebredDogsDied/numpurebredDogs*100
#percentagepurebredDogsTransfered = purebredDogsTransfered/numpurebredDogs*100
#percentagepurebredDogsReturnToOwners = purebredDogsReturnedToOwners/numpurebredDogs*100
#percentagepurebredDogsEuthanized = purebredDogsEuthanized/numpurebredDogs*100
#percentagepurebredDogsOutcomes = [percentagepurebredDogsAdopted, percentagepurebredDogsDied, percentagepurebredDogsTransfered, percentagepurebredDogsReturnToOwners, percentagepurebredDogsEuthanized]


#percentagemixCatsAdopted = mixCatsAdopted/nummixCats*100
#percentagemixCatsDied = mixCatsDied/nummixCats*100
#percentagemixCatsTransfered = mixCatsTransfered/nummixCats*100
#percentagemixCatsReturnToOwners = mixCatsReturnedToOwners/nummixCats*100
#percentagemixCatsEuthanized = mixCatsEuthanized/nummixCats*100
#percentagemixCatsOutcomes = [percentagemixCatsAdopted, percentagemixCatsDied, percentagemixCatsTransfered, percentagemixCatsReturnToOwners, percentagemixCatsEuthanized]

#percentagepurebredCatsAdopted = purebredCatsAdopted/numpurebredCats*100
#percentagepurebredCatsDied = purebredCatsDied/numpurebredCats*100
#percentagepurebredCatsTransfered = purebredCatsTransfered/numpurebredCats*100
#percentagepurebredCatsReturnToOwners = purebredCatsReturnedToOwners/numpurebredCats*100
#percentagepurebredCatsEuthanized = purebredCatsEuthanized/numpurebredCats*100
#percentagepurebredCatsOutcomes = [percentagepurebredCatsAdopted, percentagepurebredCatsDied, percentagepurebredCatsTransfered, percentagepurebredCatsReturnToOwners, percentagepurebredCatsEuthanized]


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentagemixDogsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Mixed Dog Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentagepurebredDogsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Purebred Dog Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentagemixCatsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Mixed Cat Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentagepurebredCatsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Purebred Cat Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()




#youngDogsAdopted = 0
#youngDogsDied = 0
#youngDogsTransfered = 0
#youngDogsReturnedToOwners = 0
#youngDogsEuthanized = 0

#middleAgedDogsAdopted = 0
#middleAgedDogsDied = 0
#middleAgedDogsTransfered = 0
#middleAgedDogsReturnedToOwners = 0
#middleAgedDogsEuthanized = 0

#oldDogsAdopted = 0
#oldDogsDied = 0
#oldDogsTransfered = 0
#oldDogsReturnedToOwners = 0
#oldDogsEuthanized = 0

#######################################

#youngCatsAdopted = 0
#youngCatsDied = 0
#youngCatsTransfered = 0
#youngCatsReturnedToOwners = 0
#youngCatsEuthanized = 0

#middleAgedCatsAdopted = 0
#middleAgedCatsDied = 0
#middleAgedCatsTransfered = 0
#middleAgedCatsReturnedToOwners = 0
#middleAgedCatsEuthanized = 0

#oldCatsAdopted = 0
#oldCatsDied = 0
#oldCatsTransfered = 0
#oldCatsReturnedToOwners = 0
#oldCatsEuthanized = 0

#for i in range(len(dataVectors)):
#    if data[i][5] == 'Dog' and data[i][3] == 'Adoption' and data[i][7] == '<5years':
#        youngDogsAdopted += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Died' and data[i][7] == '<5years':
#        youngDogsDied += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Transfer' and data[i][7] == '<5years':
#        youngDogsTransfered += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Return_to_owner' and data[i][7] == '<5years':
#        youngDogsReturnedToOwners += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Euthanasia' and data[i][7] == '<5years':
#        youngDogsEuthanized += 1


#    if data[i][5] == 'Dog' and data[i][3] == 'Adoption' and data[i][7] == '>=5and<10years':
#        middleAgedDogsAdopted += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Died' and data[i][7] == '>=5and<10years':
#        middleAgedDogsDied += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Transfer' and data[i][7] == '>=5and<10years':
#        middleAgedDogsTransfered += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Return_to_owner' and data[i][7] == '>=5and<10years':
#        middleAgedDogsReturnedToOwners += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Euthanasia' and data[i][7] == '>=5and<10years':
#        middleAgedDogsEuthanized += 1


#    if data[i][5] == 'Dog' and data[i][3] == 'Adoption' and data[i][7] == '>=10years':
#        oldDogsAdopted += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Died' and data[i][7] == '>=10years':
#        oldDogsDied += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Transfer' and data[i][7] == '>=10years':
#        oldDogsTransfered += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Return_to_owner' and data[i][7] == '>=10years':
#        oldDogsReturnedToOwners += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Euthanasia' and data[i][7] == '>=10years':
#        oldDogsEuthanized += 1


#    if data[i][5] == 'Cat' and data[i][3] == 'Adoption' and data[i][7] == '<5years':
#        youngCatsAdopted += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Died' and data[i][7] == '<5years':
#        youngCatsDied += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Transfer' and data[i][7] == '<5years':
#        youngCatsTransfered += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Return_to_owner' and data[i][7] == '<5years':
#        youngCatsReturnedToOwners += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Euthanasia' and data[i][7] == '<5years':
#        youngCatsEuthanized += 1


#    if data[i][5] == 'Cat' and data[i][3] == 'Adoption' and data[i][7] == '>=5and<10years':
#        middleAgedCatsAdopted += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Died' and data[i][7] == '>=5and<10years':
#        middleAgedCatsDied += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Transfer' and data[i][7] == '>=5and<10years':
#        middleAgedCatsTransfered += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Return_to_owner' and data[i][7] == '>=5and<10years':
#        middleAgedCatsReturnedToOwners += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Euthanasia' and data[i][7] == '>=5and<10years':
#        middleAgedCatsEuthanized += 1


#    if data[i][5] == 'Cat' and data[i][3] == 'Adoption' and data[i][7] == '>=10years':
#        oldCatsAdopted += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Died' and data[i][7] == '>=10years':
#        oldCatsDied += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Transfer' and data[i][7] == '>=10years':
#        oldCatsTransfered += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Return_to_owner' and data[i][7] == '>=10years':
#        oldCatsReturnedToOwners += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Euthanasia' and data[i][7] == '>=10years':
#        oldCatsEuthanized += 1


#numOfDogs = np.sum(data['AnimalType'] == 'Dog')
#numOfCats = np.sum(data['AnimalType'] == 'Cat')

#numAdopted = np.sum(data['OutcomeType'] == 'Adoption')
#numDied = np.sum(data['OutcomeType'] == 'Died')
#numEuthanized = np.sum(data['OutcomeType'] == 'Euthanasia')
#numTransfered = np.sum(data['OutcomeType'] == 'Transfer')
#numReturned = np.sum(data['OutcomeType'] == 'Return_to_owner')

#numYoungDogs = 0
#numMiddleDogs = 0
#numOldDogs = 0

#numYoungCats = 0
#numMiddleCats = 0
#numOldCats = 0

#for i in range(len(dataVectors)):

#    if data[i][5] == 'Dog' and data[i][7] == '<5years':
#        numYoungDogs += 1

#    if data[i][5] == 'Dog' and data[i][7] == '>=5and<10years':
#        numMiddleDogs += 1

#    if data[i][5] == 'Dog' and data[i][7] == '>=10years':
#        numOldDogs += 1


#    if data[i][5] == 'Cat' and data[i][7] == '<5years':
#        numYoungCats += 1

#    if data[i][5] == 'Cat' and data[i][7] == '>=5and<10years':
#        numMiddleCats += 1

#    if data[i][5] == 'Cat' and data[i][7] == '>=10years':
#        numOldCats += 1


#percentageYoungDogsAdopted = youngDogsAdopted/numYoungDogs*100
#percentageYoungDogsDied = youngDogsDied/numYoungDogs*100
#percentageYoungDogsTransfered = youngDogsTransfered/numYoungDogs*100
#percentageYoungDogsReturnToOwners = youngDogsReturnedToOwners/numYoungDogs*100
#percentageYoungDogsEuthanized = youngDogsEuthanized/numYoungDogs*100
#percentageYoungDogsOutcomes = [percentageYoungDogsAdopted, percentageYoungDogsDied, percentageYoungDogsTransfered, percentageYoungDogsReturnToOwners, percentageYoungDogsEuthanized]

#percentageMiddleDogsAdopted = middleAgedDogsAdopted/numMiddleDogs*100
#percentageMiddleDogsDied = middleAgedDogsDied/numMiddleDogs*100
#percentageMiddleDogsTransfered = middleAgedDogsTransfered/numMiddleDogs*100
#percentageMiddleDogsReturnToOwners = middleAgedDogsReturnedToOwners/numMiddleDogs*100
#percentageMiddleDogsEuthanized = middleAgedDogsEuthanized/numMiddleDogs*100
#percentageMiddleDogsOutcomes = [percentageMiddleDogsAdopted, percentageMiddleDogsDied, percentageMiddleDogsTransfered, percentageMiddleDogsReturnToOwners, percentageMiddleDogsEuthanized]

#percentageOldDogsAdopted = oldDogsAdopted/numOldDogs*100
#percentageOldDogsDied = oldDogsDied/numOldDogs*100
#percentageOldDogsTransfered = oldDogsTransfered/numOldDogs*100
#percentageOldDogsReturnToOwners = oldDogsReturnedToOwners/numOldDogs*100
#percentageOldDogsEuthanized = oldDogsEuthanized/numOldDogs*100
#percentageOldDogsOutcomes = [percentageOldDogsAdopted, percentageOldDogsDied, percentageOldDogsTransfered, percentageOldDogsReturnToOwners, percentageOldDogsEuthanized]


#percentageYoungCatsAdopted = youngCatsAdopted/numYoungCats*100
#percentageYoungCatsDied = youngCatsDied/numYoungCats*100
#percentageYoungCatsTransfered = youngCatsTransfered/numYoungCats*100
#percentageYoungCatsReturnToOwners = youngCatsReturnedToOwners/numYoungCats*100
#percentageYoungCatsEuthanized = youngCatsEuthanized/numYoungCats*100
#percentageYoungCatsOutcomes = [percentageYoungCatsAdopted, percentageYoungCatsDied, percentageYoungCatsTransfered, percentageYoungCatsReturnToOwners, percentageYoungCatsEuthanized]

#percentageMiddleCatsAdopted = middleAgedCatsAdopted/numMiddleCats*100
#percentageMiddleCatsDied = middleAgedCatsDied/numMiddleCats*100
#percentageMiddleCatsTransfered = middleAgedCatsTransfered/numMiddleCats*100
#percentageMiddleCatsReturnToOwners = middleAgedCatsReturnedToOwners/numMiddleCats*100
#percentageMiddleCatsEuthanized = middleAgedCatsEuthanized/numMiddleCats*100
#percentageMiddleCatsOutcomes = [percentageMiddleCatsAdopted, percentageMiddleCatsDied, percentageMiddleCatsTransfered, percentageMiddleCatsReturnToOwners, percentageMiddleCatsEuthanized]

#percentageOldCatsAdopted = oldCatsAdopted/numOldCats*100
#percentageOldCatsDied = oldCatsDied/numOldCats*100
#percentageOldCatsTransfered = oldCatsTransfered/numOldCats*100
#percentageOldCatsReturnToOwners = oldCatsReturnedToOwners/numOldCats*100
#percentageOldCatsEuthanized = oldCatsEuthanized/numOldCats*100
#percentageOldCatsOutcomes = [percentageOldCatsAdopted, percentageOldCatsDied, percentageOldCatsTransfered, percentageOldCatsReturnToOwners, percentageOldCatsEuthanized]


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageYoungDogsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Young Dog Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageMiddleDogsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Middle Aged Dog Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageOldDogsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Old Dog Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageYoungCatsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Young Cat Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageMiddleCatsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Middle Aged Cats Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageOldCatsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Old Cats Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#namedDogsAdopted = 0
#namedDogsDied = 0
#namedDogsTransfered = 0
#namedDogsReturnedToOwners = 0
#namedDogsEuthanized = 0

#unNamedDogsAdopted = 0
#unNamedDogsDied = 0
#unNamedDogsTransfered = 0
#unNamedDogsReturnedToOwners = 0
#unNamedDogsEuthanized = 0


#namedCatsAdopted = 0
#namedCatsDied = 0
#namedCatsTransfered = 0
#namedCatsReturnedToOwners = 0
#namedCatsEuthanized = 0

#unNamedCatsAdopted = 0
#unNamedCatsDied = 0
#unNamedCatsTransfered = 0
#unNamedCatsReturnedToOwners = 0
#unNamedCatsEuthanized = 0


#for i in range(len(dataVectors)):
#    if data[i][5] == 'Dog' and data[i][3] == 'Adoption' and data[i][0] == 'Named':
#        namedDogsAdopted += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Died' and data[i][0] == 'Named':
#        namedDogsDied += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Transfer' and data[i][0] == 'Named':
#        namedDogsTransfered += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Return_to_owner' and data[i][0] == 'Named':
#        namedDogsReturnedToOwners += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Euthanasia' and data[i][0] == 'Named':
#        namedDogsEuthanized += 1



#    if data[i][5] == 'Dog' and data[i][3] == 'Adoption' and data[i][0] == 'NoName':
#        unNamedDogsAdopted += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Died' and data[i][0] == 'NoName':
#        unNamedDogsDied += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Transfer' and data[i][0] == 'NoName':
#        unNamedDogsTransfered += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Return_to_owner' and data[i][0] == 'NoName':
#        unNamedDogsReturnedToOwners += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Euthanasia' and data[i][0] == 'NoName':
#        unNamedDogsEuthanized += 1


#    if data[i][5] == 'Cat' and data[i][3] == 'Adoption' and data[i][0] == 'Named':
#        namedCatsAdopted += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Died' and data[i][0] == 'Named':
#        namedCatsDied += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Transfer' and data[i][0] == 'Named':
#        namedCatsTransfered += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Return_to_owner' and data[i][0] == 'Named':
#        namedCatsReturnedToOwners += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Euthanasia' and data[i][0] == 'Named':
#        namedCatsEuthanized += 1


#    if data[i][5] == 'Cat' and data[i][3] == 'Adoption' and data[i][0] == 'NoName':
#        unNamedCatsAdopted += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Died' and data[i][0] == 'NoName':
#        unNamedCatsDied += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Transfer' and data[i][0] == 'NoName':
#        unNamedCatsTransfered += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Return_to_owner' and data[i][0] == 'NoName':
#        unNamedCatsReturnedToOwners += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Euthanasia' and data[i][0] == 'NoName':
#        unNamedCatsEuthanized += 1


#numNamedDogs = 0
#numUnNamedDogs = 0

#numNamedCats = 0
#numUnNamedCats = 0

#for i in range(len(dataVectors)):

#    if data[i][5] == 'Dog' and data[i][0] == 'Named':
#        numNamedDogs += 1

#    if data[i][5] == 'Dog' and data[i][0] == 'NoName':
#        numUnNamedDogs += 1


#    if data[i][5] == 'Cat' and data[i][0] == 'Named':
#        numNamedCats += 1

#    if data[i][5] == 'Cat' and data[i][0] == 'NoName':
#        numUnNamedCats += 1


#percentageNamedDogsAdopted = namedDogsAdopted/numNamedDogs*100
#percentageNamedDogsDied = namedDogsDied/numNamedDogs*100
#percentageNamedDogsTransfered = namedDogsTransfered/numNamedDogs*100
#percentageNamedDogsReturnToOwners = namedDogsReturnedToOwners/numNamedDogs*100
#percentageNamedDogsEuthanized = namedDogsEuthanized/numNamedDogs*100
#percentageNamedDogsOutcomes = [percentageNamedDogsAdopted, percentageNamedDogsDied, percentageNamedDogsTransfered, percentageNamedDogsReturnToOwners, percentageNamedDogsEuthanized]

#percentageUnNamedDogsAdopted = unNamedDogsAdopted/numUnNamedDogs*100
#percentageUnNamedDogsDied = unNamedDogsDied/numUnNamedDogs*100
#percentageUnNamedDogsTransfered = unNamedDogsTransfered/numUnNamedDogs*100
#percentageUnNamedDogsReturnToOwners = unNamedDogsReturnedToOwners/numUnNamedDogs*100
#percentageUnNamedDogsEuthanized = unNamedDogsEuthanized/numUnNamedDogs*100
#percentageUnNamedDogsOutcomes = [percentageUnNamedDogsAdopted, percentageUnNamedDogsDied, percentageUnNamedDogsTransfered, percentageUnNamedDogsReturnToOwners, percentageUnNamedDogsEuthanized]


#percentageNamedCatsAdopted = namedCatsAdopted/numNamedCats*100
#percentageNamedCatsDied = namedCatsDied/numNamedCats*100
#percentageNamedCatsTransfered = namedCatsTransfered/numNamedCats*100
#percentageNamedCatsReturnToOwners = namedCatsReturnedToOwners/numNamedCats*100
#percentageNamedCatsEuthanized = namedCatsEuthanized/numNamedCats*100
#percentageNamedCatsOutcomes = [percentageNamedCatsAdopted, percentageNamedCatsDied, percentageNamedCatsTransfered, percentageNamedCatsReturnToOwners, percentageNamedCatsEuthanized]

#percentageUnNamedCatsAdopted = unNamedCatsAdopted/numUnNamedCats*100
#percentageUnNamedCatsDied = unNamedCatsDied/numUnNamedCats*100
#percentageUnNamedCatsTransfered = unNamedCatsTransfered/numUnNamedCats*100
#percentageUnNamedCatsReturnToOwners = unNamedCatsReturnedToOwners/numUnNamedCats*100
#percentageUnNamedCatsEuthanized = unNamedCatsEuthanized/numUnNamedCats*100
#percentageUnNamedCatsOutcomes = [percentageUnNamedCatsAdopted, percentageUnNamedCatsDied, percentageUnNamedCatsTransfered, percentageUnNamedCatsReturnToOwners, percentageUnNamedCatsEuthanized]


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageNamedDogsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Named Dog Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageUnNamedDogsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Un-Named Dog Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageNamedCatsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Named Cat Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageUnNamedCatsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Un-Named Cat Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#SolidColorDogsAdopted = 0
#SolidColorDogsDied = 0
#SolidColorDogsTransfered = 0
#SolidColorDogsReturnedToOwners = 0
#SolidColorDogsEuthanized = 0

#MixedColorDogsAdopted = 0
#MixedColorDogsDied = 0
#MixedColorDogsTransfered = 0
#MixedColorDogsReturnedToOwners = 0
#MixedColorDogsEuthanized = 0


#SolidColorCatsAdopted = 0
#SolidColorCatsDied = 0
#SolidColorCatsTransfered = 0
#SolidColorCatsReturnedToOwners = 0
#SolidColorCatsEuthanized = 0

#MixedColorCatsAdopted = 0
#MixedColorCatsDied = 0
#MixedColorCatsTransfered = 0
#MixedColorCatsReturnedToOwners = 0
#MixedColorCatsEuthanized = 0


#for i in range(len(dataVectors)):
#    if data[i][5] == 'Dog' and data[i][3] == 'Adoption' and data[i][9] == 'SolidColor':
#        SolidColorDogsAdopted += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Died' and data[i][9] == 'SolidColor':
#        SolidColorDogsDied += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Transfer' and data[i][9] == 'SolidColor':
#        SolidColorDogsTransfered += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Return_to_owner' and data[i][9] == 'SolidColor':
#        SolidColorDogsReturnedToOwners += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Euthanasia' and data[i][9] == 'SolidColor':
#        SolidColorDogsEuthanized += 1



#    if data[i][5] == 'Dog' and data[i][3] == 'Adoption' and data[i][9] == 'MixedColor':
#        MixedColorDogsAdopted += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Died' and data[i][9] == 'MixedColor':
#        MixedColorDogsDied += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Transfer' and data[i][9] == 'MixedColor':
#        MixedColorDogsTransfered += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Return_to_owner' and data[i][9] == 'MixedColor':
#        MixedColorDogsReturnedToOwners += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Euthanasia' and data[i][9] == 'MixedColor':
#        MixedColorDogsEuthanized += 1


#    if data[i][5] == 'Cat' and data[i][3] == 'Adoption' and data[i][9] == 'SolidColor':
#        SolidColorCatsAdopted += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Died' and data[i][9] == 'SolidColor':
#        SolidColorCatsDied += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Transfer' and data[i][9] == 'SolidColor':
#        SolidColorCatsTransfered += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Return_to_owner' and data[i][9] == 'SolidColor':
#        SolidColorCatsReturnedToOwners += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Euthanasia' and data[i][9] == 'SolidColor':
#        SolidColorCatsEuthanized += 1


#    if data[i][5] == 'Cat' and data[i][3] == 'Adoption' and data[i][9] == 'MixedColor':
#        MixedColorCatsAdopted += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Died' and data[i][9] == 'MixedColor':
#        MixedColorCatsDied += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Transfer' and data[i][9] == 'MixedColor':
#        MixedColorCatsTransfered += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Return_to_owner' and data[i][9] == 'MixedColor':
#        MixedColorCatsReturnedToOwners += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Euthanasia' and data[i][9] == 'MixedColor':
#        MixedColorCatsEuthanized += 1


#numSolidColorDogs = 0
#numMixedColorDogs = 0

#numSolidColorCats = 0
#numMixedColorCats = 0

#for i in range(len(dataVectors)):

#    if data[i][5] == 'Dog' and data[i][9] == 'SolidColor':
#        numSolidColorDogs += 1

#    if data[i][5] == 'Dog' and data[i][9] == 'MixedColor':
#        numMixedColorDogs += 1


#    if data[i][5] == 'Cat' and data[i][9] == 'SolidColor':
#        numSolidColorCats += 1

#    if data[i][5] == 'Cat' and data[i][9] == 'MixedColor':
#        numMixedColorCats += 1


#percentageSolidColorDogsAdopted = SolidColorDogsAdopted/numSolidColorDogs*100
#percentageSolidColorDogsDied = SolidColorDogsDied/numSolidColorDogs*100
#percentageSolidColorDogsTransfered = SolidColorDogsTransfered/numSolidColorDogs*100
#percentageSolidColorDogsReturnToOwners = SolidColorDogsReturnedToOwners/numSolidColorDogs*100
#percentageSolidColorDogsEuthanized = SolidColorDogsEuthanized/numSolidColorDogs*100
#percentageSolidColorDogsOutcomes = [percentageSolidColorDogsAdopted, percentageSolidColorDogsDied, percentageSolidColorDogsTransfered, percentageSolidColorDogsReturnToOwners, percentageSolidColorDogsEuthanized]

#percentageMixedColorDogsAdopted = MixedColorDogsAdopted/numMixedColorDogs*100
#percentageMixedColorDogsDied = MixedColorDogsDied/numMixedColorDogs*100
#percentageMixedColorDogsTransfered = MixedColorDogsTransfered/numMixedColorDogs*100
#percentageMixedColorDogsReturnToOwners = MixedColorDogsReturnedToOwners/numMixedColorDogs*100
#percentageMixedColorDogsEuthanized = MixedColorDogsEuthanized/numMixedColorDogs*100
#percentageMixedColorDogsOutcomes = [percentageMixedColorDogsAdopted, percentageMixedColorDogsDied, percentageMixedColorDogsTransfered, percentageMixedColorDogsReturnToOwners, percentageMixedColorDogsEuthanized]


#percentageSolidColorCatsAdopted = SolidColorCatsAdopted/numSolidColorCats*100
#percentageSolidColorCatsDied = SolidColorCatsDied/numSolidColorCats*100
#percentageSolidColorCatsTransfered = SolidColorCatsTransfered/numSolidColorCats*100
#percentageSolidColorCatsReturnToOwners = SolidColorCatsReturnedToOwners/numSolidColorCats*100
#percentageSolidColorCatsEuthanized = SolidColorCatsEuthanized/numSolidColorCats*100
#percentageSolidColorCatsOutcomes = [percentageSolidColorCatsAdopted, percentageSolidColorCatsDied, percentageSolidColorCatsTransfered, percentageSolidColorCatsReturnToOwners, percentageSolidColorCatsEuthanized]

#percentageMixedColorCatsAdopted = MixedColorCatsAdopted/numMixedColorCats*100
#percentageMixedColorCatsDied = MixedColorCatsDied/numMixedColorCats*100
#percentageMixedColorCatsTransfered = MixedColorCatsTransfered/numMixedColorCats*100
#percentageMixedColorCatsReturnToOwners = MixedColorCatsReturnedToOwners/numMixedColorCats*100
#percentageMixedColorCatsEuthanized = MixedColorCatsEuthanized/numMixedColorCats*100
#percentageMixedColorCatsOutcomes = [percentageMixedColorCatsAdopted, percentageMixedColorCatsDied, percentageMixedColorCatsTransfered, percentageMixedColorCatsReturnToOwners, percentageMixedColorCatsEuthanized]


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageSolidColorDogsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Solid Color Dog Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageMixedColorDogsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Mixed Color Dog Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageSolidColorCatsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Solid Color Cat Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageMixedColorCatsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Mixed Color Cat Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#SpringDogsAdopted = 0
#SpringDogsDied = 0
#SpringDogsTransfered = 0
#SpringDogsReturnedToOwners = 0
#SpringDogsEuthanized = 0

#SummerDogsAdopted = 0
#SummerDogsDied = 0
#SummerDogsTransfered = 0
#SummerDogsReturnedToOwners = 0
#SummerDogsEuthanized = 0

#FallDogsAdopted = 0
#FallDogsDied = 0
#FallDogsTransfered = 0
#FallDogsReturnedToOwners = 0
#FallDogsEuthanized = 0

#WinterDogsAdopted = 0
#WinterDogsDied = 0
#WinterDogsTransfered = 0
#WinterDogsReturnedToOwners = 0
#WinterDogsEuthanized = 0


#SpringCatsAdopted = 0
#SpringCatsDied = 0
#SpringCatsTransfered = 0
#SpringCatsReturnedToOwners = 0
#SpringCatsEuthanized = 0

#SummerCatsAdopted = 0
#SummerCatsDied = 0
#SummerCatsTransfered = 0
#SummerCatsReturnedToOwners = 0
#SummerCatsEuthanized = 0

#FallCatsAdopted = 0
#FallCatsDied = 0
#FallCatsTransfered = 0
#FallCatsReturnedToOwners = 0
#FallCatsEuthanized = 0

#WinterCatsAdopted = 0
#WinterCatsDied = 0
#WinterCatsTransfered = 0
#WinterCatsReturnedToOwners = 0
#WinterCatsEuthanized = 0


#for i in range(len(dataVectors)):
#    if data[i][5] == 'Dog' and data[i][3] == 'Adoption' and data[i][1] == 'Spring':
#        SpringDogsAdopted += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Died' and data[i][1] == 'Spring':
#        SpringDogsDied += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Transfer' and data[i][1] == 'Spring':
#        SpringDogsTransfered += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Return_to_owner' and data[i][1] == 'Spring':
#        SpringDogsReturnedToOwners += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Euthanasia' and data[i][1] == 'Spring':
#        SpringDogsEuthanized += 1



#    if data[i][5] == 'Dog' and data[i][3] == 'Adoption' and data[i][1] == 'Summer':
#        SummerDogsAdopted += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Died' and data[i][1] == 'Summer':
#        SummerDogsDied += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Transfer' and data[i][1] == 'Summer':
#        SummerDogsTransfered += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Return_to_owner' and data[i][1] == 'Summer':
#        SummerDogsReturnedToOwners += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Euthanasia' and data[i][1] == 'Summer':
#        SummerDogsEuthanized += 1


#    if data[i][5] == 'Dog' and data[i][3] == 'Adoption' and data[i][1] == 'Fall':
#        FallDogsAdopted += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Died' and data[i][1] == 'Fall':
#        FallDogsDied += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Transfer' and data[i][1] == 'Fall':
#        FallDogsTransfered += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Return_to_owner' and data[i][1] == 'Fall':
#        FallDogsReturnedToOwners += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Euthanasia' and data[i][1] == 'Fall':
#        FallDogsEuthanized += 1



#    if data[i][5] == 'Dog' and data[i][3] == 'Adoption' and data[i][1] == 'Winter':
#        WinterDogsAdopted += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Died' and data[i][1] == 'Winter':
#        WinterDogsDied += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Transfer' and data[i][1] == 'Winter':
#        WinterDogsTransfered += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Return_to_owner' and data[i][1] == 'Winter':
#        WinterDogsReturnedToOwners += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Euthanasia' and data[i][1] == 'Winter':
#        WinterDogsEuthanized += 1



#    if data[i][5] == 'Cat' and data[i][3] == 'Adoption' and data[i][1] == 'Spring':
#        SpringCatsAdopted += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Died' and data[i][1] == 'Spring':
#        SpringCatsDied += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Transfer' and data[i][1] == 'Spring':
#        SpringCatsTransfered += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Return_to_owner' and data[i][1] == 'Spring':
#        SpringCatsReturnedToOwners += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Euthanasia' and data[i][1] == 'Spring':
#        SpringCatsEuthanized += 1



#    if data[i][5] == 'Cat' and data[i][3] == 'Adoption' and data[i][1] == 'Summer':
#        SummerCatsAdopted += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Died' and data[i][1] == 'Summer':
#        SummerCatsDied += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Transfer' and data[i][1] == 'Summer':
#        SummerCatsTransfered += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Return_to_owner' and data[i][1] == 'Summer':
#        SummerCatsReturnedToOwners += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Euthanasia' and data[i][1] == 'Summer':
#        SummerCatsEuthanized += 1


#    if data[i][5] == 'Cat' and data[i][3] == 'Adoption' and data[i][1] == 'Fall':
#        FallCatsAdopted += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Died' and data[i][1] == 'Fall':
#        FallCatsDied += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Transfer' and data[i][1] == 'Fall':
#        FallCatsTransfered += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Return_to_owner' and data[i][1] == 'Fall':
#        FallCatsReturnedToOwners += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Euthanasia' and data[i][1] == 'Fall':
#        FallCatsEuthanized += 1



#    if data[i][5] == 'Cat' and data[i][3] == 'Adoption' and data[i][1] == 'Winter':
#        WinterCatsAdopted += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Died' and data[i][1] == 'Winter':
#        WinterCatsDied += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Transfer' and data[i][1] == 'Winter':
#        WinterCatsTransfered += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Return_to_owner' and data[i][1] == 'Winter':
#        WinterCatsReturnedToOwners += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Euthanasia' and data[i][1] == 'Winter':
#        WinterCatsEuthanized += 1



#numSpringDogs = 0
#numSummerDogs = 0
#numFallDogs = 0
#numWinterDogs = 0

#numSpringCats = 0
#numSummerCats = 0
#numFallCats = 0
#numWinterCats = 0

#for i in range(len(dataVectors)):

#    if data[i][5] == 'Dog' and data[i][1] == 'Spring':
#        numSpringDogs += 1

#    if data[i][5] == 'Dog' and data[i][1] == 'Summer':
#        numSummerDogs += 1

#    if data[i][5] == 'Dog' and data[i][1] == 'Fall':
#        numFallDogs += 1

#    if data[i][5] == 'Dog' and data[i][1] == 'Winter':
#        numWinterDogs += 1


#    if data[i][5] == 'Cat' and data[i][1] == 'Spring':
#        numSpringCats += 1

#    if data[i][5] == 'Cat' and data[i][1] == 'Summer':
#        numSummerCats += 1

#    if data[i][5] == 'Cat' and data[i][1] == 'Fall':
#        numFallCats += 1

#    if data[i][5] == 'Cat' and data[i][1] == 'Winter':
#        numWinterCats += 1


#percentageSpringDogsAdopted = SpringDogsAdopted/numSpringDogs*100
#percentageSpringDogsDied = SpringDogsDied/numSpringDogs*100
#percentageSpringDogsTransfered = SpringDogsTransfered/numSpringDogs*100
#percentageSpringDogsReturnToOwners = SpringDogsReturnedToOwners/numSpringDogs*100
#percentageSpringDogsEuthanized = SpringDogsEuthanized/numSpringDogs*100
#percentageSpringDogsOutcomes = [percentageSpringDogsAdopted, percentageSpringDogsDied, percentageSpringDogsTransfered, percentageSpringDogsReturnToOwners, percentageSpringDogsEuthanized]

#percentageSummerDogsAdopted = SummerDogsAdopted/numSummerDogs*100
#percentageSummerDogsDied = SummerDogsDied/numSummerDogs*100
#percentageSummerDogsTransfered = SummerDogsTransfered/numSummerDogs*100
#percentageSummerDogsReturnToOwners = SummerDogsReturnedToOwners/numSummerDogs*100
#percentageSummerDogsEuthanized = SummerDogsEuthanized/numSummerDogs*100
#percentageSummerDogsOutcomes = [percentageSummerDogsAdopted, percentageSummerDogsDied, percentageSummerDogsTransfered, percentageSummerDogsReturnToOwners, percentageSummerDogsEuthanized]

#percentageFallDogsAdopted = FallDogsAdopted/numFallDogs*100
#percentageFallDogsDied = FallDogsDied/numFallDogs*100
#percentageFallDogsTransfered = FallDogsTransfered/numFallDogs*100
#percentageFallDogsReturnToOwners = FallDogsReturnedToOwners/numFallDogs*100
#percentageFallDogsEuthanized = FallDogsEuthanized/numFallDogs*100
#percentageFallDogsOutcomes = [percentageFallDogsAdopted, percentageFallDogsDied, percentageFallDogsTransfered, percentageFallDogsReturnToOwners, percentageFallDogsEuthanized]

#percentageWinterDogsAdopted = WinterDogsAdopted/numWinterDogs*100
#percentageWinterDogsDied = WinterDogsDied/numWinterDogs*100
#percentageWinterDogsTransfered = WinterDogsTransfered/numWinterDogs*100
#percentageWinterDogsReturnToOwners = WinterDogsReturnedToOwners/numWinterDogs*100
#percentageWinterDogsEuthanized = WinterDogsEuthanized/numWinterDogs*100
#percentageWinterDogsOutcomes = [percentageWinterDogsAdopted, percentageWinterDogsDied, percentageWinterDogsTransfered, percentageWinterDogsReturnToOwners, percentageWinterDogsEuthanized]


#percentageSpringCatsAdopted = SpringCatsAdopted/numSpringCats*100
#percentageSpringCatsDied = SpringCatsDied/numSpringCats*100
#percentageSpringCatsTransfered = SpringCatsTransfered/numSpringCats*100
#percentageSpringCatsReturnToOwners = SpringCatsReturnedToOwners/numSpringCats*100
#percentageSpringCatsEuthanized = SpringCatsEuthanized/numSpringCats*100
#percentageSpringCatsOutcomes = [percentageSpringCatsAdopted, percentageSpringCatsDied, percentageSpringCatsTransfered, percentageSpringCatsReturnToOwners, percentageSpringCatsEuthanized]

#percentageSummerCatsAdopted = SummerCatsAdopted/numSummerCats*100
#percentageSummerCatsDied = SummerCatsDied/numSummerCats*100
#percentageSummerCatsTransfered = SummerCatsTransfered/numSummerCats*100
#percentageSummerCatsReturnToOwners = SummerCatsReturnedToOwners/numSummerCats*100
#percentageSummerCatsEuthanized = SummerCatsEuthanized/numSummerCats*100
#percentageSummerCatsOutcomes = [percentageSummerCatsAdopted, percentageSummerCatsDied, percentageSummerCatsTransfered, percentageSummerCatsReturnToOwners, percentageSummerCatsEuthanized]

#percentageFallCatsAdopted = FallCatsAdopted/numFallCats*100
#percentageFallCatsDied = FallCatsDied/numFallCats*100
#percentageFallCatsTransfered = FallCatsTransfered/numFallCats*100
#percentageFallCatsReturnToOwners = FallCatsReturnedToOwners/numFallCats*100
#percentageFallCatsEuthanized = FallCatsEuthanized/numFallCats*100
#percentageFallCatsOutcomes = [percentageFallCatsAdopted, percentageFallCatsDied, percentageFallCatsTransfered, percentageFallCatsReturnToOwners, percentageFallCatsEuthanized]

#percentageWinterCatsAdopted = WinterCatsAdopted/numWinterCats*100
#percentageWinterCatsDied = WinterCatsDied/numWinterCats*100
#percentageWinterCatsTransfered = WinterCatsTransfered/numWinterCats*100
#percentageWinterCatsReturnToOwners = WinterCatsReturnedToOwners/numWinterCats*100
#percentageWinterCatsEuthanized = WinterCatsEuthanized/numWinterCats*100
#percentageWinterCatsOutcomes = [percentageWinterCatsAdopted, percentageWinterCatsDied, percentageWinterCatsTransfered, percentageWinterCatsReturnToOwners, percentageWinterCatsEuthanized]


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageSpringDogsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Spring Dog Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageSummerDogsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Summer Dog Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageFallDogsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Fall Dog Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageWinterDogsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Winter Dog Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageSpringCatsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Spring Cat Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageSummerCatsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Summer Cat Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageFallCatsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Fall Cat Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageWinterCatsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Winter Cat Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()




#MorningDogsAdopted = 0
#MorningDogsDied = 0
#MorningDogsTransfered = 0
#MorningDogsReturnedToOwners = 0
#MorningDogsEuthanized = 0

#AfternoonDogsAdopted = 0
#AfternoonDogsDied = 0
#AfternoonDogsTransfered = 0
#AfternoonDogsReturnedToOwners = 0
#AfternoonDogsEuthanized = 0

#NightDogsAdopted = 0
#NightDogsDied = 0
#NightDogsTransfered = 0
#NightDogsReturnedToOwners = 0
#NightDogsEuthanized = 0


#MorningCatsAdopted = 0
#MorningCatsDied = 0
#MorningCatsTransfered = 0
#MorningCatsReturnedToOwners = 0
#MorningCatsEuthanized = 0

#AfternoonCatsAdopted = 0
#AfternoonCatsDied = 0
#AfternoonCatsTransfered = 0
#AfternoonCatsReturnedToOwners = 0
#AfternoonCatsEuthanized = 0

#NightCatsAdopted = 0
#NightCatsDied = 0
#NightCatsTransfered = 0
#NightCatsReturnedToOwners = 0
#NightCatsEuthanized = 0


#for i in range(len(dataVectors)):
#    if data[i][5] == 'Dog' and data[i][3] == 'Adoption' and data[i][2] == 'Morning':
#        MorningDogsAdopted += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Died' and data[i][2] == 'Morning':
#        MorningDogsDied += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Transfer' and data[i][2] == 'Morning':
#        MorningDogsTransfered += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Return_to_owner' and data[i][2] == 'Morning':
#        MorningDogsReturnedToOwners += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Euthanasia' and data[i][2] == 'Morning':
#        MorningDogsEuthanized += 1



#    if data[i][5] == 'Dog' and data[i][3] == 'Adoption' and data[i][2] == 'Afternoon':
#        AfternoonDogsAdopted += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Died' and data[i][2] == 'Afternoon':
#        AfternoonDogsDied += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Transfer' and data[i][2] == 'Afternoon':
#        AfternoonDogsTransfered += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Return_to_owner' and data[i][2] == 'Afternoon':
#        AfternoonDogsReturnedToOwners += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Euthanasia' and data[i][2] == 'Afternoon':
#        AfternoonDogsEuthanized += 1


#    if data[i][5] == 'Dog' and data[i][3] == 'Adoption' and data[i][2] == 'Night':
#        NightDogsAdopted += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Died' and data[i][2] == 'Night':
#        NightDogsDied += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Transfer' and data[i][2] == 'Night':
#        NightDogsTransfered += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Return_to_owner' and data[i][2] == 'Night':
#        NightDogsReturnedToOwners += 1

#    if data[i][5] == 'Dog' and data[i][3] == 'Euthanasia' and data[i][2] == 'Night':
#        NightDogsEuthanized += 1



#    if data[i][5] == 'Cat' and data[i][3] == 'Adoption' and data[i][2] == 'Morning':
#        MorningCatsAdopted += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Died' and data[i][2] == 'Morning':
#        MorningCatsDied += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Transfer' and data[i][2] == 'Morning':
#        MorningCatsTransfered += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Return_to_owner' and data[i][2] == 'Morning':
#        MorningCatsReturnedToOwners += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Euthanasia' and data[i][2] == 'Morning':
#        MorningCatsEuthanized += 1



#    if data[i][5] == 'Cat' and data[i][3] == 'Adoption' and data[i][2] == 'Afternoon':
#        AfternoonCatsAdopted += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Died' and data[i][2] == 'Afternoon':
#        AfternoonCatsDied += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Transfer' and data[i][2] == 'Afternoon':
#        AfternoonCatsTransfered += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Return_to_owner' and data[i][2] == 'Afternoon':
#        AfternoonCatsReturnedToOwners += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Euthanasia' and data[i][2] == 'Afternoon':
#        AfternoonCatsEuthanized += 1


#    if data[i][5] == 'Cat' and data[i][3] == 'Adoption' and data[i][2] == 'Night':
#        NightCatsAdopted += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Died' and data[i][2] == 'Night':
#        NightCatsDied += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Transfer' and data[i][2] == 'Night':
#        NightCatsTransfered += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Return_to_owner' and data[i][2] == 'Night':
#        NightCatsReturnedToOwners += 1

#    if data[i][5] == 'Cat' and data[i][3] == 'Euthanasia' and data[i][2] == 'Night':
#        NightCatsEuthanized += 1


#numMorningDogs = 0
#numAfternoonDogs = 0
#numNightDogs = 0


#numMorningCats = 0
#numAfternoonCats = 0
#numNightCats = 0

#for i in range(len(dataVectors)):

#    if data[i][5] == 'Dog' and data[i][2] == 'Morning':
#        numMorningDogs += 1

#    if data[i][5] == 'Dog' and data[i][2] == 'Afternoon':
#        numAfternoonDogs += 1

#    if data[i][5] == 'Dog' and data[i][2] == 'Night':
#        numNightDogs += 1


#    if data[i][5] == 'Cat' and data[i][2] == 'Morning':
#        numMorningCats += 1

#    if data[i][5] == 'Cat' and data[i][2] == 'Afternoon':
#        numAfternoonCats += 1

#    if data[i][5] == 'Cat' and data[i][2] == 'Night':
#        numNightCats += 1


#percentageMorningDogsAdopted = MorningDogsAdopted/numMorningDogs*100
#percentageMorningDogsDied = MorningDogsDied/numMorningDogs*100
#percentageMorningDogsTransfered = MorningDogsTransfered/numMorningDogs*100
#percentageMorningDogsReturnToOwners = MorningDogsReturnedToOwners/numMorningDogs*100
#percentageMorningDogsEuthanized = MorningDogsEuthanized/numMorningDogs*100
#percentageMorningDogsOutcomes = [percentageMorningDogsAdopted, percentageMorningDogsDied, percentageMorningDogsTransfered, percentageMorningDogsReturnToOwners, percentageMorningDogsEuthanized]

#percentageAfternoonDogsAdopted = AfternoonDogsAdopted/numAfternoonDogs*100
#percentageAfternoonDogsDied = AfternoonDogsDied/numAfternoonDogs*100
#percentageAfternoonDogsTransfered = AfternoonDogsTransfered/numAfternoonDogs*100
#percentageAfternoonDogsReturnToOwners = AfternoonDogsReturnedToOwners/numAfternoonDogs*100
#percentageAfternoonDogsEuthanized = AfternoonDogsEuthanized/numAfternoonDogs*100
#percentageAfternoonDogsOutcomes = [percentageAfternoonDogsAdopted, percentageAfternoonDogsDied, percentageAfternoonDogsTransfered, percentageAfternoonDogsReturnToOwners, percentageAfternoonDogsEuthanized]

#percentageNightDogsAdopted = NightDogsAdopted/numNightDogs*100
#percentageNightDogsDied = NightDogsDied/numNightDogs*100
#percentageNightDogsTransfered = NightDogsTransfered/numNightDogs*100
#percentageNightDogsReturnToOwners = NightDogsReturnedToOwners/numNightDogs*100
#percentageNightDogsEuthanized = NightDogsEuthanized/numNightDogs*100
#percentageNightDogsOutcomes = [percentageNightDogsAdopted, percentageNightDogsDied, percentageNightDogsTransfered, percentageNightDogsReturnToOwners, percentageNightDogsEuthanized]

#percentageMorningCatsAdopted = MorningCatsAdopted/numMorningCats*100
#percentageMorningCatsDied = MorningCatsDied/numMorningCats*100
#percentageMorningCatsTransfered = MorningCatsTransfered/numMorningCats*100
#percentageMorningCatsReturnToOwners = MorningCatsReturnedToOwners/numMorningCats*100
#percentageMorningCatsEuthanized = MorningCatsEuthanized/numMorningCats*100
#percentageMorningCatsOutcomes = [percentageMorningCatsAdopted, percentageMorningCatsDied, percentageMorningCatsTransfered, percentageMorningCatsReturnToOwners, percentageMorningCatsEuthanized]

#percentageAfternoonCatsAdopted = AfternoonCatsAdopted/numAfternoonCats*100
#percentageAfternoonCatsDied = AfternoonCatsDied/numAfternoonCats*100
#percentageAfternoonCatsTransfered = AfternoonCatsTransfered/numAfternoonCats*100
#percentageAfternoonCatsReturnToOwners = AfternoonCatsReturnedToOwners/numAfternoonCats*100
#percentageAfternoonCatsEuthanized = AfternoonCatsEuthanized/numAfternoonCats*100
#percentageAfternoonCatsOutcomes = [percentageAfternoonCatsAdopted, percentageAfternoonCatsDied, percentageAfternoonCatsTransfered, percentageAfternoonCatsReturnToOwners, percentageAfternoonCatsEuthanized]

#percentageNightCatsAdopted = NightCatsAdopted/numNightCats*100
#percentageNightCatsDied = NightCatsDied/numNightCats*100
#percentageNightCatsTransfered = NightCatsTransfered/numNightCats*100
#percentageNightCatsReturnToOwners = NightCatsReturnedToOwners/numNightCats*100
#percentageNightCatsEuthanized = NightCatsEuthanized/numNightCats*100
#percentageNightCatsOutcomes = [percentageNightCatsAdopted, percentageNightCatsDied, percentageNightCatsTransfered, percentageNightCatsReturnToOwners, percentageNightCatsEuthanized]

#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageMorningDogsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Morning Dog Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageAfternoonDogsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Afternoon Dog Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageNightDogsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Night Dog Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageMorningCatsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Morning Cat Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageAfternoonCatsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Afternoon Cat Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()


#fig, ax = plt.subplots()
#bars = ax.bar(np.arange(5), percentageNightCatsOutcomes)
#ax.set_ylabel('Percentage')
#ax.set_title('Percentage Night Cat Outcomes')
#ax.set_ylim([0,100])
#ax.set_xticks(np.arange(5) + 0.42)
#ax.set_xticklabels(('Adopted','Died','Transfered','Returned', 'Euthanized'))
#plt.show()
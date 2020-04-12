import operator
import pandas as pd
import numpy as np

def eculideanDistance(inst1,inst2,length):
    distance=0
    for x in range(length):
        distance+=pow(inst1[x]-inst2[x],2)
    return np.sqrt(distance)

def getNeighbors(trainingSet,testInstance,k):
    distances=[]
    length=len(testInstance)
    for x in range(len(trainingSet)):
        dist=eculideanDistance(testInstance,trainingSet[x],length)
        distances.append((trainingSet[x],dist))
    distances.sort(key=operator.itemgetter(1))
    neighbors=[]
    for x in range(k):
        neighbors.append(distances[x][0])
    return neighbors

def getResponse(neighbors):
    a=0;b=0
    for x in range(len(neighbors)):
        response=neighbors[x][-1]
        if response=='0':
            b+=1
        else:
            a+=1
    if a>b:
        res='1'
    else:
        res='0'
    return res

def main():
    # trainSet=pd.read_csv('12.csv')
    # trainSet=np.array(trainSet)
    trainSet=[[1,1,5,3,'a'],[2,2,2,3,'a'],[1,1,3,4,'a'],[0,0,0,0,'b'],[0,0,0,7,'a'],[4,4.5,4,2,'b']]
    testInstance=[91,13,350,0.600583089]
    k=4
    neighbors=getNeighbors(trainSet,testInstance,k)
    response=getResponse(neighbors)
    print(neighbors)
    #testInstance[4]=response
    print(response)
    testInstance.append(response)
    print(testInstance)

main()
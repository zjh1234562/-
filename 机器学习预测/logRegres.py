import pandas as pd
import numpy as np
from numpy import *
pre=[]
def normalize(X):
    m, n = X.shape
    # 归一化每一个特征
    for j in range(n):
        features = X[:,j]
        minVal = features.min(axis=0)
        maxVal = features.max(axis=0)
        diff = maxVal - minVal
        if diff != 0:
           X[:,j] = (features-minVal)/diff
        else:
           X[:,j] = 0
    return X
def noisy(mat):
    #mat = pd.DataFrame({'v1':[887,788,999,688,488,585,787,889,884],'v2':[1,2,2,2,3,4,4,9,3],'v3':[1,2,2,6,3,4,4,999999999,3]})
    data=np.array(mat)
    m,n=data.shape
    averages=[]
    vars=[]
    for j in range(n):
        features = data[:,j]
        average = features.mean(axis=0)
        var = features.std(axis=0)
        averages.append(average)
        vars.append(var)
        #print(data[(np.abs(data)>(3*var)).any(1)])

    for row in range(m):
        for cloumn in range(n):
            average=averages[cloumn]
            var=vars[cloumn]
            if(data[row][cloumn]>average+3*var):
                data[row][cloumn]=average
    return data
def pca(dataMat,topNfeat=4):  #求数据矩阵每一列的均值
    meanVals=mean(dataMat,axis=0)#数据矩阵每一列特征减去该列的特征均值
    meanRemoved=dataMat-meanVals
    covMat=cov(meanRemoved,rowvar=0)#计算协方差矩阵的特征值及对应的特征向量
    Vals,Vects=linalg.eig(mat(covMat)) #sort():对特征值矩阵排序(由小到大)
    #argsort():对特征值矩阵进行由小到大排序，返回对应排序后的索引
    ValInd=argsort(Vals)#从排序后的矩阵最后一个开始自下而上选取最大的N个特征值，返回其对应的索引
    ValInd=ValInd[:-(topNfeat+1):-1]#将特征值最大的N个特征值对应索引的特征向量提取出来，组成压缩矩阵
    redEigVects=Vects[:,ValInd]#将去除均值后的数据矩阵*压缩矩阵，转换到新的空间，使维度降低为N
    lowDDataMat=meanRemoved*redEigVects
    return lowDDataMat
def sigmoid(inX):
    return 1.0/(1+exp(-inX))
def stocGradAscent1(dataMatrix, classLabels, numIter=150):
    m,n = shape(dataMatrix)
    weights = ones(n)   #initialize to all ones
    for j in range(numIter):
        dataIndex = range(m)
        for i in range(m):
            alpha = 4/(1.0+j+i)+0.0001    #apha decreases with iteration, does not
            randIndex = int(random.uniform(0,len(dataIndex)))#go to 0 because of the constant
            h = sigmoid(sum(dataMatrix[randIndex]*weights))
            error = classLabels[randIndex] - h
            weights = weights + alpha * error * dataMatrix[randIndex]
    return weights
def classifyVector(inX, weights):
    prob = sigmoid(sum(inX*weights))
    pre.append(prob)
    if prob > 0.5: return 1.0
    else: return 0.0


dftr=pd.read_csv('train_data2.csv')
trainingLabels=dftr.pop('level')
dftr=noisy(dftr)   #去异常值
dftr=np.array(dftr)
trainingLabels=np.array(trainingLabels)
dftr=normalize(dftr)   #归一
dftr=pca(dftr)   #降维
dftr=np.array(dftr)
w=stocGradAscent1(dftr,trainingLabels)
#w=[ 0.6097785  -0.01661981 -0.1657376  -0.22011304]

ver=pd.read_csv('verification_data.csv',usecols=[0,1,2,3])
ver=np.array(ver)
ver=normalize(ver)
testlables=[]
for i in range(len(ver)):
    a=classifyVector(ver[i],w)
    # print(a)
    # print('==========')
testlables=np.array(pre)
testlables=pd.DataFrame(pre,columns=['pre'])
testlables.to_csv('1.csv')

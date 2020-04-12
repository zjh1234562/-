from numpy import *
import pandas as pd
import numpy as np
#pca特征维度压缩函数
#@dataMat 数据集矩阵
#@topNfeat 需要保留的特征维度，即要压缩成的维度数
def pca(dataMat,topNfeat=2):  #求数据矩阵每一列的均值
    meanVals=mean(dataMat,axis=0)#数据矩阵每一列特征减去该列的特征均值
    meanRemoved=dataMat-meanVals
    covMat=cov(meanRemoved,rowvar=0)#计算协方差矩阵的特征值及对应的特征向量
    Vals,Vects=linalg.eig(mat(covMat)) #sort():对特征值矩阵排序(由小到大)
    print(Vals)
    #argsort():对特征值矩阵进行由小到大排序，返回对应排序后的索引
    ValInd=argsort(Vals)#从排序后的矩阵最后一个开始自下而上选取最大的N个特征值，返回其对应的索引
    print(ValInd)
    ValInd=ValInd[:-(topNfeat+1):-1]#将特征值最大的N个特征值对应索引的特征向量提取出来，组成压缩矩阵
    redEigVects=Vects[:,ValInd]#将去除均值后的数据矩阵*压缩矩阵，转换到新的空间，使维度降低为N
    lowDDataMat=meanRemoved*redEigVects
    return lowDDataMat

dataset = pd.DataFrame({'v1':[0.69,-1.31,0.39,0.09,1.29,0.49,0.19,-0.81,-0.31,-0.71],'v2':[0.49,-1.21,0.99,0.29,1.09,0.79,-0.31,-0.81,-0.31,-1.01]})
dataset=np.array(dataset)
lowDDataMat=pca(dataset)
print(lowDDataMat)

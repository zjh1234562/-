from numpy import *
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
def ridgeRegres(xMat,yMat,lam=0.2):
    '''
        Desc：
            这个函数实现了给定 lambda 下的岭回归求解。
            如果数据的特征比样本点还多，就不能再使用上面介绍的的线性回归和局部现行回归了，因为计算 (xTx)^(-1)会出现错误。
            如果特征比样本点还多（n > m），也就是说，输入数据的矩阵x不是满秩矩阵。非满秩矩阵在求逆时会出现问题。
            为了解决这个问题，我们下边讲一下：岭回归，这是我们要讲的第一种缩减方法。
        Args：
            xMat：样本的特征数据，即 feature
            yMat：每个样本对应的类别标签，即目标变量，实际值
            lam：引入的一个λ值，使得矩阵非奇异
        Returns：
            经过岭回归公式计算得到的回归系数
    '''

    xTx = xMat.T*xMat
    #岭回归就是在矩阵 xTx 上加一个 λI 从而使得矩阵非奇异，进而能对 xTx + λI 求逆
    denom = xTx + eye(shape(xMat)[1])*lam
    # 检查行列式是否为零，即矩阵是否可逆，行列式为0的话就不可逆，不为0的话就是可逆。
    if linalg.det(denom) == 0.0:
        print ("This matrix is singular, cannot do inverse")
        return
    ws = denom.I * (xMat.T*yMat)
    return ws
def ridgeTest(xArr,yArr):

    xMat = mat(xArr)
    yMat=mat(yArr).T
    yMean = mean(yMat,0)
    yMat = yMat - yMean
    xMeans = mean(xMat,0)
    xVar = var(xMat,0)
    xMat = (xMat - xMeans)/xVar
    # 可以在 30 个不同的 lambda 下调用 ridgeRegres() 函数。
    numTestPts = 30
    # 创建30 * m 的全部数据为0 的矩阵
    wMat = zeros((numTestPts,shape(xMat)[1]))
    for i in range(numTestPts):
        # exp() 返回 e^x
        ws = ridgeRegres(xMat,yMat,exp(i-5))
        wMat[i,:]=ws.T
    return wMat
def crossValidation(xArr,yArr,numVal=10):
    # 获得数据点个数，xArr和yArr具有相同长度
    m = len(yArr)
    indexList = [i for i in range(m)]
    errorMat = zeros((numVal,30))

    # 主循环 交叉验证循环
    for i in range(numVal):
        # 随机拆分数据，将数据分为训练集（70%）和测试集（30%）
        trainX=[]; trainY=[]
        testX = []; testY = []
        random.shuffle(indexList)

        # 切分训练集和测试集
        for j in range(m):
            if j < m*0.7:
                trainX.append(xArr[indexList[j]])
                trainY.append(yArr[indexList[j]])
            else:
                testX.append(xArr[indexList[j]])
                testY.append(yArr[indexList[j]])
        # 获得回归系数矩阵
        wMat = ridgeTest(trainX,trainY)
        wMat=wMat*std(trainY)/np.std(trainX,0)

        # 循环遍历矩阵中的30组回归系数
        for k in range(30):
            # 读取训练集和数据集
            matTestX = np.array(testX)
            for l in range(len(testY)):
                yEst = int(abs(int((matTestX[l] * wMat[k]).sum())))
            # 计算误差
                rmse=(yEst-testY[l])**2
                errorMat[i][k]=errorMat[i][k]+rmse
    errorMat=sqrt(errorMat/len(testY))
    meanerror=mean(errorMat,0)
    meanerror=meanerror.tolist()
    bestweight=meanerror.index(min(meanerror))
    # print(bestweight)
    print('最好的系数是{}'.format(bestweight))

def ridgeRegresplot(xArr,yArr):
    w=ridgeTest(xArr,yArr)
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.plot(w)
    plt.show()
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
            if(data[row][cloumn]>average+1*var):
                data[row][cloumn]=average
    return data
dftr=pd.read_csv('train_data2.csv',usecols=[0,2,18,19,20,24,25,26,27,28,29])
trainingLabels=pd.read_csv('train_data2.csv',usecols=[59])
dftr=np.array(dftr)
trainingLabels=noisy(trainingLabels)
trainingLabels=np.array(trainingLabels)
trainingLabels=trainingLabels.T

#crossValidation(dftr,trainingLabels)
#ridgeRegresplot(dftr,trainingLabels)
w=ridgeTest(dftr,trainingLabels)
w=w*std(trainingLabels)/np.std(dftr,0)

ver=pd.read_csv('verification_data.csv',usecols=[1,3,19,20,21,25,26,27,28,29,30])
vershare=pd.read_csv('verification_data.csv',usecols=[60])
vershare=noisy(vershare)
vershare=np.array(vershare)
ver=np.array(ver)

constant_term=sum(std(trainingLabels)/np.std(dftr,0))
print(constant_term)
mse=0
R_square1=0
R_square2=0
for j in range(len(vershare)):
    mse+=(int(sum(ver[j]*w[18])+constant_term+constant_term)-vershare[j])**2
    R_square1+=(int(sum(ver[j]*w[18])+constant_term+constant_term)-mean(vershare))**2
    R_square2+=(vershare[j]-mean(vershare))**2
mse=mse/len(vershare)
rmse=sqrt(mse)
R_square=R_square1/R_square2
print('MSE={},RMSE={},R平方={}'.format(mse,rmse,R_square))


test=pd.read_csv('test_data.csv',usecols=[1,3,19,20,21,25,26,27,28,29,30])
test=np.array(test)
tests=[]
level=[]
for i in range(len(test)):
    sums=int(sum(test[i]*w[16])+1*constant_term)
    tests.append(sums)
    if(sums<1400):
        level.append(0)
    else:
        level.append(1)

testl_y=pd.DataFrame(tests,columns=['test_y'])
testl_y.to_csv('2.csv')
tese_level=pd.DataFrame(level,columns=['level'])
tese_level.to_csv('3.csv')


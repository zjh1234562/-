import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
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
dftr=pd.read_csv('train_data2.csv',usecols=[0,2,18,19,20,24,25,26,27,28,29,59])
trainingLabels=dftr.pop('shares')
trainingLabels=pd.DataFrame(trainingLabels)

# dftr=np.array(dftr)
# trainingLabels=np.array(trainingLabels)
# print(dftr.describe())
# counts=dftr['shares'].value_counts()
# p=counts.plot(kind='bar').get_figure()
# plt.xlabel([1,2])
# plt.show()
dftr=noisy(trainingLabels)
trainingLabels=np.array(dftr)
print(dftr)
a=0
b=0
for i in range(len(dftr)):
    if(dftr[i]<30000):
        a+=1
    else:
        b+=1
print(a,b)

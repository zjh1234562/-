import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from numpy import trapz

def roc_curve(trur_lables,predicted_probs,m=100):
    thr=predicted_probs
    tpr=np.zeros(m)
    fpr=np.zeros(m)

    pos=trur_lables==1
    neg=np.logical_not(pos)
    n_pos=np.count_nonzero(pos)  #几个1
    n_neg=np.count_nonzero(neg) #几个0
    for i,t in enumerate(thr):
        tpr[i]=np.count_nonzero(np.logical_and(predicted_probs>=t,pos))/n_pos
        fpr[i]=np.count_nonzero(np.logical_and(predicted_probs>=t,neg))/n_neg
    return tpr,fpr
def acu():
    data=pd.read_csv('1.csv')
    pre=data.pop('pre')
    level=data.pop('level')
    level=list(level)
    level=level[0:100]
    pre=list(pre)
    pre=pre[0:100]
    pre.sort()
    a=np.array(level)
    thr=np.array(pre)
    fpr,tpr=roc_curve(a,thr)
    plt.plot(fpr,tpr)
    plt.show()
    area=-trapz(tpr,x=fpr)
    print(area)


acu()
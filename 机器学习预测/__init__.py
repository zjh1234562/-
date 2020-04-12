from sklearn.linear_model import LogisticRegression
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.cross_validation import train_test_split

dftr=pd.read_csv('train_data2.csv',usecols=[0,1,2,3,4,5,6,60])
trainingLabels=dftr.pop('level')
y=np.array(trainingLabels)
x=np.array(dftr)

X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.3, random_state=0)

# 使用LogisticRegression考察线性回归的预测能力
def test_LogisticRegression(X_train, X_test, y_train, y_test):
    # 选择模型
    cls = LogisticRegression()

    # 把数据交给模型训练
    cls.fit(X_train, y_train)

    print("Coefficients:%s, intercept %s"%(cls.coef_,cls.intercept_))
    print("Residual sum of squares: %.2f"% np.mean((cls.predict(X_test) - y_test) ** 2))
    print('Score: %.2f' % cls.score(X_test, y_test))

if __name__=='__main__':
    test_LogisticRegression(X_train,X_test,y_train,y_test) # 调用 test_LinearRegression

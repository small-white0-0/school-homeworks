import numpy as np
import matplotlib.pyplot as plt
import matplotlib
# %matplotlib inline

#s# 实现自己的离散朴素贝叶斯分类器
class B:
    def __init__(self) -> None:
        pass
    
    def fit(self,samples, targets):
        # 计算类概率
        self.labels, freqs = np.unique(targets,return_counts=True)    #标签
        self.y=np.zeros(shape=self.labels.max()+1)     # 类概率变量
        sum = len(targets)

        for (label,freq) in zip(self.labels,freqs):
            self.y[label]=freq/sum

        # 分类样本的数据，方便之后进行预测
        self.x=[]
        i = 0
        # 容纳不同类型的向量的数据的空间
        while True:
            self.x.append([])
            i +=1
            if i > self.labels.max():
                break

        for (label,xx) in zip(targets,samples):
            self.x[label].append(xx)

    # 对单个样本的判断
    def onePredict(self,arr):

        re = self.y.copy()
        i=0

        for x in arr:
            # 计算第i个特征值的在各分类中的概率
            for label in self.labels:
                X = np.array(self.x[label])
                Xi = X[:,i]
                re[label] *= (Xi[Xi == x ].size + 1) / (len(X)+len(X[0]))       # 拉普拉斯平滑
            i += 1

        # 找出概率最大的那一个
        max =self.labels[0]
        i=0
        for label in self.labels:
            # 跳过第一个
            if i > 0:
                if re [max] < re[label]:
                    max = label
                
            i = 1
        
        return max

    def predict(self,arrs):

        re = np.zeros(len(arrs))
        i = 0

        for arr in arrs:
            re[i]=self.onePredict(arr)
            i += 1

        return re


# 生成所有测试样本点
def make_meshgrid(x, y, h=1):

    x_min, x_max = x.min(), x.max() 
    y_min, y_max = y.min() , y.max()
    xx, yy = np.meshgrid(np.arange(x_min, x_max, h),
                         np.arange(y_min, y_max, h))
    
    return xx, yy

# 生成训练样本
def make_samples():

    rng = np.random.RandomState(1)
    X = rng.randint(20,size=(1000,2))

    y=[]
    for i in X:
        if i[0] >= i[1]:
            y.append(0)
        elif i[0] == i[1]:
            y.append(1)
        else:
            y.append(2)

    y = np.array(y)
    return X,y

# 对测试样本进行预测，并显示
def plot_test_results(ax, clf, xx, yy, **params):
    Z = clf.predict(np.c_[xx.ravel(), yy.ravel()])  # 接受一个参数array（[1,2],...[1,2]n) 返回array([1,2,...,n])
    Z = Z.reshape(xx.shape)                         # 把Z的array变为方阵
    ax.contourf(xx, yy, Z, **params)

## 主函数
def main():
    # 创建训练样本
    X,y = make_samples()
    # 创建并训练正态朴素贝叶斯分类器
    clf = B()
    clf.fit(X,y)

    title = ('GaussianBayesClassifier')

    fig, ax = plt.subplots(figsize = (5, 5))
    plt.subplots_adjust(wspace=0.4, hspace=0.4)

    X0, X1 = X[:, 0], X[:, 1]
    # 生成所有测试样本点
    xx, yy = make_meshgrid(X0, X1)

    # 显示测试样本的分类结果
    plot_test_results(ax, clf, xx, yy, cmap=plt.cm.coolwarm, alpha=0.8)
    # 显示训练样本
    ax.scatter(X0, X1, c=y, cmap=plt.cm.coolwarm, s=20, edgecolors='k')
    ax.set_xlim(xx.min(), xx.max())
    ax.set_ylim(yy.min(), yy.max())
    ax.set_xlabel('x1')
    ax.set_ylabel('x2')
    ax.set_xticks(())
    ax.set_yticks(())
    ax.set_title(title)
    plt.show()

main()

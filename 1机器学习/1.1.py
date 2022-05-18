import numpy as np

class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
        self.split = None

class Split:
    def __init__(self, best_split):
        self.best_split = best_split
    
    def split(self, s):
        if s[self.best_split[0]] == self.best_split[1]:
            return "left"
        else:
            return "right"

class DecisionTree:
    def __init__(self) -> None:
        pass
    
    def __one2two(self,D):
        # 将一维变二维，方便之后
        if D.size > 0 and D.size == len(D):
            temp = []
            temp.append(D)
            D = np.array(temp)
        return D

    def __get_targets(self, D):
        # 得到样本D 中最后一列的标签值
        # 调用该函数的应保证D不为空

        if D.size == len(D):
            temp = []
            temp.append(D[len(D) - 1])
            return np.array(temp)
        else:
            targets_index = len(D[0]) - 1
            targets = D[:,targets_index]
            return targets

    def __get_targets_freqs(self, D):
        # 得到样本D 中最后一列的标签值的不同类型的次数
        targets = self.__get_targets(D)
        types, freqs = np.unique(targets, return_counts=True)

        return types,freqs
    def __calculate_value(self, D):
        # 样本D 为空， 返回None
        if D.size == 0:
            return None

        types,freqs = self.__get_targets_freqs(D)
        max = freqs.max()
        leafNode = None
        for (i,j)in zip(freqs,types):
            if i == max:
                leafNode = Node(j)
                break
        
        return leafNode

    def __is_divisible(self, D, depth):
        # 没有样本的，不能再分了。
        if D.size == 0:
            return False

        targets = self.__get_targets(D)
        t,freqs = self.__get_targets_freqs(D)
        ED = 1 - (np.sum(freqs**2)/(len(targets)**2))
        if depth >= 20 or ED < 0.01:
            return False
        else:
            return True

    def __get_G(self, DL, DR):
        # 由于DL, DR可能有一个为空，故需要判断
        G = 0
        if DL.size > 0:
            NL = len(DL)
            types, freqsL = self.__get_targets_freqs(DL)
            G += np.sum(freqsL**2)/NL
        if DR.size > 0:
            NR = len(DR)
            types, freqsR = self.__get_targets_freqs(DR)
            
            G += np.sum(freqsR**2)/NR
        return G
        
    def __find_best_split(self, D):

        best_DL = None
        best_DR = None
        best_split = [0, 0]   # 最佳分类依据
        # 标签值所在的那一列
        target_index = len(D[0])-1

        # 遍历求 G 最大的 特征值和
        max_G = None
        for col in range(target_index):
            column = D[:, col]
            values = np.unique(column)
            # 第 col 特征值 中的类型作为分类依据
            for value in values:
                part_DL = np.array([])
                part_DR = np.array([])
                LS,RS = False,False
                #根据是否 type 类型 ，进行分类
                for i in range(len(column)):
                    if column[i] == value:
                        if not LS:
                            LS=True
                            part_DL = D[i].copy()
                        else:
                            part_DL = np.row_stack((part_DL, D[i]))
                    else:
                        if not RS:
                            RS = True
                            part_DR = D[i].copy()
                        else:
                            part_DR = np.row_stack((part_DR, D[i]))

                # 计算G
                G = self.__get_G(part_DL, part_DR)
                
                # 由于最后只需要找所有特征值中G最大的，直接只记录总的最大的就可以了。
                if max_G == None or max_G < G:
                    max_G = G
                    best_DL = part_DL
                    best_DR = part_DR
                    best_split[0] = col
                    best_split[1] = value

        return Split(best_split), best_DL, best_DR
    
    # D的最后一列应是每个样本的类型
    def train(self, D):
        if D.size > 0:
            self.DTroot = self.__train_R(D, 0)
        else:
            print("训练样本为0,异常退出")
            exit(1)

    def __train_R(self, D, depth):
        if not self.__is_divisible(D, depth):
            leafNode = self.__calculate_value(D)
            return leafNode

        else:
            # 进入该分支的样本不会为空
            (split, D1, D2) = self.__find_best_split(D)
            node = Node(0)
            node.split = split

            node.left = self.__train_R(D1, depth + 1)
            node.right = self.__train_R(D2, depth + 1)

            return node
    def __predictOne(self, s):
        cur = self.DTroot
        while True:
            if cur.split == None:
                break
            else:
                flag = cur.split.split(s)
                flag = flag.strip()
                if flag == "left":
                    cur = cur.left
                else:
                    cur = cur.right
        
        return cur.value

    def predict(self, D):
        re = []
        for sample in D:
            re.append(self.__predictOne(sample))
        
        re = np.array(re)
        return re
    

def make_samples(row = 100):
    rng = np.random.RandomState(1)
    X = rng.randint(2, size=(row, 4))

    y = []
    for x in X:
        value = np.sum(x)
        y.append(value)

    re = np.column_stack((X, y))
    return re


def main():
    train_samples = make_samples(800)
    test_samples = make_samples(40)

    DT = DecisionTree()
    DT.train(train_samples)
    predicts = DT.predict(test_samples)

    correct = 0
    test_targets = test_samples[:, len(test_samples[0])-1]

    for (i,j) in zip(predicts, test_targets):
        if i == j:
            correct += 1
    print("测试样本（最后一列为类型):")
    print(test_samples)
    print("预测结果：")
    print(predicts)
    
    print("正确率为：")
    print(correct/len(predicts))
main()
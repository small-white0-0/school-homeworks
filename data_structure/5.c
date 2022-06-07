#include <stdio.h>
#include <stdlib.h>

// 二分查找的函数
// 成功，返回目标的下标，失败返回 -1
int search(int target, int data[], int length)
{
    int target_index = -1;
    int low = 0;
    int high = length - 1;
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (data[mid] < target)
        {
            low = mid + 1;
        }
        else if (data[mid] > target)
        {
            high = mid - 1;
        }
        else
        {
            target_index = mid;
            break;
        }
    }
    return target_index;
}

/*-----------------------------------二叉排序树-----------------------------------*/
typedef struct node
{
    int data;
    struct node *lchild, *rchild;
} node, *nodeLink;

//创建一个二叉排序树的节点
nodeLink createNode(int data)
{
    nodeLink re = (nodeLink)malloc(sizeof(node));
    if (re)
    {
        re->data = data;
        re->lchild = NULL;
        re->rchild = NULL;
    }
    else
    {
        printf("空间申请失败");
        free(re);
        re = NULL;
    }
    return re;
}

//二叉排序树数插入
nodeLink insertBStree(nodeLink root, int data)
{
    if (root == NULL)
    {
        return createNode(data);
    }

    nodeLink q = NULL;
    nodeLink p = root;
    while (p != NULL && p->data != data)
    {
        q = p;
        if (data < p->data)
        {
            p = p->lchild;
        }
        else
        {
            p = p->rchild;
        }
    }
    if (p == NULL)
    {
        p = createNode(data);
        if (p->data < q->data)
        {
            q->lchild = p;
        }
        else
        {
            q->rchild = p;
        }
    }
    return root;
}

//二叉排序树的生成
nodeLink createBStree(int data[], int length)
{
    if (length == 0)
    {
        return NULL;
    }

    nodeLink root = createNode(data[0]);
    for (int i = 1; i < length; i++)
    {
        root = insertBStree(root, data[i]);
    }
    return root;
}

//二叉排序树查找
nodeLink BStreeSearch(nodeLink root, int target)
{
    //递归结束条件
    if (root == NULL)
    {
        return NULL;
    }

    nodeLink target_point = NULL;
    if (target < root->data)
    {
        target_point = BStreeSearch(root->lchild, target);
    }
    else if (target > root->data)
    {
        target_point = BStreeSearch(root->rchild, target);
    }
    else
    {
        target_point = root;
    }

    return target_point;
}

nodeLink deleteBStree(nodeLink root, int data)
{
    if (root == NULL)
    {
        return NULL;
    }
    nodeLink deleteNode = BStreeSearch(root, data);
    if (deleteNode != NULL)
    {
        //查找被删除节点的双亲节点中的指针变量
        nodeLink p = root;
        nodeLink *pLink = NULL;
        while (1)
        {
            if (p->lchild == deleteNode)
            {
                pLink = &(p->lchild);
                break;
            }
            else if (p->rchild == deleteNode)
            {
                pLink = &(p->rchild);
                break;
            }

            if (deleteNode->data < p->data)
            {
                p = p->lchild;
            }
            else
            {
                p = p->rchild;
            }
        }

        //根据被删除节点的子树情况进行删除
        if (deleteNode->lchild == NULL && deleteNode->rchild == NULL)
        {
            if (pLink != NULL)
            {
                *pLink = NULL;
            }
            else if (deleteNode == root) //被删节点为根节点
            {
                root = NULL;
            }

            free(deleteNode);
        }
        else if (deleteNode->lchild == NULL)
        {
            if (pLink != NULL)
            {
                *pLink = deleteNode->rchild;
            }
            else if (deleteNode == root) //被删节点为根节点
            {
                root = deleteNode->rchild;
            }
            free(deleteNode);
        }
        else if (deleteNode->rchild == NULL)
        {
            if (pLink != NULL)
            {
                *pLink = deleteNode->lchild;
            }
            else if (deleteNode == root) //被删节点为根节点
            {
                root = deleteNode->lchild;
            }
            free(deleteNode);
        }
        else
        {
            //找到左子树的最右端的节点
            nodeLink r = deleteNode->lchild;
            nodeLink rp = NULL;
            while (r->rchild == NULL)
            {
                rp = r;
                r = r->rchild;
            }
            //进行替换
            rp->rchild = r->lchild;
            // r 获取deleteNode的孩子关系
            r->lchild = deleteNode->lchild;
            r->rchild = deleteNode->rchild;
            // r 获取 deleteNode 的双亲关系
            if (pLink != NULL)
            {
                *pLink = r;
            }
            else if (deleteNode == root) //被删节点为根节点
            {
                root = r;
            }
            free(deleteNode);
        }
    }
    return root;
}
void displaySet(int set[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", set[i]);
    }
}

void displayBStreeByPreOrder(nodeLink root)
{
    if (root == NULL)
    {
        printf("$,");
        return;
    }
    printf("%d,", root->data);
    displayBStreeByPreOrder(root->lchild);
    displayBStreeByPreOrder(root->rchild);
}

int main(void)
{
    int test[] = {23, 12, 45, 89, 1, 90, 28, 34, 78, 28, 44};
    int test_length = sizeof(test) / sizeof(int);
    int order_test[] = {2, 7, 34, 51, 52, 67, 69, 78, 82, 85, 91, 95, 99};
    int order_test_length = sizeof(order_test) / sizeof(int);
    int select;
    int target;
    printf("--------------------------------------二分查找----------------------------------\n");

    while (1)
    {
        displaySet(order_test, order_test_length);
        printf("\n");
        printf("1. 查找\n2. 退出\n");
        printf("选择：");
        scanf("%d", &select);
        if (select == 1)
        {
            printf("请输入查找的数：");
            scanf("%d", &target);
            int index = search(target, order_test, order_test_length);
            if (index != -1)
            {
                printf("%d的下标是%d\n", target, index);
            }
            else
            {
                printf("没有找到%d\n", target);
            }
        }
        else if (select == 2)
        {
            break;
        }
        else
        {
            printf("请正确输入选项!!!\n");
        }
    }

    printf("--------------------------------------二叉树排序数----------------------------------\n");
    printf("用于创建二叉排序树的数组：");
    displaySet(test, test_length);
    printf("\n");

    printf("==开始创建==\n");
    nodeLink root = createBStree(test, test_length);
    printf("创建的二叉排序树：\n");
    displayBStreeByPreOrder(root);
    printf("\n");

    printf("==插入测试==\n");
    printf("请输入要插入的整数（如果是重复的数，二叉排序树将不会有任何改变）:\n");
    scanf("%d", &target);
    printf("插入后二叉排序树：\n");
    root = insertBStree(root, target);
    displayBStreeByPreOrder(root);
    printf("\n");

    printf("==查找测试==\n");
    printf("请输入要查找的整数:\n");
    scanf("%d", &target);
    nodeLink foundNode = BStreeSearch(root, target);
    if (foundNode)
    {
        printf("找到了%d", foundNode->data);
    }
    else
    {
        printf("没有找到%d", target);
    }
    printf("\n");

    printf("==删除测试==\n");
    displayBStreeByPreOrder(root);
    printf("请输入要删除的整数（如果是不存在的数，二叉排序树将不会有任何改变）:\n");
    scanf("%d", &target);
    printf("删除节点后的二叉排序树：\n");
    root = deleteBStree(root, target);
    displayBStreeByPreOrder(root);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stackNode
{
    char data;
    struct stackNode *next;
} stackNode;
typedef stackNode *stack;

stackNode *createStackNode(char e)
{
    stackNode *p = (stackNode *)malloc(sizeof(stackNode));
    if (p)
    {
        p->data = e;
        p->next = NULL;
    }
    return p;
}

// 初始化栈，返回栈指针的地址
stack *initStack(stack *const stackp)
{
    if (stackp != NULL)
    {
        *stackp = NULL;
    }
    return stackp;
}

//释放栈空间
// 这里释放栈空间，成功释放 会修改传入的栈指针，将其置为NULL。
int destroyStack(stack *stackp)
{
    if (stackp == NULL) //判断传入指针是否合法
    {
        return 0;
    }

    // 释放栈链表空间
    stack top = *stackp;
    stack p = NULL;
    while (top != NULL)
    {
        p = top;
        top = top->next;
        free(p);
    }
    //置栈指针为NULL
    *stackp = NULL;
    return 1;
}

//成功返回1,失败返回0
int getTop(stack top, char *e)
{
    if (e == NULL       // e传入参数e不合法
        || top == NULL) //栈为空
    {
        return 0;
    }
    //
    *e = top->data;
    return 1;
}

//入栈
//成功返回1,失败返回0
int push(stack *const stackp, char e)
{
    if (stackp == NULL)
    {
        return 0;
    }
    stack p = createStackNode(e);
    if (p)
    {
        p->data = e;
        p->next = *stackp;
        *stackp = p;
        return 1;
    }
    else
    {
        return 0;
    }
}

//出栈
//成功返回1,失败返回0
int pop(stack *const stackp, char *e)
{
    if (stackp == NULL      // 指针非法
        || e == NULL        //指针非法
        || *stackp == NULL) //栈为空
    {
        return 0;
    }

    *e = (*stackp)->data;
    stackNode *p = *stackp;
    *stackp = (*stackp)->next;
    free(p);
    return 1;
}

typedef struct queueNode
{
    char data;
    struct queueNode *next;
} queueNode;

typedef struct
{
    queueNode *front;
    queueNode *rear;
} linkQueue;

queueNode *createQueueNode(char data)
{
    queueNode *p = (queueNode *)malloc(sizeof(queueNode));
    if (p)
    {
        p->data = data;
        p->next = NULL;
    }
    return p;
}

//创建队列，返回传入参数
//创建失败（申请空间失败），队列的front指针和rear指针为NULL
linkQueue *initQueue(linkQueue *queue)
{
    if (queue != NULL)
    {
        queue->front = createQueueNode(0);
        queue->rear = queue->front;
    }
    return queue;
}

//释放队列空间
// 这里释放空间，成功释放会修改传入的栈指针，将其置为NULL。
int destoryQueue(linkQueue *queue)
{
    if (queue == NULL)
    {
        return 0;
    }

    queueNode *p = queue->front;
    queueNode *q;
    while (p)
    {
        q = p;
        p = p->next;
        free(q);
    }

    queue->front = NULL;
    queue->rear = NULL;
    return 1;
}

//入队
//成功返回1,失败返回0
int enQueue(linkQueue *const queue, char e)
{
    if (queue == NULL || queue->front == NULL)
    {
        return 0;
    }

    queueNode *p = createQueueNode(e);
    if (p) //空间申请成功
    {
        queue->rear->next = p;
        queue->rear = p;
        return 1;
    }
    else
    {
        return 0;
    }
}

//出队
//成功返回1,失败返回0
int deQueue(linkQueue *const queue, char *e)
{
    if (queue == NULL || e == NULL)
    {
        return 0;
    }

    if (queue->front != NULL)
    {
        *e = queue->front->data;
        queueNode *p = queue->front;
        queue->front = queue->front->next;
        free(p);
        return 1;
    }
    else
    {
        return 0;
    }
}

/* 下下面是方便测试的一些显示函数 */

void displayStack(stack stack)
{
    printf("Top: ");
    while (stack)
    {
        printf(" %c|", stack->data);
        stack = stack->next;
    }
    printf("\n");
}

void displayQueue(linkQueue *queue)
{
    printf("front: ");
    queueNode *p = queue->front;
    while (p)
    {
        printf(" %c ", p->data);
        p = p->next;
    }
    printf(":rear\n");
}

/* 附加题增加的一些函数 */

void deleteE(char *A, char *B)
{
    int i = 0, j = 0;
    char c;
    stack myStack;
    initStack(&myStack);
    while (A[i] != '\0')
    {
        push(&myStack, A[i]);
        i++;
        getTop(myStack, &c);
        if (c != 'e')
        {
            pop(&myStack, &B[j]);
            j++;
        }
    }
    destroyStack(&myStack);
}

int isHuiWen(char *A)
{
    int length = strlen(A);
    int re = 1; //储存返回值
    char c;
    stack myStack;
    initStack(&myStack);

    //入栈A前半截
    int i = 0;
    for (i = 0; i < length / 2; i++)
    {
        push(&myStack, A[i]);
    }

    length % 2 ? i++ : i; //如果是奇数，让 i+1，跳过最中间那个。

    //出栈，并并比较后半截
    for (; i < length; i++)
    {
        pop(&myStack, &c);
        if (c != A[i])
        {
            re = 0;
            break;
        }
    }

    destroyStack(&myStack);
    return re;
}

int main(void)
{

    int select;
    char c;
    printf("栈测试开始\n");
    printf("栈初始化ing\n");
    stack myStack;
    initStack(&myStack);
    printf("栈初始化完成\n");
    do
    {
        displayStack(myStack);
        printf("1. push\n2. pop\n0. exit\n");
        printf("请输入选项(0~2)：");
        scanf("%d", &select);
        getchar();
        switch (select)
        {
        case 1:
            printf("请输入要压栈的字符：");
            scanf("%c", &c);
            getchar();
            if (push(&myStack, c))
            {
                printf("压栈成功\n");
            }
            else
            {
                printf("压栈失败\n");
            }
            break;

        case 2:
            if (pop(&myStack, &c))
            {
                printf("出栈成功\n");
                printf("出栈：%c\n", c);
            }
            else
            {
                printf("出栈失败\n");
            }
            break;
        }
        
    } while (select);
    destroyStack(&myStack);
    printf("栈测试退出");
    getchar();

    printf("队列测试开始\n");
    printf("队列初始化ing\n");
    linkQueue myQueue;
    initQueue(&myQueue);
    printf("队列初始化完成\n");
    do
    {
        displayQueue(&myQueue);
        printf("1. enQueue\n2. deQueue\n0. exit\n");
        printf("请输入选项(0~2)：");
        scanf("%d", &select);
        getchar();
        switch (select)
        {
        case 1:
            printf("请输入要入队的字符：");
            scanf("%c", &c);
            getchar();
            if (enQueue(&myQueue, c))
            {
                printf("入队成功\n");
            }
            else
            {
                printf("入队失败\n");
            }
            break;

        case 2:
            if (deQueue(&myQueue, &c))
            {
                printf("出队成功\n");
                printf("出队：%c\n", c);
            }
            else
            {
                printf("出队失败\n");
            }
            break;
        }
    } while (select);
    destoryQueue(&myQueue);
    printf("队列测试退出\n");
    getchar();

    printf("===删除字符串中的字母 e (区分大小写)===\n");
    char A[50] = {0};
    char B[50] = {0};
    printf("请输入字符串(长度不要超过49）：");
    scanf("%s", A);
    getchar();
    printf("修改后字符串：\n");
    deleteE(A, B);
    printf("%s\n", B);

    printf("===判断是否是回文字符串===\n");
    printf("请输入字符串(长度不要超过49）：");
    scanf("%s", A);
    getchar();
    printf("%s", A);
    if (isHuiWen(A))
    {
        printf("是回文\n");
    }
    else
    {
        printf("不是回文\n");
    }

    return 0;
}
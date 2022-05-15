#include <stdio.h>
#include <stdlib.h>

#define INFINIT INT_MAX
#define MAX_NUM 20

// 简单图的邻接矩阵
typedef struct
{
    int arc[MAX_NUM][MAX_NUM]; // 邻接矩阵
    char V[MAX_NUM];           //顶点数组
    int vNum;                  //顶点数目
} matrixGraph;

//传入二维数组的邻接矩阵,和顶点
matrixGraph *createMatrixGraph(char V[], int vNum, int *a)
{
    if (vNum < 0 || a == NULL || V == NULL || vNum > MAX_NUM)
    {
        return NULL;
    }

    matrixGraph *graph = (matrixGraph *)malloc(sizeof(matrixGraph));
    graph->vNum = vNum;
    for (int i = 0; i < vNum; i++)
    {
        graph->V[i] = V[i];
        for (int j = 0; j < vNum; j++)
        {
            graph->arc[i][j] = *(a + i * vNum + j);
        }
    }
    return graph;
}

void destoryMatrixGraph(matrixGraph *graph)
{
    free(graph);
}

//该函数不建议直接调用，最好由depthFirstTravel函数调用，
// depthFirtsTravel 会做各种合法性的检查，而 dephtFirstTravelRecursively不会做任何合法性的检查
void depthFirstTraversalRecursively(matrixGraph *graph, int (*flags_)[], int start)
{
    int *flags = *flags_;
    if (flags[start])
    {
        return;
    }

    //输出并标记该元素已经遍历
    printf("%c ", graph->V[start]);
    flags[start] = 1;

    //从start开始的深度遍历
    for (int i = 0; i < graph->vNum; i++)
    {
        if (graph->arc[start][i])
        {
            depthFirstTraversalRecursively(graph, flags_, i);
        }
    }
}

// 开始深度遍历
void depthFirstTraversal(matrixGraph *graph)
{
    if (graph == NULL || graph->vNum == 0)
    {
        return;
    }

    int flags[graph->vNum];
    for (int i = 0; i < graph->vNum; i++)
    {
        flags[i] = 0;
    }

    //针对非连通图，需要循环。连通图则只用执行一次。
    for (int i = 0; i < graph->vNum; i++)
    {
        if (!flags[i])
        {
            depthFirstTraversalRecursively(graph, &flags, i);
        }
    }
    printf("\n");
}

/* ---------邻接表-------------*/

// 为了广度遍历，使用之前创建的队列代码
//由于只能单文件，为了更好浏览当前要求的实现部分，所以函数实现，放在了main后面。
typedef struct queueNode
{
    int data;
    struct queueNode *next;
} queueNode;

typedef struct
{
    queueNode *front;
    queueNode *rear;
} linkQueue;

queueNode *createQueueNode(int data);
linkQueue *initQueue(linkQueue *queue);
int destoryQueue(linkQueue *queue);
int enQueue(linkQueue *const queue, int e);
int deQueue(linkQueue *const queue, int *e);
int queueEmpty(linkQueue *const queue);

//邻接表的代码
typedef struct AdNode
{
    int v_index;
    struct AdNode *next;
} AdNode;

typedef struct
{
    char v_data;
    AdNode *list;
} vNode;

typedef struct
{
    vNode V[MAX_NUM];
    int vNum;
} AdjacencyList;

AdNode *createAdNode(int v_index)
{
    AdNode *adNode = (AdNode *)malloc(sizeof(AdNode));
    if (adNode)
    {
        adNode->v_index = v_index;
        adNode->next = NULL;
    }
    return adNode;
}

//不会检查数据是否合法，不建议直接调用
//发生错误时，节点设置为 ‘\0', 邻接表为NULL
vNode createVnode(char v_data, int row[], int vNum)
{
    vNode v;
    v.v_data = v_data;
    v.list = NULL;

    AdNode **p = &(v.list);
    //设置可达节点的链表
    for (int i = 0; i < vNum; i++)
    {
        if (row[i])
        {
            *p = createAdNode(i);

            //空间申请失败，节点设置为 ‘\0',邻接表为NULL
            if (*p == NULL)
            {
                v.v_data = '\0';
                v.list = NULL;
                break;
            }

            p = &((*p)->next);
        }
    }
    return v;
}

AdjacencyList *createAdjacencyList(char V[], int vNum, int *rank)
{
    if (vNum < 0 || rank == NULL || V == NULL || vNum > MAX_NUM)
    {
        return NULL;
    }

    AdjacencyList *graph = (AdjacencyList *)malloc(sizeof(AdjacencyList));
    graph->vNum = vNum;

    //创建邻接表头数组
    for (int i = 0; i < vNum; i++)
    {
        graph->V[i] = createVnode(V[i], rank + i * vNum, vNum);
    }

    return graph;
}

void breadthFirstTraversal(AdjacencyList *graph)
{
    if (graph == NULL)
    {
        return;
    }
    //创建队列
    linkQueue q_;
    linkQueue *Q = &q_;
    initQueue(Q);

    int flags[graph->vNum];
    for (int i = 0; i < graph->vNum; i++)
    {
        flags[i] = 0;
    }

    //开始广度遍历
    for (int i = 0; i < graph->vNum; i++)
    {
        if (!flags[i])
        {
            //输出未访问的节点，并置flags为 1
            printf("%c ", graph->V[i].v_data);
            flags[i] = 1;
            enQueue(Q, i);

            //用队进行遍历，如果图是连通图，则执行完该while循环即可遍历完成。
            while (!queueEmpty(Q))
            {
                int j;
                deQueue(Q, &j);
                AdNode *p = graph->V[j].list;
                while (p)
                {
                    int k = p->v_index;
                    if (!flags[k])
                    {
                        printf("%c ", graph->V[k].v_data);
                        flags[k] = 1;
                        enQueue(Q, k);
                    }
                    p = p->next;
                }
            }
        }
    }
    printf("\n");
}

//主函数
int main(void)
{
    // 预设数据
    int template[][5] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 1, 0, 0}};
    char V[] = {'a', 'b', 'c', 'd', 'e'};

    matrixGraph *graph1 = createMatrixGraph(V, sizeof(V), (int *)template);
    printf("邻接矩阵的的深度遍历序列：");
    depthFirstTraversal(graph1);

    printf("邻接表的的广度遍历序列：");
    AdjacencyList *graph2 = createAdjacencyList(V, sizeof(V), (int *)template);
    breadthFirstTraversal(graph2);

    return 0;
}

queueNode *createQueueNode(int data)
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
int enQueue(linkQueue *const queue, int e)
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
int deQueue(linkQueue *const queue, int *e)
{
    if (queue == NULL || e == NULL)
    {
        return 0;
    }

    if (queue->front != queue->rear)
    {
        queueNode *p = queue->front->next;
        *e = p->data;
        
        queue->front->next = p->next;
        if (queue->rear == p)
        {
            queue->rear = queue->front;
        }

        free(p);
        return 1;
    }
    else
    {
        return 0;
    }
}

int queueEmpty(linkQueue *const queue)
{
    int re = 0;
    if (queue != NULL)
    {
        queue->front == queue->rear ? (re = 1) : (re = 0);
    }
    return re;
}
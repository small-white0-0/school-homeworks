/* === UTF-8 === */
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
//顺序表
typedef struct
{
	int data[MAX];
	int length;
} L1;
//顺序表创建
L1 S_create(void)
{
	L1 L;
	L.length = 0;
	return L;
}
//顺序表插入
// x是待插入数据，i是逻辑顺序
// i最大可以取length+1,即把x放于最后
int S_insert(L1 *L, int x, int i)
{

	//判断顺序表是否创建以及序号是否合法
	if (L->length < 0 || L->length >= MAX || i > L->length + 1 || i < 1)
	{
		return 0;
	}
	for (int j = L->length; j >= i; j--)
	{
		L->data[j] = L->data[j - 1];
	}
	L->data[i - 1] = x;
	L->length++;
	return 1;
}
//顺序表删除
// i表示逻辑下标
int S_delete(L1 *L, int i)
{
	if (i <= 0 || i > L->length)
		return 0;

	for (int j = i - 1; j < L->length - 1; j++)
	{
		L->data[j] = L->data[j + 1];
	}
	L->length--;
	return 1;
}
//顺序表查找
int S_find(L1 L, int x)
{
	for (int i = 0; i < L.length; i++)
	{
		if (L.data[i] == x)
			return i + 1;
	}
	return 0;
}
//顺序表输出
void S_display(L1 L)
{
	for (int i = 0; i < L.length; i++)
	{
		printf("%d ", L.data[i]);
	}
	printf("\n");
}

//单链表结构体
typedef struct node
{
	int coef;
	int index;
	struct node *next;
} node, *link;

//创建
int initList(link *header)
{
	if (header != NULL)
	{
		*header = (link)malloc(sizeof(node));
		if (*header == NULL) //判断是否空间申请成功
			return 0;
		(*header)->next = NULL;
	}
	return 1;
}

int initList_without_header_node(link *header)
{
	if (header != NULL)
	{
		*header = NULL;
	}
	return 1;
}
//插入
int insert(link header, link x, int i)
{
	if (header == NULL || x == NULL || i < 1)
		return 0;
	link p = header;
	int j = 0;
	//找到逻辑序号i前面的节点
	while (p != NULL && j < i - 1)
	{
		p = p->next;
		j++;
	}
	if (p != NULL)
	{
		x->next = p->next;
		p->next = x;
		return 1;
	}
	else
		return 0;
}

int insert_without_header_node(link *headerp, link x, int i)
{
	if (headerp == NULL || x == NULL || i < 1)
		return 0;
	if (i == 1)
	{
		x->next = *headerp;
		*headerp = x;
	}
	else
	{

		/* 代码复用 */
		// insert(*headerp, x, i-1);

		/* 代码不复用 */
		link p = *headerp;
		int j = 1;
		while (p != NULL && j < i - 1)
		{
			p = p->next;
			j++;
		}
		if (p != NULL)
		{
			x->next = p->next;
			p->next = x;
		}
		else
			return 0;
	}
	return 1;
}

//删除
int delete (link header, int i)
{
	//判断输入参数是否合法
	if (header == NULL || i < 1)
		return 0;
	//查找x前一个节点
	link p = header;
	int j = 0;
	while (p != NULL && j < i - 1)
	{
		p = p->next;
		j++;
	}
	//如果找到第i-1个节点且其具有后继节点，进行删除。
	if (p != NULL && p->next != NULL)
	{
		link q = p->next;
		p->next = q->next;
		free(q);
		return 1;
	}
	else
		return 0;
}

int delete_without_header_node(link *headerp, int i)
{
	//判断输入参数是否合法
	if (headerp == NULL || i < 1)
		return 0;
	link p = *headerp;
	int j = 1;
	//判断删除节点是否是头节点
	if (i == 1) //头节点删除
	{
		*headerp = (*headerp)->next;
		free(p);
	}
	else //非头节点删除
	{
		/* 代码复用 */
		// delete(p, i-1);

		/*代码不复用 */
		//查找删除节点的前一个节点
		while (p != NULL && j < i - 1)
		{
			p = p->next;
			j++;
		}
		//找到第i-1个节点，且其具有后继节点，删除后继节点
		if (p != NULL && p->next != NULL)
		{
			link q = p->next;
			p->next = q->next;
			free(q);
		}
		else
			return 0;
	}
	return 1;
}

//查找
//根据指数查找并返回第一个符合的节点指针、
//没有找到，返回NULL
link locate(link header, int index)
{
	if (header == NULL)
		return 0;
	link p = header->next;
	while (p != NULL)
	{
		if (p->index == index)
			break;
		p = p->next;
	}
	return p;
}

link locate_without_header_node(link header, int index)
{
	if (header == NULL) //既可以说是输入参数不合法吗，也可以说是链表为空
		return 0;
	link p = header; //从头指针开始，其余和带头节点一样
	while (p != NULL)
	{
		if (p->index == index)
			break;
		p = p->next;
	}
	return p;
}
//输出
void display(link header)
{
	if (header == NULL)
	{
		return;
	}
	link p = header->next;
	//输出第一个，系数不带符号
	if (p != NULL)
	{
		if (p->coef == 1)
			printf("x^%d", p->index);
		else
			printf("%dx^%d", p->coef, p->index);
		p = p->next;
	}
	//输出后续项，带符号
	while (p != NULL)
	{
		if (p->coef == 1)
			printf("+x^%d", p->index);
		else
			printf("%+dx^%d", p->coef, p->index);
		p = p->next;
	}
	printf("\n");
}

void display_without_header_node(link header)
{
	if (header == NULL)
	{
		return;
	}
	link p = header; //从头节点开始，其余一样
	//输出第一个，系数不带符号
	if (p != NULL)
	{
		if (p->coef == 1)
			printf("x^%d", p->index);
		else
			printf("%dx^%d", p->coef, p->index);
		p = p->next;
	}
	//输出后续项，带符号
	while (p != NULL)
	{
		if (p->coef == 1)
			printf("+x^%d", p->index);
		else
			printf("%+dx^%d", p->coef, p->index);
		p = p->next;
	}
	printf("\n");
}
/*  下面是为了做多项式加减添加的函数,使用了上面的带头节点单链表数据类型 */

//创建单链表的一个节点
//返回创建节点的指针，错误返回NULL
link createNode(int coef, int index)
{
	link p = (link)malloc(sizeof(node));
	if (p == NULL)
		return NULL;
	p->coef = coef;
	p->index = index;
	p->next = NULL;
	return p;
}

//释放单链表空间
void freeList(link header)
{
	if (header == NULL)
		return;
	link q = header;
	link p = NULL;
	while (q != NULL)
	{
		p = q->next;
		free(q);
		q = p;
	}
}

//处理按照从大到小排序的，无重复项的多项式相加
// 返回处理好的多项式指针，错误将返回NULL
//不会修改输入多项式
link simpleAdd(const link header1, const link header2)
{
	if (header1 == NULL && header2 == NULL)
		return NULL;
	//指向第一个节点
	link q = header1->next;
	link p = header2->next;
	//储存处理后的多项式
	link re;
	initList(&re);
	if (re == NULL)
		return NULL;

	link tail = re;
	while (q != NULL || p != NULL) //两个多项式还未处理完
	{
		if (q != NULL && p != NULL) //两个多项式，都还有未处理的项
		{
			if (q->index == p->index) //指数相等
			{
				if (q->coef + p->coef) //系数和不为0,才合并，否则略过
				{
					tail->next = createNode(q->coef + p->coef, q->index);
					tail = tail->next;
				}
				q = q->next;
				p = p->next;
			}
			//指数不相等的情况
			else if (q->index > p->index)
			{
				tail->next = createNode(q->coef, q->index);
				tail = tail->next;
				q = q->next;
			}
			else if (q->index < p->index)
			{
				tail->next = createNode(p->coef, p->index);
				tail = tail->next;
				p = p->next;
			}
		}
		//有一个多项式处理完了
		else
		{
			//用tmp指针指向未处理的多项式节点
			link *tmp;
			if (q == NULL)
				tmp = &p;
			else
				tmp = &q;
			tail->next = createNode((*tmp)->coef, (*tmp)->index);
			tail = tail->next;
			*tmp = (*tmp)->next; //移动未处理完的多项式的指针。
		}
		if (tail == NULL)
			break; //创建节点失败了，说明空间不够，需要释放re申请空间，并返回NULL
	}
	if (tail == NULL)
	{
		freeList(re);
		return NULL;
	}
	else
		return re;
}

//将多项式按照从大到小排序，并合并同类项
//会修改输入的多项式
void format(link header)
{
	if (header == NULL)
		return;
	link first = header;

	link a_former = header;
	link a_latter = header->next;
	while (a_latter != NULL)
	{
		link b_former = first;
		link b_latter = first->next;
		while (b_latter != a_latter)
		{
			if (b_latter->index == a_latter->index)
			{
				b_latter->coef += a_latter->coef;
				delete (a_former, 1); // delete一种取巧的用法。
				if (b_latter->coef == 0)
					delete (b_former, 1); //删除系数为0的项
				a_latter = a_former->next;
				break;
			}
			else if (b_latter->index < a_latter->index)
			{
				a_former->next = a_latter->next;
				b_former->next = a_latter;
				a_latter->next = b_latter;
				a_latter = a_former->next;
				break;
			}
			else
			{
				b_former = b_latter;
				b_latter = b_latter->next;
			}
		}
		if (b_latter == a_latter)
		{
			a_former = a_latter;
			a_latter = a_latter->next;
		}
	}
}
//这里将两个多项式相加
//并返回和式的指针，错误将返回NULL
//会修改输入多项式
link add(link header1, link header2)
{
	format(header1);
	format(header2);
	return simpleAdd(header1, header2);
}
int main(void)
{
	int t, b, c;
	printf("顺序表测试：\n");
	printf("创建顺序表ing\n");
	L1 L = S_create();
	printf("创建顺序表完成\n");
	printf("插入测试（请输入5个数，以空格分隔）：");
	for (int i = 0; i < 5; i++)
	{
		if (scanf("%d", &t) == 1)
			S_insert(&L, t, L.length + 1);
	}
	fflush(NULL);
	S_display(L);
	printf("请输入要插入的一个数字：");
	scanf("%d", &t);
	printf("请输入要插入的位置，（1～%d)：", L.length + 1);
	scanf("%d", &b);
	printf("插入ing\n");
	if (S_insert(&L, t, b))
		printf("插入完成\n");
	else
		printf("插入失败");
	S_display(L);
	printf("请输入要删除的位置，（1～%d)：", L.length);
	if (scanf("%d", &b) == 1)
		if (S_delete(&L, b))
			printf("删除完成\n");
		else
			printf("删除失败");
	S_display(L);
	printf("请输入要查找的数字：");
	if (scanf("%d", &t))
		printf("逻辑序号是（0表示没有找到):%d\n", S_find(L, t));
	printf("顺序标测试完成\n");
	getchar();
	getchar();
	printf("单链表测试开始\n");
	printf("初始化ing\n");
	link header1, header2;
	initList(&header1);
	insert(header1, createNode(8, 12), 1);
	insert(header1, createNode(120, 3), 1);
	insert(header1, createNode(-12, 8), 1);
	printf("初始化完成\n");
	display(header1);
	printf("请输入要插入的位置（逻辑序号，从1开始）：");
	scanf("%d", &b);
	printf("请依次输入系数 指数（eg：12 18）：");
	scanf("%d%d", &t, &c);
	printf("插入ing\n");
	if (insert(header1, createNode(t, c), b))
		printf("插入成功\n");
	else
		printf("插入失败\n");
	display(header1);
	printf("请输入要删除的位置：");
	scanf("%d", &b);
	printf("删除ing\n");
	if (delete (header1, b))
		printf("删除完成\n");
	else
		printf("删除失败\n");
	display(header1);
	printf("请输入要查找的指数(返回第一个符合条件的项）：");
	scanf("%d", &c);
	printf("查找ing\n");
	link p = locate(header1, c);
	if (p != NULL)
	{
		printf("系数：%d,指数：%d\n", p->coef, p->index);
	}
	else
		printf("无此项\n");
	getchar();
	getchar();
	printf("上面修改过的多项式：");
	display(header1);
	printf("与多项式：");
	initList(&header2);
	insert(header2, createNode(-13, 2), 1);
	insert(header2, createNode(37, 9), 1);
	insert(header2, createNode(18, 3), 1);
	insert(header2, createNode(-12, 5), 1);
	display(header2);
	printf("相加得到多项式：");
	display(add(header1, header2));
	return 0;
}

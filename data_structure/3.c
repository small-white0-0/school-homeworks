#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	char data;
	struct node *left_child;
	struct node *right_child;
} BTnode;
typedef BTnode *BTptr;

//创建一个新的节点
BTptr createBTnode(char data)
{
	BTptr node = (BTptr)malloc(sizeof(BTnode));
	if (node != NULL)
	{
		node->data = data;
		node->left_child = NULL;
		node->right_child = NULL;
	}
	return node;
}

//以拓展先序遍历方式创建二叉树
BTptr createBtree(char **str)
{
	if (**str == '\0') //字符串遍历完成或为空，返回NULL
	{
		return NULL;
	}

	//读取字符，并移动指针
	char data = **str;
	*str = *str + 1;

	//根据读入的字符进行处理
	BTptr root = NULL;
	if (data != '$')
	{
		root = createBTnode(data);
		root->left_child = createBtree(str);
		root->right_child = createBtree(str);
	}
	return root;
}

// 先序遍历
void preOrder(BTptr root)
{
	if (root != NULL)
	{
		printf("%c", root->data);
		preOrder(root->left_child);
		preOrder(root->right_child);
	}
}

//中序遍历
void midOrder(BTptr root)
{
	if (root != NULL)
	{
		midOrder(root->left_child);
		printf("%c", root->data);
		midOrder(root->right_child);
	}
}

//计算二叉树的高度
int getHeight(BTptr root)
{
	int re = 0;
	if (root == NULL)
	{
		re = 0;
	}
	else
	{
		//计算左右子树的高度
		int left_height = getHeight(root->left_child);
		int right_height = getHeight(root->right_child);
		//根据左右字数的高度，得到当前树的高度
		if (left_height >= right_height)
		{
			re = left_height + 1;
		}
		else
		{
			re = right_height + 1;
		}
	}
	return re;
}

int main(void)
{
	char a[] = "abc$$1$2$$efg$$4$$5$$";
	printf("创建的树的：%s\n",a);
	char *p = &a[0];
	BTptr root = createBtree(&p);
	printf("先序遍历：");
	preOrder(root);
	printf("\n");
	printf("中序遍历：");
	midOrder(root);
	printf("\n");
	printf("高度： %d\n",getHeight(root));
	return 0;
}

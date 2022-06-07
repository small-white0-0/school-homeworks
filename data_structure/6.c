#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 接受数组和数组长度，用直接插入法进行排序
void insert_directly_sort(int a[], int length)
{
    if (length <= 1)
    {
        return;
    }

    for (int i = 1; i < length; i++)
    {
        int j = i - 1;
        //找到插入位置
        while (j >= 0 && a[j] > a[i])
        {
            j--;
        }

        //如果找到插入位置，则进行移动，并插入
        if (j != -1)
        {
            int tmp = a[i];
            for (int k = i - 1; k > j; k--)
            {
                a[k + 1] = a[k];
            }
            a[j + 1] = tmp;
        }
    }
}

void selected_easily_sort(int a[], int length)
{
    if (length <= 1)
    {
        return;
    }
    int indexOfMin = 0;
    int temp;
    for (int i = 0; i < length - 1; i++)
    {
        //查找 i～length的最小值的下标
        indexOfMin = i;
        for (int j = i; j < length; j++)
        {
            if (a[indexOfMin] > a[j])
            {
                indexOfMin = j;
            }
        }

        //最小值不是a[i],则交换两者
        if (indexOfMin != i)
        {
            temp = a[i];
            a[i] = a[indexOfMin];
            a[indexOfMin] = temp;
        }
    }
}

void quick_sort(int *a, int length)
{
    //安全检查以及递归结束条件
    if (a == NULL || length <= 1)
    {
        return;
    }
    int divide_value = a[0];
    //进行划分
    int low = 0;
    int high = length - 1;
    while (low < high)
    {
        while (low < high && divide_value <= a[high])
        {
            high--;
        }
        a[low] = a[high];

        while (low < high && divide_value >= a[low])
        {
            low++;
        }
        a[high] = a[low];
    }
    a[low] = divide_value;

    //对划分后的子数组进行划分
    quick_sort(a, low);
    quick_sort(&a[low + 1], length - low - 1);
}

void display(int a[], int length)
{
    if (length <= 0)
    {
        return;
    }
    for (int i = 0; i < length; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main(void)
{
    int a[] = {2, 34, 5, 6, 7, 23, 4, 657, 35, 134, 65, 8, 3};
    int aLength = sizeof(a) / sizeof(int);
    int *bak = (int *)malloc(sizeof(a));
    memcpy(bak, a, sizeof(a));
    // int b[] = {4, 5, 45, 324, 76, 234, 86, 12, 68, 34, 9, 34, 9, 3, 6, 1, 5, 6};
    // int bLength = sizeof(b) / sizeof(int);
    printf("===========================直接插入排序==========================\n");
    printf("排序前的数组：");
    display(a, aLength);
    insert_directly_sort(a, aLength);
    printf("排序后的数组：");
    display(a, aLength);
    memcpy(a, bak, sizeof(a));

    printf("===========================简单选择排序==========================\n");
    printf("排序前的数组：");
    display(a, aLength);
    insert_directly_sort(a, aLength);
    printf("排序后的数组：");
    display(a, aLength);
    memcpy(a, bak, sizeof(a));

    printf("===========================快速排序==========================\n");
    printf("排序前的数组：");
    display(a, aLength);
    quick_sort(a, aLength);
    printf("排序后的数组：");
    display(a, aLength);
}
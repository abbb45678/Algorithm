#include <stdio.h>
#include<stdlib.h>

//1、直接插入排序(稳定）原理：类似于打扑克牌时的整理牌的过程 时间复杂度O(n^2)
void sort_direct(int a[],int length)
{
	int i, j, temp;
	for (i = 0; i < length; i++)
	{
		j = i;
		while (j > 0 && a[j] < a[j - 1])
		{
			temp = a[j - 1];
			a[j - 1] = a[j];
			a[j] = temp;
			j--;
		}
	}
}



//2、冒泡排序（稳定）原理：类似于水泡在水中的上浮过程 时间复杂度O(n^2)
void bubble_sort(int a[],int length)
{
	for (int i = 0; i < length -1; i++)
	{
		for (int j = 0; j < length-i-1; j++)
		{
			if (a[j] > a[j+1])
			{
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}

void bubble_sort1(int a[], int length)
{
	int i, j, temp;
	for (i = length - 1; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (a[j] > a[i]) {
				temp = a[j];
				a[j] = a[i];
				a[i] = temp;
			}
		}
	}
}

void bubble_sort3(int a[], int length)
{
	if (length < 2)
		return;
	int i, temp;
	int swp = 0;//用来标记某一轮是否有交换
	for (i = 0; i < length-1; i++)
	{
		if (a[i] > a[i + 1])
		{
			temp = a[i + 1];
			a[i + 1] = a[i];
			a[i] = temp;
			swp = 1;
		}
	}
	if (swp == 0)return;
	bubble_sort3(a, --length);
}



//3、归并排序（稳定）原理：递归、分治法 时间复杂度O(nlogn)

void msort(int a[], int temp[], int le, int ri);
void merge(int a[], int temp[], int le, int ri, int mid);
//归并入口
void merge_sort(int a[],int length) 
{
	int* temp = (int*)malloc(length * sizeof(int));//分配辅助数组用来将原数组进行划分

	if (temp)
	{
		msort(a, temp, 0, length - 1);
		free(temp);
	}
	else
	{
		printf("空间分配失败！");
	}
}
//递归划分
void msort(int a[], int temp[], int le, int ri)
{
	if (le < ri)
	{
		int mid = (ri + le) / 2;
		msort(a, temp, le, mid);//递归划分左半区域
		msort(a, temp, mid + 1, ri);//递归划分右半区域
		merge(a, temp, le, ri, mid);
	}
}
//合并排序
void merge(int a[],int temp[], int le, int ri,int mid)
{
	int l_no = le;//左边第一个未排元素
	int r_no = mid +1;//右边第一个未排元素
	int i = le;

	//合并
	while (l_no <= mid && r_no <= ri)
	{
		if (a[l_no] < a[r_no])
			temp[i++] = a[l_no++];
		else
			temp[i++] = a[r_no++];
	}

	while (l_no <= mid)
		temp[i++] = a[l_no++];//只剩左半，直接将其加到临时数组后面
	

	while (r_no <= ri)
		temp[i++] = a[r_no++];//只剩右半

	while (le <= ri)
	{
		a[le] = temp[le];
		le++;
	}//将辅助数组中排序结果放到原数组中

}

void print_a(int a[],int length) {
	for (int i = 0; i < length; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

int main() {
	int a[5] = { 1,4,2,5,3 };
	int length = sizeof(a) / sizeof(a[0]);
	int* temp = (int*)malloc(length * sizeof(int));
	printf("排序前：");
	print_a(a, length);
	printf("\n");

	sort_direct(a, length);
	printf("直接插入排序：\n");
	print_a(a, length);
	printf("\n");

	bubble_sort(a, length);
	printf("标准冒泡排序：\n");
	print_a(a, length);
	printf("冒泡变体：");
	bubble_sort1(a, length);
	print_a(a, length);
	printf("冒泡优化:");
	bubble_sort3(a, length);
	print_a(a, length);
	printf("\n");

	printf("归并排序：\n");
	merge_sort(a,length);
	print_a(a, length);
	printf("\n");
	
	return 0;
}
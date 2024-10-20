#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：main.c
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.0
 * 【完成日期】：	2024年  月日
 * 【更新内容】：
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.
 * 【历史日期】：	2024年  月日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：使用malloc函数模拟开辟一个二维数组
 *******************************************************************************************/
#define __DEBUG__

#include<stdlib.h>
#include<stdio.h>
#include"vld.h"

#define Malloc(type,n) (type*)malloc(n * sizeof(type))
#define ERRORS(mem) "Open error of " #mem
#define Alloc_failed(mem) \
		if(mem == NULL)\
		{\
				perror(ERRORS(mem)); \
				mem = NULL; \
				exit(EOF);\
		}

#ifndef __DEBUG__

#define Alloc_failed(mem) "Open error of " #mem 
#define Free(mem) free(mem); mem = NULL

#define AllocFailed(mem) /
if (mem == NULL) /
{ /
perror(Alloc_failed(mem)); /
Free(mem); /
}

#endif



int main()
{
	int** arr = Malloc(int*, 3);
	Alloc_failed(arr);
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		int* pa = NULL;
		pa = Malloc(int, 5);
		Alloc_failed(pa);
		*(arr + i) = pa;
	}
	int j = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 5; j++)
		{
			*(*(arr + i) + j) = i * 5 + j;
		}
	}
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 5; j++)
		{
			printf("%d ", *(*(arr + i) + j));
		}
		printf("\n");
	}
	for (i = 0; i < 3; i++)
	{
		free(*(arr + i));
		*(arr + i) = NULL;
	}
	free(arr);
	arr = NULL;
	return 0;
}
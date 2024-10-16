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
 * 【程序内容】：随笔——动态内存管理
 *******************************************************************************************/
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<stdio.h>

typedef struct test
{
	int i;
	char* arr;
}T;

int main()
{
	T* p = (T*)malloc(sizeof(T));
	assert(p);
	p->i = 12;
	char* p1 = (char*)malloc(sizeof(char[12]));
	assert(p1);
	p->arr = p1;
	p1 = NULL;
	strcpy(p->arr, "hello world");
	printf("%s\n", p->arr);
	p->i = 16;
	p1 = (char*)realloc(p->arr, sizeof(char[16]));
	assert(p1);
	p->arr = p1;
	p1 = NULL;
	strcpy(p->arr, "I am a student.");
	printf("%s\n", p->arr);
	free(p->arr);
	p->arr = NULL;
	free(p);
	p = NULL;
	return 0;
}
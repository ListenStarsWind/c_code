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
 * 【程序内容】：随笔——预处理详解
 *******************************************************************************************/
#include<stdio.h>

#include"add.h"

int main()
{
	int a = 3;
	int b = 4;
	printf("%d\n", add(a, b));
	return 0;
}
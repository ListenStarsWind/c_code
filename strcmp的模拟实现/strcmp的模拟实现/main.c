﻿#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：	main.c
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
 * 【程序内容】：strcmp的模拟实现
 *******************************************************************************************/

#include<stdio.h>
#include<assert.h>
#include<string.h>

int my_strcmp(const char* str1, const char* str2)
{
	assert(str1 && str2);
	while (*str1 == *str2)
	{
		if (*str1 == '\0')
			return 0;
		str1++;
		str2++;
	}
	return *str1 - *str2;
}

int main()
{
	char* str1 = "abcdef";
	char* str2 = "abcdfe";
	if (my_strcmp(str1, str2) > 0)
	{
		printf("字符串1比字符串2大\n");
	}
	else
	{
		printf("字符串2比字符串1大\n");
	}
	return 0;
}
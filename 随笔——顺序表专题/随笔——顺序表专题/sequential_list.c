#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：SeqList.c
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
 * 【程序内容】：
 *******************************************************************************************/

#if 0
1.顺序表为什么叫做SeqList ?
SeqList是sequence（顺序的） 和 List(列表)

2.有个题目，说全局变量应该放在.h文件里，需要解释一下为什么不能这样做

3.记得说一下，为什么.h前面要加#pragma once

4.说说为什么typedef int SLDataType;

5.VS有“一键替换”？这可不兴用。

6.说说头文件包含策略

7.说说SL初始化为什么用指针作为形参
有趣的现象，在SLINIT__TEST中，调试，仅监视s, 函数跳出后s才变化, 如果要在函数内部看变化，要监视* ps

8.说说为什么使用开发多文件，那个test.c干什么的

9.说说条件编译SLINIT__TEST

10.宏参数不要用p，因为它们大小写太相近了

11.去介绍一下strrchr函数，string.h

12.讲一下宏__M_FILE__中strrchr为什么要查找'\\'而不是'\'

13.哈哈，我用malloc开辟了。写代码写糊涂了

14.不同的操作函数中指针名不要一样，一样了我的ASSERT中的变量指示就屁用没有了

15.记得最初的两个pop健壮性不足
#endif


#include"sequential_list.h"

//SL初始化
#ifdef SLINIT__TEST
void SLInit(SL * ps)
{
	//健壮性
	ASSERT(ps);
	ps->arr = NULL;//NULL   stdio.h  包含于sequential_list.h
	ps->capacity = ps->size = 0;
}

#else

void SLInit(SL ps)
{
	ps.arr = NULL;
	ps.capacity = ps.size = 0;
}

#endif


//SL销毁
void SLDestroy(SL* ps)
{
	ASSERT(ps);
	free(ps->arr);
	ps->arr = NULL;
	ps->size = ps->capacity = 0;
}

//能否插入函数
void SLPush(SL** ps)
{
	if ((*ps)->capacity == (*ps)->size)
	{
		int newcapacity = (*ps)->capacity == 0 ? 4 : (*ps)->capacity * 2;
		SLDataType* p = Realloc((*ps)->arr, SLDataType, newcapacity);
		ASSERT(p);
		(*ps)->arr = p;
		//这个我忘了写
		(*ps)->capacity = newcapacity;
	}
}

//尾插函数
#ifdef SLPUSHBACK

void SLPushBack(SL* ps, SLDataType x)
{
	ASSERT(ps);
	SLPush(&ps);
	ps->arr[ps->size++] = x;
}

#else

#endif

//头插函数
void SLPushFront(SL* ps, SLDataType x)
{
	ASSERT(ps);
	SLPush(&ps);
	int i = 0;
	for (i = ps->size; i > 0; i--)
	{
		ps->arr[i] = ps->arr[i - 1];
	}
	ps->size++;
	ps->arr[0] = x;
}

#ifdef __POP__


//尾删函数
void SLPopBack(SL* ps)
{
	ASSERT(ps);
	ps->size--;
}

//头删函数
void SLPopFront(SL* ps)
{
	ASSERT(ps);
	int i = 0;
	for (i = 0; i < ps->size - 1; i++)
	{
		ps->arr[i] = ps->arr[i + 1];
	}
	ps->size--;
}

#else

void SLPopBack(SL* ps)
{
	ASSERT(ps);
	if (ps->size > 0)
	{
		ps->size--;
	}
	else
	{
		printf("This memory block no longer contains valid data.\n");
		printf("%s\n", __M_FILE__);
		printf("%d\n", __LINE__);
		exit(EOF);
	}
}

void SLPopFront(SL* ps)
{
	ASSERT(ps);
	if (ps->size > 0)
	{
		int i = 0;
		for (i = 0; i < ps->size - 1; i++)
		{
			ps->arr[i] = ps->arr[i + 1];
		}
		ps->size--;
	}
	else
	{
		printf("This memory block no longer contains valid data.\n");
		printf("%s\n", __M_FILE__);
		printf("%d\n", __LINE__);
		exit(EOF);
	}
}

#endif
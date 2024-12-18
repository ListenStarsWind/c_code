#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：SeqList.c
 * 【文件标识】：主体模块
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
 * 【程序内容】：与SeqqList有关的函数
 *******************************************************************************************/
#include"SeqList.h"

 //SL初始化
#ifndef __SLINT__

#ifdef __SLINT_DEBUG__

void SLInit(SL* ps_Init)
{
	ps_Init->arr = NULL;
	ps_Init->capacity = ps_Init->size = 0;
}

#else

void SLInit(SL* ps_Init)
{
	__BUG_NULL__(ps_Init);
	ps_Init->arr = NULL;
	ps_Init->capacity = ps_Init->size = 0;
}

#endif

#else

void SLInit(SL s_Init)
{
	s_Init.arr = NULL;
	s_Init.capacity = s_Init.size = 0;
}
#endif

//SL销毁函数
void SLDestroy(SL* s_Destroy)
{
	__BUG_NULL__(s_Destroy);
	free(s_Destroy->arr);
	s_Destroy->arr = NULL;
	s_Destroy->capacity = s_Destroy->size = 0;
}

//SL扩展函数
static void SLExpand(SL** pps_Expand)
{
	__BUG_NULL__(*pps_Expand);
	int newcapacity = (*pps_Expand)->capacity == 0 ? 4 : (*pps_Expand)->capacity * 2;
	SLDataType* p = Realloc(SLDataType, (*pps_Expand)->arr, newcapacity);
	__BUG_NULL__(p);
	(*pps_Expand)->arr = p;
	(*pps_Expand)->capacity = newcapacity;
}

//SL缩小函数
static void SLContract(SL** pps_Contract)
{
	__BUG_NULL__(*pps_Contract);
	int newcapacity = (*pps_Contract)->size == 0 ? 4 : (*pps_Contract)->size;
	SLDataType* p = Realloc(SLDataType, (*pps_Contract)->arr, newcapacity);
	__BUG_NULL__(p);
	(*pps_Contract)->arr = p;
	(*pps_Contract)->capacity = newcapacity;
}

//SL尾插函数
void SLPushBack(SL* ps_PushBack, SLDataType x)
{
	__BUG_NULL__(ps_PushBack);
	if (ps_PushBack->capacity == ps_PushBack->size)
	{
		SLExpand(&ps_PushBack);
	}
	ps_PushBack->arr[ps_PushBack->size++] = x;
}

//SL尾删函数
#ifndef __SLPOPBACK__
void SLPopBack(SL* ps_PopBack)
{
	__BUG_NULL__(ps_PopBack);
	if (ps_PopBack->size)
	{
		ps_PopBack->size--;
	}
	else
	{
		printf("This memory block no longer contains valid data.\n");
		printf("%s\n", __M_FILE__);
		printf("%d\n\n", __LINE__);
		exit(EOF);
	}
	if (ps_PopBack->size * 2 < ps_PopBack->capacity)
	{
		SLContract(&ps_PopBack);
	}
}

#else

void SLPopBack(SL* ps_PopBack)
{
	__BUG_NULL__(ps_PopBack);
	ps_PopBack->size--;
	if (ps_PopBack->size * 2 < ps_PopBack->capacity)
	{
		SLContract(&ps_PopBack);
	}
}

#endif

//SL头插函数
void SLPushFront(SL* ps_PushFront, SLDataType x)
{
	__BUG_NULL__(ps_PushFront);
	if (ps_PushFront->capacity == ps_PushFront->size)
	{
		SLExpand(&ps_PushFront);
	}
	int i = 0;
	for (i = ps_PushFront->size; i > 0; i--)
	{
		ps_PushFront->arr[i] = ps_PushFront->arr[i - 1];
	}
	ps_PushFront->arr[0] = x;
	ps_PushFront->size++;
}

//SL头删函数
void SLPopFront(SL* ps_PopFront)
{
	__BUG_NULL__(ps_PopFront);
	if (ps_PopFront->size)
	{
		int i = 0;
		for (i = 0; i < ps_PopFront->size - 1; i++)
		{
			ps_PopFront->arr[i] = ps_PopFront->arr[i + 1];
		}
		ps_PopFront->size--;
	}
	else
	{
		printf("This memory block no longer contains valid data.\n");
		printf("%s\n", __M_FILE__);
		printf("%d\n\n", __LINE__);
		exit(EOF);
	}
	if (ps_PopFront->size * 2 < ps_PopFront->capacity)
	{
		SLContract(&ps_PopFront);
	}
}

//SL指定位置插入
void SLInsert(SL* ps, int pos, SLDataType x)
{
	assert(ps);
	assert(0 <= pos && pos <= ps->size);
	if (ps->capacity == ps->size)
	{
		SLExpand(&ps);
	}
	int i = 0;
	for (i = ps->size; i > pos; i--)
	{
		ps->arr[i] = ps->arr[i - 1];
	}
	ps->arr[pos] = x;
	ps->size++;
}

//SL指定位置删除
void SLErase(SL* ps, int pos)
{
	assert(ps);
	assert(0 <= pos && pos < ps->size);
	if (ps->size)
	{
		int i = 0;
		for (i = pos; i < ps->size - 1; i++)
		{
			ps->arr[i] = ps->arr[i + 1];
		}
		ps->size--;
	}
	else
	{
		printf("This memory block no longer contains valid data.\n");
		printf("%s\n", __M_FILE__);
		printf("%d\n\n", __LINE__);
		exit(EOF);
	}
	if (ps->size * 2 < ps->capacity)
	{
		SLContract(&ps);
	}
}

//SL查找
int SLFind(SL* ps, SLDataType x)
{
	assert(ps);
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (ps->arr[i] == x)
		{
			return i;
		}
	}
	return EOF;
}
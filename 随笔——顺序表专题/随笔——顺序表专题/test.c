#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：	test.c
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
#include"sequential_list.h"

#ifdef  __DEBUG__


void SLInit_test(void)
{
	SL s;

#ifdef SLINIT__TEST
	SLInit(&s);
#else
	SLInit(s);
#endif
}

void SLPrintf(SL* s)
{
	int i = 0;
	for (i = 0; i < s->size; i++)
	{
		printf("%d ", s->arr[i]);
	}
	printf("\n");
}

#ifdef SLPUSHBACK
void SLPush_test(void)
{
	SL s;
	SLInit(&s);
	SLPushBack(&s, 6);
	SLPushBack(&s, 4);
	SLPushBack(&s, 7);
	SLPushBack(&s, 2);
	SLPushBack(&s, 3);

	SLPopBack(&s);
	SLPrintf(&s);
	SLPopBack(&s);
	SLPrintf(&s);

	SLPopFront(&s);
	SLPrintf(&s);
	SLPopFront(&s);
	printf("\n");
	SLDestroy(&s);
}
#else

#endif

int main()
{
	//SLInit_test();
	SLPush_test();
	return 0;
}

#endif
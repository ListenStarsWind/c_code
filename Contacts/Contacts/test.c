#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：
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
#include"Contacts.h"
#include"SeqList.h"
#ifdef DEBUG

//功能测试（Functional Testing） : FT
//异常测试（Negative Testing） : NT
//单元测试（Unit Testing） : UT
//集成测试（Integration Testing） : IT
//系统测试（System Testing） : ST
//回归测试（Regression Testing） : RT
//性能测试（Performance Testing） : PT
//压力测试（Stress Testing） : ST
//验收测试（Acceptance Testing） : AT
//安全测试（Security Testing） : SecT


void FT(void)
{
	SL s;
	SLInit(&s);
	SLIAB(&s, 3);
	//3
	SLIAB(&s, 2);
	//2 3
	SLIAB(&s, 1);
	//1 2 3
	SLIAE(&s, 4);
	//1 2 3 4
	SLIAE(&s, 5);
	//1 2 3 4 5
	SLIAE(&s, 6);
	//1 2 3 4 5 6
	SLDAB(&s);
	//2 3 4 5 6
	SLDAB(&s);
	//3 4 5 6
	SLDae(&s);
	//3 4 5
	SLDae(&s);
	//3 4
	SLIDSP(&s, 0, 2);
	//2 3 4
	SLIDSP(&s, 0, 1);
	//1 2 3 4
	SLIDSP(&s, 2, 5);
	//1 2 5 3 4
	SLIDSP(&s, 3, 6);
	//1 2 5 6 3 4
	SLIDSP(&s, s.size, 7);
	//1 2 5 6 3 4 7
	SLIDSP(&s, s.size, 8);
	//1 2 5 6 3 4 7 8
	SLDSP(&s, 2);
	//1 2 6 3 4 7 8
	SLDSP(&s, 2);
	//1 2 3 4 7 8
	SLIDSP(&s, 4, 5);
	//1 2 3 4 5 7 8
	SLIDSP(&s, 5, 6);
	//1 2 3 4 5 6 7 8
	int find = SLFind(&s, 5);
	if (find >= 0)
	{
		printf_s("找到了，下标是%d.\n", find);
	}
	else
	{
		printf("找不到！\n");
	}
	find = SLFind(&s, 10);
	if (find >= 0)
	{
		printf_s("找到了，下标是%d.\n", find);
	}
	else
	{
		printf("找不到！\n");
	}
	SLShow(&s);
	SLDestruction(&s);
}

void NT(void)
{
	SL s;
	//SLInit(NULL);
	SLInit(&s);
	//SLIAB(NULL, 1);
	//SLIAE(NULL, 1);
	//SLDAB(NULL);
	//SLDae(NULL);
	SLIDSP(&s, 0, 2);
	SLIDSP(&s, 0, 1);
	//SLDSP(&s, 3);
	//SLDSP(&s, -1);
	//SLIDSP(&s, 3, 1);
	//SLIDSP(&s, -1, 1);
	SLDSP(&s, 0);
	SLDSP(&s, 0);
	//SLDSP(&s, 0);
	//SLFind(NULL, 6);
	//SLShow(NULL);
	SLIDSP(&s, s.size, 3);
	//SLDestruction(&s);
	SLDestruction(NULL);

}

int main()
{
	//FT();
	//NT();
	return 0;
}
#endif
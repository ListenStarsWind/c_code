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
#include"SeqList.h"
#include"Contacts.h"


void CtsInit(Cts* cts_init)
{
	SLInit(cts_init);
}

void CtsDest(Cts* cts_dest)
{
	SLDestruction(cts_dest);

}

void CtsIdsp(Cts* cts_idsp, int pos, SLDataType x)
{
	SLIDSP(cts_idsp, pos, x);
}

void CtsDsp(Cts* cts_dsp, int pos)
{
	SLDSP(cts_dsp, pos);
}

void CtsIab(Cts* cts_iab, SLDataType x)
{
	CtsIdsp(cts_iab, 0, x);
}

void CtsIae(Cts* cts_iae, SLDataType x)
{
	CtsIdsp(cts_iae, cts_iae->size, x);
}

void CtsDab(Cts* cts_dab)
{
	CtsDsp(cts_dab, 0);
}

void Ctsdae(Cts* cts_dae)
{
	CtsDsp(cts_dae, cts_dae->size - 1);
}

void CtsFind(Cts* cts_find, SLDataType x)
{

}

char* PrintfSxe(Sex x)
{
	switch (x)
	{
	case Male:
		return "Male";
		break;
	case Female:
		return "Female";
		break;
	case Confidential:
		return "Confidential";
		break;
	case Intersex:
		return "Intersex";
		break;
	}
}

int PrintfAge(const Date* brith)
{
	//用来存储当前日期
	Date current;
	//time_t 用于描述系统时自1970年1月1日00:00:00 UTC以来的秒数
	time_t t = time(NULL);
	//struct tm 是一个结构体，用于表示时间和日期的各个组成部分，如年、月、日、小时、分钟、秒等
	//函数localtime参数是time_t*,返回指向struct tm的指针，所以要解引用
	struct tm tm = *localtime(&t);
	//tm.tm_year：表示自1900年以来的年份。例如，如果当前年份是2024年，tm.tm_year 的值将是124。因此，需要加上1900来得到当前的实际年份。
	current.year = tm.tm_year + 1900;
	//tm.tm_mon：表示月份，从0到11（0表示1月，11表示12月）。因此，需要加1来得到实际的月份。
	current.month = tm.tm_mon + 1;
	//tm.tm_mday：表示当前月份中的日期，从1开始，至于为什么不从0开始，可能是一种历史遗留问题亦或者和tm.tm_mon相区分
	current.day = tm.tm_mday;
	int ret = 0;
	ret = current.year - brith->year;
	if (current.month < brith->month || (current.month == brith->month && current.day < brith->day))
	{
		ret--;
	}
	return ret;
}

void CtsShow(const Cts* cts_show)
{
	printf("name sex age QQNumber phone\n");
	int i = 0;
	for (i = 0; i < cts_show->size; i++)
	{
		printf("%s ", cts_show->p[i].name);
		printf("%s ", PrintfSxe(cts_show->p[i].sex));
		printf("%d ", PrintfAge(&(cts_show->p[i].birth)));
		printf("%s ", cts_show->p[i].QQNumber);
		printf("%s ", cts_show->p[i].phone);
		printf("\n");
	}
}

SLDataType CtcAsgn(void)
{
	SLDataType x;
	printf("请输入你的名字：\n");
	if (scanf("%s", x.name) != 1)
	{
		printf("输入失败，请重新输入：\n");
	}

	printf("你的性别是？请选择\n");
	printf("*************************0.男    1.女*************************\n");
	printf("*************************3.保密 4.模糊************************\n");
	printf("**********************输入对应序号回车即可*********************\n");
	int i = 0;
	Sex y;
	if (scanf("%d", &i) != 1)
	{
		printf("输入失败，请重新输入：\n");
	}
	switch (i)
	{
	case 0:
		y = Male;
		break;
	case 1:
		y = Female;
		break;
	case 3:
		y = Confidential;
		break;
	default:
		y = Intersex;
		break;
	}
	x.sex = y;

	printf("你的出生年份为？\n");
	if (scanf("%d", &(x.birth.year)) != 1)
	{
		printf("输入失败，请重新输入：\n");

	}
	printf("你的出生月份为？\n");
	if (scanf("%d", &(x.birth.month)) != 1)
	{
		printf("输入失败，请重新输入：\n");
	}
	printf("你的出生日期为？\n");
	if (scanf("%d", &(x.birth.day)) != 1)
	{
		printf("输入失败，请重新输入：\n");
	}

	printf("你的QQ号是？输入后回车即可：\n");
	if (scanf("%s", x.QQNumber) != 1)
	{
		printf("输入失败，请重新输入：\n");
	}

	printf("你的电话号码是？输入后回车即可：\n");
	if (scanf("%s", x.phone) != 1)
	{
		printf("输入失败，请重新输入：\n");
	}

	return x;
}


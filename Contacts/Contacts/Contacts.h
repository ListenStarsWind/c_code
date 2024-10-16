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
#pragma once 

//#define DEBUG//打开执行test.c主函数，关闭执行main.c主函数
#define NAME_MAX 20
#define BIRTH_MAX 15
#define QQNUMBER_MAX 15
#define PHONE_MAX 15

typedef enum sex
{
	Male,           //男性
	Female,         //女性
	Confidential,	//保密
	Intersex		//间性
}Sex;

typedef struct
{
	int year;
	int month;
	int day;
}Date;



typedef struct Contacts
{
	char name[NAME_MAX];
	Sex sex;
	Date birth;
	char QQNumber[QQNUMBER_MAX];
	char phone[PHONE_MAX];
}Ctc;

struct SeqList;
typedef struct SeqList Cts;

typedef Ctc SLDataType;


//Cts初始化
void CtsInit(Cts* cts_init);

//Cts销毁
//Dest：Destruction
void CtsDest(Cts* cts_dest);

//Cts指定位置插入
void CtsIdsp(Cts* cts_idsp, int pos, SLDataType x);

//Cts指定位置删除
void CtsDsp(Cts* cts_dsp, int pos);

//Cts开头插入
//Iab:Insert at the Beginning
void CtsIab(Cts* cts_iab, SLDataType x);

//Cts尾部插入
//Iae:Insert at the End
void CtsIae(Cts* cts_iae, SLDataType x);

//Cts开头删除
//Dab：Delete at the Beginning
void CtsDab(Cts* cts_dab);

//Cts尾部删除
//Dae:Delete at the End
void Ctsdae(Cts* cts_dae);

//Cts查找
//Find : find
void CtsFind(Cts* cts_find, SLDataType x);

//Cts展示
//Show:show
void CtsShow(const Cts* cts_show);

//Ctc赋值
//Asgn:Assignment
SLDataType CtcAsgn(void);
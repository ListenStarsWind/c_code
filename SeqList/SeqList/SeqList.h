#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：	SeqList.h
 * 【文件标识】：源头文件
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
 * 【程序内容】：与SeqList相关的头文件，预处理指令
 *******************************************************************************************/
#pragma once

#define __DEBUG__ //总Debug开关


 //#define __SLINT__//SLInit条件编译总开关，打开进入错误示范
//#define __SLINT_DEBUG__//打开为SLInit初始版本，没有判断形参是否为空；关闭为SLInit修正版本，判断了形参是否为空

//#define __SLPOPBACK__//打开版本健壮性不足，关闭为修正版

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include"vld.h"


#define __M_FILE__ (strrchr(__FILE__,'\\') ? strrchr(__FILE__,'\\') + 1 : __FILE__)

#define __BUG_NULL__(p) \
		if(p == NULL)\
		{\
		printf("\nBug!\n");\
		printf("The address " #p " is null." "\n");\
		printf("%s\n",__M_FILE__);\
		printf("%d\n",__LINE__);\
		exit(EOF);\
		}

#define Realloc(type, p, n) (type*)realloc(p, n * sizeof(type))


typedef int SLDataType;

typedef struct SeqList
{
	SLDataType* arr;
	//This identifier "size" is used to describe the number of valid data items.
	//这个   标识符     size  是  用来     描述         个数      有效  数据  项  
	// size：大小（尺寸）的意思    
	int size;
	//This identifier "capacity" is used to describe the number of data items it can hold.
	//这个   标识符      capacity  是 用来     描述        个数        数据 项      可以  容纳（储存） 
	//实际上capacity就是容纳能力的意思
	int capacity;
}SL;


//SL初始化
//Init全写：initialization意为初始化
#ifndef __SLINT__

#ifdef __SLINT_DEBUG__

void SLInit(SL* ps_Init);

#else

void SLInit(SL* ps_Init);

#endif

#else

void SLInit(SL s_Init);

#endif

//SL销毁函数
//Destory就是全写，意为销毁，破坏
void SLDestroy(SL* s_Destroy);

//SL尾插函数
void SLPushBack(SL* ps_PushBack, SLDataType x);

//SL尾删函数
void SLPopBack(SL* ps_PopBack);

//SL头插函数
void SLPushFront(SL* ps_PushFront, SLDataType x);

//SL头删函数
void SLPopFront(SL* ps_PopFront);

//SL指定位置插入
void SLInsert(SL* ps, int pos, SLDataType x);

//SL指定位置删除
void SLErase(SL* ps, int pos);

//SL查找
int SLFind(SL* ps, SLDataType x);
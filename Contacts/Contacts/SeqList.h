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

#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
#include"vld.h"
#include"Contacts.h"
#include<string.h>
#include<time.h>


typedef struct SeqList
{
	SLDataType* p;
	int capacity;
	int size;
}SL;

#define Realloc(p,type,n) ((type*)realloc(p,n*sizeof(type)))

//SL初始化函数
//Init:Initialization
void SLInit(SL* sl_init);

//SL销毁函数
void SLDestruction(SL* sl_destruction);

//SL指定插入
//IDSP:Insert Data at Specified Position
void SLIDSP(SL* sl_insp, int Position, SLDataType x);

//SL指定删除
//DSP:Delete at Specified Position
void SLDSP(SL* sl_dsp, int Position);

//SL头插函数
//IAB:Insert at the Beginning
void SLIAB(SL* sl_iab, SLDataType x);

//SL尾插函数
//IAE:Insert at the End
void SLIAE(SL* sl_iae, SLDataType x);

//SL头删函数
//DAB：Delete at the Beginning
void SLDAB(SL* sl_dab);

//SL尾删函数
//Dae:Delete at the End
void SLDae(SL* sl_dae);

//SL查找函数
//Find : find
int SLFind(SL* sl_find, SLDataType x);

//SL展示函数
//Show:show
void SLShow(SL* sl_show);
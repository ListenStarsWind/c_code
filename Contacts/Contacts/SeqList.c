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


void SLInit(SL* sl_init)
{
	assert(sl_init);
	sl_init->p = NULL;
	sl_init->capacity = sl_init->size = 0;
}

void SLDestruction(SL* sl_destruction)
{
	assert(sl_destruction);
	free(sl_destruction->p);
	sl_destruction->p = NULL;
	sl_destruction->capacity = sl_destruction->size = 0;
}

//SL扩展函数
//Ext:Extension
static void SLExt(SL* sl_ext)
{
	int newcapacity = sl_ext->capacity == 0 ? 4 : sl_ext->capacity * 2;
	SLDataType* p = Realloc(sl_ext->p, SLDataType, newcapacity);
	assert(p);
	sl_ext->p = p;
	sl_ext->capacity = newcapacity;
}

//SL缩小函数
//Contr:Contraction
static void SLContr(SL* sl_contr)
{
	int newcapacity = sl_contr->size == 0 ? 4 : sl_contr->size;
	SLDataType* p = Realloc(sl_contr->p, SLDataType, newcapacity);
	assert(p);
	sl_contr->p = p;
	sl_contr->capacity = newcapacity;
}
//上述两个函数不断言的原因是它们不被直接调用

void SLIDSP(SL* sl_insp, int Position, SLDataType x)
{
	assert(sl_insp);
	assert(Position >= 0 && Position <= sl_insp->size);
	if (sl_insp->capacity == sl_insp->size)
	{
		SLExt(sl_insp);
	}
	int i = 0;
	for (i = sl_insp->size; i > Position; i--)
	{
		sl_insp->p[i] = sl_insp->p[i - 1];
	}
	sl_insp->p[Position] = x;
	sl_insp->size++;
}

void SLDSP(SL* sl_dsp, int Position)
{
	assert(sl_dsp);
	assert(Position >= 0 && Position < sl_dsp->size);
	if (sl_dsp->size > 0)
	{
		int i = 0;
		for (i = Position; i < sl_dsp->size - 1; i++)
		{
			sl_dsp->p[i] = sl_dsp->p[i + 1];
		}
		sl_dsp->size--;
	}
	else
	{
		printf("已经没有有效数据了！\n");
	}
	if (sl_dsp->size * 2 < sl_dsp->capacity)
	{
		SLContr(sl_dsp);
	}

}

void SLIAB(SL* sl_iab, SLDataType x)
{
	assert(sl_iab);
	SLIDSP(sl_iab, 0, x);
}

void SLIAE(SL* sl_iae, SLDataType x)
{
	assert(sl_iae);
	SLIDSP(sl_iae, sl_iae->size, x);
}

void SLDAB(SL* sl_dab)
{
	assert(sl_dab);
	SLDSP(sl_dab, 0);
}

void SLDae(SL* sl_dae)
{
	assert(sl_dae);
	SLDSP(sl_dae, sl_dae->size - 1);
}

#if 0
int SLFind(SL* sl_find, SLDataType x)
{
	assert(sl_find);
	int i = 0;
	for (i = 0; i < sl_find->size; i++)
	{
		if (sl_find->p[i] == x)
		{
			return i;
		}
	}
	return EOF;
}

void SLShow(SL* sl_show)
{
	assert(sl_show);
	int i = 0;
	for (i = 0; i < sl_show->size; i++)
	{
		printf("%d ", sl_show->p[i]);
	}
	printf("\n");
}

#endif
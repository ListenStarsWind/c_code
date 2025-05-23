﻿#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：	main.c
 * 【文件标识】：
 * ========================================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.1
 * 【完成日期】：	2024年  4月21日
 * 【更新内容】：优化了逻辑的实现方式
 * ========================================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.0
 * 【历史日期】：	2024年  4月15日
 * ========================================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】：猜凶手
 *******************************************************************************************/
#include<stdio.h>

int main()
{
	char murderer = 'a';
	while (murderer <= 'd')
	{
		if ((murderer != 'a') + (murderer == 'c') + (murderer == 'd') + (murderer != 'd') == 3)
		{
			break;
		}
		else
		{
			murderer++;
		}
	}
	printf("凶手是%c。\n", murderer);
	return 0;
}


#if 0
日本某地发生了一件谋杀案，警察通过排查确定杀人凶手必为4个嫌疑犯的一个。
以下为4个嫌疑犯的供词 :
A说：不是我。
B说：是C。
C说：是D。
D说：C在胡说
已知3个人说了真话，1个人说的是假话。
现在请根据这些信息，写一个程序来确定到底谁是凶手。

//如果用“1”表示有罪，“0”表示无罪，那对A,B,C,D四个变量来说
//A:((A==0) &&(（B==1）||(C==1)||(D==1)))
//B:((A==0)&&(B==0)&&(C==1)&&(D==0))
//C:((A==0)&&(B==0)&&(C==0)&&(D==1))
//D:((D==0)&&((A==1)||(B==1)||(C==1)))
//小写的a,b,c,d则表示是否说真话
//小写为1，则说的是真话
#include<stdio.h>

int main()
{
	int i = 0;
	int j = 0;
	int A;
	int B;
	int C;
	int D;
	int a;
	int b;
	int c;
	int d;
	int flag = 0;
	int push = 0;
	for (i = 0; i < 4; i++)
	{
		a = 0;
		b = 0;
		c = 0;
		d = 0;
		switch (i)
		{
			//方案0
		case 0:
			A = 1;
			B = 0;
			C = 0;
			D = 0;
			flag = 0;
			if (((A == 0) && ((B == 1) || (C == 1) || (D == 1))))
			{
				a = 1;
			}
			if (((A == 0) && (B == 0) && (C == 1) && (D == 0)))
			{
				b = 1;
			}
			if (((A == 0) && (B == 0) && (C == 0) && (D == 1)))
			{
				c = 1;
			}
			if (((D == 0) && ((A == 1) || (B == 1) || (C == 1))))
			{
				d = 1;
			}
			flag = a + b + c + d;
			if (flag == 3)
			{
				push = i;
			}
			break;

			//方案1
		case 1:
			A = 0;
			B = 1;
			C = 0;
			D = 0;
			flag = 0;
			if (((A == 0) && ((B == 1) || (C == 1) || (D == 1))))
			{
				a = 1;
			}
			if (((A == 0) && (B == 0) && (C == 1) && (D == 0)))
			{
				b = 1;
			}
			if (((A == 0) && (B == 0) && (C == 0) && (D == 1)))
			{
				c = 1;
			}
			if (((D == 0) && ((A == 1) || (B == 1) || (C == 1))))
			{
				d = 1;
			}
			flag = a + b + c + d;
			if (flag == 3)
			{
				push = i;
			}
			break;

			//方案2
		case 2:
			A = 0;
			B = 0;
			C = 1;
			D = 0;
			flag = 0;
			if (((A == 0) && ((B == 1) || (C == 1) || (D == 1))))
			{
				a = 1;
			}
			if (((A == 0) && (B == 0) && (C == 1) && (D == 0)))
			{
				b = 1;
			}
			if (((A == 0) && (B == 0) && (C == 0) && (D == 1)))
			{
				c = 1;
			}
			if (((D == 0) && ((A == 1) || (B == 1) || (C == 1))))
			{
				d = 1;
			}
			flag = a + b + c + d;
			if (flag == 3)
			{
				push = i;
			}
			break;

			//方案3
		case 3:
			A = 0;
			B = 0;
			C = 0;
			D = 1;
			flag = 0;
			if (((A == 0) && ((B == 1) || (C == 1) || (D == 1))))
			{
				a = 1;
			}
			if (((A == 0) && (B == 0) && (C == 1) && (D == 0)))
			{
				b = 1;
			}
			if (((A == 0) && (B == 0) && (C == 0) && (D == 1)))
			{
				c = 1;
			}
			if (((D == 0) && ((A == 1) || (B == 1) || (C == 1))))
			{
				d = 1;
			}
			flag = a + b + c + d;
			if (flag == 3)
			{
				push = i;
			}
			break;

		}
	}
	switch (push)
	{
	case 0:
		printf("A是凶手。\n");
		break;

	case 1:
		printf("B是凶手。\n");
		break;

	case 2:
		printf("C是凶手。\n");
		break;

	case 3:
		printf("D是凶手。\n");
		break;

}
	return 0;
}
#endif

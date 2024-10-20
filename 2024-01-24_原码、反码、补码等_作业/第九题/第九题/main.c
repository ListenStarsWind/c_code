#define _CRT_SECURE_NO_WARNINGS 
/******************************************************************************************
 * 【文件名称】：
 * 【文件标识】：
 * ===================================================================
 * 【当前作者】：	听风若依
 * 【当前版本】：	V1.0
 * 【完成日期】：	2024年  4月3日
 * ===================================================================
 * 【历史作者】：	听风若依
 * 【历史版本】：	V1.
 * 【历史日期】：	2024年
 * ===================================================================
 * 【开发平台】：	VS2022
 * 【程序内容】： 	写一个函数返回参数二进制中 1 的个数。用三种方法。
 *******************************************************************************************/
#include<stdio.h>
 //第一种方法：模拟人脑统计1的个数思路
 //注意计算机实际储存的是补码，这种人脑计算的是原码，
 //而只有正数原码等于补码，所以z只能是unsigned int 
int Cale1(unsigned int z)//calculate（计算）的缩写
{
	int count = 0;//计数
	while (z)
	{
		if (z % 2 == 1)
			count++;
		z = z / 2;
	}
	return count;
}

//第二种方法：还记得单片机进行串口通信怎么输数据吗？
//这里道理相同都是使用“&”按位与；
//定义一个32位比特的二进制串，其中只有一位为1，其它都是0，
//11111111111111111111111111111111 -1的补码
//00000000000000000000000000000001
//00000000000000000000000000000001 &后得到的二进制串
int Cale2(int z)
{
	int count = 0;
	int i = 0;
	for (i = 0; i < 32; i++)
	{
		if (z & (1 << i))
			count++;
	}
	return count;
}

//第三种方法：它甚至都不需要循环32次
//不过我可想不到
int Cale3(int z)
{
	int count = 0;
	//比如13的补码1101（前面28个0就不看了）减去1变成1100，
	// 按位与后变成1100,1100与1101相比不就少一个一吗？
	//再比如1100，减去1后变成1011，按位与后变成1000，
	//1000与1100相比也少一个1.
	//具体解释的话，可以二进制数分成两大部分，
	// 一部分是受到借位影响的部分，另一部风是不受到借位影响的部分，
	// 没受到借位影响的部分是相同的，按位与后还是它自身，
	// 原来有多少1按位与后还是有多少1；至于受到借位影响的部分，
	// 你想想为什么它要借位，因为都是0呀，只有遇到1，
	// 它的连续借位才能停止，比如说1011000减去1后变成1010111，
	// 101就是不受影响的部分，1000和0111就是受影响的部分，
	// 对于受影响的部分，最高位被借走了，变成了0，
	// 其他位原来就是0，按位与后全都变成0.
	while (z)
	{
		count++;
		z = z & (z - 1);
	}
	return count;
}

//测试函数功能
int main()
{
	int test = 0;
	scanf("%d", &test);
	int i = Cale1(test);
	int j = Cale2(test);
	int k = Cale3(test);
	printf("i = %d \nj = %d \nk = %d", i, j, k);
	return 0;
}
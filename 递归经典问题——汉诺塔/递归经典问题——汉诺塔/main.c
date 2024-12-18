#define _CRT_SECURE_NO_WARNINGS 
//汉诺塔是递归中的经典问题，在游戏原神珐露珊的邀约任务中也有涉及，其玩法是：给定3根柱子A, B, C，初始有n个圆环（记为1至n号，由小到大序）在A上，最终目标是通过若干步移动，将所有圆环都移动到B上，且移动的规则为：
//①1次移动只能1个圆环（且应当是A / B / C最上面的圆环）
//②始终要求小号圆环堆叠在大号圆环上（形如金字塔形，例如不能将2号圆环移动到1号圆环之上）
//关于思路，你看这个：作者：hh - 我想静静 https ://www.bilibili.com/read/cv22299760/ 出处：bilibili
#include<stdio.h>
int Faruzan(int n)//珐露珊外文名
{
	if (n >= 2)
		return 2 * Faruzan(n - 1) + 1;
	else
		return 1;
}

int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		printf("n=%d时，最少的移法有%d种。\n", n, Faruzan(n));
	}
	return 0;
}

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
//二维树状数组
int bitArr[1025][1025];
int s;

int lowbit(int k)
{
	return k & (-k);
}

void update()
{
	int x, y, a;
	scanf("%d%d%d", &x, &y, &a);
	for (int nx = x + 1; nx <= s; nx += lowbit(nx))
		for (int ny = y + 1; ny <= s; ny += lowbit(ny))
			bitArr[nx][ny] += a;
	return;
}

int getSum(int x, int y)
{
	int sum = 0;
	for (int nx = x; nx > 0; nx = nx - lowbit(nx))
		for (int ny = y; ny > 0; ny = ny - lowbit(ny))
			sum += bitArr[nx][ny];
	return sum;
}

void query()
{
	int l, b, r, t;
	scanf("%d%d%d%d", &l, &b, &r, &t);
	printf("%d\n", getSum(r + 1, t + 1) + getSum(l, b) - getSum(l, t + 1) - getSum(r + 1, b) );
	return;
}

int main()
{
	int command;
	scanf("%d%d", &command, &s);
	memset(bitArr, 0, sizeof(bitArr));
	while (scanf("%d", &command))
	{
		if (command == 1)
			update();
		else if (command == 2)
			query();
		else
			break;
	}
	return 0;
}
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
//树状数组
class star//定义star类用来存储
{
public:
	int x, y;
	star(int x, int y) : x(x), y(y) {}
	star() {}
} stars[15005];

int Arr[32010], level[15005];//Arr为树状数组，level[i]为leve是i的星星个数
int n, theEnd;


int lowbit(int k)
{
	return k & (-k);
}

void update(int k)
{
	for (int i = k; i <= theEnd; i += lowbit(i))
		Arr[i] += 1;
	return;
}

int sum(int k)
{
	int ans = 0;
	for (int i = k; i > 0; i -= lowbit(i))
		ans += Arr[i];
	return ans;
}

int main()
{
	int x, y;
	scanf("%d", &n);
	theEnd = 0;
	for (int i = 0; i < n; ++i)
	{
		scanf("%d%d", &x, &y);
		theEnd = max(theEnd, x + 1);//找到最大的x值，x+1因为x可能为0
		stars[i] = star(x + 1, y);
	}
	int cnt_star;//存得到的sum
	for (int i = 0; i < n; ++i)
	{
		cnt_star = sum(stars[i].x);
		update(stars[i].x);
		++level[cnt_star];
	}
	for (int i = 0; i < n; ++i) //输出函数
	{
		printf("%d\n", level[i]);
	}
	return 0;
}
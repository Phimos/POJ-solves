#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
//树状数组
class cow//定义奶牛类
{
public:
	int s, e, num;
	cow() {}
	cow(int s, int e, int num) : s(s), e(e), num(num) {}
	bool operator<(const cow& b)const//用于排序，e最大的排在最前，e同样的s小的在前。
	{
		if (e != b.e)
			return e > b.e;
		else
			return s < b.s;
	}
	bool operator==(const cow& b)const
	{
		return s == b.s && e == b.e;
	}
} cows[100005];
int n;
int Arr[100005], ans[100005];//Arr数组为树状数组，ans为存储答案
int theEnd;//这是e的最大值，用来限定update的边界

int lowbit(int x)
{
	return x & (-x);
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
	while (scanf("%d", &n), n)
	{
		int s, e;
		memset(Arr, 0, n * sizeof(int));//初始化
		for (int i = 0; i < n; ++i)
		{
			scanf("%d%d", &s, &e);
			cows[i] = cow(s + 1, e + 1, i);
		}
		sort(cows, cows + n);//排序，从而摆脱e的限制，只需要考虑s
		theEnd = cows[0].e;
		ans[cows[0].num] = 0;
		update(cows[0].s);
		for (int i = 1; i < n; ++i)
		{
			if (cows[i] == cows[i - 1])	//若相同则结果一样
				ans[cows[i].num] = ans[cows[i - 1].num];
			else						//否则计算sum
				ans[cows[i].num] = sum(cows[i].s);
			update(cows[i].s);	//无论是否一样均需要将其加入更新
		}
		printf("%d", ans[0]);//输出部分
		for (int i = 1; i < n; ++i)
			printf(" %d", ans[i]);
		printf("\n");
	}
}
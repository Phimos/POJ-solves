#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
//树状数组
int n, m, k, t;
long long Arr[1010];
struct HighWay//定义结构
{
	int east, west;
	HighWay(int e, int w) : east(e), west(w) {}
	HighWay() {}
	bool operator<(const HighWay& b)const
	{
		if (east != b.east)
			return east > b.east;
		else
			return west > b.west;
	}
} HighWays[1000100];	//k暴大，巨坑

int lowbit(int x)
{
	return x & (-x);
}

void update(int k)
{
	for (int i = k; i <= m; i += lowbit(i))
		++Arr[i];
	return;
}

long long  getSum(int k)
{
	long long ans = 0;
	for (int i = k; i > 0; i -= lowbit(i))
		ans += Arr[i];
	return ans;
}

int main()
{
	scanf("%d", &t);
	for (int it = 1; it <= t; ++it)
	{
		scanf("%d%d%d", &n, &m, &k);
		memset(Arr, 0, sizeof(Arr));
		for (int i = 0; i < k; ++i)
			scanf("%d%d", &HighWays[i].east, &HighWays[i].west);
		sort(HighWays, HighWays + k);
		long long res = 0;
		for (int i = 0; i < k; ++i)
		{
			res += getSum(HighWays[i].west - 1);
			update(HighWays[i].west);
		}
		printf("Test case %d: %lld\n", it, res);
	}
	return 0;
}
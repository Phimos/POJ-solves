#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
//树状数组
#define maxn 20010
int n;
int arr[maxn];
struct player
{
	int skill, pos;
	bool operator<(const player& b)const
	{
		return skill < b.skill;
	}
} players[maxn];
int LeftLower[maxn], LeftHigher[maxn];
int RightLower[maxn], RightHigher[maxn];

int lowbit(int x)
{
	return x & (-x);
}
void update(int k)
{
	for (int i = k; i <= n; i += lowbit(i))
		arr[i] += 1;
	return;
}
int getSum(int k)
{
	int ans = 0;
	for (int i = k; i > 0; i -= lowbit(i))
		ans += arr[i];
	return ans;
}

int main()
{
	int testCase;
	scanf("%d", &testCase);
	while (testCase--)
	{
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", &players[i].skill);
			players[i].pos = i;
		}
		sort(players + 1, players + n + 1);
		memset(arr, 0, sizeof(int) * (n + 1));
		for (int i = 1; i <= n; ++i)
		{
			int k = players[i].pos;
			LeftLower[k] = getSum(k);
			RightLower[k] = i - 1 - LeftLower[k];
			update(k);
		}
		memset(arr, 0, sizeof(int) * (n + 1));
		for (int i = n; i > 0; --i)
		{
			int k = players[i].pos;
			LeftHigher[k] = getSum(k);
			RightHigher[k] = n - i - LeftHigher[k];
			update(k);
		}
		long long ans = 0;
		for (int i = 1; i <= n; ++i)
			ans += LeftHigher[i] * RightLower[i] + LeftLower[i] * RightHigher[i];
		printf("%lld\n", ans);
	}
}
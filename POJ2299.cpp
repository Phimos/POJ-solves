#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
//树状数组
#define maxn 500010
int n;
int arr[maxn];
struct node
{
	int val, pos;
	bool operator<(const node& b)const
	{
		if (val != b.val)
			return val > b.val;
		else
			return pos < b.pos;
	}
} nums[maxn];
int lowbit(int k)
{
	return k & (-k);
}
void update(int k)
{
	for (int i = k; i <= n; i += lowbit(i))
		arr[i] += 1;
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
	while (scanf("%d", &n), n)
	{
		memset(arr, 0, sizeof(int) * (n + 1));
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", &nums[i].val);
			nums[i].pos = i;
		}
		sort(nums + 1, nums + n + 1);
		long long ans = 0;
		for (int i = 1; i <= n; ++i)
		{
			ans += getSum(nums[i].pos);
			update(nums[i].pos);
		}
		printf("%lld\n", ans);
	}
}
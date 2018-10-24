#include<iostream>
#include<vector>
#include<functional>
#include<cstring>
#include<algorithm>
using namespace std;
//dfs+剪枝
int n, nums[64];
int maxLen, sumLen;
bool used[64];

bool dfs(int k, int sum, int oriLen, bool start) //k-th start,sum_len
{
	if (sum == oriLen)
	{
		for (int i = 0; i < n; ++i)
		{
			if (!used[i])
				return dfs(i, 0, oriLen, true);
		}
		return true;
	}
	for (int i = k; i < n; ++i)
	{
		if (!used[i] && sum + nums[i] <= oriLen)//没用过的棍子，且可用
		{
			if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1])//前面已经有这个长度的棍子没法用了，剪枝
				continue;
			used[i] = true;
			sum += nums[i];
			if (dfs(i + 1, sum, oriLen, false))
				return true;
			used[i] = false;
			sum -= nums[i];
		}
		if (start)	//这是第一根棍子，必须要匹配，剪枝
			return false;
	}
	return false;
}

int main()
{
	while (scanf("%d", &n), n)
	{
		sumLen = maxLen = 0;
		memset(used, 0, sizeof(used));
		memset(nums, 0, sizeof(nums));
		for (int i = 0; i < n; ++i)
		{
			scanf("%d", nums + i);
			sumLen += nums[i];
		}
		sort(nums, nums + n, greater<int>());
		maxLen = nums[0];
		for (int i = maxLen; i <= sumLen; ++i)
		{
			if ((sumLen % i == 0) && dfs(0, 0, i, true))//需要至少整除，剪枝
			{
				printf("%d\n", i);
				break;
			}
		}
	}
}
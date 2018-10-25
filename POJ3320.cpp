#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;
//尺度法+Hash
#define maxn 1000010
map<int, int> Hash, temp;
int nums[maxn];
int n, ans = 0x7fffffff;
int main()
{
	scanf("%d", &n);
	int num;
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", nums + i);
		++Hash[nums[i]];
	}
	int l = 0, r = 0;
	for (; r < n; ++r)
	{
		++temp[nums[r]];
		while (temp.size() == Hash.size())
		{
			ans = min(ans, r - l + 1);
			--temp[nums[l]];
			if (temp[nums[l]] == 0)
				temp.erase(nums[l]);
			++l;
		}
	}
	printf("%d\n", ans);
}
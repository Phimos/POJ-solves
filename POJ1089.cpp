#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
//贪心
#define maxn 50010
int n;
struct Interval
{
	int l, r;
	bool operator<(const Interval& b)const
	{
		if (l != b.l)
			return l < b.l;
		else
			return r < b.r;
	}
} intervals[maxn];

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d%d", &intervals[i].l, &intervals[i].r);
	sort(intervals, intervals + n);
	vector<Interval> temp;
	for (int i = 0; i < n; ++i)
	{
		if (!temp.empty() && temp.back().r >= intervals[i].l)
			temp.back().r = max(temp.back().r, intervals[i].r);
		else
			temp.push_back(intervals[i]);
	}
	for (int i = 0; i < temp.size(); ++i)
		printf("%d %d\n", temp[i].l, temp[i].r);
	return 0;
}
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
//并查集
class product
{
public:
	int profit, ddl;
	bool operator<(const product b)const
	{
		return profit > b.profit;
	}
};

product goods[10005];
int date[10005];

int findDate(int k)
{
	if (date[k] == -1)
		return date[k] = k;
	return k == date[k] ? k : date[k] = findDate(date[k]);
}

int main()
{
	int n;
	while (~scanf("%d", &n))
	{
		for (int i = 0; i < n; ++i)
		{
			scanf("%d%d", &goods[i].profit, &goods[i].ddl);
		}
		memset(date, -1, sizeof(date));
		sort(goods, goods + n);
		int sum = 0;

		for (int i = 0; i < n; ++i)
		{
			int TimePoint = findDate(goods[i].ddl);//利用并查集找卖出的时间点（靠后）
			if (TimePoint)
			{
				sum += goods[i].profit;
				date[TimePoint] = TimePoint - 1;
			}
		}
		printf("%d\n", sum );
	}
	return 0;
}
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
//水题
#define maxn 1010
double scores[maxn];

int main()
{
	int testCases;
	cin >> testCases;
	while (testCases--)
	{
		double percent;
		double sum = 0, avg;
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			cin >> scores[i];
			sum += scores[i];
		}
		avg = sum / n;
		sort(scores, scores + n);
		printf("%.3lf%%\n", (double((n - (upper_bound(scores, scores + n, avg) - scores)))) * 100 / n);
	}
}
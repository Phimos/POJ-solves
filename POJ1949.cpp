#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//dp
#define maxn 10010

int longest[maxn], shortest[maxn];
vector<int> pre_work[maxn];
int chore_time[maxn];
int n, p;
int main()
{
	cin >> n;
	int k, t;
	for (int i = 1; i <= n; ++i)
	{
		cin >> chore_time[i] >> k;
		for (int j = 1; j <= k; ++j)
		{
			cin >> t;
			pre_work[i].push_back(t);
		}
	}
	shortest[1] = chore_time[1];
	for (int i = 2; i <= n; ++i)
	{
		for (int j = 0; j < pre_work[i].size(); ++j)
		{
			shortest[i] = max(shortest[i], shortest[pre_work[i][j]]);
		}
		shortest[i] += chore_time[i];
	}
	int sum = 0;
	for (int i = 1; i <= n; ++i)
	{
		sum = max(sum, shortest[i]);
	}
	cout << sum << endl;
}
#include<iostream>
#include<algorithm>
//动态规划
using namespace std;

int triangle[101][101];
int dp[101];

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j <= i; ++j)
			cin >> triangle[i][j];
	}
	for (int i = 0; i < n; ++i)
		dp[i] = triangle[n - 1][i];
	for (int i = n - 2; i >= 0; --i)
	{
		for (int j = 0; j <= i; ++j)
		{
			dp[j] = max(dp[j], dp[j + 1]) + triangle[i][j];
		}
	}
	cout << dp[0] << endl;
}
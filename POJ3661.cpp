#include<iostream>
#include<algorithm>
using namespace std;
//DP
int dp[10005][505];
int n, m;
int main()
{
	cin >> n >> m;
	int d;
	for (int i = 0; i < n; ++i)
	{
		cin >> d;
		for (int j = 0; j <= m; ++j)
		{
			if (j == 0 || dp[i][j])
			{
				if (j == 0)
					dp[i + 1][0] = max(dp[i][0], dp[i + 1][0]);
				if (i + j <= n)
					dp[i + j][0] = max(dp[i + j][0], dp[i][j]);
				if (j < m)
					dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + d);
			}
		}
	}
	cout << dp[n][0] << endl;
}
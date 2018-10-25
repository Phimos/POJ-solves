#include<iostream>
#include<algorithm>
using namespace std;
//动态规划+水题
int n;
int cows[360][360];
int sum[360];

int main()
{
	cin >> n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j <= i; ++j)
			cin >> cows[i][j];
	for (int i = 0; i < n; ++i)
		sum[i] = cows[n - 1][i];
	for (int i = n - 2; i >= 0; --i)
		for (int j = 0; j <= i; ++j)
			sum[j] = cows[i][j] + max(sum[j], sum[j + 1]);
	cout << sum[0] << endl;
}
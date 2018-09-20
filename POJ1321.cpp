#include<iostream>
using namespace std;

int n, k, res;
char board[10][10];
bool col[8];

void solve(int r, int cnt)
{
	if (cnt == k) //找到了一种解答
	{
		++res;
		return;
	}
	if (k - cnt > n - r) //剩下的行数少于需要摆放的棋子数目
		return;
	for (int j = 0; j < n; ++j)
	{
		if (board[r][j] == '#' && !col[j])
		{
			col[j] = true;
			solve(r + 1, cnt + 1);
			col[j] = false;
		}
	}
	solve(r + 1, cnt);
	return;
}

int main()
{
	while (cin >> n >> k)
	{
		if (n == -1 && k == -1)
			break;
		res = 0;
		for (int i = 0; i < n; ++i)
		{
			cin >> board[i];
			col[i] = false;
		}
		solve(0, 0);
		cout << res << endl;
	}
	return 0;
}
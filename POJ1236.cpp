#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;
#define maxn 120

int dfn[maxn], low[maxn];
int idx, colorcnt, color[maxn];
bool net[maxn][maxn];
bool vis[maxn];
int indeg[maxn], outdeg[maxn];
int n;
stack<int> snodes;

void tarjan(int u)
{
	dfn[u] = low[u] = ++idx;
	snodes.push(u);
	vis[u] = true;
	for (int v = 1; v <= n; ++v)
	{
		if (net[u][v])
		{
			if (!dfn[v])
			{
				tarjan(v);
				low[u] = min(low[u], low[v]);
			}
			else if (vis[v])
			{
				low[u] = min(low[u], dfn[v]);
			}
		}
	}
	if (dfn[u] == low[u])
	{
		++colorcnt;
		int v;
		do {
			v = snodes.top();
			snodes.pop();
			color[v] = colorcnt;
			vis[v] = false;
		} while (v != u);
	}
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		int t;
		while (cin >> t, t)
			net[i][t] = 1;
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i])
			tarjan(i);
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			if (net[i][j] && color[i] != color[j])
			{
				++indeg[color[j]];
				++outdeg[color[i]];
			}
		}
	}
	int noin = 0, noout = 0;
	for (int i = 1; i <= colorcnt; ++i)
	{
		if (indeg[i] == 0)
			++noin;
		if (outdeg[i] == 0)
			++noout;
	}
	cout << noin << endl;
	cout << ((colorcnt == 1) ? 0 : max(noin, noout)) << endl;
}
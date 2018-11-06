#include<iostream>
#include<cstdio>
#include<stack>
#include<algorithm>
#include<vector>
using namespace std;
#define maxn 10010
//tarjan+缩点
int n, m;
vector<int> relation[maxn];
vector<vector<int>> oldGraph;
int dfn[maxn], low[maxn];
int vis[maxn], color[maxn];
int index;
stack<int> cows;

void tarjan(int u)
{
	dfn[u] = low[u] = ++index;
	cows.push(u);
	vis[u] = 1;
	for (int i = 0; i < relation[u].size(); ++i)
	{
		int v = relation[u][i];
		if (vis[v] == 0)
		{
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (vis[v] == 1)
		{
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u])
	{
		vector<int> temp;
		int k = oldGraph.size();
		do
		{
			temp.push_back(cows.top());
			color[cows.top()] = k;
			cows.pop();
		} while (temp.back() != u);
		oldGraph.push_back(temp);
	}
	vis[u] = 2;
}

int main()
{
	scanf("%d%d", &n, &m);
	int a, b;
	for (int i = 0; i < m; ++i)
	{
		scanf("%d%d", &a, &b);
		relation[a].push_back(b);
	}
	for (int i = 1; i <= n; ++i)
	{
		if (!vis[i])
		{
			tarjan(i);
		}
	}
	vector<int> theEnd;
	for (int i = 0; i < oldGraph.size(); ++i)
	{
		bool outExist = false;
		for (int j = 0; j < oldGraph[i].size(); ++j)
		{
			int u = oldGraph[i][j];
			for (int k = 0; k < relation[u].size(); ++k)
			{
				int v = relation[u][k];
				if (color[u] != color[v])
				{
					outExist = true;
					goto mark1;
				}
			}
		}
mark1:
		if (!outExist)
		{
			theEnd.push_back(i);
		}
	}
	int ans = 0;
	if (theEnd.size() == 1)
		ans = oldGraph[theEnd[0]].size();
	printf("%d\n", ans);
}
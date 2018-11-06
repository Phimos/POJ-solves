#include<iostream>
#include<cstdio>
#include<stack>
#include<vector>
#include<algorithm>
#include<cstring>
#include<set>
#include<queue>
using namespace std;
#define maxn 1010
//tarjan+缩点+拓扑排序
vector<int> corridors[maxn];
set<int> newGraph[maxn];
int n, m;
int id;
int dfn[maxn], vis[maxn], low[maxn];
int In[maxn];
stack<int> corridorStack;
vector<vector<int>> ans;
int color[maxn];

void init()
{
	id = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(vis, 0, sizeof(vis));
	memset(low, 0, sizeof(low));
	memset(color, 0, sizeof(color));
	memset(In, 0, sizeof(In));
	ans.clear();
	for (int i = 0; i <= n; ++i)
	{
		corridors[i].clear();
		newGraph[i].clear();
	}
}
void tarjan(int u)
{
	dfn[u] = low[u] = ++id;
	vis[u] = 1;
	corridorStack.push(u);
	for (int i = 0; i < corridors[u].size(); ++i)
	{
		int v = corridors[u][i];
		if (!vis[v])
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
		int k = ans.size();
		do
		{
			temp.push_back(corridorStack.top());
			color[temp.back()] = k;
			corridorStack.pop();
		} while (temp.back() != u);
		ans.push_back(temp);
	}
	vis[u] = 2;
}

void buildNewGraph()
{
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 0; j < corridors[i].size(); ++j)
		{
			int v = corridors[i][j];
			if (color[i] != color[v])
			{
				++In[color[v]];
				newGraph[color[i]].insert(color[v]);
			}
		}
	}
}

bool check()
{
	int k = ans.size();
	queue<int> qnodes;
	for (int i = 0; i < k; ++i)
	{
		if (In[i] == 0)
			qnodes.push(i);
	}
	while (!qnodes.empty())
	{
		if (qnodes.size() > 1)
			return false;
		int temp = qnodes.front();
		qnodes.pop();
		for (set<int>::iterator i = newGraph[temp].begin(); i != newGraph[temp].end(); ++i)
		{
			--In[*i];
			if (In[*i] == 0)
				qnodes.push(*i);
		}
	}
	return true;
}

int main()
{
	int caseNum;
	scanf("%d", &caseNum);
	while (caseNum--)
	{
		scanf("%d%d", &n, &m);
		init();
		int a, b;
		for (int i = 0; i < m; ++i)
		{
			scanf("%d%d", &a, &b);
			corridors[a].push_back(b);
		}
		for (int i = 1; i <= n; ++i)
			if (!vis[i])
				tarjan(i);
		buildNewGraph();
		if (check())
			printf("Yes\n");
		else
			printf("No\n");
	}
}
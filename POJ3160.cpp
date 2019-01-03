#include<iostream>
#include<algorithm>
#include<stack>
#include<queue>
using namespace std;
#define maxn 30010
#define maxm 150010

struct Edge
{
	int u, v, next;
	Edge(int u, int v, int next) : u(u), v(v), next(next) {}
	Edge() {}
} edges[maxm];
int edgecnt, colorcnt, idx;
int n, m;
int dfn[maxn], low[maxn];
bool vis[maxn];
int color[maxn];
int head[maxn];
int comfort[maxn], comfort_all[maxn], dp[maxn];
stack<int> snodes;

void init()
{
	edgecnt = colorcnt = idx = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(vis, 0, sizeof(vis));
	memset(color, 0, sizeof(color));
	memset(dp, 0, sizeof(dp));
	memset(comfort_all, 0, sizeof(comfort_all));
	fill(head, head + maxn, -1);
}

void addedge(int u, int v)
{
	edges[edgecnt] = Edge(u, v, head[u]);
	head[u] = edgecnt++;
}

void tarjan(int u)
{
	dfn[u] = low[u] = ++idx;
	snodes.push(u);
	vis[u] = true;
	for (int i = head[u]; i != -1; i = edges[i].next)
	{
		int v = edges[i].v;
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
	if (low[u] == dfn[u])
	{
		int v;
		++colorcnt;
		do
		{
			v = snodes.top();
			snodes.pop();
			color[v] = colorcnt;
			vis[v] = false;
			if (comfort[v] > 0)
				comfort_all[colorcnt] += comfort[v];
		} while (u != v);
	}
}

void rebuild()
{
	edgecnt = 0;
	fill(head, head + maxn, -1);
	for (int i = 0; i < m; ++i)
	{
		int u = edges[i].u, v = edges[i].v;
		if (color[u] != color[v])
		{
			addedge(color[u], color[v]);
		}
	}
}

int solve(int u)
{
	if (vis[u])
		return dp[u];
	vis[u] = true;
	int maxcomfort = 0;
	for (int i = head[u]; i != -1; i = edges[i].next)
	{
		int v = edges[i].v;
		maxcomfort = max(maxcomfort, solve(v));
	}

	return dp[u] = maxcomfort + comfort_all[u];
}

int main()
{
	while (cin >> n >> m)
	{
		int u, v;
		init();
		for (int i = 0; i < n; ++i)
		{
			cin >> comfort[i];
		}
		for (int i = 0; i < m; ++i)
		{
			cin >> u >> v;
			addedge(u, v);
		}
		for (int i = 0; i < n; ++i)
			if (!dfn[i])
				tarjan(i);
		rebuild();
		int ans = 0;
		memset(vis, 0, sizeof(vis));
		for (int i = 1; i <= colorcnt; ++i)
			ans = max(ans, solve(i));
		cout << ans << endl;
	}
}
#include<iostream>
#include<cstring>
#include<algorithm>
#include<stack>
#include<vector>
using namespace std;
#define maxn 5010
#define maxm 100010
//tarjan+缩点
int dfn[maxn], low[maxn];
bool vis[maxn];
int color[maxn];
int head[maxn];
int outdeg[maxn];
int idx, edgecnt, colorcnt;
int n, m;
stack<int> snodes;
struct Edge
{
	int u, v, next;
	Edge(int u, int v, int next) : u(u), v(v), next(next) {}
	Edge() {}
} edges[maxm];

void init()
{
	fill(head, head + maxn, -1);
	idx = edgecnt = colorcnt = 0;
	memset(outdeg, 0, sizeof(outdeg));
	memset(color, 0, sizeof(color));
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
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
	if (dfn[u] == low[u])
	{
		int v;
		++colorcnt;
		do {
			v = snodes.top();
			snodes.pop();
			color[v] = colorcnt;
			vis[v] = false;
		} while (u != v);
	}
}

void rebuild()
{
	edgecnt = 0;
	for (int i = 0; i < m; ++i)
	{
		int u = edges[i].u, v = edges[i].v;
		if (color[u] != color[v])
		{
			addedge(color[u], color[v]);
			++outdeg[color[u]];
		}
	}
}

void printans()
{
	vector<int> ans;
	for (int i = 1; i <= colorcnt; ++i)
		if (outdeg[i] == 0)
			for (int j = 1; j <= n; ++j)
				if (color[j] == i)
					ans.push_back(j);
	sort(ans.begin(), ans.end());
	cout << ans[0];
	for (int i = 1; i < ans.size(); ++i)
		cout << ' ' << ans[i];
	cout << endl;
}


int main()
{
	while (cin >> n, n)
	{
		init();
		cin >> m;
		int u, v;
		for (int i = 0; i < m; ++i)
		{
			cin >> u >> v;
			addedge(u, v);
		}
		for (int i = 1; i <= n; ++i)
			if (!dfn[i])
				tarjan(i);
		rebuild();
		printans();
	}
}
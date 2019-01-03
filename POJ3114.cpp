#include<iostream>
#include<queue>
#include<vector>
#include<cstdio>
#include<functional>
#include<algorithm>
#include<stack>
using namespace std;
#define maxn 2008
#define maxm 300008

int dfn[maxn], low[maxn];
int head[maxn], color[maxn];
int dist[maxn];
bool vis[maxn];
int edgecnt, idx, colorcnt;
stack<int> snodes;
int n, m, t;

struct Edge
{
	int u, v, w, next;
	Edge(int u, int v, int w, int next) :
		u(u), v(v), w(w), next(next) {}
	Edge() {}
} edges[maxm];

void addedge(int u, int v, int w)
{
	edges[edgecnt] = Edge(u, v, w, head[u]);
	head[u] = edgecnt++;
}

void init()
{
	edgecnt = colorcnt = idx = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	memset(color, 0, sizeof(color));
	fill(head, head + maxn, -1);
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
			vis[v] = false;
			color[v] = colorcnt;
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
			addedge(color[u], color[v], edges[i].w);
	}
}

int dijkstra(int s, int t)
{
	if (color[s] == color[t])
		return 0;
	memset(dist, 0x3f, sizeof(dist));
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > qnodes;
	qnodes.push(make_pair(0, color[s]));
	dist[color[s]] = 0;
	while (!qnodes.empty())
	{
		pair<int, int> temp = qnodes.top();
		qnodes.pop();
		int u = temp.second;
		if (temp.first != dist[u])
			continue;
		for (int i = head[u]; i != -1; i = edges[i].next)
		{
			int v = edges[i].v;
			if (dist[v] > dist[u] + edges[i].w)
			{
				dist[v] = dist[u] + edges[i].w;
				qnodes.push(make_pair(dist[v], v));
			}
		}
	}
	return dist[color[t]];
}

int main()
{
	while (scanf("%d", &n), n)
	{
		scanf("%d", &m);
		init();
		int u, v, w, ans;
		for (int i = 0; i < m; ++i)
		{
			scanf("%d%d%d", &u, &v, &w);
			addedge(u, v, w);
		}
		for (int i = 1; i <= n; ++i)
			if (!dfn[i])
				tarjan(i);
		rebuild();
		scanf("%d", &t);
		for (int i = 0; i < t; ++i)
		{
			scanf("%d%d", &u, &v);
			ans = dijkstra(u, v);
			if (ans == 0x3f3f3f3f)
				cout << "Nao e possivel entregar a carta" << endl;
			else
				cout << ans << endl;
		}
		cout << endl;
	}
}
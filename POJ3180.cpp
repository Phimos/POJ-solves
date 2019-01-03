#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;
#define maxn 10010
#define maxm 50010
//tarjan找大于1的强联通分量
struct Edge
{
	int u, v, next;
	Edge(int u, int v, int next) : u(u), v(v), next(next) {};
	Edge() {}
} edges[maxm];
int dfn[maxn], low[maxn];
bool vis[maxn];
int head[maxn];
stack<int>snodes;
int edgecnt, cnt, idx;
int n, m;

void addEdge(int u, int v)
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
			low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u])
	{
		if (u != snodes.top())
			++cnt;
		int v;
		do {
			v = snodes.top();
			snodes.pop();
			vis[v] = false;
		} while (v != u);
	}
}

int main()
{
	cin >> n >> m;
	int u, v;
	fill(head, head + maxn, -1);
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v;
		addEdge(u, v);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i])
			tarjan(i);
	cout << cnt << endl;
}
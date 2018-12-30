#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
#define maxn 500
//Dinic 二部图匹配
struct Edge
{
	int u, v, capacity, flow;
	Edge(int u, int v, int capacity, int flow) :
		u(u), v(v), capacity(capacity), flow(flow) {}
	Edge() {}
};

vector<Edge> edges;
int degree[maxn], cur[maxn];
bool vis[maxn];
vector<int> graph[maxn];
int n, m, s, t;

void addEdge(int u, int v, int cap)
{
	graph[u].push_back(edges.size());
	edges.push_back(Edge(u, v, cap, 0));
	graph[v].push_back(edges.size());
	edges.push_back(Edge(v, u, 0, 0));
}

bool bfs()
{
	memset(vis, 0, sizeof(vis));
	vis[s] = true;
	degree[s] = 0;
	queue<int> travel;
	travel.push(s);
	while (!travel.empty())
	{
		int u = travel.front();
		travel.pop();
		for (int i = 0; i < graph[u].size(); ++i)
		{
			Edge& temp = edges[graph[u][i]];
			if (!vis[temp.v] && temp.capacity > temp.flow)
			{
				vis[temp.v] = true;
				degree[temp.v] = degree[u] + 1;
				travel.push(temp.v);
			}
		}
	}
	return vis[t];
}

int dfs(int u, int inflow)
{
	if (u == t || inflow == 0)
		return inflow;
	int flow = 0, f;
	for (int& i = cur[u]; i < graph[u].size(); ++i)
	{
		Edge& temp = edges[graph[u][i]];
		if (degree[temp.v] == degree[u] + 1 && (f = dfs(temp.v, min(inflow, temp.capacity - temp.flow))) > 0)
		{
			flow += f;
			inflow -= f;
			temp.flow += f;
			edges[graph[u][i] ^ 1].flow -= f;
		}
		if (!inflow)
			break;
	}
	return flow;
}

int maxflow()
{
	int flow = 0;
	while (bfs())
	{
		memset(cur, 0, sizeof(cur));
		flow += dfs(s, 0x7fffffff);
	}
	return flow;
}

void init()
{
	for (int i = 0; i < maxn; ++i)
		graph[i].clear();
	edges.clear();
}

int main()
{
	while (cin >> n >> m)
	{
		init();
		s = 0, t = n + m + 1;
		for (int i = 1; i <= n; ++i)
		{
			int s, k;
			cin >> s;
			for (int j = 0; j < s; ++j)
			{
				cin >> k;
				addEdge(i, n + k, 0x7fffffff);
			}
		}
		for (int i = 1; i <= n; ++i)
			addEdge(s, i, 1);
		for (int i = n + 1; i <= n + m; ++i)
			addEdge(i, t, 1);
		cout << maxflow() << endl;
	}
}
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
#define maxn 210
//MaxFlow
//Dinic
struct Edge
{
	int u, v, capacity, flow;
	Edge(int u, int v, int capacity, int flow) :
		u(u), v(v), capacity(capacity), flow(flow) {}
};
vector<Edge> edges;
vector<int> graph[maxn];
bool vis[maxn];
int cur[maxn];
int degree[maxn];
int n, m;
int s, t;

bool bfs()
{
	memset(vis, 0, sizeof(vis));
	queue<int> travel;
	travel.push(1);
	degree[1] = 0;
	vis[1] = true;
	while (!travel.empty())
	{
		int from = travel.front();
		travel.pop();
		for (int i = 0; i < graph[from].size(); ++i)
		{
			Edge& temp = edges[graph[from][i]];
			if (!vis[temp.v] && temp.capacity > temp.flow)
			{
				vis[temp.v] = true;
				degree[temp.v] = degree[from] + 1;
				travel.push(temp.v);
			}
		}
	}
	return vis[m];
}

int dfs(int from, int inFlow)
{
	if (from == m || inFlow == 0)
		return inFlow;
	int flow = 0, f;
	for (int& i = cur[from]; i < graph[from].size(); ++i)
	{
		Edge& temp = edges[graph[from][i]];
		if (degree[from] + 1 == degree[temp.v] && (f = dfs(temp.v, min(inFlow, temp.capacity - temp.flow))) > 0)
		{
			inFlow -= f;
			flow += f;
			temp.flow += f;
			edges[graph[from][i] ^ 1].flow -= f;
			if (!inFlow)
				break;
		}
	}
	return flow;
}

int MaxFlow()
{
	int flow = 0;
	while (bfs())
	{
		memset(cur, 0, sizeof(cur));
		flow += dfs(1, 0x7fffffff);
	}
	return flow;
}

void init()
{
	edges.clear();
	for (int i = 1; i <= m; ++i)
		graph[i].clear();
	return;
}

int main()
{
	while (cin >> n >> m)
	{
		init();
		for (int i = 0; i < n; ++i)
		{
			int u, v, cap;
			cin >> u >> v >> cap;
			edges.push_back(Edge(u, v, cap, 0));
			edges.push_back(Edge(v, u, 0, 0));
			graph[u].push_back(i << 1);
			graph[v].push_back(i << 1 | 1);
		}
		cout << MaxFlow() << endl;
	}
}

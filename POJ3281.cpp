#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
#define maxn 500

//拆点+dinic
struct Edge
{
	int u, v, capacity, flow;
	Edge(int u, int v, int capacity, int flow) :
		u(u), v(v), capacity(capacity), flow(flow) {}
};

vector<Edge> edges;
vector<int>  graph[maxn];

int degree[maxn], cur[maxn];
bool vis[maxn];

int N, F, D;
int s, t;


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
		if (degree[temp.v] == degree[u] + 1 && (f = (dfs(temp.v, min(inflow, temp.capacity - temp.flow))) > 0))
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

void addEdge(int u, int v, int capacity)
{
	edges.push_back(Edge(u, v, capacity, 0));
	edges.push_back(Edge(v, u, 0, 0));
	int m = edges.size() - 1;
	graph[u].push_back(m - 1);
	graph[v].push_back(m);
}


int main()
{
	cin >> N >> F >> D;
	s = (N << 1) + F + D;
	t = s + 1;
	for (int i = 0; i < F; ++i)
		addEdge(s, (N << 1) + i, 1);
	for (int i = 0; i < D; ++i)
		addEdge((N << 1) + F + i, t, 1);
	for (int i = 0; i < N; ++i)
	{
		int fn, dn, f, d;
		cin >> fn >> dn;
		addEdge(i << 1, i << 1 | 1, 1);
		for (int j = 0; j < fn; ++j)
		{
			cin >> f;
			addEdge(2 * N + f - 1, i << 1, 0x7fffffff);
		}
		for (int j = 0; j < dn; ++j)
		{
			cin >> d;
			addEdge(i << 1 | 1, 2 * N + F + d - 1, 0x7fffffff);
		}
	}
	cout << maxflow() << endl;
}
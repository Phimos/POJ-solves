#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
#define maxn 250
#define inf 0x0fffffff
struct Edge
{
	int u, v, capacity, flow;
	Edge(int u, int v, int capacity, int flow) :
		u(u), v(v), capacity(capacity), flow(flow) {}
};

vector<Edge> edges;
vector<int> graph[maxn];
int degree[maxn], cur[maxn];
bool vis[maxn];

int k, c, m, n;
int dist[maxn][maxn];
int s, t;

void Floyd()
{
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

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
			inflow -= f;
			flow += f;
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

void buildGraph(int cost)
{
	for (int i = 0; i <= n + 1; ++i)
		graph[i].clear();
	edges.clear();
	for (int i = k + 1; i <= n; ++i)
		addEdge(0, i, 1);
	for (int i = 1; i <= k; ++i)
		addEdge(i, t, m);
	for (int i = k + 1; i <= n; ++i)
		for (int j = 1; j <= k; ++j)
			if (dist[i][j] <= cost)
				addEdge(i, j, 0x7fffffff);
}

int main()
{
	cin >> k >> c >> m;
	n = k + c;
	s = 0, t = k + c + 1;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
		{
			cin >> dist[i][j];
			if (!dist[i][j])
				dist[i][j] = inf;
		}
	Floyd();
	int low = 0, high = 40000;
	while (low < high)
	{
		int mid = (low + high) >> 1;
		buildGraph(mid);
		int Mflow = maxflow();
		if (Mflow == c)
			high = mid;
		else
			low = mid + 1;
	}
	cout << low << endl;
}
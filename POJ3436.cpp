#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<climits>
#include<vector>
using namespace std;
//拆点 dinic
int p, n, m;
vector<int> ansu, ansv, ansf;

struct Edge
{
	int u, v, capacity, flow;
	Edge(int u, int v, int capacity, int flow) :
		u(u), v(v), capacity(capacity), flow(flow) {}
};

vector<Edge> edges;
vector<int> graph[110];
bool vis[110];
int degree[110];
int cur[110];
struct Machine
{
	int q;
	int s[10];
	int d[10];
} machines[50];

bool bfs()
{
	memset(vis, 0, sizeof(vis));
	queue<int> travel;
	travel.push(n << 1);
	degree[n << 1] = 0;
	vis[n << 1] = true;
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
	return vis[n << 1 | 1];
}

int dfs(int from, int InFlow)
{
	if (from == (n << 1 | 1) || InFlow == 0)	//如果找到增广的路或无法继续增广，返回当前流量；
		return InFlow;

	int flow = 0, f;

	for (int& i = cur[from]; i < graph[from].size(); ++i)
	{
		Edge& temp = edges[graph[from][i]];

		if (degree[from] + 1 == degree[temp.v] && (f = dfs(temp.v, min(InFlow, temp.capacity - temp.flow))) > 0)
		{
			temp.flow += f;
			edges[graph[from][i] ^ 1].flow -= f;		//反向减掉
			flow += f;				//当前流量增加
			InFlow -= f;				//当前流量a要-f（流走了）
			if (InFlow == 0)
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
		flow += dfs(n << 1, INT_MAX);
	}
	return flow;
}

bool canBeConnected(int u, int v)
{
	for (int i = 0; i < p; ++i)
		if (machines[v].s[i] != 2 && machines[u].d[i] != machines[v].s[i])
			return false;
	return true;
}

bool isStart(int k)
{
	for (int i = 0; i < p; ++i)
		if (machines[k].s[i] == 1)
			return false;
	return true;
}

bool isEnd(int k)
{
	for (int i = 0; i < p; ++i)
		if (machines[k].d[i] != 1)
			return false;
	return true;
}

void addEdge(int u, int v, int cap)
{
	edges.push_back(Edge(u, v, cap, 0));
	edges.push_back(Edge(v, u, 0, 0));
	int m = edges.size() - 1;
	graph[u].push_back(m - 1);
	graph[v].push_back(m);
}

void buildGraph()
{
	for (int i = 0; i < n; ++i)
	{
		addEdge(i << 1, i << 1 | 1, machines[i].q);
		if (isStart(i))
			addEdge(n << 1, i << 1, INT_MAX);
		if (isEnd(i))
			addEdge(i << 1 | 1, n << 1 | 1, INT_MAX);
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (i == j)
				continue;
			if (canBeConnected(i, j))
				addEdge(i << 1 | 1, j << 1, INT_MAX);
		}
	}
}

void printAns()
{
	for (int i = 0; i < edges.size(); ++i)
	{
		if (edges[i].capacity == INT_MAX && edges[i].flow != 0 && edges[i].u != (n << 1) && edges[i].v != (n << 1 | 1))
		{
			ansu.push_back(edges[i].u);
			ansv.push_back(edges[i].v);
			ansf.push_back(edges[i].flow);
		}
	}
	cout << ' ' << ansu.size() << endl;
	for (int i = 0; i < ansu.size(); ++i)
	{
		cout << (ansu[i] >> 1) + 1 << ' ' << (ansv[i] >> 1) + 1 << ' ' << ansf[i] << endl;
	}
}

void init()
{
	ansu.clear();
	ansv.clear();
	ansf.clear();
	edges.clear();
	for (int i = 0; i < ((n + 1) << 1); ++i)
		graph[i].clear();
}

int main()
{
	while (cin >> p >> n)
	{
		init();
		for (int i = 0; i < n; ++i)
		{
			cin >> machines[i].q;
			for (int j = 0; j < p; ++j)
				cin >> machines[i].s[j];
			for (int j = 0; j < p; ++j)
				cin >> machines[i].d[j];
		}
		buildGraph();
		cout << MaxFlow();
		printAns();
	}
}
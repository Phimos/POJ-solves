#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
#define maxn 2010
#define maxm 50010

int dist[maxn], pre[maxn];
int head[maxn];
int n, m, s, t;

struct Edge
{
	int u, v, flow, cap, cost, next;
	Edge(int u, int v, int flow, int cap, int cost, int next) :
		u(u), v(v), flow(flow), cap(cap), cost(cost), next(next) {}
	Edge() {}
} edges[maxm];
int edgecnt;

void addedge(int u, int v, int d)
{
	edges[edgecnt] = Edge(u, v, 0, 1, d, head[u]);
	head[u] = edgecnt++;
	edges[edgecnt] = Edge(v, u, 0, 0, -d, head[v]);
	head[v] = edgecnt++;
}

bool spfa()
{
	memset(dist, 0x3f, sizeof(dist));
	queue<int> qnodes;
	dist[s] = 0;
	pre[s] = -1;
	qnodes.push(s);
	while (!qnodes.empty())
	{
		int u = qnodes.front();
		qnodes.pop();
		for (int i = head[u]; i != -1; i = edges[i].next)
		{
			Edge& temp = edges[i];
			if (dist[temp.v] > dist[u] + temp.cost && temp.cap > temp.flow)
			{
				dist[temp.v] = dist[u] + temp.cost;
				pre[temp.v] = i;
				qnodes.push(temp.v);
			}
		}
	}
	return dist[t] < 0x3f3f3f3f;
}

void mcmf(int& flow, int& cost)
{
	flow = cost = 0;
	int f;
	while (spfa())
	{
		f = 0x7fffffff;
		for (int i = pre[t]; i != -1; i = pre[edges[i].u])
		{
			Edge& temp = edges[i];
			f = min(f, temp.cap - temp.flow);
		}
		flow += f;
		for (int i = pre[t]; i != -1; i = pre[edges[i].u])
		{
			edges[i].flow += f;
			edges[i ^ 1].flow -= f;
			cost += edges[i].cost * f;
		}
		if (flow >= 2)
			break;
	}
	return;
}

int main()
{
	cin >> n >> m;
	int u, v, d;
	s = 1, t = n;
	fill(head, head + maxn, -1);
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v >> d;
		addedge(u, v, d);
		addedge(v, u, d);
	}
	int flow, cost;
	mcmf(flow, cost);
	cout << cost << endl;
}
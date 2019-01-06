#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
#define maxn 1010
#define maxm 4010
int t, n;
struct Edge
{
	int v, w, next;
	Edge(int v, int w, int next) : v(v), w(w), next(next) {}
	Edge() {}
} edges[maxm];
int edgecnt;
int dist[maxn];
int head[maxn];

void addedge(int u, int v, int w)
{
	edges[edgecnt] = Edge(v, w, head[u]);
	head[u] = edgecnt++;
	edges[edgecnt] = Edge(u, w, head[v]);
	head[v] = edgecnt++;
}
int spfa()
{
	queue<int> qnodes;
	memset(dist, 0x3f, sizeof(dist));
	dist[1] = 0;
	qnodes.push(1);
	while (!qnodes.empty())
	{
		int u = qnodes.front();
		qnodes.pop();
		for (int i = head[u]; i != -1; i = edges[i].next)
		{
			int v = edges[i].v, w = edges[i].w;
			if (dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				qnodes.push(v);
			}
		}
	}
	return dist[n];
}
int main()
{
	cin >> t >> n;
	int u, v, w;
	fill(head, head + maxn, -1);
	for (int i = 0; i < t; ++i)
	{
		cin >> u >> v >> w;
		addedge(u , v , w);
	}
	cout << spfa() << endl;
}
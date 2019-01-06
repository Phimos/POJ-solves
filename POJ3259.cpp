#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
#define maxn 600
#define maxm 8000
//spfa负环
int F, N, M, W;
struct Edge
{
	int v, w, next;
	Edge(int v, int w, int next) : v(v), w(w), next(next) {}
	Edge() {}
} edges[maxm];
int edgecnt;
int head[maxn], dist[maxn];
int update[maxn];
bool vis[maxn];
void init()
{
	edgecnt = 0;
	fill(head, head + maxn, -1);
}
void addedge(int u, int v, int w)
{
	edges[edgecnt] = Edge(v, w, head[u]);
	head[u] = edgecnt++;
}

bool spfa()
{
	memset(dist, 0x3f, sizeof(dist));
	memset(update, 0, sizeof(update));
	dist[1] = 0;
	queue<int> qnodes;
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
				++update[v];
				if (update[v] >= N)
					return true;
				qnodes.push(v);
			}
		}
	}
	return false;
}

int main()
{
	cin >> F;
	while (F--)
	{
		init();
		cin >> N >> M >> W;
		int u, v, w;
		for (int i = 0; i < M; ++i)
		{
			cin >> u >> v >> w;
			addedge(u, v, w);
			addedge(v, u, w);
		}
		for (int i = 0; i < W; ++i)
		{
			cin >> u >> v >> w;
			addedge(u, v, -w);
		}
		if (spfa())
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}
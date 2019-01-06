#include<iostream>
#include<algorithm>
#include<queue>
#include<cstdio>
using namespace std;
#define maxn 1010
struct Node
{
	int pos, fuel, cost;
	Node(int pos, int fuel, int cost) : pos(pos), fuel(fuel), cost(cost) {}
	Node() {}
	bool operator<(const Node& other) const
	{
		return other.cost < cost;
	}
};

struct Edge
{
	int to, next, cost;
	Edge(int to, int next, int cost) :
		to(to), next(next), cost(cost) {}
	Edge() {}
} edges[10010 << 1];


int price[maxn];
int head[maxn];
int edgecnt = 0;
int consume[maxn][110];
int n, m, s, t, p;

void addEdge(int u, int v, int c)
{
	edges[edgecnt] = Edge(v, head[u], c);
	head[u] = edgecnt++;
	edges[edgecnt] = Edge(u, head[v], c);
	head[v] = edgecnt++;
}

int dijkstra()
{
	priority_queue<Node> pqueue;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j <= p; ++j)
			consume[i][j] = 0x7fffffff;
	pqueue.push(Node(s, 0, 0));
	consume[s][0] = 0;
	while (!pqueue.empty())
	{
		Node temp = pqueue.top();
		pqueue.pop();
		if (temp.cost >= consume[t][0])
			break;
		if (consume[temp.pos][temp.fuel] == temp.cost)
		{
			int& pos = temp.pos;
			int& fuel = temp.fuel;
			if (fuel < p && consume[pos][fuel + 1] > temp.cost + price[pos])
			{
				consume[pos][fuel + 1] = temp.cost + price[pos];
				pqueue.push(Node(pos, fuel + 1, consume[pos][fuel + 1]));
			}
			for (int i = head[pos]; i != -1; i = edges[i].next)
			{
				if (fuel >= edges[i].cost && consume[edges[i].to][fuel - edges[i].cost] > temp.cost)
				{
					consume[edges[i].to][fuel - edges[i].cost] = temp.cost;
					pqueue.push(Node(edges[i].to, fuel - edges[i].cost, temp.cost));
				}
			}
		}
	}
	return consume[t][0];
}


int main()
{
	scanf("%d%d", &n, &m);
	fill(head, head + maxn, -1);
	for (int i = 0; i < n; ++i)
		scanf("%d", price + i);
	for (int i = 0; i < m; ++i)
	{
		scanf("%d%d%d", &s, &t, &p);
		addEdge(s, t, p);
	}
	int q;
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d%d%d", &p, &s, &t);
		int ans = dijkstra();
		if (ans != 0x7fffffff)
			printf("%d\n", ans);
		else
			printf("impossible\n");
	}
}
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
#define maxn 100010
//BFS
vector<int> adj[maxn];
int n, c1, c2;
int step[maxn];
int travel[maxn];
void bfs()
{
	int head = 0, tail = 0;
	memset(step, 0, sizeof(step));
	travel[tail++] = c1;
	step[c1] = 1;
	while (head != tail)
	{
		int u = travel[head++];
		for (int i = 0; i < adj[u].size(); ++i)
		{
			int v = adj[u][i];
			if (!step[v])
			{
				step[v] = step[u] + 1;
				travel[tail++] = v;
				if (v == c2)
					return;
			}
		}
	}
}

int main()
{
	scanf("%d", &n);
	int label, adj_node, k;
	for (int i = 0; i < n; ++i)
	{
		scanf("%d%d", &label, &k);
		for (int i = 0; i < k; ++i)
		{
			scanf("%d", &adj_node);
			adj[label].push_back(adj_node);
		}
	}
	scanf("%d%d", &c1, &c2);
	bfs();
	printf("%d %d %d\n", c1, c2, step[c2] - 2);
	return 0;
}
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define maxn 108
int graph[maxn][maxn];
int n, m;
int main()
{
	memset(graph, 0x3f, sizeof(graph));
	int u, v;
	cin >> n >> m;
	for (int i = 0; i < m; ++i)
	{
		cin >> u >> v;
		graph[u][v] = 1;
	}
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (graph[i][j] > graph[i][k] + graph[k][j])
					graph[i][j] = graph[i][k] + graph[k][j];
	int cnt = 0;
	for (int i = 1; i <= n; ++i)
	{
		int j;
		for (j = 1; j <= n; ++j)
			if (i != j && graph[i][j] >= 0x3f3f3f3f && graph[j][i] >= 0x3f3f3f3f)
				break;
		if (j == n + 1)
			++cnt;
	}
	cout << cnt << endl;
}
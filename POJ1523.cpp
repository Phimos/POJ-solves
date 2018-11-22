#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>
#include<stack>
#include<set>
using namespace std;
#define maxn 1010

vector<int> edges[maxn];
int dfn[maxn], low[maxn];
int nTime = 0, group_count = 0;
vector<pair<int, int>> cutVetext;

void tarjan(int u, int fa)
{
	dfn[u] = low[u] = ++nTime;
	int child = 0;
	for (int i = 0; i < edges[u].size(); ++i)
	{
		int v = edges[u][i];
		if (!dfn[v])
		{
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u])
				++child;
		}
		else if (v != fa)
			low[u] = min(low[u], dfn[v]);
	}
	if (fa == 0 && child > 1)
		cutVetext.push_back(pair<int, int>(u, child));
	else if (fa != 0 && child)
		cutVetext.push_back(pair<int, int>(u, child + 1));
}

void init()
{
	memset(dfn, 0, sizeof(dfn));
	memset(low, 0, sizeof(low));
	nTime = 0;
	cutVetext.clear();
	for (int i = 0; i < maxn; ++i)
		edges[i].clear();
}

int main()
{
	ios::sync_with_stdio(false);
	int a, b;
	int test_cnt = 0;
	while (cin >> a, a)
	{
		init();
		int n = 0;
		while (cin >> b)
		{
			edges[a].push_back(b);
			edges[b].push_back(a);
			n = max(n, max(a, b));
			cin >> a;
			if (a == 0)
				break;
		}
		for (int i = 1; i <= n; ++i)
			if (!dfn[i])
				tarjan(i, 0);
		cout << "Network #" << ++test_cnt << endl;
		if (!cutVetext.empty())
		{
			sort(cutVetext.begin(), cutVetext.end());
			for (int i = 0; i < cutVetext.size(); ++i)
				cout << "  SPF node " << cutVetext[i].first << " leaves " << cutVetext[i].second << " subnets" << endl;
		}
		else
			cout << "  No SPF nodes" << endl;
		cout << endl;
	}
}
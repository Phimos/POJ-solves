#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

int n, d;
int x[1005], y[1005], parent[1005];//坐标，并查集
bool repaired[1005];//标志是否被修理
vector<int> adjacent_nodes[1005];//相邻节点


int get_root(int k)
{
	return k == parent[k] ? k : parent[k] = get_root(parent[k]);
}

void merge(int a, int b)
{
	int pa = get_root(a);
	int pb = get_root(b);
	if (pa == pb)
		return;
	parent[pb] = pa;
}

void repair(int k)
{
	int n = adjacent_nodes[k].size();
	repaired[k] = true;
	for (int i = 0; i<n; ++i)
	{
		if (repaired[adjacent_nodes[k][i]])
			merge(adjacent_nodes[k][i], k);
	}
}

void test(int x, int y)
{
	if (get_root(x) == get_root(y))
		printf("SUCCESS\n");
	else
		printf("FAIL\n");
}

int main()
{
	scanf("%d%d", &n, &d);
	for (int i = 1; i <= n; ++i)//写入数据及初始化
	{
		scanf("%d%d", x + i, y + i);
		parent[i] = i;
		repaired[i] = false;
	}
	for (int i = 1; i<n; ++i)//初始化邻接表
	{
		for (int j = i + 1; j <= n; ++j)
		{
			if ((x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]) <= d * d)
			{
				adjacent_nodes[i].push_back(j);
				adjacent_nodes[j].push_back(i);
			}
		}
	}
	int x, y;
	char op[10];
	while (~scanf("%s", op))//模拟操作
	{
		if (op[0] == 'O')
		{
			scanf("%d", &x);
			repair(x);
		}
		else
		{
			scanf("%d%d", &x, &y);
			test(x, y);
		}
	}
	return 0;
}
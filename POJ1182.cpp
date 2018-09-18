#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;
//好题，每个链为一个并查集，维护捕食关系
vector<int> parent;
vector<int> relation_with_root;//0 the same,1 be ate,2 eat root

int get_root(int k)
{
	if (k == parent[k])
		return k;
	int root = get_root(parent[k]);
	relation_with_root[k] = (relation_with_root[k] + relation_with_root[parent[k]]) % 3;
	parent[k] = root;
	return root;
}

bool query(int a, int b)
{
	return get_root(a) == get_root(b);
}

bool check_relation(int new_relation, int x, int y)
{
	get_root(x);
	get_root(y);
	int relation = (relation_with_root[y] - relation_with_root[x] + 3) % 3;
	if (relation + 1 == new_relation)
		return true;
	else
		return false;
}

void add_relation(int relation, int x, int y)
{
	int px = get_root(x);
	int py = get_root(y);
	parent[py] = px;
	relation_with_root[py] = (relation - 1 + relation_with_root[x] - relation_with_root[y] + 3) % 3;
}

void init_data(int n)
{
	parent.resize(n + 1);
	relation_with_root.resize(n + 1);
	for (int i = 1; i <= n; ++i)
	{
		parent[i] = i;
		relation_with_root[i] = 0;
	}
}

int main()
{
	int n, k;
	cin >> n >> k;
	init_data(n);
	int relation, x, y, lie_cnt = 0;
	for (int i = 0; i < k; ++i)
	{
		scanf("%d%d%d", &relation, &x, &y);
		if ((x > n || y > n) || (relation == 2 && x == y))
			++lie_cnt;
		else
		{
			if (query(x, y))
			{
				if (!check_relation(relation, x, y))
					++lie_cnt;
			}
			else
			{
				add_relation(relation, x, y);
			}
		}
	}
	cout << lie_cnt << endl;
	return 0;
}
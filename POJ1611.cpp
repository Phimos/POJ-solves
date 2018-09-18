#include<iostream>
#include<vector>
using namespace std;
//并查集，merge中维护sum数组
vector<int> groups;
vector<int> sum;
int get_root(int k)
{
	if (k == groups[k])
		return k;
	else
		return groups[k] = get_root(groups[k]);
}
void merge(int a, int b)
{
	int root_a = get_root(a);
	int root_b = get_root(b);
	if (root_a == root_b)
		return;
	groups[root_b] = root_a;
	sum[root_a] += sum[root_b];
	sum[root_b] = sum[root_a];
}
void init(int n)
{
	groups.resize(n);
	sum.resize(n);
	for (int i = 0; i<n; ++i)
	{
		groups[i] = i;
		sum[i] = 1;
	}
}
int  main()
{
	int n, m;
	while (cin >> n >> m && (n||m))
	{
		init(n);
		for (int i = 0; i<m; ++i)
		{
			int k, group_head, student;
			cin >> k;
			cin >> group_head;
			for (int j = 1; j<k; ++j)
			{
				cin >> student;
				merge(group_head, student);
			}
		}
		cout << sum[get_root(0)] << endl;
	}
	return 0;
}
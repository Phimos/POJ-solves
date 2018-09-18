#include<cstdio>
#include<iostream>
#include<vector>
using namespace std;

int num_bugs, num_interactions;
int parent[2010];
bool same_sax[2010];

void init_data(int n)
{
	for (int i = 1; i <= n; ++i)
	{
		parent[i] = i;
		same_sax[i] = true;
	}
}

int get_root(int k)
{
	if (k == parent[k])
		return k;
	else
	{
		int root = get_root(parent[k]);
		same_sax[k] = !(same_sax[k] ^ same_sax[parent[k]]);
		parent[k] = root;
		return root;
	}
}

bool check_and_add(int x, int y)
{
	int px = get_root(x);
	int py = get_root(y);
	if (px == py)
	{
		if (same_sax[x] == same_sax[y])
			return false;
	}
	else
	{
		parent[py] = px;
		same_sax[py] = same_sax[x] ^ same_sax[y];
	}
	return true;
}

int main()
{
	int num_scenarios;
	scanf("%d", &num_scenarios);
	for (int i = 1; i <= num_scenarios; ++i)
	{
		scanf("%d%d", &num_bugs, &num_interactions);
		init_data(num_bugs);
		int x, y;
		bool correct = true;
		for (int j = 0; j < num_interactions; ++j)
		{
			scanf("%d%d", &x, &y);
			if (correct)
				correct &= check_and_add(x, y);
		}
		cout << "Scenario #" << i << ':' << endl;
		if (correct)
			cout << "No suspicious bugs found!" << endl;
		else
			cout << "Suspicious bugs found!" << endl;
		cout << endl;
	}
	return 0;
}
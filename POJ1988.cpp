#include<iostream>
using namespace std;
//并查集
//under实质上是与parent的关系，在get_root中维护一直到根的关系
#define MAX 30010
int sum[MAX], parent[MAX], under[MAX];

void init_data()
{
	for (int i = 0; i < MAX; ++i)
	{
		parent[i] = i;
		sum[i] = 1;
		under[i] = 0;
	}
}

int get_root(int k)
{
	if (k == parent[k])
		return k;
	int root = get_root(parent[k]);
	under[k] += under[parent[k]];
	parent[k] = root;
	return parent[k];
}

void merge(int x, int y)
{
	int px = get_root(x);
	int py = get_root(y);
	parent[px] = py;
	under[px] = sum[py];
	sum[py] += sum[px];
}

int main()
{
	int p;
	cin >> p;
	init_data();
	for (int i = 0; i < p; ++i)
	{
		char command;
		cin >> command;
		if (command == 'M')
		{
			int x, y;
			cin >> x >> y;
			merge(x, y);
		}
		else
		{
			int x;
			cin >> x;
			get_root(x);
			cout << under[x] << endl;
		}
	}
	return 0;
}
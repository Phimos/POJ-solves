#include<iostream>
#include<set>
#include<cstdio>
#define MAX 1004
using namespace std;

int parent[MAX], merge_time;
bool be_pointed[MAX], not_tree;
set<int> nodes;

void init_data()
{
	for (int i = 0; i < MAX; ++i)
	{
		parent[i] = i;
		be_pointed[i] = false;
	}
	not_tree = false;
	nodes.clear();
	merge_time = 0;
}

int get_root(int k)
{
	return k == parent[k] ? k : parent[k] = get_root(parent[k]);
}

void merge(int a, int b)
{
	int pa = get_root(a);
	int pb = get_root(b);
	parent[pb] = pa;
	nodes.insert(a);
	nodes.insert(b);
	++merge_time;
}


int main()
{
	int s, e, i = 0; //start & end
	init_data();
	while (scanf("%d%d", &s, &e), (~s || ~e))//两个-1终止
	{
		if (s == 0 && e == 0) //两个0终止
		{
			++i;
			if (!not_tree&&(!merge_time||merge_time + 1 == nodes.size()))//第一个确认不出现环或非树结构，第二个保证不为树林
			{
				cout << "Case " << i << " is a tree." << endl;
			}
			else
			{
				cout << "Case " << i << " is not a tree." << endl;
			}
			init_data();//为之后输入做准备
		}
		else if (not_tree)//减少操作
			continue;
		else
		{
			if (be_pointed[e]) //已经有被指向了
			{
				not_tree = true;
			}
			else if (get_root(s) == get_root(e))
			{
				not_tree = true;
			}
			else
			{
				be_pointed[e] = true;
				merge(s, e);
			}
		}
	}
	return 0;
}
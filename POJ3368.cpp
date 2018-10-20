#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
//线段树+优化
#define maxn 100010
int n, q;
int occur;
vector<int> points;

struct Node//每个叶节点是存的完全一样的东西，并且是[l,r)
{
	int l, r, maxlen;	//maxlen是完全覆盖时候的优化，存的是此区间中出现最多的次数
	bool leafNode;
} tree[maxn << 2];

void buildTree(int root, int l, int r)
{
	tree[root].l = points[l];
	tree[root].r = points[r];
	tree[root].leafNode = false;
	if (l + 1 == r)
	{
		tree[root].maxlen = tree[root].r - tree[root].l;
		tree[root].leafNode = true;
	}
	else
	{
		int mid = (l + r) >> 1;
		buildTree(root << 1, l, mid);
		buildTree(root << 1 | 1, mid, r);
		tree[root].maxlen = max(tree[root << 1].maxlen, tree[root << 1 | 1].maxlen);//维护maxlen
	}
}

void query(int root, int l, int r)
{
	if (tree[root].l == l && tree[root].r == r)
	{
		occur = max(occur, tree[root].maxlen);
	}
	else if (tree[root].leafNode)
	{
		occur = max(occur, r - l);
	}
	else
	{
		if (tree[root << 1].r >= r)
			query(root << 1, l, r);
		else if (tree[root << 1 | 1].l <= l)
			query(root << 1 | 1, l, r);
		else
		{
			query(root << 1, l, tree[root << 1].r);
			query(root << 1 | 1, tree[root << 1 | 1].l, r);
		}
		return;
	}
}

int main()
{
	while (scanf("%d", &n), n)
	{
		scanf("%d", &q);
		int lastNum = -999999;
		int num;
		points.clear();//初始化！
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d", &num);
			if (num != lastNum)
			{
				points.push_back(i);
				lastNum = num;
			}
		}
		points.push_back(n + 1);
		buildTree(1, 0, points.size() - 1);
		int l, r;
		for (int i = 0; i < q; ++i)
		{
			scanf("%d%d", &l, &r);
			occur = 0;
			query(1, l, r + 1);
			printf("%d\n", occur);
		}
	}
}
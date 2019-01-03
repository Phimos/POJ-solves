#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
//线段树
#define maxn 20000
struct Node
{
	int l, r, llen, rlen, maxlen;
	int state;	//0-allfree,1-alloccupied,2-default
	Node(int l, int r) :
		l(l), r(r), llen(r - l + 1), rlen(r - l + 1), maxlen(r - l + 1), state(2) {};
	Node() {};
} tree[maxn << 2];
int n, m;
void build(int root, int l, int r)
{
	tree[root] = Node(l, r);
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	build(root << 1, l, mid);
	build(root << 1 | 1, mid + 1, r);
}

void pushdown(int root)
{
	if (tree[root].state == 2)
		return;
	if (tree[root].state == 1)
		tree[root].llen = tree[root].rlen = tree[root].maxlen = 0;
	else
		tree[root].llen = tree[root].rlen = tree[root].maxlen = tree[root].r - tree[root].l + 1;
	if (tree[root].l != tree[root].r)
	{
		tree[root << 1 | 1].state = tree[root << 1].state = tree[root].state;
	}
	tree[root].state = 2;
	return;
}

void pushup(int root)
{
	if (tree[root << 1].llen == tree[root << 1].r - tree[root << 1].l + 1)
		tree[root].llen = tree[root << 1].llen + tree[root << 1 | 1].llen;
	else
		tree[root].llen = tree[root << 1].llen;
	if (tree[root << 1 | 1].rlen == tree[root << 1 | 1].r - tree[root << 1 | 1].l + 1)
		tree[root].rlen = tree[root << 1 | 1].rlen + tree[root << 1].rlen;
	else
		tree[root].rlen = tree[root << 1 | 1].rlen;
	tree[root].maxlen = max(max(tree[root << 1].maxlen, tree[root << 1 | 1].maxlen), tree[root << 1].rlen + tree[root << 1 | 1].llen);
	return;
}

void change(int root, int l, int r, int op)
{
	if (tree[root].l == l && tree[root].r == r)
	{
		if (op == 1)
			tree[root].state = 1;
		else
			tree[root].state = 0;
		pushdown(root);
		return;
	}
	pushdown(root);
	if (l <= tree[root << 1].r)
		change(root << 1, l, min(tree[root << 1].r, r), op);
	else
		pushdown(root << 1);
	if (r >= tree[root << 1 | 1].l)
		change(root << 1 | 1, max(tree[root << 1 | 1].l, l), r, op);
	else
		pushdown(root << 1 | 1);
	pushup(root);
	return;
}

int main()
{
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	int op, k, t;
	for (int i = 0; i < m; ++i)
	{
		scanf("%d", &op);
		if (op == 3)
			cout << tree[1].maxlen << endl;
		else
		{
			scanf("%d%d", &k, &t);
			change(1, k, k + t - 1, op);
		}
	}
}
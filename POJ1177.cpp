#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
//线段树 分x和y两个方向做，不用离散化
#define maxn 20010
int n, perimeter = 0;

struct Line
{
	int l, r, order;
	bool start;
	Line(int l, int r, int order, bool start) : l(l), r(r), order(order), start(start) {}
	Line() {}
	bool operator<(const Line& b)const
	{
		return order < b.order;
	}
} xlines[5010], ylines[5010];


struct Node
{
	int l, r, len;
	int covers;
	Node(int l, int r) : l(l), r(r), len(0), covers(0) {}
	Node() {}
} tree[maxn << 2];

void buildTree(int root, int l, int r)
{
	tree[root] = Node(l, r);
	if (l == r)
		return;
	else
	{
		int mid = (l + r) >> 1;
		buildTree(root << 1, l, mid);
		buildTree(root << 1 | 1, mid + 1, r);
	}
}

void changeLine(int root, int l, int r, bool start)
{
	if (tree[root].l == l && tree[root].r == r)
	{
		tree[root].covers += start ? 1 : -1;
		if (tree[root].covers)
			tree[root].len = r - l + 1;
		else
		{
			if (l == r)
				tree[root].len = 0;
			else
				tree[root].len = tree[root << 1].len + tree[root << 1 | 1].len;
		}
		return;
	}
	else
	{
		if (tree[root << 1].r >= r)
		{
			changeLine(root << 1, l, r, start);
		}
		else if (tree[root << 1 | 1].l <= l)
		{
			changeLine(root << 1 | 1, l, r, start);
		}
		else
		{
			changeLine(root << 1, l, tree[root << 1].r, start);
			changeLine(root << 1 | 1, tree[root << 1 | 1].l, r, start);
		}
		if (!tree[root].covers)
			tree[root].len = tree[root << 1].len + tree[root << 1 | 1].len;
	}
}

int main()
{
	scanf("%d", &n);
	int x1, y1, x2, y2;
	for (int i = 0; i < n; ++i)
	{
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		xlines[i << 1] = Line(x1, x2 - 1, y1, true);
		xlines[i << 1 | 1] = Line(x1, x2 - 1, y2, false);
		ylines[i << 1] = Line(y1, y2 - 1, x1, true);
		ylines[i << 1 | 1] = Line(y1, y2 - 1, x2, false);
	}
	sort(xlines, xlines + (n << 1));
	sort(ylines, ylines + (n << 1));
	buildTree(1, -10000, 10000);
	int lastLen = 0;
	for (int i = 0; i < (n << 1); ++i)
	{
		changeLine(1, xlines[i].l, xlines[i].r, xlines[i].start);
		perimeter += abs(tree[1].len - lastLen);
		lastLen = tree[1].len;
	}
	lastLen = 0;
	for (int i = 0; i < (n << 1); ++i)
	{
		changeLine(1, ylines[i].l, ylines[i].r, ylines[i].start);
		perimeter += abs(tree[1].len - lastLen);
		lastLen = tree[1].len;
	}
	printf("%d\n", perimeter);
}
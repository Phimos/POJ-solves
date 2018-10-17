#include<cstdio>
#include<cstring>
#include<algorithm>
//线段树
using namespace std;
#define maxn 50010
int n, m;

struct Node	//节点
{
	int l, r, length, lmax, rmax, maxlen;//lmax，rmax表示左右的最大空房间，maxlen表示总的最大空房间
	int occupied, change;//change相当于lazyTag
	Node(int l, int r) : l(l), r(r), length(r + 1 - l), lmax(length), rmax(length), maxlen(length), occupied(0), change(-1) {}
	Node() {}
} tree[4 * maxn];

void buildTree(int root, int l, int r)//建树
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

int checkIn(int root, int d)
{
	if (tree[root].maxlen < d)	//没有足够连续空房间
		return 0;
	else if (tree[root].lmax >= d)
		return tree[root].l;
	else
	{
		if (tree[root << 1].maxlen >= d)	//如果左边可以容下
			return checkIn(root << 1, d);
		else if (tree[root << 1].rmax + tree[root << 1 | 1].lmax >= d)	//如果有一部分左边一部分右边可以容下
			return tree[root << 1].r - tree[root << 1].rmax + 1;
		else	//一定在右边
			return checkIn(root << 1 | 1, d);
	}
}

void pushDown(int root)
{
	if (tree[root].change == -1)	//无标志位
		return;
	int len = tree[root].change == 0 ? tree[root].length : 0;
	tree[root].maxlen = tree[root].lmax = tree[root].rmax = len;	//更新三个长度
	tree[root].occupied = tree[root].change;	//更新occupied
	if (tree[root].l < tree[root].r)
		tree[root << 1].change = tree[root << 1 | 1].change = tree[root].change;
	tree[root].change = -1;		//标志位重置
	return;
}

void pushUp(int root)	//利用子节点信息更新root
{
	pushDown(root << 1);
	pushDown(root << 1 | 1);
	tree[root].maxlen = max(tree[root << 1].rmax + tree[root << 1 | 1].lmax, max(tree[root << 1].maxlen, tree[root << 1 | 1].maxlen));
	tree[root].lmax = tree[root << 1].lmax + (tree[root << 1].length == tree[root << 1].maxlen ? tree[root << 1 | 1].lmax : 0);
	tree[root].rmax = tree[root << 1 | 1].rmax + (tree[root << 1 | 1].length == tree[root << 1 | 1].maxlen ? tree[root << 1].rmax : 0);
}

void update(int root, int l, int r, bool in)	//从l到r来更新，in为真表示checkin，为假表示checkout
{
	pushDown(root);
	if (tree[root].l == l && tree[root].r == r)
	{
		tree[root].change = in ? 1 : 0;
		pushDown(root);
		return;
	}
	else
	{
		if (tree[root << 1].r >= r)
			update(root << 1, l, r, in);
		else if (tree[root << 1 | 1].l <= l)
			update(root << 1 | 1, l, r, in);
		else
		{
			update(root << 1, l, tree[root << 1].r, in);
			update(root << 1 | 1, tree[root << 1 | 1].l, r, in);
		}
	}
	pushUp(root);
	return;
}

int main()
{
	scanf("%d%d", &n, &m);
	buildTree(1, 1, n);
	int op, d, x;
	int t;
	while (m--)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d", &d);
			t = checkIn(1, d);
			printf("%d\n", t);
			if (t)
				update(1, t, t + d - 1, 1);
		}
		else
		{
			scanf("%d%d", &x, &d);
			update(1, x, x + d - 1, 0);
		}
	}
}
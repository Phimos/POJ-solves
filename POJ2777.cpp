#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;
//线段树
#define maxn 100010
int l, t, o;

struct Node
{
	int l, r;
	unsigned color, tag;
	Node(int l, int r) : l(l), r(r), color(2), tag(0) {}//颜色初始位1，所以color初始化为2
	Node() {}
} tree[maxn << 2];

void buildTree(int root, int l, int r)//建树
{
	tree[root] = Node(l, r);
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	buildTree(root << 1, l, mid);
	buildTree(root << 1 | 1, mid + 1, r);
	return;
}

void pushDown(int root)//状态下传
{
	if (tree[root].tag)
	{
		tree[root].color = tree[root].tag;
		if (tree[root].l != tree[root].r)
			tree[root << 1].tag = tree[root << 1 | 1].tag = tree[root].tag;
		tree[root].tag = 0;
	}
	return;
}

void color(int root, int l, int r, int c)
{
	pushDown(root);
	if (tree[root].l == l && tree[root].r == r)
	{
		tree[root].tag = 1 << c;//更新tag
		pushDown(root);//下传
	}
	else
	{
		if (tree[root << 1].r < l)
			color(root << 1 | 1, l, r,c);
		else if (tree[root << 1 | 1].l > r)
			color(root << 1, l, r, c);
		else
		{
			color(root << 1, l, tree[root << 1].r, c);
			color(root << 1 | 1, tree[root << 1 | 1].l, r, c);
		}
		pushDown(root << 1);
		pushDown(root << 1 | 1);
		tree[root].color = tree[root << 1].color | tree[root << 1 | 1].color;//根据下方的color更新，即上传
	}
	return;
}

void query(int root, int l, int r, unsigned& ans)
{
	pushDown(root);//需要取消当前位的tag
	if (tree[root].l == l && tree[root].r == r)
	{
		ans |= tree[root].color;
		return;
	}
	else
	{
		if (tree[root << 1].r < l)
			query(root << 1 | 1, l, r, ans);
		else if (tree[root << 1 | 1].l > r)
			query(root << 1, l, r, ans);
		else
		{
			query(root << 1, l, tree[root << 1].r, ans);
			query(root << 1 | 1, tree[root << 1 | 1].l, r, ans);
		}
		return;
	}
}

int countBit(unsigned x)//计算x的1的位数，即颜色的种类数
{
	if (x == 0)
		return 0;
	else
	{
		int res = 0;
		while (x)
		{
			x = x & (x - 1);
			++res;
		}
		return res;
	}
}

int main()
{
	scanf("%d%d%d", &l, &t, &o);
	buildTree(1, 1, l);
	char op;
	int l, r, c;
	while (o--)
	{
		getchar();
		scanf("%c%d%d", &op, &l, &r);
		if (l > r) //可能存在l>r的情况
			swap(l, r);
		if (op == 'C')
		{
			scanf("%d", &c);
			color(1, l, r, c);
		}
		else
		{
			unsigned ans = 0;
			query(1, l, r, ans);
			printf("%d\n", countBit(ans));
		}
	}
}
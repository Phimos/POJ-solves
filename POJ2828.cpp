#include<cstdio>
#include<cstring>
using namespace std;
//线段树
//从后往前插入，pos=i表示寻找已有的i+1个空位，其中empty由线段树维护
#define maxn 200010

int FinalOrder[maxn], pos[maxn], val[maxn];
int n;

struct Node
{
	int l, r, empty;
	Node(int l, int r) : l(l), r(r), empty(r - l + 1) {}
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

int query(int root, int k)
{
	if (tree[root].l == tree[root].r)
	{
		tree[root].empty = 0;
		return tree[root].l;
	}
	int ans;
	if (tree[root << 1].empty >= k)
		ans = query(root << 1, k);
	else
		ans = query(root << 1 | 1, k - tree[root << 1].empty);
	tree[root].empty = tree[root << 1].empty + tree[root << 1 | 1].empty;
	return ans;
}

int main()
{
	while (~scanf("%d", &n))
	{
		memset(FinalOrder, 0xffffffff, sizeof(FinalOrder));
		buildTree(1, 1, n);
		for (int i = 0; i < n; ++i)
		{
			scanf("%d%d", pos + i, val + i);
		}
		for (int i = n - 1; i >= 0; --i)
		{
			int k = query(1, pos[i] + 1);
			FinalOrder[k] = val[i];
		}
		for (int i = 1; i <= n; ++i)
			printf("%d\n", FinalOrder[i]);
	}
}
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
//线段树+离散化，insert的时候将h作为lazyTag，之后query的时候pushDown，保证叶节点得到最高的高度，然后求和
#define maxn 40010
int n;
vector<long long> xset;
vector<long long> hset;

struct Building
{
	long long x1, x2, h;
} buildings[maxn];

struct Node
{
	int l, r;
	long long h;
	Node(int l, int r) : l(l), r(r), h(0) {}
	Node() {}
} tree[maxn << 3];

void buildTree(int root, int l, int r)
{
	tree[root] = Node(l, r);
	if (l + 1 == r)	//叶节点
		return;
	else
	{
		int mid = (l + r) >> 1;
		buildTree(root << 1, l, mid);
		buildTree(root << 1 | 1, mid, r);
	}
}

void insert(int root, long long l, long long r, long long h)

{
	if (xset[tree[root].l] == l && xset[tree[root].r] == r)
	{
		tree[root].h = max(tree[root].h, h);
		return;
	}
	long long mid = xset[tree[root << 1].r];
	if (mid <= l)
		insert(root << 1 | 1, l, r, h);
	else if (mid >= r)
		insert(root << 1, l, r, h);
	else
	{
		insert(root << 1, l, mid, h);
		insert(root << 1 | 1, mid, r, h);
	}
	return;
}

void pushDown(int root)
{
	tree[root << 1].h = max(tree[root].h, tree[root << 1].h);
	tree[root << 1 | 1].h = max(tree[root].h, tree[root << 1 | 1].h);
	return;
}

long long query(int root)
{
	if (tree[root].l + 1 == tree[root].r)
		return (xset[tree[root].r] - xset[tree[root].l]) * tree[root].h;
	else
	{
		pushDown(root);
		return query(root << 1) + query(root << 1 | 1);
	}
}


int main()
{
	scanf("%d", &n);
	hset.push_back(0);
	for (int i = 0; i < n; ++i)
	{
		scanf("%lld%lld%lld", &buildings[i].x1, &buildings[i].x2, &buildings[i].h);
		xset.push_back(buildings[i].x1);
		xset.push_back(buildings[i].x2);
	}
	sort(xset.begin(), xset.end());
	xset.erase(unique(xset.begin(), xset.end()), xset.end());
	buildTree(1, 0, xset.size() - 1);
	long long  area = 0;
	for (int i = 0; i < n; ++i)
		insert(1, buildings[i].x1, buildings[i].x2, buildings[i].h);
	area = query(1);
	printf("%lld\n", area);
}
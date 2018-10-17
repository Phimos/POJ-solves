#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int n;
int smallerBrands[8010];
int ans[8010];

struct Node
{
	int L, R, num;
	Node(int L, int R) : L(L), R(R), num(R - L + 1) {}
	Node() {}
	int mid()
	{
		return (L + R) / 2;
	}
};

class IntervalTree
{
public:
	Node tree[40000];
	int n;
	IntervalTree(int n) : n(n) {}
	IntervalTree() {}
	void init(int root, int L, int R)
	{
		tree[root] = Node(L, R);
		if (L == R)
			return;
		init(root * 2 + 1, L, tree[root].mid());
		init(root * 2 + 2, tree[root].mid() + 1, R);
	}
	int FindAndUpdate(int root, int k)
	{
		--tree[root].num;
		if (tree[root].L == tree[root].R)
			return tree[root].L;
		if (k > tree[root * 2 + 1].num)
			return FindAndUpdate(root * 2 + 2, k - tree[root * 2 + 1].num);
		else
			return FindAndUpdate(root * 2 + 1, k);
	}
};

int main()
{
	scanf("%d", &n);
	for (int i = 1; i < n; ++i)
		scanf("%d", smallerBrands + i);
	IntervalTree Tree(n);
	Tree.init(0, 1, n);
	for (int i = n - 1; i >= 0; --i)
		ans[i] = Tree.FindAndUpdate(0, smallerBrands[i] + 1);
	for (int i = 0; i < n; ++i)
		printf("%d\n", ans[i]);
}
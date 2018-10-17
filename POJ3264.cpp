#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
//线段树，构造与查找，不需要更新（水题）
int N, Q;
int MAXH, MINH;
struct Node
{
	int l, r;
	int maxh, minh;
	Node(int l, int r) : l(l), r(r), maxh(0x80000000), minh(0x7fffffff) {}
	Node() {}
} Tree[200010];
int CowHeight[50010];//存数据

void buildTree(int root, int L, int R)//建树
{
	Tree[root] = Node(L, R);
	if (L == R)
	{
		Tree[root].maxh = Tree[root].minh = CowHeight[L];
		return;
	}
	int mid = (L + R) >> 1;
	buildTree(root * 2 + 1, L, mid);
	buildTree(root * 2 + 2, mid + 1, R);
	Tree[root].minh = min(Tree[root * 2 + 1].minh, Tree[root * 2 + 2].minh);
	Tree[root].maxh = max(Tree[root * 2 + 1].maxh, Tree[root * 2 + 2].maxh);
	return;
}

void Query(int root, int L, int R)//查找
{
	if (Tree[root].l == L && Tree[root].r == R)
	{
		MAXH = max(MAXH, Tree[root].maxh);
		MINH = min(MINH, Tree[root].minh);
		return;
	}
	if (L > Tree[2 * root + 1].r)
	{
		Query(2 * root + 2, L, R);
	}
	else if (R < Tree[2 * root + 2].l)
	{
		Query(2 * root + 1, L, R);
	}
	else
	{
		Query(2 * root + 1, L, Tree[2 * root + 1].r);
		Query(2 * root + 2, Tree[2 * root + 2].l, R);
	}
	return;
}

int main()
{
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; ++i)
	{
		scanf("%d", CowHeight + i);
	}
	buildTree(0, 1, N);
	int L, R;
	while (Q--)
	{
		scanf("%d%d", &L, &R);
		MINH = 0x7fffffff;
		MAXH = 0x80000000;
		Query(0, L, R);
		cout << MAXH - MINH << endl;
	}
	return 0;
}
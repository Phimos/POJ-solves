#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
//线段树，区间更新（lazyTag）
int N, Q;
long long nums[100010];

struct Node
{
	int  L, R;
	long long sum;
	long long lazyTag;
	Node(int L, int R) : L(L), R(R), sum(0), lazyTag(0) {}
	Node() {}
} Tree[400010];

void buildTree(int root, int L, int R)//建树
{
	Tree[root] = Node(L, R);
	if (L == R)
	{
		Tree[root].sum = nums[L];
		return;
	}
	int mid = (L + R) >> 1;
	buildTree(root * 2 + 1, L, mid);
	buildTree(root * 2 + 2, mid + 1, R);
	Tree[root].sum = Tree[root * 2 + 1].sum + Tree[root * 2 + 2].sum;
	return;
}

void downTag(int root)
{
	Tree[root].sum += (Tree[root].R - Tree[root].L + 1) * Tree[root].lazyTag;
	if (Tree[root].R != Tree[root].L)
	{
		Tree[root * 2 + 1].lazyTag += Tree[root].lazyTag;
		Tree[root * 2 + 2].lazyTag += Tree[root].lazyTag;
	}
	Tree[root].lazyTag = 0;
	return;
}

long long Query(int root, int L, int R)//查询
{
	if (Tree[root].lazyTag)
		downTag(root);
	if (Tree[root].L == L && Tree[root].R == R)
	{
		return Tree[root].sum;
	}
	if (L > Tree[root * 2 + 1].R)
	{
		return Query(root * 2 + 2, L, R);
	}
	else if (R < Tree[root * 2 + 2].L)
	{
		return Query(root * 2 + 1, L, R);
	}
	else
	{
		return Query(root * 2 + 1, L, Tree[root * 2 + 1].R) + Query(root * 2 + 2, Tree[root * 2 + 2].L, R);
	}
}

void update(int root, int L, int R, int Inc)//更新
{
	if (Tree[root].L == L && Tree[root].R == R)
	{
		Tree[root].lazyTag += Inc;
		return;
	}
	Tree[root].sum += (R - L + 1) * Inc;
	if (L > Tree[root * 2 + 1].R)
	{
		update(root * 2 + 2, L, R, Inc);
	}
	else if (R < Tree[root * 2 + 2].L)
	{
		update(root * 2 + 1, L, R, Inc);
	}
	else
	{
		update(root * 2 + 1, L, Tree[root * 2 + 1].R, Inc);
		update(root * 2 + 2, Tree[root * 2 + 2].L, R, Inc);
	}
	return;
}

int main()
{
	scanf("%d%d", &N, &Q);
	for (int i = 1; i <= N; ++i)
	{
		scanf("%lld", nums + i);
	}
	buildTree(0, 1, N);
	int L, R, Inc;
	char command;
	while (Q--)
	{
		getchar();
		scanf("%c", &command);
		if (command == 'Q')
		{
			scanf("%d%d", &L, &R);
			Query(0, L, R);
			printf("%lld\n", Query(0, L, R));
		}
		else
		{
			scanf("%d%d%d", &L, &R, &Inc);
			update(0, L, R, Inc);
		}
	}
}
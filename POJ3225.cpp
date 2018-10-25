#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
#include<map>
using namespace std;
//线段树，边界条件，区间，巨尼玛恶心
#define maxn 70000
vector<pair<int, int>> intervals;
struct Node
{
	int l, r, Xor, cover;
} tree[maxn << 2];

void buildTree(int root, int l, int r)
{
	tree[root].l = l;
	tree[root].r = r;
	tree[root].cover = 0;
	tree[root].Xor = 0;
	if (l == r)
		return;
	else
	{
		buildTree(root << 1, l, (l + r) >> 1);
		buildTree(root << 1 | 1, ((l + r) >> 1) + 1, r);
	}
}

void pushDown(int root)
{
	if (tree[root].cover != -1)
	{
		if (tree[root].Xor)
		{
			tree[root].cover ^= 1;
			tree[root].Xor = 0;
		}
		if (tree[root].l != tree[root].r)
		{
			tree[root << 1].cover = tree[root << 1 | 1].cover = tree[root].cover;
			tree[root << 1].Xor = tree[root << 1 | 1].Xor = 0;
		}
	}
	else
	{
		if (tree[root].Xor)
		{
			tree[root << 1].Xor ^= 1;
			tree[root << 1 | 1].Xor ^= 1;
			tree[root].Xor = 0;
		}
	}
}

void pushUp(int root)
{
	pushDown(root << 1);
	pushDown(root << 1 | 1);
	if (tree[root << 1].cover == tree[root << 1 | 1].cover)
		tree[root].cover = tree[root << 1].cover;
	else
		tree[root].cover = -1;
}

void update(int root, int l, int r, char op)
{
	pushDown(root);
	if (tree[root].l == l && tree[root].r == r)
	{
		if (op == 'U')
			tree[root].cover = 1;
		else if (op == 'D')
			tree[root].cover = 0;
		else if (op == 'I')
			;
		else
			tree[root].Xor = 1;
	}
	else
	{
		if (tree[root << 1].r >= r)
		{
			if (op == 'C' || op == 'I')
			{
				tree[root << 1 | 1].cover = 0;
				tree[root << 1 | 1].Xor = 0;
			}
			update(root << 1, l, r, op);
		}
		else if (tree[root << 1 | 1].l <= l)
		{
			if (op == 'C' || op == 'I')
			{
				tree[root << 1].cover = 0;
				tree[root << 1].Xor = 0;
			}
			update(root << 1 | 1, l, r, op);
		}
		else
		{
			update(root << 1, l, tree[root << 1].r, op);
			update(root << 1 | 1, tree[root << 1 | 1].l, r, op);
		}
		pushUp(root);
	}

}


void addInterval(int l, int r)
{
	if (intervals.empty())
		intervals.push_back(pair<int, int>(l, r));
	else
	{
		if (intervals.back().second + 1 == l)
			intervals.back().second = r;
		else
			intervals.push_back(pair<int, int>(l, r));
	}
}

void query(int root)
{
	pushDown(root);
	if (tree[root].cover == 1)
		addInterval(tree[root].l, tree[root].r);
	else if (tree[root].cover == 0)
		return;
	else if (tree[root].l != tree[root].r)
	{
		query(root << 1);
		query(root << 1 | 1);
	}
}
void printInterval(pair<int, int> interval)
{
	if (interval.first & 1)
		printf("(%d", interval.first >> 1);
	else
		printf("[%d", interval.first >> 1);
	if (interval.second & 1)
		printf(",%d)", (interval.second >> 1) + 1);
	else
		printf(",%d]", interval.second >> 1);
}

int main()
{
	char lBracket, rBracket, command;
	int l, r;
	buildTree(1, 0, 65535 * 2 + 1);
	while (scanf("%c %c%d,%d%c\n", &command, &lBracket, &l, &r, &rBracket) != EOF)
	{
		if (lBracket == '(')
			l = l << 1 | 1;
		else
			l = l << 1;
		if (rBracket == ')')
			r = (r << 1) - 1;
		else
			r = r << 1;
		if (l > r)
		{
			if (command == 'I' || command == 'C')
				tree[1].cover = 0;
		}
		else
			update(1, l, r, command);
	}
	query(1);
	if (intervals.empty())
		printf("empty set");
	else
	{
		printInterval(intervals[0]);
		for (int i = 1; i < intervals.size(); ++i)
		{
			printf(" ");
			printInterval(intervals[i]);
		}
		printf("\n");
	}
}
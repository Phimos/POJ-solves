#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define maxn 100010
int n, m;
vector<int> initnums;
//线段树+二分
struct Node
{
	vector<int> nums;
	int l, r;
} tree[maxn << 2];

vector<int>& SortedNums = tree[1].nums;

void mergeVector(int root)
{
	vector<int> &des = tree[root].nums, &src1 = tree[root << 1].nums, &src2 = tree[root << 1 | 1].nums;
	int i = 0, j = 0;
	while (i < src1.size() && j < src2.size())
	{
		if (src1[i] < src2[j])
		{
			des.push_back(src1[i++]);
		}
		else
		{
			des.push_back(src2[j++]);
		}
	}
	while (i < src1.size())
		des.push_back(src1[i++]);
	while (j < src2.size())
		des.push_back(src2[j++]);
	return;
}

void buildTree(int root, int l, int r)
{
	tree[root].l = l;
	tree[root].r = r;
	if (l == r)
	{
		tree[root].nums.push_back(initnums[l]);
		return;
	}
	else
	{
		int mid = (l + r) >> 1;
		buildTree(root << 1, l, mid);
		buildTree(root << 1 | 1, mid + 1, r);
		mergeVector(root);
	}
}

int query(int root, int l, int r, int num)
{
	if (tree[root].l == l && tree[root].r == r)
	{
		int ans = upper_bound(tree[root].nums.begin(), tree[root].nums.end(), num) - tree[root].nums.begin();
		return ans;
	}
	else
	{
		if (tree[root << 1].r >= r)
			return query(root << 1, l, r, num);
		else if (tree[root << 1 | 1].l <= l)
			return query(root << 1 | 1, l, r, num);
		else
			return query(root << 1, l, tree[root << 1].r, num) + query(root << 1 | 1, tree[root << 1 | 1].l, r, num);
	}
}

void find_ans(int l, int r, int k)//二分搜索答案
{
	int ll = 0, rr = SortedNums.size() - 1;
	while (ll != rr)
	{
		int mid = (ll + rr) >> 1;
		if (query(1, l - 1, r - 1, SortedNums[mid]) < k )
		{
			ll = mid + 1;
		}
		else
		{
			rr = mid;
		}
	}
	printf("%d\n", SortedNums[ll]);
}

int main()
{
	scanf("%d%d", &n, &m);
	initnums.resize(n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &initnums[i]);
	}
	buildTree(1, 0, initnums.size() - 1);
	int l, r, k;
	for (int i = 0; i < m; ++i)
	{
		scanf("%d%d%d", &l, &r, &k);
		find_ans(l, r, k);
	}
}
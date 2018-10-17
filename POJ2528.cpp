#include<iostream>
#include<vector>
#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
//离散化+线段树，再拿指针写线段树我就是狗
struct Poster
{
	int l, r;
	Poster() {}
	Poster(int l, int r) : l(l), r(r) {}
};

Poster posters[10010];
set<int> temp;
vector<int> nums;
int n, cnt;

struct Node
{
	int L, R;
	bool covered;
	Node() {}
	Node(int L, int R) : L(L), R(R), covered(false) {}
} Tree[80000];

void buildTree(int root, int l, int r)
{
	Tree[root] = Node(nums[l], nums[r]);
	if (l + 1 == r)	//由于所代表的是点，所以不存在单点的poster
	{
		return;
	}
	int mid = (l + r) / 2;	//确保所有区间能被取到
	buildTree(2 * root + 1, l, mid);
	buildTree(2 * root + 2, mid, r);
}

bool CheckAndUpdate(int root, int l, int r)	//如果被完全盖住则返回true，否则返回false
{
	bool res = true;
	if (Tree[root].covered)//区间已经全覆盖
		return true;
	if (l == Tree[root].L && r == Tree[root].R) //和区间重合
	{
		res = Tree[root].covered;
		Tree[root].covered = true;
		return res;
	}
	if (l >= Tree[root * 2 + 1].R)
		res &= CheckAndUpdate(root * 2 + 2, l, r);
	else if (r <= Tree[root * 2 + 2].L)
		res &= CheckAndUpdate(root * 2 + 1, l, r);
	else
	{
		res &= CheckAndUpdate(root * 2 + 1, l, Tree[root * 2 + 1].R);
		res &= CheckAndUpdate(root * 2 + 2, Tree[root * 2 + 2].L, r);
	}
	if (Tree[root * 2 + 1].covered && Tree[root * 2 + 2].covered) //更新covered
		Tree[root].covered = true;
	return res;
}

void init()//初始化
{
	temp.clear();
	nums.clear();
	cnt = 0;
	memset(Tree, 0, sizeof(Tree));
}

int main()
{
	int caseNum, l, r;
	scanf("%d", &caseNum);
	while (caseNum--)
	{
		init();
		scanf("%d", &n);
		if (n != 0)
		{
			for (int i = 0; i < n; ++i)
			{
				scanf("%d%d", &l, &r);
				posters[i] = Poster(l - 1, r);	//从最左端端点开始编号，所以需要l-1
				temp.insert(l - 1);
				temp.insert(r);
			}
			nums.assign(temp.begin(), temp.end());//离散化
			buildTree(0, 0, nums.size() - 1);	//建树
			for (int i = n - 1; i >= 0; --i)
			{
				cnt += !CheckAndUpdate(0, posters[i].l, posters[i].r);
			}
		}
		printf("%d\n", cnt);
	}
}

//下面是也过了的树结构线段树
//#include<iostream>
//#include<vector>
//#include<cstdio>
//#include<set>
//using namespace std;
//
//struct Poster
//{
//	int l, r;
//	Poster() {}
//	Poster(int l, int r) : l(l), r(r) {}
//};
//
//Poster posters[10010];
//set<int> temp;
//vector<int> nums;
//int n, cnt;
//
//struct Node
//{
//	int L, R;
//	bool covered;
//	Node* pleft, *pright;
//	Node() {}
//	Node(int L, int R) : L(L), R(R), covered(false), pleft(NULL), pright(NULL) {}
//};
//
//void buildTree(Node* root, int l, int r)
//{
//	if (l + 1 == r)	//由于所代表的是点，所以不存在单点的poster
//	{
//		//		root->pleft = new Node(nums[l], nums[l]);
//		//	root->pright = new Node(nums[r], nums[r]);
//		return;
//	}
//	int mid = (l + r) / 2;
//	root->pleft = new Node(nums[l], nums[mid]);	//确保所有区间能被取到
//	buildTree(root->pleft, l, mid);
//	root->pright = new Node(nums[mid], nums[r]);
//	buildTree(root->pright, mid, r);
//}
//
//bool CheckAndUpdate(Node* root, int l, int r)	//如果被完全盖住则返回true，否则返回false
//{
//	bool res = true;
//	if (root->covered)//区间已经全覆盖
//		return true;
//	if (l == root->L && r == root->R) //和区间重合
//	{
//		res = root->covered;
//		root->covered = true;
//		return res;
//	}
//	if (l >= root->pleft->R)
//		res &= CheckAndUpdate(root->pright, l, r);
//	else if (r <= root->pright->L)
//		res &= CheckAndUpdate(root->pleft, l, r);
//	else
//	{
//		res &= CheckAndUpdate(root->pleft, l, root->pleft->R);
//		res &= CheckAndUpdate(root->pright, root->pright->L, r);
//	}
//	if (root->pleft && root->pleft->covered && root->pright && root->pright->covered) //更新covered
//		root->covered = true;
//	return res;
//}
//
//void init()//初始化
//{
//	temp.clear();
//	nums.clear();
//	cnt = 0;
//}
//
//int main()
//{
//	int caseNum, l, r;
//	scanf("%d", &caseNum);
//	while (caseNum--)
//	{
//		init();
//		scanf("%d", &n);
//		for (int i = 0; i < n; ++i)
//		{
//			scanf("%d%d", &l, &r);
//			posters[i] = Poster(l - 1, r);	//从最左端端点开始编号，所以需要l-1
//			temp.insert(l - 1);
//			temp.insert(r);
//		}
//		nums.assign(temp.begin(), temp.end());//离散化
//		Node* TreeRoot = new Node(nums[0], nums.back());	//设定ROOT的初试区间（即最大范围）
//		buildTree(TreeRoot, 0, nums.size() - 1);	//建树
//		for (int i = n - 1; i >= 0; --i)
//		{
//			cnt += !CheckAndUpdate(TreeRoot, posters[i].l, posters[i].r);
//		}
//		printf("%d\n", cnt);
//	}
//}
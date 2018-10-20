#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
#define maxn 210

int n;
double area;
vector<double> yy;

struct Line
{
	double y1, y2, x;
	bool left;
	Line(double x, double y1, double y2, bool left) : x(x), y1(y1), y2(y2), left(left) {}
	Line() {}
	bool operator<(const Line& b)const
	{
		return x < b.x;
	}
} lines[210];

struct Node
{
	double u, d;		//u<d
	double len;
	int covers;
	Node(int u, int d) : u(yy[u]), d(yy[d]), len(0), covers(0) {}
	Node() {}
} tree[maxn << 3];

void buildTree(int root, int up, int down)
{
	tree[root] = Node(up, down);
	if (up + 1 == down)
		return;
	else
	{
		int mid = (up + down) >> 1;
		buildTree(root << 1, up, mid);
		buildTree(root << 1 | 1, mid, down);
	}
}

void ChangeLine(int root, double y1, double y2, bool left)
{
	if (tree[root].u == y1 && tree[root].d == y2)
	{
		if (left)
		{
			tree[root].covers += 1;
		}
		else
		{
			tree[root].covers -= 1;
		}
		if (tree[root].covers)
		{
			tree[root].len = y2 - y1;
		}
		else
		{
			if ((root << 1 | 1) < maxn << 3)
				tree[root].len = tree[root << 1].len + tree[root << 1 | 1].len;
		}
		return;
	}
	else
	{
		if (tree[root << 1 | 1].u >= y2)
			ChangeLine(root << 1, y1, y2, left);
		else if (tree[root << 1].d <= y1)
			ChangeLine(root << 1 | 1, y1, y2, left);
		else
		{
			double mid = tree[root << 1].d;
			ChangeLine(root << 1, y1, mid, left);
			ChangeLine(root << 1 | 1, mid, y2, left);
		}
		if (!tree[root].covers)	//不被全覆盖
			tree[root].len = tree[root << 1].len + tree[root << 1 | 1].len;
		return;
	}
}

int main(int argc, char const *argv[])
{
	int TestCase = 0;
	while (scanf("%d", &n), n)
	{
		++TestCase;
		printf("Test case #%d\n", TestCase);
		double x1, y1, x2, y2;
		for (int i = 0; i < n; ++i)
		{
			scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
			lines[i << 1] = Line(x1, y1, y2, true);		//left
			lines[i << 1 | 1] = Line(x2, y1, y2, false);		//right
			yy.push_back(y1);
			yy.push_back(y2);
		}
		sort(lines, lines + (n << 1));
		sort(yy.begin(), yy.end());
		yy.erase(unique(yy.begin(), yy.end()), yy.end());	//compress
		buildTree(1, 0, yy.size() - 1);
		area = 0;
		ChangeLine(1, lines[0].y1, lines[0].y2, lines[0].left);
		for (int i = 1; i < (n << 1); ++i)
		{
			area += (lines[i].x - lines[i - 1].x) * tree[1].len;
			ChangeLine(1, lines[i].y1, lines[i].y2, lines[i].left);
		}
		printf("Total explored area: %.2lf\n\n", area);
	}
	return 0;
}
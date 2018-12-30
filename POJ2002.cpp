#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define maxn 100007
//hash
struct Node
{
	int x, y;
	Node(int x, int y) : x(x), y(y) {}
	Node() {}
};

vector<Node> ha[maxn];
Node nodes[1010];

int hk(Node a)
{
	return (a.x * a.x + a.y * a.y) % maxn;
}

void Insert(Node a)
{
	int h = hk(a);
	ha[h].push_back(a);
}

bool Find(Node a)
{
	int h = hk(a);
	for (int i = 0; i < ha[h].size(); ++i)
		if (ha[h][i].x == a.x && ha[h][i].y == a.y)
			return true;
	return false;
}

void init()
{
	for (int i = 0; i < maxn; ++i)
		ha[i].clear();
}

int main()
{
	int n;
	while (cin >> n, n)
	{
		init();
		for (int i = 0; i < n; ++i)
		{
			cin >> nodes[i].x >> nodes[i].y;
			Insert(nodes[i]);
		}
		int cnt = 0;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (i == j)
					continue;
				int dx = nodes[j].x - nodes[i].x;
				int dy = nodes[j].y - nodes[i].y;
				if (Find(Node(nodes[i].x + dy, nodes[i].y - dx)) && Find(Node(nodes[i].x + dx + dy, nodes[i].y + dy - dx)))
					++cnt;
			}
		}
		cout << (cnt >> 2) << endl;
	}
}
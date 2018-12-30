#include<cstdio>
#include<algorithm>
using namespace std;
bool pd[201][20001];
struct data {
	int x, y, step;
} q[2000001];
int n, t = 0, w = 1; bool ans;
void inq(int x, int y)
{
	if (x > y)
		swap(x, y);
	if (ans || x > 200 || y > 20000)
		return;
	if (!pd[x][y]) {
		pd[x][y] = 1;
		q[w].x = x;
		q[w].y = y;
		q[w].step = q[t].step + 1;
		if (x == n || y == n)
		{
			ans = 1;
			printf("%d", q[w].step);
		}
		w++;
	}
}
void bfs()
{
	q[0].x = 0; q[0].y = 1;
	while (t < w)
	{
		int x = q[t].x, y = q[t].y;
		inq(x, x + x); inq(x, x + y);
		inq(x, y + y); inq(x, y - x);
		inq(x + x, y); inq(x + y, y);
		inq(y + y, y); inq(y - x, y);
		t++;
		if (ans)return;
	}
}
int main()
{
	scanf("%d", &n);
	bfs();
	return 0;
}
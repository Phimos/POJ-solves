#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 1010
//几何+水题
int n, m;
int X1, Y1, X2, Y2;
int box_cnt[maxn], cnt[maxn];

struct Line
{
	int U, L;
	bool operator<(const Line& b)const
	{
		return U + L < b.U + b.L;
	}
} lines[maxn];

void binSearchBox(int x, int y)
{
	int l = 0, r = n;
	while (l != r)
	{
		int mid = ((l + r) >> 1) + 1;
		if (((x - lines[mid].L) * ( Y1 - y) - ( lines[mid].U - x) * (y - Y2)) < 0)
			r = mid - 1;
		else
			l = mid;
	}
	++box_cnt[l];
	return;
}

int main()
{
	while (scanf("%d", &n), n)
	{
		memset(cnt, 0, sizeof(cnt));
		memset(box_cnt, 0, sizeof(box_cnt));
		scanf("%d%d%d%d%d", &m, &X1, &Y1, &X2, &Y2);
		for (int i = 1; i <= n; ++i)
		{
			scanf("%d%d", &lines[i].U, &lines[i].L);
		}
		lines[0].U = lines[0].L = 0;
		sort(lines, lines + n + 1);
		int x, y;
		for (int i = 0; i < m; ++i)
		{
			scanf("%d%d", &x, &y);
			binSearchBox(x, y);
		}
		for (int i = 0; i <= n; ++i)
		{
			++cnt[box_cnt[i]];
		}
		puts("Box");
		for (int i = 1; i <= n; ++i)
		{
			if (cnt[i])
				printf("%d: %d\n", i, cnt[i]);
		}
	}
}
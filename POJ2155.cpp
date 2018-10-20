#include<cstdio>
#include<cstring>
#include<algorithm>
//二维树状数组
//每一个区块可以考虑记入边界，只有两种情况，一种是在内部，查询时候总和为1，否则在外部查询时候总和为0,2,4
//可以利用树状数组更新四个点，然后求和&1

#define maxn 1010

int n, t, testCase;
int arr[maxn][maxn];

int lowbit(int k)
{
	return k & -k;
}

void update(int x, int y)
{
	for (int i = x; i <= n + 1; i += lowbit(i))
		for (int j = y; j <= n + 1; j += lowbit(j))
			arr[i][j] += 1;
}

bool query(int x, int y)
{
	int ans = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		for (int j = y; j > 0; j -= lowbit(j))
			ans += arr[i][j];
	return ans & 1;
}

int main()
{
	scanf("%d", &testCase);
	while (testCase--)
	{
		scanf("%d%d", &n, &t);
		memset(arr, 0, sizeof(arr));
		char op;
		int x1, y1, x2, y2;
		while (t--)
		{
			getchar();
			scanf("%c", &op);
			if (op == 'C')
			{
				scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
				update(x1, y1);
				update(x2 + 1, y2 + 1);	//将外侧点+1，化方格为边界顶点
				update(x1, y2 + 1);
				update(x2 + 1, y1);
			}
			else
			{
				scanf("%d%d", &x1, &y1);
				if (query(x1, y1 ))
					printf("1\n");
				else
					printf("0\n");
			}
		}
		printf("\n");
	}
}
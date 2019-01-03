#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 40010
//并查集
int fa[maxn], wedis[maxn], nsdis[maxn];
int f1[maxn], f2[maxn], l[maxn];
char D[maxn];
int n, m;

void init()
{
	memset(wedis, 0, sizeof(wedis));
	memset(nsdis, 0, sizeof(nsdis));
	for (int i = 1; i <= n; ++i)
		fa[i] = i;
}

int getroot(int k)
{
	if (k == fa[k])
		return k;
	else
	{
		int pk = fa[k];
		int rk = getroot(pk);
		wedis[k] += wedis[pk];
		nsdis[k] += nsdis[pk];
		fa[k] = rk;
		return rk;
	}
}

void merge(int a, int b, int l, char dir)
{
	int pa = getroot(a), pb = getroot(b);
	if (pa == pb)
		return;
	fa[pa] = pb;
	switch (dir)
	{
	case 'W':
		wedis[pa] = l + wedis[b] - wedis[a];
		nsdis[pa] = nsdis[b] - nsdis[a];
		break;
	case 'E':
		wedis[pa] = -l + wedis[b] - wedis[a];
		nsdis[pa] = nsdis[b] - nsdis[a];
		break;
	case 'N':
		nsdis[pa] = l + nsdis[b] - nsdis[a];
		wedis[pa] = wedis[b] - wedis[a];
		break;
	case 'S':
		nsdis[pa] = -l + nsdis[b] - nsdis[a];
		wedis[pa] = wedis[b] - wedis[a];
		break;
	default:
		break;
	}
	return;
}

int query(int a, int b)
{
	int pa = getroot(a), pb = getroot(b);
	if (pa != pb)
		return -1;
	else
		return abs(nsdis[a] - nsdis[b]) + abs(wedis[a] - wedis[b]);
}

int main()
{
	cin >> n >> m;
	init();
	for (int i = 0; i < m; ++i)
		cin >> f1[i] >> f2[i] >> l[i] >> D[i];
	int t, F1, F2, I;
	cin >> t;
	for (int i = 0, j = 0; i < t; ++i)
	{
		cin >> F1 >> F2 >> I;
		for (; j < I; ++j)
			merge(f1[j], f2[j], l[j], D[j]);
		cout << query(F1, F2) << endl;
	}
}
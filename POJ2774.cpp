#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

#define maxn 200010
int wa[maxn], wb[maxn], wv[maxn], wws[maxn];
int sa[maxn], rk[maxn], height[maxn];
char s[maxn];

void BuildSA(char* s, int sa[], int n, int m)
{
	int i, j, p, *pm = wa, *k2sa = wb, *t;
	for (i = 0; i < m; ++i) wws[i] = 0;
	for (i = 0; i < n; ++i)wws[pm[i] = s[i]]++;
	for (i = 1; i < m; ++i)wws[i] += wws[i - 1];
	for (i = n - 1; i >= 0; --i)sa[--wws[pm[i]]] = i;
	for (j = p = 1; p < n; j <<= 1, m = p)
	{
		for (p = 0, i = n - j; i < n; ++i)k2sa[p++] = i;
		for (i = 0; i < n; ++i)if (sa[i] >= j)k2sa[p++] = sa[i] - j;
		for (i = 0; i < m; ++i)wws[i] = 0;
		for (i = 0; i < n; ++i)wws[wv[i] = pm[k2sa[i]]]++;
		for (i = 1; i < m; ++i)wws[i] += wws[i - 1];
		for (i = n - 1; i >= 0; --i)sa[--wws[wv[i]]] = k2sa[i];
		for (t = pm, pm = k2sa, k2sa = t, pm[sa[0]] = 0, p = i = 1; i < n; ++i)
		{
			int a = sa[i - 1], b = sa[i];
			if (k2sa[a] == k2sa[b] && k2sa[a + j] == k2sa[b + j])
				pm[sa[i]] = p - 1;
			else
				pm[sa[i]] = p++;
		}
	}
	return;
}


void BuildHeight(char* str, int n, int* sa, int* rk)
{
	int i, j, k;
	for (i = 0; i < n; ++i)
		rk[sa[i]] = i;
	for (i = k = 0; i < n; height[rk[i++]] = k)
		for (k ? k-- : 0, j = sa[rk[i] - 1]; str[i + k] == str[j + k]; k++);
}

int main()
{
	int slen1, slen;
	scanf("%s", s);
	slen1 = strlen(s);
	s[slen1] = '-';
	scanf("%s", s + slen1 + 1);
	slen = strlen(s);
	BuildSA(s, sa, slen + 1, 130);
	BuildHeight(s, slen + 1, sa, rk);
	int ans = 0;
	for (int i = 0; i <= slen; ++i)
		if ((sa[i] < slen1 && sa[i - 1] > slen1) || (sa[i] > slen1 && sa[i - 1] < slen1))
			ans = max(ans, height[i]);
	printf("%d\n", ans);
}
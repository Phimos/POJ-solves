#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN = 20010;
int wa[MAXN], wb[MAXN], wv[MAXN], Ws[MAXN]; //辅助数组
int n;											//注意，wv和Ws的元素个数应该同时超过字符串的字符种类数和字符串长度
int sa[MAXN]; //sa[i]是名次为i的后缀的位置，即后缀数组
int str[MAXN];
void buildSA(int * s, int * sa, int n, int m)
{	//n: 字符串s的长度
	//m: 开始是字符串s中字符的种类数，后来变成不同j-后缀的个数
	//调用方法： buildSA("banana",sa,6，127);
	int i, j, p, *pm = wa, *k2sa = wb, *t;
	for (i = 0; i < m; i++) Ws[i] = 0;
	for (i = 0; i < n; i++) Ws[pm[i] = s[i]]++; //(1)
	//此时Ws[i]是字符i(编码为i的字符)出现的次数 ，pm是原字符串s的复制品
	//字符的编码就是字符的排名，此处排名可不连续，相对大小正确即可
	//Ws[i]也可以看作排名为i的1-后缀的出现次数
	for (i = 1; i < m; i++) Ws[i] += Ws[i - 1];
	//此时Ws[i]是编码不大于i的字符出现的次数,
	//也可以说是排名不大于 i 的字符出现的次数


	for (i = n - 1; i >= 0; i--) sa[--Ws[pm[i]]] = i;  //(2)
	//循环中  i 代表位置
	//将名次未确定的字符（1-后缀)称为 U字符
	//此时sa[k]是名次为k的1-后缀的位置
	//下标为i的那个字符，名次是 Ws[pm[i]]-1。因为:
	//下标为i的那个字符，就是pm[i]。现在，有Ws[pm[i]]个U字符排名不大于pm[i]
	//即名次不大于pm[i]
	//那么pm[i]显然是这些字符里面排名最大的
	//虽然可能有多个字符和pm[i]相同，但由于i是从大到小遍历的
	//pm[i]就是所有和pm[i]相同的U字符里，位置最大的，也就是名次最大的
	//那么pm[i]的名次就是 Ws[pm[i]] - 1 (名次从0开始算）
	//--Ws[pm[i]]是因为新确定了一个字符的名字，U字符的个数就要减一
	for (j = p = 1; p < n; j <<= 1, m = p) {  //烧脑循环
		//在一次循环中,已知j-后缀相关信息,要求 2j-后缀相关信息
		//此时，sa[i]是名次为i的j-后缀的位置,pm[i]是位置为i的j-后缀的排名
		// j > 1时，m 是不同j-后缀的个数
		for (p = 0, i = n - j; i < n; i++) k2sa[p++] = i;
		//k2sa[i]是所有2j-后缀按照第二关键字（第二个j-后缀）排序后，名次为i的 2j-后缀的位置
		//从位置 n-j开始的2j-后缀，第二关键字为NULL，NULL的排名最小,
		//共j个2j-后缀的第二关键字是NULL
		//执行完此循环后，p = j, k2sa[0] - k2sa[j-1]值确定
		for (i = 0; i < n; i++) //按名次从小到大遍历n个j-后缀
			if (sa[i] >= j) k2sa[p++] = sa[i] - j;
		for (i = 0; i < m; i++) Ws[i] = 0;
		for (i = 0; i < n; i++)
			//按第二关键字名次遍历2j-后缀的第一关键字
			Ws[wv[i] = pm[k2sa[i]]]++;
		for (i = 1; i < m; i++) Ws[i] += Ws[i - 1];
		//此时 Ws[i]是排名不大于i的j-后缀的个数

		for (i = n - 1; i >= 0; i--)
			//按第二关键字的名次从大到小遍历所有2j-后缀
			sa[--Ws[wv[i]]] = k2sa[i];//求位置为k2sa[i]的2j-后缀的名次
		for (t = pm, pm = k2sa, k2sa = t,
		        pm[sa[0]] = 0, p = i = 1; i < n; i++) { //按名次遍历2j-后缀
			//p为目前发现的，不同的 2j-后缀的个数
			int a = sa[i - 1], b = sa[i];
			if (k2sa[a] == k2sa[b] && a + j < n && b + j < n &&
			        k2sa[a + j] == k2sa[b + j])
				pm[sa[i]] = p - 1; //未发现新的2j-后缀
			//位置为sa[i](即排名为i的那个2j-后缀的位置)的2j-后缀的排名是 p - 1
			else
				pm[sa[i]] = p++; //发现新的2j-后缀
		} //当p达到n时，说明已经有了n个不同的2j-后缀，并且都在sa里排好了序。
	} //烧脑循环结束
	return;
}
int height[MAXN], rk[MAXN];
void BuildHeight(int * str, int n, int * sa, int * Rank) {
	int i, j, k;
	for (int i = 0; i < n; ++i) //i 是名次,n是字符串长度
		Rank[sa[i]] = i;
	height[0] = 0;
	for (i = k = 0; i < n - 1; height[Rank[i++]] = k)//i是位置
		for (k ? k-- : 0, j = sa[Rank[i] - 1]; //Rank[0]>0才不越界
		        str[i + k] == str[j + k]; k++);
	//k相当于是 H[i]; height[Rank[i]] =  H[i] ;
}

bool check(int L)
{
	int l, r, i, j;
	i = j = 1;
	while (i < n)
	{
		if (height[i] < L)
		{
			++i;
			continue;
		}
		else
		{
			for (j = i; j <= n && height[j] >= L; ++j)
				;
			--j;
			int maxsa = 0, minsa = 0x7fffffff;
			for (int ii = i - 1; ii <= j; ++ii)
			{
				maxsa = max(maxsa, sa[ii]);
				minsa = min(minsa, sa[ii]);
			}
			if (maxsa - minsa > L)
				return true;
			i = j + 1;
		}
	}
	return false;
}

int main()
{
	while (scanf("%d", &n), n)
	{
		for (int i = 0; i < n; ++i)
			scanf("%d", str + i);
		for (int i = 1; i < n; ++i)
			str[i - 1] = str[i] - str[i - 1] + 100;

		str[n - 1] = 0;
		int l = 0, r = n >> 1, ans = 0;
		buildSA(str, sa, n, 200);
		BuildHeight(str, n, sa, rk);
		while (l <= r)
		{
			int mid = (r + l) >> 1;
			if (check(mid))
			{
				l = mid + 1;
				ans = mid;
			}
			else
			{
				r = mid - 1;
			}
		}
		if (ans < 4)
			printf("0\n");
		else
			printf("%d\n", ans + 1);
	}
}
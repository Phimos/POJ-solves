#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
//dfs+树状数组
int n, m;//存数据
vector<int>* tree;//链接表存树结构
bool *apple;//是否存在苹果
int *Arr, *s, *e;//树状数组，开始位置，结束位置
int cnt = 1;

void dfs(int k)//构建原始数组
{
	s[k] = cnt++;
	for (int i = 0; i < tree[k].size(); ++i)
		dfs(tree[k][i]);
	e[k] = cnt++;
}

int lowbit(int x)
{
	return x & (-x);
}

void init()//初始化
{
	Arr = new int[2 * n + 1];
	s = new int[n + 1];
	e = new int[n + 1];
	tree = new vector<int>[n + 1];
	apple = new bool[2 * n + 1];
	for (int i = 1; i <= 2 * n; ++i)
	{
		Arr[i] = lowbit(i);
		apple[i] = true;
	}
}

void change(int k)
{
	int delta = apple[s[k]] ? -1 : 1;
	for (int i = s[k]; i <= 2 * n; i += lowbit(i))
		Arr[i] += delta;
	for (int i = e[k]; i <= 2 * n; i += lowbit(i))
		Arr[i] += delta;
	apple[e[k]] = apple[s[k]] = !apple[s[k]];
}

int getSum(int k)
{
	int sum = 0;
	for (int i = k; i > 0; i -= lowbit(i))
		sum += Arr[i];
	return sum;
}

void inquiry(int k)
{
	printf("%d\n", (getSum(e[k]) - getSum(s[k] - 1)) / 2);
	return;
}

int main()
{
	scanf("%d", &n);
	int father, child;
	init();
	for (int i = 1; i < n; ++i)
	{
		scanf("%d%d", &father, &child);
		tree[father].push_back(child);
	}
	dfs(1);
	scanf("%d", &m);
	char command;
	int x;
	for (int i = 0; i < m; ++i)
	{
		getchar();
		scanf("%c%d", &command, &x);
		if (command == 'Q')
			inquiry(x);
		else
			change(x);
	}
}
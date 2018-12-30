#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<cstdio>
#include<queue>
#include<map>
using namespace std;
#define maxn 1010
#define INF 0xfffffff
map<char, int> DNAset;
//AC自动机
int nodeCnt = 2;
string str;
int dp[maxn][maxn];

struct Node
{
	Node* children[4];
	Node* fail;
	bool virus;
} tree[maxn];

void insert(string& s)
{
	Node* root = tree + 1;
	for (int i = 0; i < s.length(); ++i)
	{
		int k = DNAset[s[i]];
		if (root->children[k] == NULL)
		{
			root->children[k] = tree + nodeCnt;
			++nodeCnt;
		}
		root = root->children[k];
	}
	root->virus = true;
}

void buildDfa()
{
	for (int i = 0; i < 4; ++i)
	{
		tree[0].children[i] = tree + 1;
	}
	tree[1].fail = tree;
	queue<Node*> qNodes;
	qNodes.push(tree + 1);
	while (!qNodes.empty())
	{
		Node* temp = qNodes.front();
		qNodes.pop();
		for (int i = 0; i < 4; ++i)
		{
			Node* pChild = temp->children[i];
			if (pChild)	//可以保证上面的children数组都是满的
			{
				Node* pFail = temp->fail;
				pChild->fail = pFail->children[i];
				if (pChild->fail->virus)
					pChild->virus = true;
				qNodes.push(pChild);
			}
			else
			{
				if (temp == tree + 1)
					temp->children[i] = tree + 1;
				else
					temp->children[i] = temp->fail->children[i];
			}
		}
	}
}

int main()
{
	DNAset['A'] = 0;
	DNAset['G'] = 1;
	DNAset['C'] = 2;
	DNAset['T'] = 3;
	int n;
	int caseCnt = 0;
	string tempString;
	while (cin >> n, n)
	{
		++caseCnt;
		nodeCnt = 2;
		memset(tree, 0, sizeof(tree));
		for (int i = 0; i < n; ++i)
		{
			cin >> tempString;
			insert(tempString);
		}
		buildDfa();
		cin >> str;
		int slen = str.length();
		for (int i = 0; i <= slen; ++i)
			for (int j = 1; j < nodeCnt; ++j)
				dp[i][j] = INF;
		dp[0][1] = 0;
		for (int i = 0; i < slen; ++i)
		{
			for (int j = 1; j < nodeCnt; ++j)
			{
				if (dp[i][j] < INF)
				{
					for (int k = 0; k < 4; ++k)
					{
						int idx = tree[j].children[k] - tree;
						if (tree[idx].virus == false)
							dp[i + 1][idx] = min(dp[i + 1][idx], dp[i][j] + (DNAset[str[i]] != k));
					}
				}
			}
		}
		int ans = INF;
		for (int i = 1; i < nodeCnt; ++i)
		{
			ans = min(ans, dp[slen][i]);
		}
		if (ans == INF)
			ans = -1;
		printf("Case %d: %d\n", caseCnt, ans);
	}
}
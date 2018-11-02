#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<map>
using namespace std;
//AC自动机
#define maxn 1010
#define INF 0x7fffffff
map<char, int> DNAset;
DNAset['A'] = 0;
DNAset['G'] = 1;
DNAset['C'] = 2;
DNAset['T'] = 3;

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
		int k = DNASet[s[i]];
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
	for (int i = 0; i < 4; ++i)
	{
		if (!tree[1]->children[i])
			tree[1].children[i] = tree + 1;
	}
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
				temp->children[i] = temp->fail->children[i];
			}
		}
	}
}



int main()
{
	int n;
	string tempString;
	while (cin >> n, n)
	{
		for (int i = 0; i < n; ++i)
		{
			cin >> tempString;
			insert(tempString);
		}
		buildDfa();
		cin >> s;
		int slen = s.length();
		memeset(dp, INF, sizeof(dp));
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
						dp[i + 1][idx] = min(dp[i + 1][idx], dp[i][j] + DNAset[str[i - 1]] != k);
					}
				}
			}
		}
		int ans = INF;
		for (int i = 1; i < nodeCnt; ++i)
		{
			ans = min(ans, dp[slen][i]);
		}
		printf("%d\n", ans);
	}
}
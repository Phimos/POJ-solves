#include<cstdio>
#include<iostream>
#include<queue>
#include<string>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;
#define maxn 200010
//AC自动机
int nodeCnt = 2;
int virusCnt = 1;
set<int> ansSet;
int minLoop[26];
struct Node
{
	Node* children[26];
	Node* fail;
	bool vis;
	int virus;
	void initNode()
	{
		memset(children, 0, sizeof(children));
		fail = NULL;
		vis = false;
		virus = 0;
	}
} tree[maxn];

void insert(string& s)
{
	Node* root = tree + 1;
	for (int i = 0; i < s.length(); ++i)
	{
		int k = s[i] - 'A';
		if (root->children[k] == NULL)
		{
			root->children[k] = tree + nodeCnt;
			++nodeCnt;
		}
		root = root->children[k];
	}
	root->virus = virusCnt;
	++virusCnt;
}

void buildDfa()
{
	for (int i = 0; i < 26; ++i)
		tree[0].children[i] = tree + 1;
	tree[1].fail = tree;
	queue<Node*> qNodes;
	qNodes.push(tree + 1);
	while (!qNodes.empty())
	{
		Node* temp = qNodes.front();
		qNodes.pop();
		for (int i = 0; i < 26; ++i)
		{
			Node* pChild = temp->children[i];
			if (pChild)
			{
				Node* pFail = temp->fail;
				while (pFail->children[i] == NULL)
					pFail = pFail->fail;
				pChild->fail = pFail->children[i];
				qNodes.push(pChild);
			}
		}
	}
}

void search(string& s)
{
	Node* pnode = tree + 1;
	for (int i = 0; i < s.length(); ++i)
	{
		int k = s[i] - 'A';
		while (pnode->children[k] == NULL)
			pnode = pnode->fail;
		pnode = pnode->children[k];
		if (!pnode->vis)
		{
			Node* tempnode = pnode;
			while (!tempnode->vis && tempnode != tree + 1)	//将fail连接的看成一条串，末尾在tree+1，标记vis减少重复访问
			{
				if (tempnode->virus)
					ansSet.insert(tempnode->virus);	//维护一个ansset，保存所有virus的编号
				tempnode->vis = true;
				tempnode = tempnode->fail;
			}
		}
		pnode->vis = true;
	}
	return;
}

string transfer(string& s)	//转换字符串
{
	string t;
	for (int i = 0; i < s.length(); ++i)
	{
		if (isalpha(s[i]))
			t.push_back(s[i]);
		else if (s[i] == '[')
		{
			int num = 0;
			++i;
			while (isdigit(s[i]))
				num = num * 10 + s[i++] - '0';
			for (int j = 0; j < num; ++j)
				t.push_back(s[i]);
			++i;
		}
	}
	return t;
}

void init()	//初始化函数
{
	for (int i = 1; i < nodeCnt; ++i)
		tree[i].initNode();
	nodeCnt = 2;
	virusCnt = 1;
	ansSet.clear();
}

int main()
{
	int testNum;
	cin >> testNum;
	while (testNum--)
	{
		init();
		int n;
		string temp;
		cin >> n;
		for (int i = 0; i < n; ++i)
		{
			cin >> temp;
			insert(temp);
		}
		buildDfa();
		cin >> temp;
		temp = transfer(temp);
		search(temp);
		reverse(temp.begin(), temp.end());
		search(temp);
		cout << ansSet.size() << endl;
	}
}
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
using namespace std;
#define maxn 6010
//树形DP
vector<int> sub[maxn];
int rating[maxn];
bool notroot[maxn];
int n;

pair<int, int> get_rating(int root)
{
	if (sub[root].empty())
		return make_pair(rating[root], 0);
	int with_root = rating[root], without_root = 0;
	for (int i = 0; i < sub[root].size(); ++i)
	{
		pair<int, int> temp = get_rating(sub[root][i]);
		with_root += temp.second;
		without_root += max(temp.first, temp.second);
	}
	return make_pair(with_root, without_root);
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> rating[i];
	memset(notroot, 0, sizeof(notroot));
	int l, k;
	pair<int, int> ans;
	for (int i = 1; i < n; ++i)
	{
		cin >> l >> k;
		sub[k].push_back(l);
		notroot[l] = true;
	}
	for (int i = 1; i <= n; ++i)
	{
		if (!notroot[i])
		{
			ans = get_rating(i);
			break;
		}
	}
	cout << max(ans.first, ans.second) << endl;
}
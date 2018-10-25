#include<iostream>
using namespace std;
//数学+二分查找
int findN(int k)
{
	int l = 0, r = 150;
	while (l != r)
	{
		int mid = ((l + r) >> 1) + 1;
		if (mid * (mid + 1) / 2 <= k)
			l = mid;
		else
			r = mid - 1;
	}
	return l;
}
int main()
{
	int k;
	while (cin >> k, k)
	{
		int n = findN(k);
		cout << k << ' ' << n * (2 * n + 1)*(n + 1) / 6 + (k - (n * (n + 1) / 2))*(n + 1) << endl;
	}
}
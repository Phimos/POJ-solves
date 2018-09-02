#include<iostream>
#include<algorithm>
using namespace std;
//如题构造length函数模拟
int length(int k)
{
	int i = 1;
	while (k != 1)
	{
		if (k % 2 == 1)
			k = 3 * k + 1;
		else
			k = k / 2;
		++i;
	}
	return i;
}

int main()
{
	int i, j;
	while (cin >> i >> j)
	{
		int max_length = 0;
		int smaller = min(i, j), bigger = max(i, j);
		for (int k = smaller; k <= bigger; ++k)
			max_length = max(max_length, length(k));
		cout << i << ' ' << j << ' ' << max_length << endl;
	}
	return 0;
}
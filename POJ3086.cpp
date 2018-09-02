#include<iostream>
using namespace std;

int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		int k;
		cin >> k;
		cout << i << ' ' << k << ' ' << ((k+1)*(k + 2) / 2)*((k+1)*(k + 2) / 2 - 1)/2 << endl;
	}
	return 0;
}
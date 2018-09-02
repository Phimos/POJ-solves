#include<iostream>
using namespace std;

int main()
{
	int n, x, y;
	cin >> n;
	while (n--)
	{
		cin >> x >> y;
		if ((x == y || x == y + 2) && y >= 0)
			cout << 2 * x - (x % 2) - (x == y + 2) * 2 << endl;
		else
			cout << "No Number" << endl;
	}
}

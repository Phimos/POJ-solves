#include<iostream>
#include<algorithm>
using namespace std;
//水题
int main()
{
	int Width;
	while (cin >> Width, Width)
	{
		int ansW = 0, ansH = 0;
		int ww = 0, hh = 0;
		int w, h;
		while (cin >> w >> h, ~w || ~h)
		{
			if (ww + w <= Width)
			{
				ww += w;
				hh = max(hh, h);
			}
			else
			{
				ansW = max(ansW, ww);
				ansH += hh;
				ww = w;
				hh = h;
			}
		}
		ansW = max(ansW, ww);
		ansH += hh;
		cout << ansW << " x " << ansH << endl;
	}
}
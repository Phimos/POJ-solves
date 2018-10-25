#include<iostream>
#include<algorithm>
using namespace std;
#define maxn=1010
//数学
int nums[maxn][maxn];

//边长k的矩阵homogeneous只要边长k-1的矩阵homogeneous就好了

int main()
{
	int k;
	while (cin >> k, k)
	{
		for (int i = 0; i < k; ++i)
			for (int j = 0; j < k; ++j)
				cin >> maxn[i][j];
		bool ok = true;
		for (int i = 1; i < k; ++i)
			for (int j = 1; j < k; ++j)
				if (nums[i][j] + nums[i - 1][j - 1] != nums[i - 1][j] + nums[i][j - 1])
				{
					ok = false;
					goto printans;
				}
printans:
		if (ok)
			cout << "homogeneous" << endl;
		else
			cout << "not homogeneous" << endl;
	}
}
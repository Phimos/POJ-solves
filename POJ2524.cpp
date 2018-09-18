#include<iostream>
#include<vector>
using namespace std;

vector<int> religion_num;

int get_religion(int k)
{
	if (k != religion_num[k])
		religion_num[k] = get_religion(religion_num[k]);
	return religion_num[k];
}

void merge(int a, int b)
{
	int ra = get_religion(a);
	int rb = get_religion(b);
	if (ra == rb)
		return;
	religion_num[rb] = ra;
}

int main()
{
	int n, m, case_num = 0;
	while (cin >> n >> m && (n || m))
	{
		++case_num;
		religion_num.resize(n);
		for (int i = 0; i<n; ++i)
			religion_num[i] = i;
		for (int i = 0; i<m; ++i)
		{
			int student_a, student_b;
			cin >> student_a >> student_b;
			merge(student_a - 1, student_b - 1);
		}
		int cnt = 0;
		for (int i = 0; i<n; ++i)
			if (i == religion_num[i])
				++cnt;
		cout << "Case " << case_num << ": " << cnt << endl;
	}
	return 0;
}
#include<iostream>
#include<string>
using namespace std;

int weight[12];
string question[3][3];

int getweight(string& s)
{
	int ans = 0;
	for (int i = 0; i < s.size(); ++i)
		ans += weight[s[i] - 'A'];
	return ans;
}

bool test()
{
	bool mark = true;
	for (int i = 0; i < 3; ++i)
	{
		if (question[i][2] == "even")
			mark &= (getweight(question[i][0]) == getweight(question[i][1]));
		else if (question[i][2] == "up")
			mark &= (getweight(question[i][0]) > getweight(question[i][1]));
		else
			mark &= (getweight(question[i][0]) < getweight(question[i][1]));
	}
	return mark;
}

int main()
{
	int caseNum;
	cin >> caseNum;
	while (caseNum--)
	{
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				cin >> question[i][j];
		for (int i = 0; i < 12; ++i)
			weight[i] = 1;
		for (int i = 0; i < 12; ++i)
		{
			weight[i] = 0;
			if (test())
			{
				cout << char('A' + i) << " is the counterfeit coin and it is light." << endl;
				break;
			}
			weight[i] = 2;
			if (test())
			{
				cout << char('A' + i) << " is the counterfeit coin and it is heavy." << endl;
				break;
			}
			weight[i] = 1;
		}
	}
}
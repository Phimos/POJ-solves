#include<cstdio>
#include<string>
#include<iostream>
#include<vector>
using namespace std;
//直接模拟
vector<string> dic;

void check(string temp)
{
	bool ismatch = false;
	for (int i = 0; i < dic.size(); ++i)
	{
		if (temp == dic[i])
		{
			ismatch = true;
			break;
		}
	}
	if (ismatch)
	{
		cout << " is correct" << endl;
		return;
	}
	else
	{
	    cout<<':';
		for (int i = 0; i < dic.size(); ++i)
		{
			bool ok = true, mark;
			if (dic[i].length() == temp.length())
			{
				mark = false;
				for (int j = 0; j < temp.length(); ++j)
				{
					if (temp[j] != dic[i][j])
					{
						if (mark)
						{
							ok = false;
							break;
						}
						else
							mark = true;
					}
				}
			}
			else if (dic[i].length() + 1 == temp.length())
			{
				mark = false;
				for (int j = 0, k = 0; j < temp.length(); ++j, ++k)
				{
					if (temp[j] != dic[i][k])
					{
						if (mark)
						{
							ok = false;
							break;
						}
						else
						{
							mark = true;
							--k;
						}
					}
				}
			}
			else if (dic[i].length() == temp.length() + 1)
			{
				mark = false;
				for (int j = 0, k = 0; j < temp.length(); ++j, ++k)
				{
					if (temp[j] != dic[i][k])
					{
						if (mark)
						{
							ok = false;
							break;
						}
						else
						{
							mark = true;
							--j;
						}
					}
				}
			}
			else
				ok = false;
			if (ok)
				cout << ' ' << dic[i];
		}
		cout << endl;
	}
}

int main()
{
	string temp;
	while (cin >> temp && temp != "#")
	{
		dic.push_back(temp);
	}
	while (cin >> temp && temp != "#")
	{
		cout << temp;
		check(temp);
	}
	return 0;
}
#include<iostream>
#include<string>
using namespace std;
//水题
char board[25][20];

int main()
{
	int c;
	string code;
	while (cin >> c, c)
	{
		cin >> code;
		int delta = 1;
		int row = 0, col = 0;
		for (int i = 0; i < code.length(); ++i)
		{
			if (col == -1 || col == c)
			{
				delta = -delta;
				col += delta;
				++row;
			}
			board[row][col] = code[i];
			col += delta;
		}
		for (int i = 0; i < c; ++i)
			for (int j = 0; j <= row; ++j)
				cout << board[j][i];
		cout << endl;
	}
}
// https://www.acmicpc.net/problem/9548
// 무제
#include<iostream>
#include<string>
#include<algorithm>
#include<map>
using namespace std;

string str;
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	int T; cin >> T;
	while (T--)
	{
		cin >> str;
		string command;
		while (true)
		{
			cin >> command;
			if (command[0] == 'P')
			{
				int s, e; cin >> s >> e;
				for (int i = s; i <= e; i++)
				{
					cout << str[i];
				}
				cout << "\n";
			}
			else if (command[0] == 'I')
			{
				string temp; cin >> temp;
				int idx; cin >> idx;
				str.insert(idx, temp);
			}
			else if (command[0] == 'E')
				break;
		}
	}
}

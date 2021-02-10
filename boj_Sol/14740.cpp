// https://www.acmicpc.net/problem/14740
// 14740번 Highway Track

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int N;
vector<long long> getoil;
vector<long long> consume;
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> N;
	getoil.resize(N);
	long long oilsum = 0;
	for (int i = 0; i < N; i++)
	{
		cin >> getoil[i];
		oilsum += getoil[i];
	}
	consume.resize(N);
	long long consumesum = 0;
	consume[0] = 0;
	long long minim = 9999999999999;
	for (int i = 1; i < N; i++)
	{
		long long temp; cin >> temp;
		consume[i] = consume[i - 1] - temp + getoil[i-1];
		consumesum += temp;
		minim = min(minim, consume[i]);
	}
	long long temp; cin >> temp;
	consumesum += temp;
	consume[0] = consume[N - 1] - temp + getoil[N - 1];
	minim = min(minim, consume[0]);
	if (consumesum > oilsum)
	{
		cout << "0\n";
	}
	else
	{
		int cnt = 0;
		for (int i = 0; i < N; i++)
		{
			if (consume[i] == minim|| minim >0)
			{
				cnt++;
			}
		}
		cout << cnt << endl;
	}
}

// 님게임3 16895.cpp
#include<iostream>
#include<vector>

using namespace std;
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int N; cin >> N;
	vector<int> a;
	int ret = 0;
	for (int i = 0; i < N; i++)
	{
		int temp; cin >> temp;
		a.push_back(temp);
		ret = ret ^ temp;
	}
	if (ret)
	{
		int cnt = 0;
		for (int i = 0; i < N; i++)
		{
			ret = ret ^ a[i];
			if (ret < a[i])
				cnt++;
			ret = ret ^ a[i];
		}
		cout << cnt << "\n";
	}
	else
		cout << "0\n";	
}

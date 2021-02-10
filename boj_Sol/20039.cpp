// https://www.acmicpc.net/problem/20039
// 20039번 Coronavirus Trend

#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
int segTree[500001 * 4][4];

int N;
bool cmp(pair<int, int> a, pair<int, int> b)
{
	return a.second < b.second;
}
void update(int ptr, int s, int e, int i, int val, int type)
{
	if (s > i || e < i) return;
	if (s == e)
	{
		segTree[ptr][type] = max(segTree[ptr][type], val);
		return;
	}
	update(ptr * 2, s, (s + e) / 2, i, val, type);
	update(ptr * 2 + 1, (s + e) / 2 + 1, e, i, val, type);
	segTree[ptr][type] = max(segTree[ptr*2][type], segTree[ptr * 2 + 1][type]);
	
}

int getVal(int ptr, int s, int e, int l, int r, int type)
{
	if (s > r || e < l) return 0;
	if (l <= s && e <= r)
		return segTree[ptr][type];
	return max(getVal(ptr * 2, s, (s + e) / 2, l, r, type), getVal(ptr * 2 + 1, (s + e) / 2 + 1, e, l, r, type));
}
vector<pair<int, int>> v;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> N;
	v.resize(N + 1);
	for (int i = 1; i <= N; i++)
	{
		cin >> v[i].first;
		v[i].second = i;
	}
	sort(v.begin(), v.end());
	for (int i = 1; i <= N; i++)
	{
		v[i].first = i;
	}
	sort(v.begin(), v.end(), cmp);

	int ret = 0;
	// type1 = 마지막에 감소한 최대 길이, 2 = 마지막 전이랑 마지막이 감소최대길이,
	// 3 = 마지막에 상승한 최대 길이, 4 = 마지막 전이랑 마지막이 상승한 최대길이.
	for (int i = 1; i <= N; i++)
	{
		int type1 = getVal(1, 1, N, v[i].first + 1, N, 0);	// 이번에 하강해줘야해
		int type2_low = getVal(1, 1, N, 1, v[i].first, 1);	// 해방
		int type2_high = getVal(1, 1, N, v[i].first, N, 1); // 해방
		int type3 = getVal(1, 1, N, 1, v[i].first - 1, 2);	//  상승해줘야해!
		int type4_low = getVal(1, 1, N, 1, v[i].first, 3);	// 해방!
		int type4_high = getVal(1, 1, N, v[i].first, N, 3);	// 해방!
		if (type2_low >= 3)			//마지막이 상승
		{
			update(1, 1, N, v[i].first, type2_low + 1, 2);
		}
		if (type2_high >= 3)
		{
			update(1, 1, N, v[i].first, max(type1, type2_high) + 1, 1);
			ret = max(ret, max(type1, type2_high) + 1);
		}
		else if(type1 >= 2)
		{
			update(1, 1, N, v[i].first, type1 + 1, 1);		//해방됨
			ret = max(ret, type1 + 1);
		}
		else
		{
			update(1, 1, N, v[i].first, type1 + 1, 0);		//한번더 하락해줘야해
		}
		if (type4_low >= 3)
		{
			update(1, 1, N, v[i].first, max(type3, type4_low) + 1, 3);
			ret = max(ret, max(type3, type4_low) + 1);
		}
		else if (type3 >= 2)
		{
			update(1, 1, N, v[i].first, type3 + 1, 3);		//해방됨
			ret = max(ret, type3 + 1);
		}
		else
		{
			update(1, 1, N, v[i].first, type3 + 1, 2);		//한번더 상승해줘야해
		}
		if (type4_high >= 3)
		{
			update(1, 1, N, v[i].first, type4_high + 1, 0);
		}
		int maxim = max(type4_high, type4_low);
		maxim = max(type2_low, maxim);
		maxim = max(type2_high, maxim);
		if(maxim>2)
			ret = max(maxim, ret);
	}
	cout << ret << endl;

}

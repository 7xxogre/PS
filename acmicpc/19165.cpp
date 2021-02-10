// https://www.acmicpc.net/problem/19165
// Addition Robot

#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;

int N, Q;
const long long mod = 1e9 + 7;
pair<pair<long long, long long>, pair<long long, long long>> segTree[100004 * 4];
bool lazy[100004 * 4];

void setLazy(int ptr, int s, int e)
{
	pair<long long, long long> A = { segTree[ptr].second.second, segTree[ptr].second.first };
	pair<long long, long long> B = { segTree[ptr].first.second, segTree[ptr].first.first };
	segTree[ptr] = { A,B };
	if (s != e)
	{
		lazy[ptr * 2] = !lazy[ptr * 2];
		lazy[ptr * 2 + 1] = !lazy[ptr * 2 + 1];
	}
	lazy[ptr] = 0;
}

void init(int ptr, int s, int e, int idx, pair<pair<long long, long long>, pair<long long, long long>> val)
{
	if (s > idx || e < idx) return;
	if (s == e)
	{
		segTree[ptr] = val;
		return;
	}
	init(ptr * 2, s, (s + e) / 2, idx, val);
	init(ptr * 2 + 1, (s + e) / 2 + 1, e, idx, val);
	pair<long long, long long> A = { (segTree[ptr * 2 + 1].first.first * segTree[ptr * 2].first.first + segTree[ptr * 2 + 1].first.second * segTree[ptr * 2].second.first) % mod, (segTree[ptr * 2 + 1].first.first * segTree[ptr * 2].first.second + segTree[ptr * 2 + 1].first.second * segTree[ptr * 2].second.second) % mod };
	pair<long long, long long> B = { (segTree[ptr * 2 + 1].second.first * segTree[ptr * 2].first.first + segTree[ptr * 2 + 1].second.second * segTree[ptr * 2].second.first) % mod, (segTree[ptr * 2 + 1].second.first * segTree[ptr * 2].first.second + segTree[ptr * 2 + 1].second.second * segTree[ptr * 2].second.second) % mod };
	segTree[ptr] = { A,B };
}

void update(int ptr, int s, int e, int l, int r)
{
	if (lazy[ptr]) setLazy(ptr, s, e);
	if (s > r || e < l) return;
	if (l <= s && e <= r)
	{
		pair<long long, long long> A = { segTree[ptr].second.second, segTree[ptr].second.first };
		pair<long long, long long> B = { segTree[ptr].first.second, segTree[ptr].first.first };
		segTree[ptr] = { A,B };
		if (s != e)
		{
			lazy[ptr * 2] = !lazy[ptr * 2];
			lazy[ptr * 2 + 1] = !lazy[ptr * 2 + 1];
		}
		return;
	}
	update(ptr * 2, s, (s + e) / 2, l, r);
	update(ptr * 2 + 1, (s + e) / 2 + 1, e, l, r);
	pair<long long, long long> A = { (segTree[ptr * 2 + 1].first.first * segTree[ptr * 2].first.first + segTree[ptr * 2 + 1].first.second * segTree[ptr * 2].second.first) % mod, (segTree[ptr * 2 + 1].first.first * segTree[ptr * 2].first.second + segTree[ptr * 2 + 1].first.second * segTree[ptr * 2].second.second) % mod };
	pair<long long, long long> B = { (segTree[ptr * 2 + 1].second.first * segTree[ptr * 2].first.first + segTree[ptr * 2 + 1].second.second * segTree[ptr * 2].second.first) % mod, (segTree[ptr * 2 + 1].second.first * segTree[ptr * 2].first.second + segTree[ptr * 2 + 1].second.second * segTree[ptr * 2].second.second) % mod };
	segTree[ptr] = { A,B };

}

pair<pair<long long, long long>, pair<long long, long long>> getVal(int ptr, int s, int e, int l, int r)
{
	if (lazy[ptr]) setLazy(ptr, s, e);
	if (s > r || e < l) return { {1,0}, {0,1} };
	if (l <= s && e <= r)
	{
		return segTree[ptr];
	}
	pair<pair<long long, long long>, pair<long long, long long>> temp1 = getVal(ptr * 2, s, (s + e) / 2, l, r);
	pair<pair<long long, long long>, pair<long long, long long>> temp2 = getVal(ptr * 2 + 1, (s+e)/2+1, e, l, r);
	pair<long long, long long> A = { (temp2.first.first * temp1.first.first + temp2.first.second * temp1.second.first) % mod, (temp2.first.first * temp1.first.second + temp2.first.second * temp1.second.second) % mod };
	pair<long long, long long> B = { (temp2.second.first * temp1.first.first + temp2.second.second * temp1.second.first) % mod , (temp2.second.first * temp1.first.second + temp2.second.second * temp1.second.second) % mod };
	return { A,B };
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> Q;
	for (int i = 0; i <= 4*N; i++)        // I로 미리 넣어둠
		segTree[i] = { {1,0}, {0,1} };
	for (int i = 1; i <= N; i++)
	{
		char temp; cin >> temp;
		if (temp == 'A')      //a인 경우 pair<pair<int,int>,pair<int,int>>로 {{1,1},{0,1}}
		{
			init(1, 1, N, i, { {1,1}, {0,1} });
		}
		else	                //b인경우 pair<pair<int,int>,pair<int,int>>로 {{1,0}, {1,1}}해줌
		{
			init(1, 1, N, i, { {1,0}, {1,1} });
		}
	}
	while (Q--)
	{
		int com, L, R; long long A, B;
		cin >> com >> L >> R;
		if (com == 1)
		{
			update(1, 1, N, L, R);
		}
		else
		{
			cin >> A >> B;
			pair<pair<int, int>, pair<int, int>> P = getVal(1, 1, N, L, R);
			long long tempA = (A * P.first.first + B * P.first.second) % mod;
			long long tempB = (A * P.second.first + B * P.second.second) % mod;
			cout << tempA << " " << tempB << '\n';
		}
	}
}

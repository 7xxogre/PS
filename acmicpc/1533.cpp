// https://www.acmicpc.net/problem/1533

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
int N, S, E, T;
const long long MOD = 1e6+3;

vector<vector<long long>> m_pow(vector<vector<long long>> m, int cnt)       // 행렬 거듭제곱 O((N*5)^3*log(cnt))
{
	if (cnt == 0)
	{
		vector<vector<long long>> I(N * 5, vector<long long>(N * 5));
		for (int i = 0; i < N * 5; i++)
			I[i][i] = 1;
		return I;
	}
	vector<vector<long long>> res = m_pow(m, cnt / 2);
	vector<vector<long long>> ret(N * 5, vector<long long>(N * 5));
	for (int i = 0; i < N * 5; i++)
	{
		for (int j = 0; j < N * 5; j++)
		{
			long long temp = 0;
			for (int k = 0; k < N * 5; k++)
			{
				temp = (temp + res[i][k] * res[k][j]) % MOD;
			}
			ret[i][j] = temp;
		}
	}
	if (cnt % 2)
	{
		res = ret;
		for (int i = 0; i < N * 5; i++)
		{
			for (int j = 0; j < N * 5; j++)
			{
				long long temp = 0;
				for (int k = 0; k < N * 5; k++)
				{
					temp = (temp + res[i][k] * m[k][j]) % MOD;
				}
				ret[i][j] = temp;
			}
		}
	}
	return ret;
}


int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> S >> E >> T;
	vector<vector<long long>> adj(N*5, vector<long long>(N*5));
	// 어차피 5까지밖에 없으니까 한 정점을 5개로 나눠서 모든 가중치를 1로 만들어 행렬 제곱을 이용해 갯수를 세버리자
	for (int i = 0; i < N; i++)
	{
		string str;
		cin >> str;
		for (int j = 0; j < str.size(); j++)
		{
			if (str[j] != '0')
			{
				adj[i][N * (str[j] - '1') + j] = 1;
			}
		}
	}
	for (int i = 0; i < N; i++)         // 1개의 정점을 5개로 나눴으니 이어주자!
	{
		for (int j = 4; j > 0; j--)
		{
			adj[N * j + i][N * (j - 1) + i] = 1;
		}
	}
	vector<vector<long long>> ret = m_pow(adj, T);
	cout << ret[S - 1][E - 1] << "\n";
  // 시작점(S-1)에서 시작해 T분후의 목표지점(E-1)로 가는 길의 가짓수 = 행렬의 거듭제곱[S-1][E-1] (이산수학 복습)
}

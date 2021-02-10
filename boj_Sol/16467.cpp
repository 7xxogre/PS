// https://www.acmicpc.net/problem/16467
// 병아리의 변신은 무죄


#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int K, N;
const long long MOD = 1e8 + 7;      // 1억 7임에 주의!!
vector<vector<long long>> m_pow(vector<vector<long long>> m, int cnt)     //행렬 거듭 제곱
{
	if (cnt == 0)
	{
		vector<vector<long long>> I(K + 1, vector<long long>(K + 1));
		for (int i = 0; i <= K; i++)
			I[i][i] = 1;
		return I;
	}
	vector<vector<long long>>res = m_pow(m, cnt/2);
	vector<vector<long long>>ret(K + 1, vector<long long>(K + 1));
	for (int i = 0; i <= K; i++)
	{
		for (int j = 0; j <= K; j++)
		{
			long long temp = 0;
			for (int k = 0; k <= K; k++)
			{
				temp = (temp + res[i][k] * res[k][j]) % MOD;
			}
			ret[i][j] = temp;
		}
	}

	if (cnt % 2)
	{
		res = ret;
		for (int i = 0; i <= K; i++)
		{
			for (int j = 0; j <= K; j++)
			{
				long long temp = 0;
				for (int k = 0; k <= K; k++)
				{
					temp = (temp + res[i][k] * m[k][j]) % MOD;
				}
				ret[i][j] = temp;
			}
		}
	}
	return ret;
}

long long my_pow(long long a, int cnt)      // 나만의 정수 거듭제곱, math.h의 pow는 O(N)으로 너무 느려서 1억승을 하기는 힘들고 %연산도 귀찮음
{
	if (cnt == 0)
		return 1;
	long long ret = my_pow(a, cnt / 2);
	ret = (ret * ret) % MOD;
	if (cnt % 2)
		ret = (ret * a) % MOD;
	return ret;
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T; cin >> T;
	while (T--)
	{
		cin >> K >> N;
		if (K == 0)       // k = 0일때는 2^N 승
		{
			cout << my_pow(2, N) << "\n";
		}
		else              // K>0일때는 S[K][i+1] = S[K][i - 1 - K] + S[K][i]
		{
			vector<long long> initial(K + 1, 0);
			initial[K] = 1;
			vector<vector<long long>> start(K + 1, vector<long long>(K + 1));
			for (int i = 0; i < K; i++)
				start[i][i+1] = 1;
			start[K][0] = 1; start[K][K] = 1;
			vector<vector<long long>> res = m_pow(start, N);
			
			cout << res[K][K] << "\n";
		}
	}
}


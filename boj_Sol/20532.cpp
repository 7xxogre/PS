// https://www.acmicpc.net/problem/20532
// 20532번 정점 간 통신 네트워크
#include<iostream>
#include<vector>
#include<string.h>
#include<algorithm>
#include<math.h>

using namespace std;
int N;
int A[100001];
vector<vector<int>>adj;

long long cnt = 0;
int multiplecnt[100001]; 
int discovered[100001];
vector<vector<int>> divi;


void dfs(int here)
{
	cnt += multiplecnt[A[here]];
	
	for (int i : divi[A[here]])
	{
		++multiplecnt[i];
		if (discovered[i] && i != A[here])
			cnt += discovered[i];
	}
	++discovered[A[here]];
	for (int i : adj[here])
	{
		dfs(i);
	}
	for (int i : divi[A[here]])
	{
		--multiplecnt[i];
	}
	--discovered[A[here]];
}


int main()
{
	ios::sync_with_stdio(false); cout.tie(0); cin.tie(0);
	cin >> N;
	divi.resize(100001);
	for (int i = 1; i <= N; i++)
	{
		cin >> A[i];
		if (divi[A[i]].empty())
		{
			for (int j = 1; j * j <= A[i]; j++)	//약수 찾기
			{
				if (A[i] % j == 0)
				{
					divi[A[i]].push_back(j);
					if(j * j != A[i])
						divi[A[i]].push_back(A[i] / j);
				}
			}
		}
	}
	adj.resize(N+1);
	for (int i = 2; i <= N; i++)
	{
		int p; cin >> p;
		adj[p].push_back(i);
	}
	dfs(1);
	cout << cnt << "\n";
}

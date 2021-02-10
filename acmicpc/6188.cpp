// https://www.acmicpc.net/problem/6188
// Clear Cold Water

#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;
vector<vector<int>> v;
vector<int> dep;
int N, C;
void dfs(int here, int depth)
{
	dep[here] = depth;
	for (int i = 0; i < v[here].size(); i++)
	{	
		dfs(v[here][i], depth + 1);		
	}
}

int main()
{

	scanf("%d %d", &N, &C);
	v.resize(N);
	dep.resize(N);
	for (int i = 0; i < C; i++)
	{
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);
		a--; b--; c--;
		v[a].push_back(b);
		v[a].push_back(c);
	}
	dfs(0, 1);
	for (int i = 0; i < N; i++)
		printf("%d\n", dep[i]);
}

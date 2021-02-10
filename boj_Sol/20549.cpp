// https://www.acmicpc.net/problem/20549
// 20549번 인덕이의 고민

#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<string.h>
#include<math.h>
#include<queue>
using namespace std; 
int N, M;
bool check(int y, int x)
{
	if (x >= N || x < 0 || y >= N || y < 0) return 0;
	return 1;
}
vector<pair<int,pair<int, int>>> adj[50][50];
int A, B, C;
vector<pair<int, int>> food;		//y,x 순
vector<vector<int>> fooddist; int startx, starty;
vector<int> duck[5];
vector<int> dijk(int y, int x)
{
	priority_queue<pair<int, pair<int, int>>> pq;
	vector<vector<int>> dist(N, vector<int>(N, 987654321));
	
	pq.push({ 0, {y, x} });
	while (!pq.empty())
	{
		int cost = -pq.top().first;
		int y = pq.top().second.first;
		int x = pq.top().second.second;
		pq.pop();
		if (dist[y][x] <= cost)
			continue;
		dist[y][x] = cost;
		for (pair<int,pair<int,int>> there : adj[y][x])
		{
			int therecost = there.first + cost;
			if (dist[there.second.first][there.second.second] > therecost)
			{
				pq.push({ -therecost,there.second });
			}
		}
	}
	vector<int> ret;
	ret.push_back(dist[starty][startx]);
	for (int i = 0; i < M; i++)
	{
		
		ret.push_back(dist[food[i].first][food[i].second]);
	}

	return ret;
}

int mindist(int use, int here)
{
	if (use == (1 << M+1) - 1)
		return 0;
	int ret = 987654321;
	for (int i = 1; i < M+1; i++)
	{
		if (use & 1 << i)
		{
			continue;
		}
		else
		{
			ret = min(ret, mindist(use|(1<<i), i) + duck[here][i]);
		}
	}
	return ret;
}



int main()
{
	ios::sync_with_stdio(false); cout.tie(0); cin.tie(0);
	cin >> N;
	cin >> A >> B >> C;
	cin >> startx >> starty;
	cin >> M; food.resize(M);
	for (int i = 0; i < M; i++)
	{
		cin >> food[i].second >> food[i].first;
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			for (int k = i + 1; k < N; k++)		
			{
				adj[i][j].push_back({ C,{ k, j } });
				adj[k][j].push_back({ C,{ i,j } });
			}
			for (int k = j + 1; k < N; k++)
			{
				adj[i][j].push_back({ C,{i, k } });
				adj[i][k].push_back({ C, {i, j} });
			}
			//룩
			int temp = 1;
			while (check(i + temp, j + temp))
			{
				adj[i][j].push_back({ B, {i + temp, j + temp} });
				adj[i + temp][j + temp].push_back({ B, {i, j} });
				++temp;
			}
			temp = 1;
			while (check(i + temp, j - temp))
			{
				adj[i][j].push_back({ B, {i + temp, j - temp} });
				adj[i + temp][j - temp].push_back({ B, {i, j} });
				++temp;
			}
			// 비숍
			if (check(i + 1, j - 2))
			{
				adj[i + 1][j - 2].push_back({ A, {i, j} });
				adj[i][j].push_back({ A, {i + 1, j - 2} });
			}
			if(check(i+1, j+2))
			{
				adj[i + 1][j + 2].push_back({ A, {i, j} });
				adj[i][j].push_back({ A, {i + 1, j + 2} });
			}
			if(check(i+2, j+1))
			{
				adj[i + 2][j + 1].push_back({ A, {i, j} });
				adj[i][j].push_back({ A, {i + 2, j + 1} });
			}
			if(check(i+2, j-1))
			{
				adj[i + 2][j - 1].push_back({ A, {i, j} });
				adj[i][j].push_back({ A, {i + 2, j - 1} });
			}			
		}
	}
	
	duck[0] = dijk(starty, startx);
	for (int i = 0; i < M; i++)
		duck[i + 1] = dijk(food[i].first, food[i].second);

	cout << mindist(1, 0) << "\n";
	

}

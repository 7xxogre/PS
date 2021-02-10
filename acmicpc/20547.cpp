// https://www.acmicpc.net/problem/20547
// 신입생 청원이
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<string.h>
using namespace std;
int N, M;
vector<pair<long long, long long>> lecture;
map<string, int> ma;
long long adj[505][505];
long long cache[503][2000];

long long dp(int here, long long time)      // dp를 이용해서 here에 time시간에 있다면 앞으로 얻을수 있는 최대 수강시간
{
	if (time > 1600)
		return 0;
	long long& ret = cache[here][time];
	if (ret != -1)
		return ret;
	ret = 0;
	for (int i = 0; i < N; i++)
	{
		if (adj[here][i] != 987654321 && i != here)
		{
			if (lecture[i].second > lecture[here].second + adj[here][i])
			{
				ret = max(ret, dp(i, lecture[here].second + adj[here][i]) + lecture[here].second - max(lecture[here].first, time));
			}
			else if (lecture[i].second > time + adj[here][i])
			{
				ret = max(ret, dp(i, time + adj[here][i]));
			}
		}
	}
	ret = max(ret, lecture[here].second - max(time, lecture[here].first));
	return ret;
}




int main()
{
	ios::sync_with_stdio(false); cout.tie(0); cin.tie(0);
	memset(cache, -1, sizeof(cache));
	cin >> N >> M;
	lecture.resize(N);
	for (int i = 0; i < 502; i++)
		for (int j = 0; j < 502; j++)
			adj[i][j] = 987654321;
	for (int i = 0; i < 502; i++)
		adj[i][i] = 0;
	for (int i = 0; i < N; i++)
	{
		string str; cin >> str;
		ma[str] = i;
		string start, end; cin >> start >> end;
		int starttime = (10 * (start[0] - '0') + start[1] - '0') * 60;
		starttime += (10 * (start[3] - '0') + start[4] - '0');
		int endtime = (10 * (end[0] - '0') + end[1] - '0') * 60;
		endtime += (10 * (end[3] - '0') + end[4] - '0');
		lecture[i] = { starttime, endtime };
	}
	int startidx = -1;
	int startTime = 987654321;
	map<string, int>::iterator itr = ma.begin();
	for (itr; itr != ma.end(); itr++)
	{
		if (lecture[itr->second].first < startTime)
		{
			startTime = lecture[itr->second].first;
			startidx = itr->second;
		}
	}

	for (int i = 0; i < M; i++)
	{
		string sstr, estr; cin >> sstr >> estr;
		string w; cin >> w;
		int s = ma[sstr];
		int e = ma[estr];
		long long weight = (10 * (w[0] - '0') + w[1] - '0') * (long long)60;
		weight += (10 * (w[3] - '0') + w[4] - '0');
		adj[s][e] = min(adj[s][e], weight);
		adj[e][s] = adj[s][e];
	}
  // 
	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
	// 플로이드 끝

	long long ret = dp(startidx, 0);
	string sret = "";
	int hour = ret / 60;
	sret += (hour / 10) + '0';
	sret += (hour % 10) + '0';
	sret += ":";
	int minute = ret % 60;
	sret += (minute / 10) + '0';
	sret += (minute % 10) + '0';
	cout << sret << "\n";
}

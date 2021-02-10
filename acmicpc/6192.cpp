// https://www.acmicpc.net/problem/6192
// Cow Pie Treasures

#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;
vector<vector<int>> v;
int cache[101][101];
int R, C;
int gold(int row, int col)
{
	if (row < 0 || col < 0)
		return -987654321;
	if (row >= R || col >= C)
		return -987654321;
	if (col == 0)
	{
		if (row == 0)
			return v[0][0];
		else
			return -987654321;
	}
	
	int& ret = cache[row][col];
	if (ret != -1)
		return ret;

	ret = gold(row-1, col-1);
	ret = max(ret, gold(row, col-1));
	ret = max(ret, gold(row + 1, col - 1));
	ret += v[row][col];
	return ret;
}

int main()
{

	scanf("%d %d", &R, &C);
	v.resize(R);
	for (int i = 0; i < R; i++)
	{
		v[i].resize(C);
		for (int j = 0; j < C; j++)
		{
			scanf("%d", &v[i][j]);
		}
	}
	memset(cache, -1, sizeof(cache));
	int ret = gold(R - 1, C - 1);
	printf("%d\n", ret);
}

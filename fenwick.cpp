#include<iostream>
#include<vector>
using namespace std;
struct fenwick
{
	vector<long long int> tree;
	fenwick(int n) : tree(n + 1) {}
	long long int sum(int pos)
	{
		pos++;
		long long int ret = 0;
		while (pos > 0)
		{
			ret += tree[pos];
			pos = pos & (pos - 1);
		}
		return ret;
	}
	void add(int pos, long long int val)
	{
		pos++;
		while (pos < tree.size())
		{
			tree[pos] += val;
			pos += pos & (-pos);
		}
	}
};
int gu[1000000];

int main()
{
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);

	fenwick fenwic(N+1);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &gu[i]);
		fenwic.add(i, gu[i]);
	}
	int a, b, c;
	long long int cprime;
	for (int i = 0; i < M + K; i++)
	{
		scanf("%d", &a);
		if (a - 1) //ÇÕÀÏ½Ã
		{
			scanf("%d %d", &b, &c);
			printf("%lld\n", fenwic.sum(c-1) - fenwic.sum(b-2));
		}
		else
		{
			scanf("%d %lld", &b, &cprime);
			cprime = cprime - gu[b-1];
			gu[b-1] = gu[b-1] + cprime;
			fenwic.add(b-1, cprime);
		}
	}
}
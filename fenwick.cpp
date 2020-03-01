#include<iostream>
#include<vector>
using namespace std;
template<typename T>
struct fenwick
{
	vector<T> tree;
	fenwick(int n) : tree(n + 1) {}
	T sum(int pos)
	{
		pos++;
		T ret = 0;
		while (pos > 0)
		{
			ret += tree[pos];
			pos = pos & (pos - 1);
		}
		return ret;
	}
	void add(int pos, T val)
	{
		pos++;
		while (pos < tree.size())
		{
			tree[pos] += val;
			pos += pos & (-pos);
		}
	}
};

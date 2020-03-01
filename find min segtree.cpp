#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;




struct seg
{
	vector<int> segtree;	  // 최소를 구해주는 트리로 짬
	int len;
	seg(vector<int>& array)
	{
		len = array.size();
		segtree.resize(4 * len);
		init(array, 0, len - 1, 0);
	}
	int init(vector<int>& array, int left, int right, int node)
	{
		if (left == right)
			return array[node];
		int mid = (right + left) >> 1;
		return min(init(array, left, mid, node * 2), init(array, mid + 1, right, node * 2));	
	}
	int query(int left, int right, int noderight, int nodeleft, int node)
	{
		if (left > nodeleft || right < noderight)
			return 987654321;
		if (left <= noderight && nodeleft <= right)
			return segtree[node];
		int mid = (noderight + nodeleft) >> 1;
		return min(query(left, right, noderight, mid, node * 2), query(left, right, mid + 1, nodeleft, node * 2 + 1));
	}
	int query(int left, int right)		// 바깥에서 접근하는 용
	{
		return query(left, right, 0, len - 1, 0)
	}
	int update(int left, int right, int node, int idx, int val)
	{
		if (idx < left || right < idx)
			return 987654321;
		if (left == right)
			return segtree[node] = val;
		int mid = (right + left) >> 1;
		return segtree[node] = min(update(left, mid, node * 2, idx, val), update(mid + 1, right, node * 2 + 1, idx, val));
	}
	int update(int idx, int val) 
	{
		return update(0, len - 1, 0, idx, val);
	}
};
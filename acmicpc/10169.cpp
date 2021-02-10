# https://www.acmicpc.net/problem/10169

#include<iostream>
#include<string.h>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

int N, M;
int par[100005];
int height[100005];
int dep[100005];
vector<pair<pair<long long, int>, pair<int, int>>> edge;
vector<vector<pair<int, int>>> adj;
bool used[300005];
vector<pair<int,int>> parent;
long long rep[300005];

int find(int a)
{
    if (a == par[a]) return a;
    return par[a] = find(par[a]);
}
void merge(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a == b) return;

    if (height[a] > height[b])
        par[b] = a;
    else
    {
        par[a] = b;
        if (height[a] == height[b]) height[b]++;
    }
}
int Vcnt = 0;
void dfs(int here, int depth)
{
    dep[here] = depth;
    for (pair<int, int> there : adj[here])
    {
        if (dep[there.first] == 0)
        {
            parent[there.first] = { here, there.second };
            dfs(there.first, depth + 1);     
        }
    }
}
int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> M;
    for (int i = 0; i <= N; i++)
        par[i] = i;
    edge.resize(M);
    for (int i = 0; i < M; i++)
    {
        cin >> edge[i].second.first >> edge[i].second.second >> edge[i].first.first;
        edge[i].first.second = i;
    }
    sort(edge.begin(), edge.end());
    int cnt = 0;
    long long minimcost = 0;
    adj.resize(N + 1);
    for (int i = 0; i < edge.size(); i++)
    {
        if (cnt == N - 1) break;

        int u = edge[i].second.first;
        int v = edge[i].second.second;
        int w = edge[i].first.first;
        if (find(u) == find(v)) continue;
        
        merge(u, v);
        cnt++;
        minimcost += w;
        used[i] = true;
        adj[u].push_back({ v, i });
        adj[v].push_back({ u, i });
    }
    // 전체 mst완성, 그래프 완성
    parent.resize(N+1);
    parent[1] = { 1,0 };
    
    dfs(1, 1);
    // 루트가 1인 트리 완성

    memset(rep, -1, sizeof(rep));
    for (int i = 0; i <= N; i++)
        par[i] = i;
    // 윾파로 풀자! O(N)걸림
    for (int i = 0; i < edge.size(); i++)
    {
        if (!used[i])       // mst에 사용 안된 엣지면! u와 v 단순 경로 내에 있는 모든 간선은 이 간선으로 대체 가능하니까 그 간선을 대체하는 최소값을 찾으면 됨
        {                   // 오름차순으로 정렬 되어있으므로 부모를 따라 가다가 대체 가능한 값이 있는 간선이 나오면 다음 사용안한 간선 찾아서 반복 해주면 됨
            int u = find(edge[i].second.first);
            int v = find(edge[i].second.second);
            long long w = edge[i].first.first;
            while (u != v)
            {                
                if (dep[u] < dep[v])
                {
                    int parv = parent[v].first;
                    int edgenum = parent[v].second;
                    if (rep[edgenum] == -1)
                    {
                        rep[edgenum] = w;
                        par[v] = parv;
                    }
                }
                else
                {
                    int paru = parent[u].first;
                    int edgenum = parent[u].second;
                    if (rep[edgenum] == -1)
                    {
                        rep[edgenum] = w;
                        par[u] = paru;
                    }
                }
                u = find(u);
                v = find(v);
            }
        }
    }
    
    vector<pair<int, long long>> ret;
    for (int i = 0; i < edge.size(); i++)
    {
        if (used[i])    // 기존 mst에 사용된거라면...
        {
            int u = edge[i].second.first;
            int v = edge[i].second.second;
            int w = edge[i].first.first;
            if (rep[i] == -1)       // 대체 불가능하다면...
                ret.push_back({ edge[i].first.second, -1 });
            else          // 대체 가능
                ret.push_back({ edge[i].first.second, minimcost + rep[i] - w });
        }
        else            // 아니면 걍 mst 리턴
        {
            ret.push_back({ edge[i].first.second, minimcost });
        }
    }
    
    // 입력 순서대로 다시 정렬
    sort(ret.begin(), ret.end());
    for (int i = 0; i < ret.size(); i++)
        cout << ret[i].second << "\n";
    return 0;
}

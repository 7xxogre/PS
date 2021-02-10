// https://www.acmicpc.net/problem/19955
// 침략전쟁

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<algorithm>
#include<queue>
#include<string.h>
using namespace std;
int day = 0;
int N, M, Q, Nsq;
int country[1000001];
bool visit[2005][2005];	bool expanding = true;
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
int lastupdate[2000 * 2000 + 1];  // 자동전투 끝난후엔 공격이 일어나거나 쿼리가 들어올때만 변경됨
int vcnt = 0;							//가상부모 갯수세기 최대 2000000개 가능
int vptorp[2000003];						// 가상부모를 받으면 실제 부모를 리턴
int ran[2000003];

int parent[2000 * 2000 + 1 + 2000003];
long long int siz[2000 * 2000 + 1];
long long int mili[2000 * 2000 + 1];
inline bool Range(int x, int y) {
	if (y<1 || x<1 || y>N || x>N)return false;
	return true;
}
int find(int u) {
	if (u == parent[u]) return u;
	return parent[u] = find(parent[u]);
}
void merge(int a, int b)			// a는 주인없는땅 b가 루트
{
	b = find(b);		//가상부모찾기
	if (a == b)
		return;
	parent[a] = b;
	siz[vptorp[b - Nsq]]++;			//진짜부모로 바꿔서 size++
}
void fight(int a, int b)
{
	int va = find(a), vb = find(b);								// 가상부모 가리키기
	int pa = vptorp[va - Nsq], pb = vptorp[vb - Nsq];			// 진짜 부모 가리키기
	if (pa == pb)
		return;
	mili[pa] += ((long long)day - (long long)lastupdate[pa]) * siz[pa];
	mili[pb] += ((long long)day - (long long)lastupdate[pb]) * siz[pb];
	lastupdate[pa] = day;
	lastupdate[pb] = day;
	
	if (mili[pa] > mili[pb])	//a국가가 b국가보다 군사수가 많다면..
	{
		mili[pa] -= mili[pb];
		mili[pb] = 0;
		if (siz[pb] != 1) {
			siz[pa] += siz[pb] - 1;
			siz[pb] = 1;


			vptorp[vb - Nsq] = pa;			// pb의 가상부모의 진짜 부모를 pa를 가리키게...
			if (ran[vb - Nsq] > ran[va - Nsq])
			{
				swap(vb, va);
			}
			parent[vb] = va;  // pb의 가상부모를 pa의 가상부모를 가리키게...

			if (ran[vb - Nsq] == ran[va - Nsq])
				ran[va - Nsq]++;
			parent[pb] = (++vcnt) + Nsq;			// pb의 새로운 가상부모 만들어주기
			vptorp[vcnt] = pb;				//pb의 새 가상부모에게 진짜 부모 연결
		}
	}
	else if (mili[pa] < mili[pb])
	{
		mili[pb] -= mili[pa];
		mili[pa] = 0;
		if (siz[pa] != 1) {
			siz[pb] += siz[pa] - 1;
			siz[pa] = 1;

			vptorp[va - Nsq] = pb;			// pa의 가상부모의 진짜 부모를 pb를 가리키게...
			if (ran[vb - Nsq] < ran[va - Nsq])
			{
				swap(vb, va);
			}
			parent[va] = vb;  // pa의 가상부모를 pb의 가상부모를 가리키게...	
			if (ran[vb - Nsq] == ran[va - Nsq])
				ran[vb - Nsq]++;

			parent[pa] = (++vcnt) + Nsq;			// pa의 새로운 가상부모 만들어주기
			vptorp[vcnt] = pa;				//pa의 새 가상부모에게
		}
	}
}

int main()
{
	scanf("%d %d %d", &N, &M, &Q);
	Nsq = N * N;

	for (int i = 0; i < 2000 * 2000 + 1 + 2000003; i++)
	{
		parent[i] = i;
	}

	queue<pair<int, int>> q;
	for (int i = 1; i <= M; i++)// 전처리
	{
		int x, y; long long int soldier;
		scanf("%d %d %lld", &x, &y, &soldier);
		country[i] = (x - 1) * N + y;
		visit[x][y] = 1;
		mili[country[i]] = soldier;
		parent[country[i]] = Nsq + (++vcnt);
		vptorp[vcnt] = country[i];
		q.push({ x,y });
		siz[country[i]]++;
	}


	while (Q--)
	{
		int command; int t;
		scanf("%d %d", &command, &t);

		if (!q.empty())
		{
			// 병사수 업데이트는 필요할때만!
			for (int da = day + 1; da <= t; da++) {
				int _size = q.size();
				if (!_size)
					break;
				queue<pair<int, int>> qprime;
				for (int i = 0; i < _size; i++)
				{
					int x = q.front().first, y = q.front().second;
					q.pop();
					int p = (x - 1) * N + y;
					for (int j = 0; j < 4; j++)  // bfs
					{
						int nx = x + dx[j];
						int ny = y + dy[j];
						if (Range(nx, ny))
						{
							if (!visit[nx][ny])  // 방문 안함-> 빈 영토	
							{
								visit[nx][ny] = 1;
								int here = find(p);
								here = vptorp[here - Nsq];	// 이 영토의 주인이 될 수도
								mili[here] += ((long long)da - (long long)lastupdate[here]) * siz[here];
								lastupdate[here] = da; // da일일때의 전략단계까지 업데이트했단뜻
								for (int l = 0; l < 4; l++)  // 빈영토 주변 병사수가 많고 가장 번호가 낮은 나라 뽑기
								{
									int nnx = nx + dx[l];
									int nny = ny + dy[l];
									if (Range(nnx, nny))
									{
										int there = find((nnx - 1) * N + nny);		//가상부모 찾기

										if (there > Nsq)   // 주변에 또 다른 국가의 영역 가상부모가 N*N이상이면 영토있는거임
										{
											there = vptorp[there - Nsq];
											if (there != here)  // 같은 국가가 아니라면
											{
												mili[there] += ((long long)da - (long long)lastupdate[there]) * siz[there];
												lastupdate[there] = da; // da일일때의 전략단계까지 업데이트했단뜻
												if (mili[here] < mili[there])  //병사수 부족
												{
													here = there;
												}
												else if (mili[here] == mili[there])  // 병사수 같다
												{
													here = (here > there ? there : here);
												}
											}
										}
									}
								}
								qprime.push({ (nx - 1) * N + ny, here });
								
								q.push({ nx, ny });
							}
						}
					}
				}
				while (!qprime.empty())			//이날 영토 영입
				{
					int p = qprime.front().first, capi = qprime.front().second;
					
					merge(p, capi);
					qprime.pop();
				}
			}
		}
		
		day = t;

		if (day == t)
		{
			if (command == 1)		// 공격하기
			{
				int xa, xb, ya, yb;
				scanf("%d %d %d %d", &xa, &ya, &xb, &yb);
				int ca = (xa - 1) * N + ya, cb = (xb - 1) * N + yb;
				fight(ca, cb);
			}
			else					// 소유 국가 병사수 출력
			{
				int xc, yc;
				scanf("%d %d", &xc, &yc);
				int p = (xc - 1) * N + yc;
				p = find(p);		//가상 부모
				p = vptorp[p - Nsq];		//진짜 부모
				
				mili[p] += ((long long)day - (long long)lastupdate[p]) * siz[p];
				lastupdate[p] = day;
				
				printf("%lld\n", mili[p]);
			}
		
		}
		
	}
	return 0;
}



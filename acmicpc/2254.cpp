// https://www.acmicpc.net/problem/2254
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
int N;
int px, py;

struct Point // 기하 문제이므로 좌표 구조체를 짜줍니다.
{
	int x, y;
	int p, q;
	bool used;
	Point(int x = 0, int y = 0, int p = 1, int q = 0)
	{
		this->x = x;
		this->y = y;
		this->q = q;
		this->p = p;
		used = false;
	}
	bool operator<(const Point O)     // 정렬을 위한 cmp함수
	{
		if (1LL * this->q * O.p != 1LL * this->p * O.q)
			return 1LL * this->q * O.p < 1LL * this->p * O.q;
		if (this->y != O.y)
			return this->y < O.y;
		return this->x < O.x;
	}
};
bool cmp(Point A, Point B)        // y좌표값만 보고 정렬하기
{
	if (A.y != B.y)
		return A.y < B.y;
	return A.x < B.x;
}

long long ccw(Point& A, Point& B, Point& C)     // ccw
{
	return 1LL * (B.x - A.x) * (C.y - A.y) - 1LL * (B.y - A.y) * (C.x - A.x);
}

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  
	vector<Point> p;
	cin >> N >> px >> py;
	p.push_back(Point(px, py));
	for (int i = 0; i < N; i++)
	{
		int pillarx, pillary; cin >> pillarx >> pillary;
		p.push_back(Point(pillarx, pillary));
	}
  
	// 외부 겹의 갯수
  int cnt = 0;
	
	while (1)
	{
		sort(p.begin(), p.end(), cmp);		// y 좌표순 정렬
		int crix = -1, criy = -1;			// 기준점
		int start = -1;
		for (int i = 0; i <= N; i++)  // 사용 안한 점 중 y좌표 최솟 값을 기준점으로
		{
			if (!p[i].used)
			{
				crix = p[i].x;
				criy = p[i].y;
				start = i;
				break;
			}
		}
    
		for (int i = start + 1; i <= N; i++)		// 기준점으로부터의 상대 좌표
		{
			if (!p[i].used)
			{
				p[i].p = p[i].x - p[start].x;
				p[i].q = p[i].y - p[start].y;
			}
		}
		p[start].p = 1; p[start].q = 0;
		sort(p.begin() + start+1, p.end());		//기준점은 고정, 기준점 보다 y좌표가 위인 점들을 기준점에 시계방향으로 정렬
    
    // 볼록 껍질 만들기
		stack<int> S;
		S.push(start);
		p[start].used = true;
		if (p[start].x == px && p[start].y == py)     //기준점이면..
			break;

		for (; start <= N; start++)         // 다음 사용 안한 점 찾기
			if (!p[start].used)
				break;
		S.push(start);
		p[start].used = true;
		if (p[start].x == px && p[start].y == py)     //기준점이면..
			break;
		int prison_idx = -1;
    // 볼록 껍질 생성
		for (int i = start + 1; i <= N; i++)
		{
			if (!p[i].used)
			{
				if (p[i].x == px && p[i].y == py)
				{
					prison_idx = i;
				}
				while (S.size() >= 2)
				{
					int first = S.top(); S.pop();
					int second = S.top();
					if (ccw(p[second], p[first], p[i]) > 0)
					{
						S.push(first);
						break;
					}
					else
					{
						p[first].used = false;
					}
				}
				S.push(i);
				p[i].used = true;
			}
		}
		if (p[prison_idx].used)           // 이번 볼록 껍질에 감옥인 좌표를 사용했다면 break
			break;
		++cnt;
	}
	cout << cnt << "\n";
}

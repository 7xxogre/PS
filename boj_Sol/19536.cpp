// https://www.acmicpc.net/problem/19536
// UCPC 2020 예선 감자 농장
#include<iostream>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;

int N, Q;
int pote[1000005];
vector<long long>prefix_left, prefix_right;
vector<int>poteto_left, poteto_right;

string str;

int main()
{
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N >> Q;
	cin >> str;
	str = "." + str + ".";
	int leftR = 0, rightR = 0;
	long long sum = 0;
	for (int i = 1; i <= N; i++)			// 최좌측 R 찾기
	{
		if (str[i] == 'P')
		{
			poteto_left.push_back(i);
			sum += i;
			prefix_left.push_back(sum);
		}
		else if (str[i] == 'R')
		{
			leftR = i;
			break;
		}
	}

	for (int i = 0; i < poteto_left.size() + 1; i++) 			// 감자 개수만큼 leftR 패딩 넣어주기
	{
		sum += leftR;
		prefix_left.push_back(sum);
	}

	sum = 0;
	
	for (int i = N; i > 0; --i)					// 최우측 R 찾기
	{
		if (str[i] == 'R')
		{
			rightR = i;
			break;
		}
	}

	for (int i = rightR + 1; i <= N; ++i)
	{
		if (str[i] == 'P')
		{
			poteto_right.push_back(i);
		}
	}

	for (int i = 0; i < poteto_right.size(); i++)
	{
		sum += poteto_right[i];
		prefix_right.push_back(sum);
	}

	
	int left = leftR, cnt = 0;
	int iter = left + 1;
	while (left < rightR)				// 중간에 못나오는 구간 수확량 세기
	{
		if (str[iter] == 'P')
			cnt++;
		else if (str[iter] == 'R')
		{
			for (int i = left; i < iter; i++)
			{
				pote[i] = cnt;
			}
			left = iter + 1;
			cnt = 0;
		}
		iter++;
	}


	int poteto_right_size = poteto_right.size();
	int poteto_left_size = poteto_left.size();
	while (Q--)
	{
		int a; cin >> a;
		if (leftR < a && a < rightR) 				// 못 나오는 구간
		{
			cout << pote[a] << " " << "-1\n";
		}
		else
		{
			if (a < leftR)							// 왼쪽으로 나오기!
			{
				int k = lower_bound(poteto_left.begin(), poteto_left.end(), a) - poteto_left.begin();
				if (k == 0) 						// 제일 첫 감자 뽑고 나오기
				{
					if (poteto_left.size())
						cout << 1 << " " << poteto_left[0] * 2 - a << "\n";
					else
						cout << 0 << " " << leftR * 2 - a << "\n";
				}
				else 
				{
					long long cost;
					if (k < poteto_left.size())		// 감자들 사이에서 시작
						cost = poteto_left[k] - (long long)a + (prefix_left[k + k] - prefix_left[k]) * 2 - (prefix_left[k - 1]) * 2 + poteto_left[k];
					else							// 왼쪽에 있는 감자 이후에서 시작
						cost = leftR - (long long)a + (prefix_left[k + k] - prefix_left[k]) * 2 - (prefix_left[k - 1]) * 2 + leftR;
					cout << min(k + k + 1, poteto_left_size) << " " << cost << "\n";
				}
			}
			else 						// 오른쪽으로 나올 수 있는 경우
			{
				if (rightR)  			// R이 있는 경우 -> 오른쪽으로 나옴
				{
					int k = lower_bound(poteto_right.begin(), poteto_right.end(), a) - poteto_right.begin();
					if (k == (int)poteto_right.size())
					{
						cout << 0 << " " << N + 1 - a << '\n';
					}
					else
					{
						long long cost = poteto_right[k] * 2LL - (long long)a;
						cost = cost + (prefix_right[poteto_right_size - 1] - prefix_right[k]) * 2;
						if (k < (poteto_right_size - k))		//R을 사용시
						{
							int Rtimes = k * 2 - poteto_right_size;
							cost = cost + 1LL * rightR * (Rtimes) * 2;
							if (k)
							{
								cost = cost - prefix_right[k - 1] * 2;
							}
						}
						else
						{
							if (k - 1 - (poteto_right_size - k) == -1)
							{
								cost = cost - prefix_right[k - 1] * 2;
							}
							else
							{
								cost = cost - (prefix_right[k - 1] - prefix_right[k - 1 - (poteto_right_size - k)]) * 2;
							}
						}
						cost += 1LL * N + 1LL;
						cout << min((poteto_right_size - k) * 2, poteto_right_size) << " " << cost << "\n";
					}
				}
				else					// R이 하나도 없는 경우
				{
					int k = lower_bound(poteto_right.begin(), poteto_right.end(), a) - poteto_right.begin();
					if (k == (int)poteto_right.size())
					{
						cout << 0 << " " << N + 1 - a << '\n';
					}
					else
					{					
						long long cost;
						if (k >= (poteto_right_size + 1) / 2)		// 우로 탈출
						{
							cost = poteto_right[k] * 2LL - (long long)a;
							cost = cost + (prefix_right[poteto_right_size - 1] - prefix_right[k]) * 2;
							if (k - 1 - (poteto_right_size - k) == -1)
							{
								cost = cost - prefix_right[k - 1] * 2;
							}
							else
							{
								cost = cost - (prefix_right[k - 1] - prefix_right[k - 1 - (poteto_right_size - k)]) * 2;
							}
							cost += (N + 1) * 1LL;
							cout << (poteto_right_size - k) * 2 << " " << cost << "\n";
						}
						else								// 좌로 탈출
						{
							if (k == 0)
							{
								if (poteto_left.size())
									cout << 1 << " " << poteto_left[0] * 2 - a << "\n";
								else
									cout << 0 << " " << leftR * 2 - a << "\n";
							}
							else 
							{
								cost = poteto_left[k] - (long long)a + (prefix_left[k + k] - prefix_left[k]) * 2 - (prefix_left[k - 1]) * 2 + poteto_left[k];
								cout << k * 2 + 1 << " " << cost << "\n";
							}
						}
						
					}
				}
			}
		}
	}

	return 0;
}
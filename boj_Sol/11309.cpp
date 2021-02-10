// https://www.acmicpc.net/problem/11309
// 11309번 파워!!달걀

#include <iostream>

using namespace std;

long long dp[40][40];           

int main() {
    for (int i = 1; i <= 32; i++) dp[1][i] = i;

   
    for (int i = 2; i <= 32; i++) {     //i개의 달걀
        dp[i][0] = 0;
        for (int j = 1; j <= 32; j++) {     // j번 던지기
            dp[i][j] = dp[i - 1][j - 1] + dp[i][j - 1] + 1;
        }       // i개의 달걀로 j번 던지기 = i-1개의 달걀로 j-1번 던지기(깨진경우) + i개의 달걀로 j-1번 던지기(안깨진경우) + 1 층수 커버 가능
    }

    int t;
    cin >> t;
    for (int test = 0; test < t; test++) {
        int n, k;
        cin >> n >> k;
        int idx = 0;
        for (; idx <= 32; idx++) {        
            if (dp[k][idx] >= n) break;
        }

        if (dp[k][idx] >= n)      // 커버 가능한 높이라면
        { 
            cout << idx << endl;
        }
        else                      // 커버 불가능
        { 
            cout << "Impossible" << endl;
        }
    }

    return 0;
}

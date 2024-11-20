#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 물건을 담을 수 있는 최대 가치를 계산하는 함수 (0/1 배낭 문제)
int knapsack(int W, const vector<int> &weights, const vector<int> &values, int n)
{
    // DP 테이블을 초기화 (배낭의 무게 W + 1 크기, 물건의 개수 n + 1 크기로 2차원 배열 생성)
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // DP 테이블을 채움
    for (int i = 1; i <= n; i++)
    { // i는 현재 고려 중인 물건 번호
        for (int w = 1; w <= W; w++)
        { // w는 현재 배낭의 용량
            if (weights[i - 1] <= w)
            {
                // 현재 물건을 넣는 경우와 넣지 않는 경우 중 최대 가치를 선택
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            }
            else
            {
                // 현재 물건의 무게가 배낭 용량보다 큰 경우, 현재 물건을 넣을 수 없음
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // DP 테이블의 마지막 값이 최대 가치
    return dp[n][W];
}

int main()
{
    int n, W;
    cin >> n >> W;

    vector<int> weights(n), values(n);

    for (int i = 0; i < n; i++)
    {
        cin >> weights[i] >> values[i];
    }

    int max_value = knapsack(W, weights, values, n);
    cout << max_value << endl; // 최대 가치 값만 출력

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

vector<vector<int>> dp;    // 최소 곱셈 횟수를 저장하는 DP 테이블
vector<vector<int>> split; // 최적의 곱셈 순서를 기록하는 테이블

// 최소 곱셈 횟수를 찾고 곱셈 순서를 저장하는 함수
int matrixChainOrder(const vector<int> &dims, int n)
{
    dp.assign(n, vector<int>(n, 0));
    split.assign(n, vector<int>(n, 0));

    for (int chainLen = 2; chainLen < n; ++chainLen)
    {
        for (int i = 1; i < n - chainLen + 1; ++i)
        {
            int j = i + chainLen - 1;
            dp[i][j] = INT_MAX;

            for (int k = i; k < j; ++k)
            {
                int cost = dp[i][k] + dp[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                    split[i][j] = k;
                }
            }
        }
    }
    return dp[1][n - 1]; // 최소 곱셈 횟수 반환
}

// 최적의 곱셈 순서를 출력하는 함수
string printOptimalOrder(int i, int j)
{
    if (i == j)
    {
        return "M" + to_string(i); // 단일 행렬은 "M1", "M2" 등으로 표시
    }
    return "(" + printOptimalOrder(i, split[i][j]) + printOptimalOrder(split[i][j] + 1, j) + ")";
}

int main()
{
    int n;
    cin >> n;

    vector<int> dims(n + 1); // 행렬의 크기를 저장할 배열
    for (int i = 0; i < n; ++i)
    {
        int rows, cols;
        cin >> rows >> cols;
        dims[i] = rows;     // 각 행렬의 행 크기를 저장
        dims[i + 1] = cols; // 마지막 열 크기를 저장
    }

    int minCost = matrixChainOrder(dims, n + 1);
    cout << minCost << endl;
    cout << printOptimalOrder(1, n) << endl;

    return 0;
}

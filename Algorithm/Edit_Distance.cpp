#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    string S, T;
    cin >> S >> T;

    vector<vector<int>> vec(S.size() + 1, vector<int>(T.size() + 1));

    for (int i = 0; i < S.size() + 1; i++)
    {
        vec[i][0] = i;
    }

    for (int i = 0; i < T.size() + 1; i++)
    {
        vec[0][i] = i;
    }

    for (int i = 1; i < S.size() + 1; i++)
    {
        for (int j = 1; j < T.size() + 1; j++)
        {
            int temp;
            if (S[i - 1] == T[j - 1])
                temp = 0;
            else
                temp = 1;
            vec[i][j] = min(min(vec[i][j - 1] + 1, vec[i - 1][j] + 1), vec[i - 1][j - 1] + temp);
        }
    }
    cout << vec[S.size()][T.size()];
}
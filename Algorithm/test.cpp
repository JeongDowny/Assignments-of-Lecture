#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 1e9
using namespace std;

void dajik(vector<vector<int>> &graph, vector<int> &nodes, int n, int start) // 다익스트라 함수
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    nodes[start] = 0;

    while (!pq.empty())
    {
        int weight = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        for (int i = 1; i <= n; i++) // 1부터 n까지
        {
            if (graph[node][i] == 0)
                continue;

            int nextWeight = graph[node][i];
            int nextNode = i;
            int newWeight = weight + nextWeight;

            if (nodes[nextNode] > newWeight) // 원래 가중치보다 새로운 가중치가 작을 때 업데이트
            {
                nodes[nextNode] = newWeight;
                pq.push({newWeight, nextNode});
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1, vector<int>(n + 1, 0)); // n+1로 설정
    vector<int> nodes(n + 1, INF);                           // n+1로 설정

    for (int i = 0; i < m; i++)
    {
        int temp1, temp2, temp3;
        cin >> temp1 >> temp2 >> temp3;

        graph[temp1][temp2] = temp3;
        graph[temp2][temp1] = temp3;
    }

    dajik(graph, nodes, n, 1); // start를 1로 수정

    for (int i = 1; i <= n; i++) // 1부터 n까지 출력
    {
        cout << i << ' ' << (nodes[i] == INF ? -1 : nodes[i]) << '\n'; // INF인 경우 -1 출력
    }

    return 0;
}
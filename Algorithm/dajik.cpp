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
    while (!pq.empty()) // 큐가 빌 때까지 반복
    {
        int weight = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        for (int i = 1; i < n; i++)
        {
            if (graph[node][i] == 0) // 입력으로 주어지지 않은 간선은 무시
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

    vector<vector<int>> graph(n, vector<int>(n, 0));
    vector<int> nodes(n, INF);
    for (int i = 0; i < m; i++) // 입력 받기
    {
        int temp1, temp2, temp3;
        cin >> temp1 >> temp2 >> temp3;
        graph[temp1][temp2] = temp3;
        graph[temp2][temp1] = temp3;
    }

    dajik(graph, nodes, n, 0);

    for (int i = 1; i < nodes.size(); i++) // 노드와 노드까지의 최단거리 출력
    {
        cout << i << ' ' << nodes[i] << '\n';
    }
}
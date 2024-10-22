#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge // 출발점, 도착점, 가중치
{
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};

void primMST(int V, vector<vector<pair<int, int>>> &node) // 프림 함수
{
    vector<bool> visited(V, false);                                                                                      // 방문 여부 기록
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq; // 가중치를 기준으로 오름차순 정렬하는 우선순위 큐 정의

    visited[0] = true;
    for (int i = 0; i < node[0].size(); ++i) // 0에서 도달할 수 있는 노드를 큐에 푸쉬
    {
        int v = node[0][i].first;
        int w = node[0][i].second;
        pq.push(make_pair(w, make_pair(0, v)));
    }

    vector<Edge> mst; // 최소 신장 트리

    while (!pq.empty() && mst.size() < V - 1)
    {
        pair<int, pair<int, int>> now = pq.top();
        pq.pop();

        int u = now.second.first;
        int v = now.second.second;
        int w = now.first;

        if (!visited[v]) // 방문 안 한 노드일 때 mst에 추가, 방문 여부 기록, v에서 방문할 수 있는 노드를 큐에 추가
        {
            mst.push_back(Edge(u, v, w));
            visited[v] = true;

            for (int i = 0; i < node[v].size(); ++i)
            {
                int next = node[v][i].first;
                int weight = node[v][i].second;
                if (!visited[next])
                {
                    pq.push(make_pair(weight, make_pair(v, next)));
                }
            }
        }
    }

    for (Edge &e : mst) // mst출력
    {
        cout << e.u << " " << e.v << " " << e.w << endl;
    }
}

int main()
{
    int V, E;
    cin >> V >> E;

    vector<vector<pair<int, int>>> node(V);

    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        node[u].push_back(make_pair(v, w));
        node[v].push_back(make_pair(u, w));
    }

    primMST(V, node);

    return 0;
}
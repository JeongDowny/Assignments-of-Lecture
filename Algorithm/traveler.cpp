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

vector<Edge> primMST(int V, vector<vector<int>> &node) // 프림 함수 (가중치 배열로 수정)
{
    vector<bool> visited(V, false);                                                                                      // 방문 여부 기록
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq; // 가중치를 기준으로 오름차순 정렬하는 우선순위 큐 정의

    visited[0] = true;
    for (int i = 0; i < V; ++i) // 0에서 도달할 수 있는 노드를 큐에 푸쉬
    {
        if (node[0][i] != 0) // 0번 마을에서 연결된 마을만 큐에 푸쉬
            pq.push(make_pair(node[0][i], make_pair(0, i)));
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

            for (int i = 0; i < V; ++i)
            {
                if (node[v][i] != 0 && !visited[i]) // 연결된 노드만 탐색
                {
                    pq.push(make_pair(node[v][i], make_pair(v, i)));
                }
            }
        }
    }
    return mst;
}

void dfs(int node, vector<vector<int>> &graph, vector<bool> &visited, vector<int> &path)
{
    path.push_back(node);

    for (int next : graph[node])
    {
        if (!visited[next])
        {
            dfs(next, graph, visited, path);
        }
    }
}

vector<int> findPath(vector<vector<int>> &graph)
{
    vector<int> path;
    vector<bool> visited(graph.size(), false);
    dfs(0, graph, visited, path);
    path.push_back(0);
    return path;
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> node(n, vector<int>(n, 0));

    // 마을 간의 거리 입력 받기
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> node[i][j];
        }
    }

    // MST 계산
    vector<Edge> mst = primMST(n, node);

    // 최소 신장 트리 출력
    cout << "MST: ";
    for (const auto &edge : mst)
    {
        cout << "(" << edge.u << ", " << edge.v << ") ";
    }
    cout << endl;

    vector<int> travlePath = findPath(node);
    // 여행 경로 출력
    cout << "방문 경로: ";
    for (int i = 0; i < travlePath.size(); i++)
    {
        cout << travlePath[i] << ' ';
    }
    cout << travlePath[0] << endl; // 마지막에 시작점을 추가하여 경로가 순환되게 함

    return 0;
}
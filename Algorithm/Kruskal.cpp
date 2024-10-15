#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

// compare 함수 이름 수정
int compare(const tuple<int, int, int> &a, const tuple<int, int, int> &b)
{
    return get<2>(a) < get<2>(b);
}

// find 함수 구현
int find(int a, vector<int> &parent)
{
    if (parent[a] != a)
        parent[a] = find(parent[a], parent); // 경로 압축
    return parent[a];
}

// union 함수 구현
void union_sets(int a, int b, vector<int> &parent)
{
    int rootA = find(a, parent);
    int rootB = find(b, parent);
    if (rootA != rootB)
        parent[rootB] = rootA; // 부모를 설정하여 두 집합을 합침
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> vec;
    vector<tuple<int, int, int>> vertex;
    vector<int> parent(n);

    for (int i = 0; i < n; i++) // parent 초기화
    {
        parent[i] = i;
    }

    for (int i = 0; i < m; i++)
    {
        int temp1, temp2, temp3;
        cin >> temp1 >> temp2 >> temp3;
        vec.push_back(make_tuple(temp1, temp2, temp3));
    }

    // 벡터 정렬
    sort(vec.begin(), vec.end(), compare);

    int weight = 0; // 가중치 초기화
    for (int i = 0; i < vec.size(); i++)
    {
        int u = get<0>(vec[i]);
        int v = get<1>(vec[i]);
        int w = get<2>(vec[i]);

        // 두 정점의 루트를 찾아서 서로 다른 집합에 있을 때만 추가
        if (find(u, parent) != find(v, parent))
        {
            vertex.push_back(vec[i]); // 간선 추가
            union_sets(u, v, parent); // 집합을 합침
            weight += w;              // 가중치 추가
        }
    }

    // 결과 출력
    for (int i = 0; i < vertex.size(); i++)
    {
        cout << get<0>(vertex[i]) << ' ' << get<1>(vertex[i]) << ' ' << get<2>(vertex[i]) << '\n';
    }
    cout << weight << '\n';

    return 0; // main 함수 종료
}
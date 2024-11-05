#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// 물건을 정의하는 구조체
struct Stuff
{
    int weight;
    int value;
    int index;
    double ratio; // 단위 무게당 가치
};

// 단위 무게당 가치를 기준으로 내림차순 정렬하기 위한 비교 함수
bool compare(Stuff a, Stuff b)
{
    return a.ratio > b.ratio;
}

int main()
{
    int n; // 물건의 개수
    cin >> n;

    vector<Stuff> stuffs(n);

    // 각 물건의 무게와 가치를 입력받음
    for (int i = 0; i < n; i++)
    {
        cin >> stuffs[i].weight >> stuffs[i].value;
        stuffs[i].index = i;
        stuffs[i].ratio = (double)stuffs[i].value / stuffs[i].weight; // 단위 무게당 가치
    }

    int capacity; // 배낭의 용량
    cin >> capacity;

    // 물건을 단위 무게당 가치 기준, 내림차순으로 정렬
    sort(stuffs.begin(), stuffs.end(), compare);

    double totalValue = 0.0;                  // 배낭에 담긴 물건들의 총 가치
    vector<pair<int, double>> selectedStuffs; // 선택된 물건과 그 비율

    for (int i = 0; i < n; i++)
    {
        if (capacity == 0)
            break; // 배낭이 꽉 차면 종료

        // 현재 물건을 통째로 넣을 수 있는 경우
        if (stuffs[i].weight <= capacity)
        {
            selectedStuffs.push_back({stuffs[i].index, 1.0}); // 물건 전체를 넣음
            totalValue += stuffs[i].value;                    // 전체 가치 추가
            capacity -= stuffs[i].weight;                     // 배낭 용량 감소
        }
        // 현재 물건을 나누어 넣어야 하는 경우
        else
        {
            double fraction = (double)capacity / stuffs[i].weight; // 넣을 수 있는 비율 계산
            selectedStuffs.push_back({stuffs[i].index, fraction}); // 물건의 일부만 넣음
            totalValue += stuffs[i].value * fraction;              // 부분적으로 넣은 가치 추가
            capacity = 0;                                          // 배낭이 꽉 참
        }
    }

    for (auto stuff : selectedStuffs)
    {
        cout << stuff.first << " " << fixed << setprecision(1) << stuff.second << endl;
    }

    cout << fixed << setprecision(0) << totalValue << endl;

    return 0;
}

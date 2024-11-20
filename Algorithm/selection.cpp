#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int main()
{
    string inputLine;
    vector<int> numbers;

    getline(std::cin, inputLine);

    // 입력 문자열을 스트림으로 변환
    stringstream ss(inputLine);
    int number;

    // 스트림에서 숫자를 추출하여 벡터에 저장
    while (ss >> number)
    {
        numbers.push_back(number);
    }

    for (int pass = 1; pass < numbers.size(); pass++) // 요소 개수-1 만큼 반복
    {
        int min = pass - 1;                             // 각 pass의 시작 지점
        for (int i = pass - 1; i < numbers.size(); i++) // 최소값 찾기
        {
            if (numbers[min] > numbers[i])
            {
                min = i;
            }
        }

        swap(numbers[pass - 1], numbers[min]); // 최소값과 시작 지점을 swap, 결과 출력
        cout << "(pass " << pass << "): [";
        for (int j = 0; j < numbers.size(); j++)
        {
            if (j != numbers.size() - 1)
                cout << numbers[j] << ", ";
            else
                cout << numbers[j];
        }
        cout << "]\n";
    }

    cout << "result: [";
    for (int i = 0; i < numbers.size(); i++) // 최종 결과 출력
    {
        if (i != numbers.size() - 1)
            cout << numbers[i] << ", ";
        else
            cout << numbers[i];
    }
    cout << "]";
    return 0;
}
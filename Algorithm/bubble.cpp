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
        bool swaped = false;
        for (int i = 1; i < numbers.size() - pass + 1; i++)
        {
            if (numbers[i - 1] > numbers[i]) // 앞 요소가 더 클 때 swap, swap 결과 출력
            {
                swap(numbers[i - 1], numbers[i]);
                swaped = true;
                cout << "(pass " << pass << ", Swap): [";
                for (int j = 0; j < numbers.size(); j++)
                {
                    if (j != numbers.size() - 1)
                        cout << numbers[j] << ", ";
                    else
                        cout << numbers[j];
                }
                cout << "]\n";
            }
        }
        if (swaped == false) // 한 번의 pass동안 swap하지 않았을 떄 결과 출력
        {
            cout << "(pass " << pass << ", No swap): [";
            for (int j = 0; j < numbers.size(); j++)
            {
                if (j != numbers.size() - 1)
                    cout << numbers[j] << ", ";
                else
                    cout << numbers[j];
            }
            cout << "]\n";
            break;
        }
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
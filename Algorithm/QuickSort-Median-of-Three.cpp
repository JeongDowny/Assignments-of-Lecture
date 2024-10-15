#include <iostream>
#include <vector>
using namespace std;

vector<int> pivotVec; //피벗을 저장할 벡터 선언

void swap(int& first, int& second) { //swap함수 정의
    int temp = first;
    first = second;
    second = temp;
}

void quickSort(vector<int>& data, int start, int end) {
    if (start < end) { //start<end일 경우 quickSort 실행
        int low = start;
        int high = end;
        int mid = start + (end - start) / 2;
        int pivot;

        if((end-start)>2) { //배열의 길이가 3이상일 때 처음값, 중앙값, 끝값 중 중간값을 피벗로 설정
            if((data[start]>data[mid] && data[mid]>data[end]) || (data[end]>data[mid] && data[mid]>data[start])) pivot = mid;
            else if((data[mid]>data[start] && data[start]>data[end]) || (data[end]>data[start] && data[start]>data[mid])) pivot = start;
            else if((data[start]>data[end] && data[end]>data[mid]) || (data[mid]>data[end] && data[end]>data[start])) pivot = end;
            else if(data[start]==data[mid]) pivot = start;
            else if(data[start]==data[end]) pivot = start;
            else if(data[mid]==data[end]) pivot = mid;
            else pivot = end;
        }
        else { //배열의 길이가 2일 때 왼쪽 값을 피벗으로 설정
            pivot = start;
        }
        

        pivotVec.emplace_back(data[pivot]); //피벗 기록
        swap(data[start], data[pivot]); //피벗과 처음값을 swap
        low++; //피벗값 다음값부터 비교

        while (low < high) { //low<high일 때 반복
            for(int i=low; i<end; i++) { //low가 배열 밖을 가리키지 않도록 제한
                if(data[low] > data[start]) { //low가 가리키는 값이 피벗값보다 클 때 break, 작을 때 low++
                    break;
                }
                else low++;
            }
            for(int i=high; i>start; i--) { //high가 배열 밖을 가리키지 않도록 제한
                if(data[high] < data[start]) { //high가 가리키는 값이 피벗값보다 작을 때 break, 클 때 high--
                    break;
                }
                else high--;
            }
            if (low < high) { //low보다 high가 우측에 있을 때 swap
                swap(data[low], data[high]);
            }
        }

        if(end-start != 1) swap(data[start], data[high]); //배열의 길이가 2이상일 때 정렬이 끝나면 피벗을 마지막 high가 가리키는 값과 교환(high가 가리키는 값은 피벗보다 작기 때문)
        else { //배열의 길이가 1일 때 두 값을 비교, 정렬
            if(data[start]>data[end]) swap(data[start], data[end]);
        }
        quickSort(data, start, high - 1); //피벗보다 작은 값으로 정렬된 왼쪽 배열 quickSort 재귀호출
        quickSort(data, high+1, end); //피벗보다 큰 값으로 정렬된 오른쪽 배열 quickSort 재귀호출
    }
}

int main() {
    int n;
    cin>>n;
    vector<int> data(n);

    for (int i = 0; i < n; i++) { //정렬할 배열 입력
        cin >> data[i];
    }

    quickSort(data, 0, n - 1); //quickSort 실행

    for (int i = 0; i < n; i++) { //정렬된 배열 출력
        cout << data[i] << " "; 
    }
    cout << endl;

    for (int i = 0; i < pivotVec.size(); i++) { //기록된 피벗값 출력
        cout << pivotVec[i] << " ";
    }
    cout<< endl;

    return 0;
}
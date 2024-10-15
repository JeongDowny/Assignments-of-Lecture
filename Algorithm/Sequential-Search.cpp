#include <iostream>
#include <time.h>
using namespace std;

int main() {
    clock_t start, stop = 0;
    double result = 0;
    start = clock();

    FILE* fp = fopen("APSOLUTE_PATH\\1.in", "r");
    if (fp == NULL) return -1;

    int searchNum;
    cin>>searchNum;

    for(int i=0; i<10000001; i++) {
        int temp;
        fscanf(fp, "%d", &temp);
        if(temp == searchNum) {
            break;
        }
    }

    stop = clock();
    result = (double)(stop - start);
    cout<<"걸린 시간은 "<<result<<"초 입니다";
}
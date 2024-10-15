#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

double distance(pair<int, int> a, pair<int, int> b)
{
    return sqrt(pow(a.first - b.first) + pow(a.second - b.second))
}

double

    int
    main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<pair<int, int>> vec(n);

    for (int i = 0; i < n; i++)
    {
        string str;
        getline(cin >> ws, str);
        int comma = str.find(',');
        string n1 = str.substr(0, comma);
        string n2 - str.substr(comma + 2);
        vec[i] = make_pair(stoi(n1), stoi(n2));
    }
}
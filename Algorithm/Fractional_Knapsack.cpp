#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    float limitWeight;
    cin >> n;

    vector<tuple<int, float, float>> stuff;
    vector<tuple<int, float, float>> bag;

    for (int i = 0; i < n; i++)
    {
        float w, v;
        cin >> w >> v;
        stuff.push_back(make_tuple(i, w, v / w));
    }

    cin >> limitWeight;

    sort(stuff.begin(), stuff.end(), [](const tuple<int, float, float> &a, const tuple<int, float, float> &b)
         { return get<2>(a) > get<2>(b); });

    float weightBag = 0;
    float valueBag = 0;

    while (weightBag + get<1>(stuff[0]) <= limitWeight)
    {
        bag.push_back(make_tuple(get<0>(stuff[0]), get<1>(stuff[0]), get<1>(stuff[0]) * get<2>(stuff[0])));
        weightBag += get<1>(stuff[0]);
        valueBag += get<1>(stuff[0]) * get<2>(stuff[0]);
        stuff.erase(stuff.begin());
    }
    if (!stuff.empty())
    {
        for (int i = 0; i < stuff.size(); i++)
        {
            if (limitWeight - weightBag > 0)
            {
                bag.push_back(make_tuple(get<0>(stuff[i]), limitWeight - weightBag, get<2>(stuff[i])));
                valueBag += (limitWeight - weightBag) * get<2>(stuff[i]);
            }
        }
    }

    for (int i = 0; i < bag.size(); i++)
    {
        cout << get<0>(bag[i]) << ' ';
        if (i != bag.size() - 1)
        {
            cout << "1.0";
        }
        else
        {
            cout << get<2>(bag[i]) / get<2>(stuff[0]);
        }
        cout << '\n';
    }
    cout << valueBag;
}
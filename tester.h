#include <iostream>
#include <vector>
#include <map>

using namespace std;

void test()
{
    vector<int> testN = {10, 30, 50}; // 5, 15, 25
    vector<int> testM = {10, 17, 26};
    map<int, vector<string>> tests;

    for (int i = 0; i < testM.size(); ++i)
    {
        string test;
        for (int j = 0; j < testM[i]; ++j)
        {
            test += "a";
        }
        bool change = false;
        int cont = 1;
        for (int j = 0; j < testN[i]; ++j)
        {
            if (change)
            {
                tests[testN[i]].push_back(test);
                test[test.size()-cont] = test[test.size()-cont]+cont;
                ++cont;
            }
            change = !change;
        }
        cout << endl;
    }
    
    for (auto it : tests)
    {
        for (auto it2 : it.second)
        {
            cout << it2 << endl;
        }
        cout << endl << endl;
    }
}

#include <iostream>
#include <set>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include "sptrie.h"

using namespace std;

bool sortBySecond(const pair<int,int> &a, const pair<int,int> &b)
{
    return (a.second > b.second);
}

pair<SPTrieNode*, int> pregunta1Greedy(set<string> S, set<char> sigma, int m)
{
    unordered_map<char, unordered_map<int, int>> umap;
    vector<pair<int, int>> maxPerLevel;
    // n*m
    for (int i = 0; i < m; ++i)
    {
        int max = -1;
        for (auto it : S)
        {
            umap[it[i]][i]++;
            if (umap[it[i]][i] > max)
            {
                max = umap[it[i]][i];
            }
        }
        maxPerLevel.push_back(make_pair(i, max));
    }
    // m*lgm
    sort(maxPerLevel.begin(), maxPerLevel.end(), sortBySecond);
    vector<int> p;
    cout << "p: ( ";
    for (int i = 0; i < maxPerLevel.size(); ++i)
    {
        p.push_back(maxPerLevel[i].first);
        cout << maxPerLevel[i].first;
        if (i < maxPerLevel.size()-1)
        {
            cout << ", ";
        }
    }
    cout << " )";
    cout << endl;

    SPTrieNode *root = new SPTrieNode(p);
    // n*m
    for (auto it : S)
    {
        root->insert(it);
    }
    // 2nm+mlgm = O(nm+mlgm)
    return make_pair(root, aristas);
}

int main()
{
    // Inputs
    set<string> S;
    set<char> sigma;
    // n cadenas
    int n;
    cin >> n;
    // cada cadena de longitud m
    int m;
    cin >> m;  
    string cadena;
    // llenar el conjunto S
    for (int i = 0; i < n; ++i)
    {
        cin >> cadena;
        // por si el profe nos da un testcase con mayúsculas
        for_each(cadena.begin(), cadena.end(), [](char & c) 
        {
            c = ::tolower(c);
        });
        S.insert(cadena.substr(0, m));
    }
    // llenar el alfabeto
    for (auto it : S)
    {
        for (auto it2 : it)
        {
            sigma.insert(it2);
        }
    }
    auto rpta = pregunta1Greedy(S, sigma, m);
    char str[n];
    cout << "Cadenas:\n";
    print(rpta.first, str, 0);
    cout << "Aristas: " << rpta.second;
}
// Ejemplo de input:
// n m cadena1 cadena2 ... cadenaN
// 4 3 aaa baa bac cbb
// 2 3 aaa baa

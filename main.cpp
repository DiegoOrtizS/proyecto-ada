#include <iostream>
#include <set>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include "sptrie.h"

using namespace std;


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
    auto rpta = pregunta1Greedy(S, m);
    char str[n];
    cout << "Cadenas:\n";
    print(rpta.first, str, 0);
    cout << "Aristas: " << rpta.second;
}
// Ejemplo de input:
// n m cadena1 cadena2 ... cadenaN
// 4 3 aaa baa bac cbb
// 2 3 aaa baa

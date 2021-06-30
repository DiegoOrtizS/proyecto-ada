#include <iostream>
#include <set>
#include <vector>
#include <queue>

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
}
// Ejemplo de input:
// 4 3 aaa baa bac cbb

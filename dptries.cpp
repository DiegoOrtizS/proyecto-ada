#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

vector<int> U;
vector<string> S;

vector<int> K(int i, int j)
{
    // O(mn)
    /*
    Peor de los casos, por ejemplo:
    abc
    abc
    abc
    */
    // pero normalmente va mejor por el break, ya que en caso de directamente encontrar 
    // caracteres que sean distintos ya pasa al siguiente nivel.
    // j-i < n
    // donde m es longitud de las cadenas y n es la cantidad de cadenas.
    vector<int> positions;
    --i;
    --j;
    if (i == j)
    {
        for (int i = 0; i < S[0].size(); ++i) positions.push_back(i);
    }
    else
    {
        for (int iter = 0; iter < S[0].size(); ++iter)
        {
            bool flag = true;
            char primeraLetra = S[i][iter];
            if (i+1 == j)
            {
                flag = (primeraLetra == S[i+1][iter]);
            }
            else
            {
                for (int aux = i+1; aux < j; ++aux)
                {
                    if (S[aux][iter] != primeraLetra)
                    {
                        flag = false;
                        break;
                    }
                }
            }
            if (flag)
            {
                positions.push_back(iter);
            }
        }
    }
    return positions;
}

vector<int> R(int i, int j, vector<int> K)
{
    // los vectores U y K están ordenados
    // |U| = m
    // O(m+|K|)
    vector<int> difference;
    set_difference(
    U.begin(), U.end(),
    K.begin(), K.end(),
    back_inserter(difference));
    return difference;
}


vector<pair<int, int>> C(int i, int j, int r)
{
    vector<pair<int, int>> result;
    // considerando que S está ordenado




    return result;
}

// int OPTRecursivo(int i, int j)
// {
//     if (i == j) return 0;
//     auto k = K(i, j, S);
//     // auto r = R(i, j);
// }

template <typename T>
void printVector(vector<T> v)
{
    for (auto it : v)
    {
        cout << it << " ";
    }
    cout << endl;
}

int main()
{
    // Inputs
    // n m (cadena 1, ..., cadena n)
    // 3 3 aaa bab cab
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
        S.push_back(cadena.substr(0, m));
    }
    // llenar el alfabeto
    for (auto it : S)
    {
        for (auto it2 : it)
        {
            sigma.insert(it2);
        }
    }
    // llenar el universo
    for (int i = 0; i < m; ++i)
    {
        U.push_back(i);
    }

    auto aux = K(1, 3);
    printVector(aux);
    printVector(R(1, 3, aux));

    aux = K(2, 3);
    printVector(aux);
    printVector(R(2, 3, aux));

    aux = K(3, 3);
    printVector(aux);
    printVector(R(3, 3, aux));
}
#include <iostream>
#include "sptrie.h"
#include <set>
#include <algorithm>
#include <unordered_map>
#include <limits>

using namespace std;

vector<int> U;
vector<string> S;

int INF = numeric_limits<int>::max();

// bool cmp(pair<int, int>& a,
//          pair<int, int>& b)
// {
//     return a.second < b.second;
// }

// vector<pair<int, int>> sort(unordered_map<int, int> &umap)
// {
//     vector<pair<int, int>> v;
  
//     for (auto& it : umap) 
//     {
//         v.push_back(it);
//     }
  
//     sort(v.begin(), v.end(), cmp);
//     return v;
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

template <typename T1, typename T2>
void printVectorPair(vector<pair<T1, T2>> v)
{
    cout << "{";
    for (auto it : v)
    {
        cout << "(" << it.first << ", " << it.second << ") ";
    }
    cout << "}";
    cout << endl;
}

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
    if (i == j)
    {
        for (int iter = 0; iter < S[0].size(); ++iter) positions.push_back(iter);
    }
    else
    {
        --i;
        --j;
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
    // los vectores U y K están ordenados de forma creciente
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
    if (i == j)
    {
        ++r;
        result.push_back(make_pair(r, r));
    }
    else
    {
        --i;
        --j;
        int start = i, iter;    
        for (iter = i; iter < j; ++iter)
        {
            if (S[iter][r] != S[iter+1][r])
            {
                result.push_back(make_pair(start+1, iter+1));
                start = iter+1;
            }
        }
        result.push_back(make_pair(start+1, iter+1));
    }
    return result;
}

int OPTR(int i, int j)//,unordered_map<int,int> &rmap)
{
    if (i == j) return 0;
    auto k = K(i, j);
    auto Raux = R(i, j, k);
    vector<int> sumas;
    int minimo = INF;
    for (auto r : Raux)
    {
        auto c = C(i, j, r);
        // printVectorPair(c);
        int suma = 0;
        for (auto par : c)
        {
            suma += OPTR(par.first, par.second) + K(par.first, par.second).size() - k.size();
        }
        // sumas.push_back(suma);

        if (suma < minimo) minimo = suma;
        // if (rmap[r] < suma)
        //    rmap[r] = suma;
    }
    // return *min_element(sumas.begin(), sumas.end());
    return minimo;
}

int OPT(int i, int j)//, vector<int> &p)
{
    // auto k = K(i, j);
    // for (auto it : k)
    // {
    //     p.push_back(it);
    // }
    // unordered_map<int,int> rmap;
    // auto optres = OPTR(i, j, rmap);
    // auto paux = sort(rmap);
    // for (auto it : paux)
    // {
    //     p.push_back(it.first);
    // }
    // for (auto it : p)
    // {
    //     cout << it << " ";
    // }
    // cout << endl;
    return OPTR(i, j) + K(i, j).size();
}

int main()
{
    // Inputs
    // n m (cadena 1, ..., cadena n)
    // 3 3 aaa bab cab // 6
    // 6 3 aaa bab cab cbb dcb dcc // 13
    // 4 3 aaa baa bac cbb // 8
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

    // vector<int> p;
    cout << OPT(1, n) << endl;
}
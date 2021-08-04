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

typedef unordered_map<int, unordered_map<int, int>> matriz;

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

template <typename T>
void printMapOfMaps(unordered_map<T, unordered_map<T, T>> umap)
{
    for (auto it : umap)
    {
        for (auto it2 : it.second)
        {
            cout << it.first << "," << it2.first << ": " << it2.second << " ";
        }
        cout << endl;
    }
}

vector<int> K(int i, int j)
{
    // O(nm)
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
                for (int aux = i+1; aux <= j; ++aux)
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

// O(n^3*m) complejidad algorítmica
void fillMap(matriz &umapOPT, matriz &umapK)
{
    // umapOPT y umapK son de complejidad espacial O(n^2). 
    // Luego, para guardar el trie se necesitará O(n*m*sigma).
    for (int iter1 = 1; iter1 < S.size()+1; ++iter1)
    {
        for (int iter2 = 1; iter2 < iter1+1; ++iter2)
        {
            if (iter1 == iter2) umapOPT[iter2][iter1] = 0;
            else umapOPT[iter2][iter1] = -1;
            umapK[iter2][iter1] = K(iter2, iter1).size();
        }
    }
}

vector<int> R(int i, int j, vector<int> K)
{
    // los vectores U y K están ordenados de forma creciente
    // |U| = m
    // m+|K|
    // En el peor de los casos |K| es m porque guardaría todas las posiciones
    // O(m)
    vector<int> difference;
    set_difference(
    U.begin(), U.end(),
    K.begin(), K.end(),
    back_inserter(difference));
    return difference;
}

vector<int> RsinK(int i, int j)
{
    // O(nm)
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
                flag = (primeraLetra != S[i+1][iter]);
            }
            else
            {
                for (int aux = i+1; aux <= j; ++aux)
                {
                    if (S[aux][iter] != primeraLetra)
                    {
                        flag = false;
                        break;
                    }
                }
            }
            if (!flag)
            {
                positions.push_back(iter);
            }
        }
    }
    return positions;
}


vector<pair<int, int>> C(int i, int j, int r)
{
    // O(n)
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
    // con un dfs para reconstruir el trie
    if (i == j) return 0;
    auto k = K(i, j); // O(nm)
    auto Raux = R(i, j, k); // O(m)
    int minimo = INF;
    for (auto r : Raux)
    {
        auto c = C(i, j, r);
        int suma = 0;
        for (auto par : c)
        {
            suma += OPTR(par.first, par.second) + K(par.first, par.second).size() - k.size();
        }
        if (suma < minimo) 
        {
            minimo = suma;
        }
    }
    return minimo;
}

int OPT(int i, int j)
{
    return OPTR(i, j) + K(i, j).size();
}

// TODO:
// Complejidad algorítmica que pide es O(n^3*m+n^2*m^2)
// Complejidad espacial que pide es O(n^2+n*m*sigma), 
// donde tenemos dos matriz de n^2 pero igual O(n^2) + O(n^2) = O(n^2)
// Note que el O(n*m*sigma) de espacio viene dado por el trie que se va a construir.
int Memoizado(int i, int j, matriz &umapOPT, matriz &umapK)
{
    if (i == j) return 0;
    auto k = umapK[i][j]; // O(1)
    auto Raux = RsinK(i, j); // O(mn)
    int minimo = INF;
    // R en el peor casos es de longitud m cuando k está vacío, 
    // ya que se queda con todas las posiciones desde 0, ..., m-1.
    for (auto r : Raux) // <= m iteraciones
    {
        auto c = C(i, j, r); // <= n iteraciones
        int suma = 0;
        for (auto par : c) // <= n iteraciones
        {
            suma += umapK[par.first][par.second] - k;
            if (umapOPT[par.first][par.second] != -1) suma += umapOPT[par.first][par.second];
            else suma += OPTR(par.first, par.second);
        }
        if (suma < minimo) minimo = suma;
    }
    umapOPT[i][j] = minimo;
    return minimo;
}

int LlamarMemoizado(int i, int j, matriz &umapOPT, matriz &umapK)
{
    fillMap(umapOPT, umapK); // O(n^3*m)
    return Memoizado(i, j, umapOPT, umapK) + umapK[i][j];
}

int ProgramacionDinamica(int i, int j, matriz &umapOPT, matriz &umapK)
{
    // fillMap(umap);
    // int iter2 = j;
    // for (int iter1 = i; iter1 < j; ++iter1, --iter2)
    // {
    //     K(iter1, iter2);

    // }
}

int main()
{
    // Inputs
    // n m (cadena 1, ..., cadena n)
    // 3 3 aaa bab cab // 6
    // 6 3 aaa bab cab cbb dcb dcc // 13
    // 4 3 aaa baa bac cbb // 9
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
    // en umap se va a guarda OPT con la raya encima (el del pdf)
    matriz umapOPT;
    matriz umapK;
    // cout << K(1, 4).size() << endl;
    // for (auto it : K(1, 4))
    // {
    //     cout << it << " ";
    // }
    // cout << endl;
    cout << LlamarMemoizado(1, n, umapOPT, umapK) << endl;
    // Si quiero OPT(1, n) que es la rpta se le debe sumar |K(1, n)| al umap(1, n)
    // cout << umap[1][n] + K(1, n).size() << endl;
    // cout << ProgramacionDinamica(1, n, umapOPT, umapK) << endl;
}
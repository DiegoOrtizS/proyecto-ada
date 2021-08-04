#include <iostream>
#include "sptrie.h"
#include <set>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <limits>

using namespace std;

vector<int> U;
vector<string> S;

int INF = numeric_limits<int>::max();

typedef map<int, map<int, int>> mapa;

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

void printMap(mapa umap)
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
void fillMap(mapa &umapOPT, mapa &umapK)
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

// Complejidad algorítmica que pide es O(n^3*m+n^2*m^2)
// Complejidad espacial que pide es O(n^2+n*m*sigma), 
// donde tenemos dos mapa de n^2 pero igual O(n^2) + O(n^2) = O(n^2)
// Note que el O(n*m*sigma) de espacio viene dado por el trie que se va a construir.
int Memoizado(int i, int j, mapa &umapOPT, mapa &umapK)
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

int LlamarMemoizado(int i, int j)
{
    mapa umapOPT, umapK;
    fillMap(umapOPT, umapK); // O(n^3*m)
    return Memoizado(i, j, umapOPT, umapK) + umapK[i][j];
}

int ProgramacionDinamica(int start, int end)
{
    // umapAgrupa: agrupar
    // umapOPT: OPT
    // umapK: K
    --start;
    --end;
    mapa umapAgrupa, umapOPT, umapK, umapXd;
    fillMap(umapOPT, umapK); // O(n^3*m)

    // O(m*n)
    for (int i = 0; i < S[0].size(); ++i) // <= m iteraciones
    {
        umapAgrupa[i][end] = end;
        for (int j = end-1; j >= 0; --j) // <= n iteraciones
        {
            umapAgrupa[i][j] = (S[j][i] == S[j+1][i]) ? umapAgrupa[i][j+1] : j;
        }
    }
    
    // O(n^2*m)
    for (int len = 1; len <= S.size(); ++len) // <= n iteraciones
    {
        for (int i = 0; i <= S.size() - len; ++i) // <= n iteraciones
        {
            int j = i+len-1;
            
            // Nodo interno
            if (umapK[i+1][j+1] != S[0].size())
            {
                int minimo = INF;
                for (int k = 0; k < S[0].size(); ++k) // <= m iteraciones
                {
                    if (umapAgrupa[k][i] < j)
                    {
                        int suma = 0;
                        for (int l = i; l <= j; l = umapAgrupa[k][l]+1)
                        {
                            if (j < umapAgrupa[k][l])
                            {
                                suma += umapK[l+1][j+1] + umapOPT[l][j];
                            }
                            else
                            {
                                suma += umapK[l+1][umapAgrupa[k][l]+1] + umapOPT[l][umapAgrupa[k][l]];
                            }
                            suma -= umapK[i+1][j+1];
                        }
                        // Nuevo mínimo
                        if (suma < minimo) minimo = suma;
                    }
                }
                // Lleno el OPT para i, j
                umapOPT[i][j] = minimo;
            }
            // Nodo hoja
            else
            {
                umapOPT[i][j] = 0;
            }
        }
    }

    // Agregar aristas faltantes en caso haya (para casos donde hay varios mínimos)
    // O(m) (ej: 3 3 aaa bab cab)
    for (int k = 0; k < S[0].size(); ++k)
    {
        if (umapAgrupa[k][start] == end) umapOPT[start][end]++;
    }
    return umapOPT[start][end];
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

    // Pregunta 3
    cout << "Recursivo min edges: " << OPT(1, n) << endl;
    // Pregunta 4
    cout << "Memoizado min edges: " << LlamarMemoizado(1, n) << endl;
    // Pregunta 5
    cout << "DP min edges: " << ProgramacionDinamica(1, n) << endl;
}
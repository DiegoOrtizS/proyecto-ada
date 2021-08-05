#include <vector>
#include <iostream>
using namespace std;


vector<int> U;
vector<string> S;

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

vector<int> RsinK(int i, int j);
vector<pair<int, int>> C(int i, int j, int r);
vector<int> R(int i, int j, vector<int> K);
vector<int> K(int i, int j);
void fillMap(matriz &umapOPT, matriz &umapK);
void printMapOfMaps(matriz umap);


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

vector<int> R(int i, int j, vector<int> K)
{
    // los vectores U y K están ordenados de forma creciente
    // |U| = m
    // m+|K|
    // En el peor de los casos |K| es m porque guardaría todas las posiciones
    // O(m)
    vector<int> difference;
    set_difference(U.begin(), U.end(),K.begin(), K.end(),back_inserter(difference));
    return difference;
}


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

void printMapOfMaps(matriz umap)
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
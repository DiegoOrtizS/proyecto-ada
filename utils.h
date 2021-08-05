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

#include <iostream>
#include "sptrie.h"
#include <set>
#include <algorithm>
#include <unordered_map>
#include <limits>
#include<queue>
#include <map>

using namespace std;

vector<int> U;
vector<string> S;


int INF = numeric_limits<int>::max();

typedef unordered_map<int, unordered_map<int, int>> matriz;

vector<int> K(int i, int j);
vector<pair<int, int>> C(int i, int j, int r);
vector<int> R(int i, int j, vector<int> K);




struct node{
    int id;
    int pos;
    map<char,node*>adj;
};

node* build_trie(int i, int j, matriz &min_pos){
    int p = min_pos[i][j];//no se como guardar cuando es i==j
    auto c = C(i,j,p);
    //cambiar con la tabla de Ks para reducir la compeljidad
    auto r = R(i,j,K(i,j));
    int index = 1;
    node* root = new node{};
    root->pos = p;
    root->id = index;
    //root->isleaf=false;
    //1,1
    if(i==j){
        return root;
    }

    for (auto par : c)
    {
        auto rp = R(par.first,par.second,K(par.first, par.second));
        node* newNode = build_trie(par.first,par.second, min_pos); 
        vector<int> difR;
        vector<int> difP;
        difP.push_back(p);
        set_difference(r.begin(), r.end(),difP.begin(),difP.end(), back_inserter(difR)); //O(m)
    
        if(difR.size()>0){
            newNode->pos=difR[0];
        }

        auto temp= newNode;
        if(rp.size()==0){
            for (auto pp : difR)
            {
                if(pp == p)
                    continue;
                node* nodeP = new node{};
                nodeP->pos = -1;
                nodeP->id = ++index;
                newNode->adj[S[par.second-1][pp]] = nodeP;
                newNode = nodeP;

            }
        }

        root->adj[S[par.second-1][p]] = temp;        
    }
    return root;

}

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




bool printTrieGen(node* root){
    queue<node*>Q;
    Q.push(root);
    while(!Q.empty()){
        node* u = Q.front();
        Q.pop();
        for(auto it : u->adj)
        {
            Q.push(it.second);
            cout << it.second->pos << "\n" << it.first << " " ;
        }
    }
    return true;

};





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

int OPTR(int i, int j, matriz &min_pos)//,unordered_map<int,int> &rmap)
{
    // con un dfs para reconstruir el trie
    if (i == j) {
        min_pos[i][j]=-1;
        return 0;
    }
        
    auto k = K(i, j); // O(nm)
    auto Raux = R(i, j, k); // O(m)
    int minimo = INF;
    for (auto r : Raux)
    {
        auto c = C(i, j, r);
        int suma = 0;
        for (auto par : c)
        {
            suma += OPTR(par.first, par.second, min_pos) + K(par.first, par.second).size() - k.size();
        }
        if (suma < minimo) 
        {
            minimo = suma;
            min_pos[i][j] = r;
        }
    }
    return minimo;
}

int OPT(int i, int j, matriz min_pos)
{  
    
    auto ktp=K(i, j);
    auto min = OPTR(i, j, min_pos) + ktp.size();

    // for(auto it : K(i,j)){
    //     min_pos[i][j] = it;
    // }

    node* root = build_trie(i,j,min_pos);
    //uno con los ks
    for (int i=0;i<ktp.size();i++){
         node* tmp=new node{};
         char chartmp= S[0][ktp[i]];
         tmp->pos=ktp[i];
         tmp->adj[chartmp]=root;
         root=tmp;
    }
    
    printTrieGen(root);
    return min;
}

// TODO:
// Complejidad algorítmica que pide es O(n^3*m+n^2*m^2)
// Complejidad espacial que pide es O(n^2+n*m*sigma), 
// donde tenemos dos matriz de n^2 pero igual O(n^2) + O(n^2) = O(n^2)
// Note que el O(n*m*sigma) de espacio viene dado por el trie que se va a construir.
int Memoizado(int i, int j, matriz &umapOPT, matriz &umapK, matriz &min_pos)
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
            else suma += OPTR(par.first, par.second, min_pos);
        }
        if (suma < minimo) minimo = suma;
    }
    umapOPT[i][j] = minimo;
    return minimo;
}

int LlamarMemoizado(int i, int j, matriz &umapOPT, matriz &umapK , matriz min_pos)
{
    fillMap(umapOPT, umapK); // O(n^3*m)
    return Memoizado(i, j, umapOPT, umapK, min_pos) + umapK[i][j];
}

// int ProgramacionDinamica(int i, int j, matriz &umap)
// {
//     fillMap(umap);
//     int iter2 = j;
//     for (int iter1 = i; iter1 < j; ++iter1, --iter2)
//     {
//         K(iter1, iter2);

//     }
// }

int main()
{
    // Inputs
    // n m (cadena 1, ..., cadena n)
    // 3 3 aaa bab cab // 6
    // 6 3 aaa bab cab cbb dcb dcc // 13
    // 4 3 aaa baa bac cbb // 8
    matriz min_pos;

    
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
    cout << OPT(1, n, min_pos) << endl;
    // en umap se va a guarda OPT con la raya encima (el del pdf)
    // matriz umapOPT;
    // matriz umapK;
    // cout << LlamarMemoizado(1, n, umapOPT, umapK, min_pos) << endl;
    // Si quiero OPT(1, n) que es la rpta se le debe sumar |K(1, n)| al umap(1, n)
    // cout << umap[1][n] + K(1, n).size() << endl;
    // ProgramacionDinamica(1, n, umap);
}
#include "lib.h"
#include "utils.h"
#include "recursivo.h"
#include "sptrieGen.h"
#include "memorizado.h"

using namespace std;

// O(n^3*m) complejidad algorítmica


// int OPT(int i, int j, matriz min_pos)
// {  
    
//     auto ktp=K(i, j);
//     auto min = OPTR(i, j, min_pos) + ktp.size();

//     // node* root = build_trie(i,j,min_pos);
//     // //uno con los ks
//     // for (int i=0;i<ktp.size();i++){
//     //      node* tmp=new node{};
//     //      char chartmp= S[0][ktp[i]];
//     //      tmp->pos=ktp[i];
//     //      tmp->adj[chartmp]=root;
//     //      root=tmp;
//     // }
    
//     // printTrieGen(root);
//     return min;
// }

// TODO:
// Complejidad algorítmica que pide es O(n^3*m+n^2*m^2)
// Complejidad espacial que pide es O(n^2+n*m*sigma), 
// donde tenemos dos matriz de n^2 pero igual O(n^2) + O(n^2) = O(n^2)
// Note que el O(n*m*sigma) de espacio viene dado por el trie que se va a construir.



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

     vector<int> p;
      cout << OPT(1, n, min_pos) << endl;
      auto *nodeRecursivo =completeBuild(1,n,min_pos);
    //   printTrieGen(nodeRecursivo);
      
    // en umap se va a guarda OPT con la raya encima (el del pdf)
    //    matriz umapOPT;
    //    matriz umapK;


    //    matriz min_pos2;
    //    cout << LlamarMemoizado(1, n, umapOPT, umapK, min_pos2) << endl;
    //    auto *nodeMemorizado =completeBuild(1,n,min_pos2);
    //    printTrieGen(nodeMemorizado);
    // Si quiero OPT(1, n) que es la rpta se le debe sumar |K(1, n)| al umap(1, n)
    // cout << umap[1][n] + K(1, n).size() << endl;
    // ProgramacionDinamica(1, n, umap);
}
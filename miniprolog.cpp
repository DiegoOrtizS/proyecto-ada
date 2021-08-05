#include "lib.h"
#include "utils/utils.h"
#include "utils/parser.h"
#include "estructuras/sptrieGen.h"
#include "estructuras/sptrie.h"
#include "algoritmos/dinamic.h"
#include "algoritmos/greedy.h"
// #include "memorizado.h"

int main()
{
    // .first mapa de entrada
    // .second mapa de consulta
    auto entradaYconsulta = parser();

    while (true)
    {
        int option;
        cout << "1. Greedy (compilación heurística)\n";
        cout << "2. Programación dinámica (compilación óptima)\n";
        cout << "3. Salir\n";
        cin >> option;

        if (option == 3) break;

        else if (option == 1)
        {
            unordered_map<string, SPTrieNode*> rtriesG;
            // Greedy (S-ptrie)
            for (auto it : entradaYconsulta.first)
            {
                S = it.second;
                aristas = 0;
                auto rpta = pregunta1Greedy(S, S[0].size());
                cout << "Greedy Result: " << rpta.second << endl;
                rtriesG[it.first] = rpta.first;
            }

            for (auto it : entradaYconsulta.second)
            {
                cout<<it.first<<":"<<endl;
                for (auto it2 : it.second)
                {
                    cout<<it2<<" -> ";
                    vector<char> result;
                    executeQueryGreedy(rtriesG[it.first], it2, result, nullptr, 0);
                    printVector(result);
                }
            }
        }

        else if (option == 2)
        {
            unordered_map<string, node*> rtriesDP;
            // ProgramacionDinamica (S-ptrie generalizado)
            for (auto it : entradaYconsulta.first)
            {
                S = it.second;
                U.clear();
                // llenar el universo
                for (int i = 0; i < S[0].size(); ++i)
                {
                    U.push_back(i);
                }
                matriz min_pos;
                cout<<"Dinamico Result:"<<ProgramacionDinamica(1, S.size(),min_pos)<<endl;
                rtriesDP[it.first] = completeBuild(1, S.size(), min_pos);
                printTrieGen(rtriesDP[it.first]);
                cout<<endl;
            }
            for (auto it : entradaYconsulta.second)
            {
                cout<<it.first<<":"<<endl;
                for (auto it2 : it.second)
                {
                    cout<<it2<<" -> ";
                    vector<char> result;
                    executeQuery(rtriesDP[it.first], it2, result, nullptr);
                    printVector(result);
                }
            }
        }
    }
}
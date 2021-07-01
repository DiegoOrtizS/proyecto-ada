#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

int aristas = 0;

struct SPTrieNode
{
    vector<SPTrieNode*> children;
    bool isLeaf;
    vector<pair<int, int>> p;
 
    SPTrieNode(vector<pair<int, int>> p) // pero solo el .first del p me importa 
    {
        this->p = p;
        isLeaf = false;
 
        for (int i = 0; i < 26; ++i) 
        {
            children.push_back(nullptr);
        }
    }
 
    void insert(string palabra)
    {
        SPTrieNode* current = this;
        // p.size() = palabra.size() = m
        for (int j = 0; j < p.size(); ++j)
        {
            int i = p[j].first;
            int alphabetPos = palabra[i] - 97;
            if (current->children[alphabetPos] == nullptr) 
            {
                current->children[alphabetPos] = new SPTrieNode(p);
                ++aristas;
            }
            current = current->children[alphabetPos];
        }
        current->isLeaf = true;
    }
};

bool sortBySecond(const pair<int,int> &a, const pair<int,int> &b)
{
    return (a.second > b.second);
}

void print(SPTrieNode* current, char str[], int level)
{
    if (current->isLeaf) 
    {
        str[level] = '\0';
        cout << str << endl;
    }

    for (int i = 0; i < 26; i++) 
    {
        if (current->children[i]) 
        {
            str[level] = i + 97;
            print(current->children[i], str, level + 1);
        }
    }
}

pair<SPTrieNode*, int> pregunta1Greedy(set<string> S, set<char> sigma, int m)
{
    unordered_map<char, unordered_map<int, int>> umap;
    vector<pair<int, int>> maxPerLevel;
    // n*m
    for (int i = 0; i < m; ++i)
    {
        int max = -1;
        for (auto it : S)
        {  
            // if (umap.find(it[i]) == umap.end())
            // {
            //     umap[it[i]][i] = 0;
            // }
            umap[it[i]][i]++;
            if (umap[it[i]][i] > max)
            {
                max = umap[it[i]][i];
            }
        }
        maxPerLevel.push_back(make_pair(i, max));
    }
    // m*lgm
    sort(maxPerLevel.begin(), maxPerLevel.end(), sortBySecond);
    cout << "p: ( ";
    for (int i = 0; i < maxPerLevel.size(); ++i)
    {
        cout << maxPerLevel[i].first;
        if (i < maxPerLevel.size()-1)
        {
            cout << ", ";
        }
    }
    cout << " )";
    cout << endl;

    SPTrieNode *root = new SPTrieNode(maxPerLevel);
    // n*m
    for (auto it : S)
    {
        root->insert(it);
    }
    // 2nm+mlgm = O(nm+mlgm)
    return make_pair(root, aristas);
}

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
        // por si el profe nos da un testcase con mayúsculas
        for_each(cadena.begin(), cadena.end(), [](char & c) 
        {
            c = ::tolower(c);
        });
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
    auto rpta = pregunta1Greedy(S, sigma, m);
    char str[n];
    cout << "Cadenas:\n";
    print(rpta.first, str, 0);
    cout << "Aristas: " << rpta.second;
}
// Ejemplo de input:
// n m cadena1 cadena2 ... cadenaN
// 4 3 aaa baa bac cbb
// 2 3 aaa baa

#include "lib.h"

int aristas = 0;

struct SPTrieNode
{
    vector<SPTrieNode*> children;
    bool isLeaf;
    vector<int> p;

    SPTrieNode(vector<int> p)
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
        for (int j = 0; j < p.size(); ++j)
        {
            int i = p[j];
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



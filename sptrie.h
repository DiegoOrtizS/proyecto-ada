struct SPTrieNode
{
    // map<char, SPTrieNode*> adj;
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

void executeQueryGreedy(SPTrieNode* root, string query, vector<char> &rpta, char* cumple, int i){
    if (root->isLeaf) 
    {
        if (cumple != nullptr)
            rpta.push_back(*cumple);
        return;
    }
    
    if (query[root->p[i]] == 'X')
    {
        for (int it = 0; it < root->children.size(); ++it)
        {
            if (root->children[it] != nullptr)
            {
                cumple = new char[1];
                *cumple= it + 97; 
            
                executeQueryGreedy(root->children[it], query, rpta, cumple, i+1);
            }
        }
    }
    else
    {
        if (root->children[query[root->p[i]]-97] == nullptr) return;
        executeQueryGreedy(root->children[query[root->p[i]]-97], query, rpta, cumple, i+1);
    }
}

bool sortBySecond(const pair<int,int> &a, const pair<int,int> &b)
{
    return (a.second > b.second);
}

pair<SPTrieNode*, int> pregunta1Greedy(vector<string> S, int m)
{
    unordered_map<char, unordered_map<int, int>> umap;
    vector<pair<int, int>> maxPerLevel;
    // n*m
    for (int i = 0; i < m; ++i)
    {
        int max = -1;
        for (auto it : S)
        {
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
    vector<int> p;
    cout << "p: ( ";
    for (int i = 0; i < maxPerLevel.size(); ++i)
    {
        p.push_back(maxPerLevel[i].first);
        cout << maxPerLevel[i].first;
        if (i < maxPerLevel.size()-1)
        {
            cout << ", ";
        }
    }
    cout << " )";
    cout << endl;

    SPTrieNode *root = new SPTrieNode(p);
    // n*m
    for (auto it : S)
    {
        root->insert(it);
    }
    // 2nm+mlgm = O(nm+mlgm)
    return make_pair(root, aristas);
}

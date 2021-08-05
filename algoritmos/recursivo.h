int OPTR(int i, int j, matriz &min_pos);
int OPT(int i, int j, matriz &min_pos);

int OPTR(int i, int j, matriz &min_pos)//,unordered_map<int,int> &rmap)
{
    // con un dfs para reconstruir el trie
    if (i == j) {
        return 0;
    }
        
    auto k = K(i, j); // O(nm)
    auto Raux = R(i, j, k); // O(m)
    int minimo = maxInt;
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

int OPT(int i, int j, matriz &min_pos)
{  
    return OPTR(i, j, min_pos) + K(i, j).size();
}

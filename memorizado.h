
int Memoizado(int i, int j, matriz &umapOPT, matriz &umapK, matriz &min_pos);
void fillMap(matriz &umapOPT, matriz &umapK);
int LlamarMemoizado(int i, int j, matriz &umapOPT, matriz &umapK , matriz &min_pos);


int Memoizado(int i, int j, matriz &umapOPT, matriz &umapK, matriz &min_pos)
{
    if (i == j) {
      min_pos[i][j]=-1;
      return 0;
    }
        
    auto k = umapK[i][j]; // O(1)
    auto Raux = RsinK(i, j); // O(mn)
    int minimo = maxInt;
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
        if (suma < minimo) {
            min_pos[i][j]=r;
            minimo = suma;
        }
            
    }
    umapOPT[i][j] = minimo;
    return minimo;
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

int LlamarMemoizado(int i, int j, matriz &umapOPT, matriz &umapK , matriz &min_pos)
{
    fillMap(umapOPT, umapK); // O(n^3*m)
    return Memoizado(i, j, umapOPT, umapK, min_pos) + umapK[i][j];
}

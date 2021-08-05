
int Memoizado(int i, int j, matriz &umapOPT, matriz &umapK, matriz &min_pos);

int LlamarMemoizado(int i, int j, matriz &umapOPT, matriz &umapK , matriz &min_pos);


int Memoizado(int i, int j, matriz &umapOPT, matriz &umapK, matriz &min_pos)
{
    if (i == j) 
    {
        //min_pos[i][j] = -1;
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
            if (umapOPT[i][j] != -1) return umapOPT[i][j];
            suma += Memoizado(par.first, par.second, umapOPT, umapK, min_pos) + umapK[par.first][par.second] - k;
        }
        if (suma < minimo) 
        {
            min_pos[i][j] = r;
            minimo = suma;
        }
    }
    umapOPT[i][j] = minimo;
    return minimo;
}


int LlamarMemoizado(int i, int j, matriz &umapOPT, matriz &umapK , matriz &min_pos)
{
    fillMap(umapOPT, umapK); // O(n^3*m)
    return Memoizado(i, j, umapOPT, umapK, min_pos) + umapK[i][j];
}

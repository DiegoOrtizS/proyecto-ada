
int ProgramacionDinamica(int start, int end, matriz& minpos);


int ProgramacionDinamica(int start, int end, matriz& minpos)
{
    // umapAgrupa: agrupar
    // umapOPT: OPT
    // umapK: K
    --start;
    --end;
    matriz umapAgrupa, umapOPT, umapK;
    fillMap(umapOPT, umapK); // O(n^3*m)

    // O(m*n)
    for (int i = 0; i < S[0].size(); ++i) // <= m iteraciones
    {
        umapAgrupa[i][end] = end;
        for (int j = end-1; j >= 0; --j) // <= n iteraciones
        {
            umapAgrupa[i][j] = (S[j][i] == S[j+1][i]) ? umapAgrupa[i][j+1] : j;
        }
    }
    
    // O(n^3*m)
    for (int len = 1; len <= S.size(); ++len) // <= n iteraciones
    {
        for (int i = 0; i <= S.size() - len; ++i) // <= n iteraciones
        {
            int j = i+len-1;
            
            // Nodo interno
            if (umapK[i+1][j+1] != S[0].size())
            {
                int minimo = maxInt;
                for (int k = 0; k < S[0].size(); ++k) // <= m iteraciones
                {
                    if (umapAgrupa[k][i] < j)
                    {
                        int suma = 0;
                        for (int l = i; l <= j; l = umapAgrupa[k][l]+1) // <= n iteraciones
                        {
                            if (j < umapAgrupa[k][l])
                            {
                                suma += umapK[l+1][j+1] + umapOPT[l][j];
                            }
                            else
                            {
                                suma += umapK[l+1][umapAgrupa[k][l]+1] + umapOPT[l][umapAgrupa[k][l]];
                            }
                            suma -= umapK[i+1][j+1];
                        }
                        // Nuevo mínimo
                        if (suma < minimo) {
                            minimo = suma;
                            minpos[i+1][j+1]=k;
                        }
                            
                    }
                }
                // Lleno el OPT para i, j
                umapOPT[i][j] = minimo;
            }
            // Nodo hoja
            else
            {
                umapOPT[i][j] = 0;
            }
        }
    }


    // Agregar aristas faltantes en caso haya (para casos donde hay varios mínimos)
    // O(m) (ej: 3 3 aaa bab cab)
    for (int k = 0; k < S[0].size(); ++k)
    {
        if (umapAgrupa[k][start] == end) umapOPT[start][end]++;
    }
    return umapOPT[start][end];
}
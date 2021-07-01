# proyecto-ada
## Trie-eficiente
### Pregunta 1
#### Greedy:
##### Entrada:
Recibe un conjunto S de n cadenas de longitud m y el alfabeto Sigma.
##### Salida:
Un par donde el first es la raíz del SPTrie y el second la mínima cantidad de aristas.
##### Elección voraz:
Se analiza comparando las letras de cada una de las n cadenas desde la posición i = (0, 1, …, m-1) y se obtienen m pares con la posición i (first) y la máxima frecuencia de letra (second) para dicha posición O(nm). Luego, se ordenan todos estos en base al segundo elemento del par y de forma creciente O(mlgm).
##### Proof: 
Sea X una solución óptima al problema donde X tiene un p = (p0, p1, …, pm-1) tal que la máxima frecuencia está ordenada de forma creciente y se selecciona la posición (first) para llenar p.
p0.second > p1.second > … > pm-1.second
Suponga por contradicción que X no es óptimo, entonces existe un Y’ que tiene una permutación de p’ que hace que tenga un mínimo número de aristas, es decir aristas(Y’) < aristas(X). Note que puede darse el caso en el que exista otra permutación p’ tal que aristas(Y’) = aristas(X) debido a una distinta forma de ordenamiento para los valores iguales, ya que se ordenan pares a partir del second pero al final solo se toma el first. Luego, para que exista un Y’ con un menor número de aristas que X deben existir dos resultados distintos de ordenar un mismo arreglo de forma creciente (sin contar los valores iguales), lo cual es imposible y se llega a una contradicción de la existencia de Y’, por lo que X es óptimo.
##### Complejidad algorítmica
Identificar la máxima frecuencia de letra cada una de las n cadenas desde la posición i = (0, 1, …, m-1) O(nm).

Ordenamiento del vector maxPerLevel O(mlgm).

Construir el SPTrie O(nm).

Por lo que, la complejidad final se puede acotar como O(nm+mlgm).
#### Recursividad:
set[] S // n cadenas de longitud m
pregunta1Recursivo(arr[] p, string permutation, arr[] &edges, arr[] &SPTries)
{
  if p.size == 0  then
  {
   SPTrie root(string_to_int_array(permutation))
   for cadena in S
     root.insert(cadena)
   edges.push_back(root.n_edges)
   SPTries.push_back(root)
   return
  }
  for i=1 to p.size
  {
   arr[] pSinFirst = p;
   pSinFirst.erase(pSinFirst.begin()) // se borra el primero
   pregunta1Recursivo(pSinFirst, permutation+to_string(p[1]), edges, SPTries)
   rotate(p.begin(), p.begin()+1, p.end())
  }
}

pregunta1Principal(arr[] p)
{
 arr[] edges = []
 arr[] SPTries = []
 pregunta1Recursivo(p, "", edges, SPTries)
 pos = min{n_edge : n_edge pertenece edges}
 return pair(edges[pos], SPTries[pos])
}

pregunta1Principal([0, 1, 2])

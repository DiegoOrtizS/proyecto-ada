# proyecto-ada
## Trie-eficiente
### Pregunta 1
#### Greedy:
##### Entrada:
Recibe un conjunto S de n cadenas de longitud m y el alfabeto Sigma.
##### Salida:
Un par donde el first es la raíz del SPTrie y el second la mínima cantidad de aristas.
##### Elección voraz:
Se analiza comparando las letras de cada una de las n cadenas desde la posición i = (0, 1, …, m-1) y se obtienen m pares con la posición i (first) y la máxima frecuencia de letra (second) para dicha posición O(nm). Luego, se ordenan todos estos en base al segundo elemento del par y de forma decreciente O(mlgm).
##### Complejidad algorítmica
Identificar la máxima frecuencia de letra cada una de las n cadenas desde la posición i = (0, 1, …, m-1) O(nm).

Ordenamiento del vector maxPerLevel O(mlgm).

Construir el SPTrie O(nm).

Por lo que, la complejidad final se puede acotar como O(nm+mlgm).

# proyecto-ada
## Trie-eficiente
### Pregunta 1
#### Elección voraz:
Se analiza comparando las letras de cada una de las cadenas desde la posición i = (0, 1, …, m-1) y se obtienen m pares con la posición i (first) y la máxima frecuencia de letra (second) para dicha posición. Luego, se ordenan todos estos en base al segundo elemento del par y de forma creciente.
#### Proof: 
Sea X una solución óptima al problema donde X tiene un p = (p0, p1, …, pm-1) tal que la máxima frecuencia está ordenada de forma creciente y se selecciona la posición (first) para llenar p.
p0.second > p1.second > … > pm-1.second
Suponga por contradicción que X no es óptimo, entonces existe un Y’ que tiene una permutación de p’ que hace que tenga un mínimo número de aristas, es decir aristas(Y’) < aristas(X). Puede darse el caso en el que exista otra permutación p’ tal que aristas(Y’) = aristas(X) debido a una distinta forma de ordenamiento para los valores iguales. Note que para que exista un Y’ con un menor número de aristas que X deben existir dos resultados distintos de ordenar un mismo arreglo de forma creciente, lo cual es imposible y se llega a una contradicción de la existencia de Y’, por lo que X es óptimo.

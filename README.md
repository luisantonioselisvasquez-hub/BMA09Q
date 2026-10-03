## Grupo 7: Árbol de expansión mínima

- **Árbol de expansión:** Definición de árbol de expansión y explicación de sus características dentro de un grafo conexo.

- **Árbol de expansión mínima:** Definición del problema de encontrar un árbol de expansión cuyo costo total sea mínimo y explicación de sus características.

- **Kruskal:** Explicación del algoritmo de Kruskal, su estrategia para seleccionar las aristas de menor peso y cómo evita la formación de ciclos.

- **Prim:** Explicación del algoritmo de Prim, su estrategia para construir progresivamente el árbol a partir de un vértice inicial.

- **Comparación entre Kruskal y Prim:** Comparación de las estrategias utilizadas por ambos algoritmos y de las características de los grafos en las que resulta conveniente cada uno.

- **Selección del algoritmo:** Explicación de los criterios que permiten determinar cuándo utilizar Kruskal o Prim según las características del problema.
---

## Implementación

Los algoritmos de Kruskal y Prim fueron implementados en lenguaje C.

### Archivos

- `src/kruskal.c`: implementación del algoritmo de Kruskal.
- `src/prim.c`: implementación del algoritmo de Prim.
- `informe/Informe_Grupo7_Arbol_Expansion_Minima.pdf`: informe final del trabajo.

## Compilación

### Kruskal
```bash
gcc src/kruskal.c -o kruskal
./kruskal

### Prim
```bash
gcc src/prim.c -o prim
./prim
```

Ambas implementaciones utilizan el mismo grafo de prueba y obtienen un árbol de expansión mínima con costo total 19.

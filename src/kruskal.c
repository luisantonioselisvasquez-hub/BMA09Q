#include <stdio.h>
#include <stdlib.h>

// Estructura para representar una arista con origen, destino y peso
struct Edge {
    int src, dest, weight;
};

// Estructura para representar el grafo
struct Graph {
    int V, E;
    struct Edge* edges;
};

// Estructura auxiliar para el manejo de Conjuntos Disjuntos (Union-Find)
struct Subset {
    int parent;
    int rank;
};

// Funcion para inicializar el grafo
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge*)malloc(E * sizeof(struct Edge));
    return graph;
}

// Funcion find con compresion de caminos
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Funcion union por rango
void Union(struct Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Funcion de comparacion para qsort (orden ascendente por peso)
int compareEdges(const void* a, const void* b) {
    const struct Edge* a1 = (const struct Edge*)a;
    const struct Edge* b1 = (const struct Edge*)b;

    if (a1->weight < b1->weight)
        return -1;
    if (a1->weight > b1->weight)
        return 1;
    return 0;
}

// Algoritmo principal de Kruskal
void kruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];
    int e = 0;
    int i = 0;

    // Ordenar las aristas por peso
    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);

    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < graph->E) {
        struct Edge next_edge = graph->edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // Si no se forma ciclo, se añade al resultado
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }
    if (e != V - 1) {
    	printf("\nEl grafo es desconexo. Se obtuvo un bosque de expansion minimo.\n");

    	printf("Arista (Origen - Destino) \t Peso\n");
    	int costoTotal = 0;

    	for (int j = 0; j < e; ++j) {
        	printf("       %d <---> %d        \t  %d\n",
            result[j].src, result[j].dest, result[j].weight);
        	costoTotal += result[j].weight;
    	}

   		printf("Costo total del bosque: %d\n", costoTotal);
    	free(subsets);
    	return;
	}
    // Impresion de resultados para la ejecucion del programa
    printf("\n--- ARBOL DE EXPANSION MINIMA (KRUSKAL) ---\n");
    printf("Arista (Origen - Destino) \t Peso\n");
    int costoTotal = 0;
    for (int j = 0; j < e; ++j) {
        printf("       %d <---> %d        \t  %d\n", result[j].src, result[j].dest, result[j].weight);
        costoTotal += result[j].weight;
    }
    printf("Costo total del MST: %d\n", costoTotal);

    free(subsets);
}

int main() {
    int V = 4;
    int E = 5;
    struct Graph* graph = createGraph(V, E);

    // Carga de datos de prueba
    graph->edges[0] = (struct Edge){0, 1, 10};
    graph->edges[1] = (struct Edge){0, 2, 6};
    graph->edges[2] = (struct Edge){0, 3, 5};
    graph->edges[3] = (struct Edge){1, 3, 15};
    graph->edges[4] = (struct Edge){2, 3, 4};

    kruskalMST(graph);

    free(graph->edges);
    free(graph);

    return 0;
}

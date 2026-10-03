#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

// Numero de vertices en el grafo
#define V 4

// Función auxiliar para encontrar el vertice con el valor de clave minimo,
// entre los vertices que aun no estan incluidos en el MST
int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Funcion para imprimir el Arbol de Expansion Minima almacenado en parent[]
void printMST(int parent[], int graph[V][V]) {
    printf("\n=== RESULTADO DEL MST (ALGORITMO DE PRIM) ===\n");
    printf("Arista (Origen - Destino) \t Peso\n");
    int costoTotal = 0;
    for (int i = 1; i < V; i++) {
        printf("       %d <---> %d        \t  %d\n", parent[i], i, graph[i][parent[i]]);
        costoTotal += graph[i][parent[i]];
    }
    printf("Costo total minimo de la red: %d\n", costoTotal);
}

// Función principal que construye e imprime el MST para un grafo representado
// mediante una matriz de adyacencia
void primMST(int graph[V][V]) {
    int parent[V];   // Almacenara el MST construido
    int key[V];      // Valores de peso minimo utilizados para elegir la arista de corte
    bool mstSet[V];  // Representa el conjunto de vertices ya incluidos en el MST

    // Inicializar todas las claves como INFINITAS y mstSet como falso
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    // Siempre incluimos el primer vertice en el MST.
    key[0] = 0;     // Su clave se hace 0 para que sea el primer nodo seleccionado
    parent[0] = -1; // El primer nodo es siempre la raiz del MST

    // Procesar todos los vertices del grafo
	for (int count = 0; count < V; count++) {

    	// Elegir el vertice con la clave minima
		int u = minKey(key, mstSet);

    	// Si no existe un vertice alcanzable, el grafo es desconexo
    	if (u == -1) {
        	printf("El grafo es desconexo. No existe un unico MST.\n");
        	return;
    	}
    	// Marcar el vertice elegido como procesado
    	mstSet[u] = true;
    	// Actualizar las claves de los vertices adyacentes
    	for (int v = 0; v < V; v++) {
        	if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
            	parent[v] = u;
            	key[v] = graph[u][v];
        	}
    	}
	}

    // Imprimir el resultado estructurado
    printMST(parent, graph);
}

int main() {
    // Definicion del grafo mediante una matriz de adyacencia (0 indica que no hay arista directa)
    int graph[V][V] = {
        { 0, 10,  6,  5 },
        { 10, 0,  0, 15 },
        {  6, 0,  0,  4 },
        {  5, 15, 4,  0 }
    };

    // Ejecutar el algoritmo de Prim
    primMST(graph);

    return 0;
}

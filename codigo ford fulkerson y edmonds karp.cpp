#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODOS 100
#define INF 1e9

int num_nodos;
int capacidad[MAX_NODOS][MAX_NODOS];
int red_residual[MAX_NODOS][MAX_NODOS];
int padre[MAX_NODOS];
bool visitado[MAX_NODOS];

// =======================================================
// 1. FORD-FULKERSON (Usa Búsqueda en Profundidad - DFS)
// =======================================================

// DFS que guarda el camino recorrido mediante el arreglo 'padre'
bool dfs_camino(int u, int t) {
    if (u == t) return true;
    visitado[u] = true;

    for (int v = 0; v < num_nodos; v++) {
        if (!visitado[v] && red_residual[u][v] > 0) {
            padre[v] = u;
            if (dfs_camino(v, t)) return true;
        }
    }
    return false;
}

void ejecucion_ford_fulkerson(int s, int t) {
    printf("\n============ EJECUCION: FORD-FULKERSON (DFS) ============\n");
    int flujo_maximo = 0;
    int iteracion = 1;

    // Inicializar la red residual con las capacidades originales
    for (int i = 0; i < num_nodos; i++) {
        for (int j = 0; j < num_nodos; j++) {
            red_residual[i][j] = capacidad[i][j];
        }
    }

    while (true) {
        memset(visitado, false, sizeof(visitado));
        padre[s] = -1;

        if (!dfs_camino(s, t)) {
            break; // No hay más caminos aumentantes
        }

        // Encontrar la capacidad residual mínima (cuello de botella)
        int cuello_botella = INF;
        for (int v = t; v != s; v = padre[v]) {
            int u = padre[v];
            if (red_residual[u][v] < cuello_botella) {
                cuello_botella = red_residual[u][v];
            }
        }

        // Imprimir el camino encontrado en consola
        printf("\nIteracion %d:\n", iteracion++);
        printf("  -> Camino Aumentante encontrado (DFS): ");
        
        // Reconstruir camino para imprimirlo ordenado s -> ... -> t
        int camino[MAX_NODOS];
        int tam_camino = 0;
        for (int v = t; v != -1; v = padre[v]) {
            camino[tam_camino++] = v;
        }
        for (int i = tam_camino - 1; i >= 0; i--) {
            printf("%d%s", camino[i], (i > 0) ? " -> " : "");
        }

        printf("\n  -> Cuello de botella (Flujo enviado): %d\n", cuello_botella);

        // Actualizar la red residual
        for (int v = t; v != s; v = padre[v]) {
            int u = padre[v];
            red_residual[u][v] -= cuello_botella;
            red_residual[v][u] += cuello_botella;
        }

        flujo_maximo += cuello_botella;
        printf("  -> Flujo Acumulado actual: %d\n", flujo_maximo);
    }

    printf("\n---------------------------------------------------------\n");
    printf("RESULTADO FINAL: El Flujo Maximo de la red es: %d\n", flujo_maximo);
    printf("---------------------------------------------------------\n");
}


// =======================================================
// 2. EDMONDS-KARP (Usa Búsqueda en Anchura - BFS)
// =======================================================

bool bfs_camino(int s, int t) {
    memset(visitado, false, sizeof(visitado));
    int cola[MAX_NODOS];
    int frente = 0, final = 0;

    cola[final++] = s;
    visitado[s] = true;
    padre[s] = -1;

    while (frente < final) {
        int u = cola[frente++];

        for (int v = 0; v < num_nodos; v++) {
            if (!visitado[v] && red_residual[u][v] > 0) {
                cola[final++] = v;
                padre[v] = u;
                visitado[v] = true;
                if (v == t) return true;
            }
        }
    }
    return false;
}

void ejecucion_edmonds_karp(int s, int t) {
    printf("\n============ EJECUCION: EDMONDS-KARP (BFS) ============\n");
    int flujo_maximo = 0;
    int iteracion = 1;

    for (int i = 0; i < num_nodos; i++) {
        for (int j = 0; j < num_nodos; j++) {
            red_residual[i][j] = capacidad[i][j];
        }
    }

    while (bfs_camino(s, t)) {
        int cuello_botella = INF;
        for (int v = t; v != s; v = padre[v]) {
            int u = padre[v];
            if (red_residual[u][v] < cuello_botella) {
                cuello_botella = red_residual[u][v];
            }
        }

        printf("\nIteracion %d:\n", iteracion++);
        printf("  -> Camino Mas Corto encontrado (BFS): ");

        int camino[MAX_NODOS];
        int tam_camino = 0;
        for (int v = t; v != -1; v = padre[v]) {
            camino[tam_camino++] = v;
        }
        for (int i = tam_camino - 1; i >= 0; i--) {
            printf("%d%s", camino[i], (i > 0) ? " -> " : "");
        }

        printf("\n  -> Cuello de botella (Flujo enviado): %d\n", cuello_botella);

        for (int v = t; v != s; v = padre[v]) {
            int u = padre[v];
            red_residual[u][v] -= cuello_botella;
            red_residual[v][u] += cuello_botella;
        }

        flujo_maximo += cuello_botella;
        printf("  -> Flujo Acumulado actual: %d\n", flujo_maximo);
    }

    printf("\n---------------------------------------------------------\n");
    printf("RESULTADO FINAL: El Flujo Maximo de la red es: %d\n", flujo_maximo);
    printf("---------------------------------------------------------\n");
}


// =======================================================
// MAIN: GRAFO DE EJEMPLO Y MENÚ INTERACTIVO
// =======================================================
int main() {
    num_nodos = 6;
    memset(capacidad, 0, sizeof(capacidad));

    // Grafo de ejemplo estandar (Nodos: 0 a 5, Fuente: 0, Sumidero: 5)
    capacidad[0][1] = 16;
    capacidad[0][2] = 13;
    capacidad[1][2] = 10;
    capacidad[1][3] = 12;
    capacidad[2][1] = 4;
    capacidad[2][4] = 14;
    capacidad[3][2] = 9;
    capacidad[3][5] = 20;
    capacidad[4][3] = 7;
    capacidad[4][5] = 4;

    int fuente = 0, sumidero = 5;

    // Ejecutamos ambos algoritmos para mostrar las diferencias en la exposicion
    ejecucion_ford_fulkerson(fuente, sumidero);
    ejecucion_edmonds_karp(fuente, sumidero);

    return 0;
}

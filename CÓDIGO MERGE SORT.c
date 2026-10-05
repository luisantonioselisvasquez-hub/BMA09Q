#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Combina dos subarreglos contiguos ordenados y cuenta las inversiones cruzadas.
 * 
 * Subarreglos:
 *   - Izquierdo: arr[inicio ... medio]
 *   - Derecho:   arr[medio + 1 ... fin]
 */
long long merge_and_count(int arr[], int temp[], int inicio, int medio, int fin) {
    int i = inicio;      // Puntero para el subarreglo izquierdo
    int j = medio + 1;   // Puntero para el subarreglo derecho
    int k = inicio;      // Puntero para el arreglo auxiliar combinado
    long long inv_cruzadas = 0;

    // Recorrido simultaneo de ambas mitades
    while (i <= medio && j <= fin) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            // Si arr[i] > arr[j], entonces todos los elementos restantes en la
            // mitad izquierda (desde i hasta medio) forman una inversion con arr[j].
            inv_cruzadas += (long long)(medio - i + 1);
        }
    }

    // Copiar elementos restantes de la mitad izquierda (si quedan)
    while (i <= medio) {
        temp[k++] = arr[i++];
    }

    // Copiar elementos restantes de la mitad derecha (si quedan)
    while (j <= fin) {
        temp[k++] = arr[j++];
    }

    // Transferir el contenido ordenado de vuelta al arreglo original
    for (i = inicio; i <= fin; i++) {
        arr[i] = temp[i];
    }

    return inv_cruzadas;
}

/**
 * @brief Funcion recursiva que aplica Divide y Venceras para ordenar y contar inversiones.
 */
long long merge_sort_count(int arr[], int temp[], int inicio, int fin) {
    long long total_inv = 0;

    // Caso base: 0 o 1 elemento (ya esta ordenado, 0 inversiones)
    if (inicio < fin) {
        // Calculo seguro del indice medio para evitar overflow de enteros
        int medio = inicio + (fin - inicio) / 2;

        // Fase 1 y 2: Division y Conquista recursiva
        total_inv += merge_sort_count(arr, temp, inicio, medio);
        total_inv += merge_sort_count(arr, temp, medio + 1, fin);

        // Fase 3: Combinacion y conteo de inversiones cruzadas
        total_inv += merge_and_count(arr, temp, inicio, medio, fin);
    }

    return total_inv;
}

int main(void) {
	int i;
    int A[] = {54, 26, 93, 17, 77, 31, 44, 55, 20, 65};
    int n = sizeof(A) / sizeof(A[0]);

    printf("Arreglo original:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n\n");

    // Asignacion de un unico buffer auxiliar para evitar llamadas repetidas a malloc
    int *temp = (int *)malloc(n * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria.\n");
        return 1;
    }

    long long total_inversiones = merge_sort_count(A, temp, 0, n - 1);

    printf("Arreglo ordenado:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n\n");

    printf("Numero total de inversiones detectadas: %lld\n", total_inversiones);

    free(temp);
    return 0;
}

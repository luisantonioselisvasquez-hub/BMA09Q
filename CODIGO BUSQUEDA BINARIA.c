#include <stdio.h>

int busquedaBinaria(int arr[], int inicio, int fin, int objetivo) {
    
    if (inicio > fin) {
        return -1;
    }

    int medio = (inicio + fin) / 2;

    if (arr[medio] == objetivo) {
        return medio; 
    }

    if (arr[medio] > objetivo) {
        return busquedaBinaria(arr, inicio, medio - 1, objetivo);
    }

    return busquedaBinaria(arr, medio + 1, fin, objetivo);
}

int main() {

    int datos[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};

    int n = sizeof(datos) / sizeof(datos[0]); //sizeof lee el espacio en bytes, un numero ocupa 4 bytes.
    
    int objetivo = 5;
    printf("Buscando numero %i...\n", objetivo);

    int resultado = busquedaBinaria(datos, 0, n - 1, objetivo); //funcion recursiva

    if (resultado == -1) {
    	printf("Elemento no encontrado.\n");
    } else {
        printf("Elemento encontrado en la posicion %d.\n", resultado);
    }

    return 0;
}

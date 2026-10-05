#include <stdio.h>

void intercambiar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particion(int A[], int inicio, int fin) {
    int pivote = A[fin]; 
    int i = inicio - 1;  
    int j;

    for (j = inicio; j < fin; j++) {
        if (A[j] >= pivote) { 
            i++;
            intercambiar(&A[i], &A[j]);
        }
    }
    
    intercambiar(&A[i + 1], &A[fin]);
    return (i + 1); 
}

void quickSort(int A[], int inicio, int fin) {
    if (inicio < fin) {
        int pi = particion(A, inicio, fin);

        quickSort(A, inicio, pi - 1); 
        quickSort(A, pi + 1, fin);    
    }
}

void imprimirArreglo(int A[], int tam) {
	int i;
    for (i = 0; i < tam; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    int n, i;

    printf("Ingrese la cantidad de numeros a ordenar: ");
    scanf("%d", &n);

    int datos[n];

    printf("Ingrese los %d numeros:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &datos[i]);
    }

    quickSort(datos, 0, n - 1);

    printf("\nArreglo ordenado de mayor a menor:\n");
    imprimirArreglo(datos, n);

    return 0;
}

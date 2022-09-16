/**
 * @file Horner_0.1.c
 * @author Roberto Reyes Brito  (roberto1500reyes@gmail.com)
 * @brief Programa que verifica si un punto es una raíz con el método de Horner y
 *        realiza el algoritmo completo de Horner para obtener el desarrollo de Taylor.
 * @version 0.1
 * @date 2022-09-16
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Método de Horner que regresa el resuido de un polinomios.
 * 
 * @param p Arreglo del polinomio.
 * @param r Punto a evaluar.
 * @param size Tamaño del arreglo.
 * @return int 
 */
int MetodoHorner(int *p, int r, int size){
    int bk = p[size - 1]; // bn = an.

    printf("b%d = %d\n", size - 1, bk);

    for(int i = size - 2; i >= 0; i--){
        bk = p[i] + (bk * r); // bn-1 = an-1 + rbn.
        printf("b%d = %d\n", i, bk);
    }

    return bk;
}

/**
 * @brief Algoritmo completo de Horner. 
 *        Imprime el desarrollo de Taylor de un polinomio.
 * 
 * @param p Arreglo del polinomio.
 * @param r Punto a evaluar.
 * @param size Tamaño del arreglo.
 */
void AlgoritmoCompletoHorner(int *p, int r, int size){
    int bk;
    int *pAux = p; // Arreglo auxiliar para guardar los an.
    int *pAux2; // Arreglo auxiliar para guardar los bn y pasralos como an a pAux.
    int c[size - 1]; // Arraglo de las coeficientes.
    int count = size - 1; // Entero para recorrer y guardar los coeficientes.
    c[0] = p[count];

    for(int i = size - 1; i >= 0; i--){
        pAux2 = malloc(i * sizeof(int));
        bk = pAux[i]; // bn = an.
        pAux2[i - 1] = bk; // guardar bn para la próxima iteración.

        printf("%d, ", bk);

        // Método de Horner.
        for (int j = i - 1; j >= 0; j--){
            bk = pAux[j] + (bk * r); // bn-1 = an-1 + rbn.
            printf("%d, ", bk);
            if(j == 0){
                c[count] = bk; // Agrega los coeficientes cuando se obtienen.
                count--;
            }else{
                pAux2[j - 1] = bk; // Si no guardar los bk en un arreglo.
            }
        }

        printf("\n");
        free(pAux);
        pAux = malloc(i* sizeof(int));
        pAux = pAux2; // Copia los coeficientes del polinomio  fatorizado.
        free(pAux2);
    }

    // Imprime el deasrrollo de Taylor del polinomio.
    printf("\nDesarrollo de Taylor: ");
    printf("\nP(x) = %d(x-%d)^%d", c[0], r, size - 1);
    int j = size - 2;
    for (int i = 1; i < size - 1; i++){
        if(c[j] < 0){
            printf("%d(x-%d)^%d", c[i], r, j);
        }else{
            printf("+%d(x-%d)^%d", c[i], r, j);
        }
        j--;
    }
    if(c[size - 1] < 0){
            printf("%d\n", c[size - 1]);
        }else{
            printf("+%d\n", c[size - 1]);
        }
    
    // Liberación de mameoria.
    free(pAux);
    free(pAux2);
}

int main(void) {
    int *p; // Arreglo para guardar el polinomio.
    int size; // Tamaño del polinomio, (n = size - 1).
    int r; // Punto a evaluar.

    printf("Ingrese el tamanio del polinomio: ");
    scanf("%d", &size);

    if(size <= 0){
        printf("El tamanio tiene que ser mayor a 0\n");
        return 0;
    }

    p = malloc( size * sizeof(int)); // Alojación dinamica de memoria del arrglo del polinomio.

    // Ingresar los términos del polinomio.
    for(int i = 0; i < size; i++){
        printf("Ingrese el termino a%d: ", i);
        scanf("%d", &p[i]);
    }

    printf("Ingrese la raiz a evaluar: ");
    scanf("%d", &r);

    // Imprime el polinomio.
    printf("\nPolinomio: ");
    printf("%dX^%d", p[size-1], size-1);
    for(int i = size - 2 ; i >= 0 ; i--){
        if(p[i] < 0){
            printf("%dX^%d", p[i], i);
        }else{
            printf("+%dX^%d", p[i], i);
        }
    }

    printf("\n\nMetodo de Horner: \n");

    // Llamada de la función del método de Horner.
    int b0 = MetodoHorner(p, r, size);
    
    // Verifica si el punto r es raíz.
    if(b0 == 0){
        printf("\n%d si es raiz del polinomio.\n", r);
    }else{
        printf("\n%d no es raiz del polinomio.\n", r);
    }

    printf("\nAlgoritmo completo de Horner: \n");
    // Llamada de la función del algoritmo completo de Horner.
    AlgoritmoCompletoHorner(p, r, size);

    free(p);
    return 0;
}

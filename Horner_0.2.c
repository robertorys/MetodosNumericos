/**
 * @file Horner_0.2.c
 * @author Roberto Reyes Brito (roberto1500reyes@gmail.com)
 * @brief Programa que verifica si un punto es una raíz con el método de Horner y
 *        realiza el algoritmo completo de Horner para obtener el desarrollo de Taylor.
 * @version 0.2
 * @date 2022-09-16
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Método de Horner para evaluar si un punto es raíz.
 * 
 * @param p Puntero a un arrrglo que tiene los coeficietes del polinomio.
 * @param r Punto a evaluar.
 * @param size Tamaño del arreglo.
 * @return int* Arreglo que regresa los bn.
 */
int *MetodoHorner(int *p, int r, int size);

/**
 * @brief Funcón que imprime los bn en ordes descendente.
 * 
 * @param p Puntero a un arrrglo que tiene los coeficietes del polinomio.
 * @param size Tamaño del arreglo.
 */
void ImprimirBn(int *p, int size);

/**
 * @brief Verifica si el punto a evaluar es una raíz.
 * 
 * @param b0 residuo del metodo de Horner.
 * @return int regresa 1 si es raíz y 0 si no es raíz.
 */
int VerificarRaiz(int b0, int r);

/**
 * @brief Algoritmo completo de Horner para el desarrollo de Taylor de un polinomio.
 * 
 * @param p Puntero a un arrrglo que tiene los coeficietes del polinomio.
 * @param r Punto a evaluar.
 * @param size Tamaño del arreglo.
 * @return int* Arreglo que regresa los coeficientes para el desarrollo de Taylor.
 */
int *AlgortmoCompletoHorner(int *p, int r, int size);

/**
 * @brief Imprime el desarrollo de Taylor del polinomio.
 * 
 * @param c Puntero que guarda un arreglo con los coeficientes.
 * @param r Punto a evaluar.
 * @param size Tamaño del arreglo.
 */
void ImprimeDesarrolloT(int *c, int r, int size);

/**
 * @brief Imprime en la consola el polinomio.
 * 
 * @param p Puntero que gurda el arreglo de coeficientes del polinomio.
 * @param size Tamaño del arreglo.
 */
void ImprimirPolinomio(int *p, int size);

int main(void) {
    int *p; // Puntero de un arreglo para guardar el polinomio.
    int size; // Tamaño del polinomio, (n = size - 1).
    int r; // Punto a evaluar.
    int *c; // Puntero de un arreglo para guardar los coeficientes del desarrollo de Taylor.

    printf("Ingrese el tamanio del polinomio: ");
    scanf("%d", &size);

    if(size <= 0){
        printf("El tamanio tiene que ser mayor a 0\n");
        return 0;
    }

    p = malloc(size * sizeof(int)); // Reservar memoria para arrglo del polinomio.

    // Ingresar los coeficientes del polinomio.
    for(int i = 0; i < size; i++){
        printf("Ingrese el coeficiente a%d: ", i);
        scanf("%d", &p[i]);
    }

    printf("Ingrese el punto a evaluar: ");
    scanf("%d", &r);

    ImprimirPolinomio(p, size);

    printf("\nMetodo de Horner: \n");

    int *pBn = malloc(size * sizeof(int));
    pBn = MetodoHorner(p, r, size);

    // Verificar que r sea una raíz para el polinomio.
    VerificarRaiz(pBn[0], r);

    // Llamada de la función del algoritmo completo de Horner.
    c = AlgortmoCompletoHorner(p, r, size);
    ImprimeDesarrolloT(c, r, size);

    free(c);
    free(p);
    free(pBn);
    return 0;
}

int *MetodoHorner(int *p, int r, int size) {
    int *pAux = malloc(size * sizeof(int));
    int bk = p[size - 1]; // bn = an.

    pAux[size - 1] = p[size - 1]; // Guardar bn.

    for(int i = size - 2; i >= 0; i--){
        bk = p[i] + (bk * r); // bn-1 = an-1 + rbn.
        pAux[i] = bk; // Guardar bk.
    }

    ImprimirBn(pAux, size);

    return pAux;
}

void ImprimirBn(int *p, int size) {
    printf("\n[ ");
    for(int i = size - 1; i > 0; i--){
        printf("b%d = %d, ", i, p[i]);
    }
    printf("b0 = %d ]\n", p[0]);
}

int VerificarRaiz(int b0, int r){
    if(b0 == 0){
        printf("\n%d si es raiz del polinomio.\n", r);
        return 1;
    }else{
        printf("\n%d no es raiz del polinomio.\n", r);
        return 0;
    }
}

int *AlgortmoCompletoHorner(int *p, int r, int size) {
    int *pAux = p;
    int *pAux2;
    int bk;
    int *c = malloc(size * sizeof(int));
    int Ci = 0;
    c[size - 1] = p[size - 1];

    printf("\nAlgoritmo completo de Horner: \n");

    for(int i = size; i > 0; i--) {
        pAux2 = malloc(i * sizeof(int));
        pAux2 = MetodoHorner(pAux, r, i);
        c[Ci] = pAux2[0];
        Ci++;
        free(pAux);
        pAux = malloc((i - 1) * sizeof(int));
        for (int j = i - 1; j > 0; j--) {
            pAux[j - 1] = pAux2[j];
        }
        free(pAux2);
    }
    free(pAux);

    return c;
}

void ImprimeDesarrolloT(int *c, int r, int size){
    printf("\nDesarrollo de Taylor: \n");
    printf("P(x) = ");

    if(size > 2){
        if(r > 0){
            if(c[size - 1] != 0){
                printf("%d(x-%d)^%d", c[size - 1], r, size - 1);
            }
        }else if(r < 0){
            if(c[size - 1] != 0){
                printf("%d(x+%d)^%d", c[size - 1], -r, size - 1);
            }
        }else{
           if(c[size - 1] != 0){
                printf("%dx^%d", c[size - 1], size - 1);
            } 
        }

        for(int i = size - 2; i > 1; i--){
            if(r > 0){
                if(c[i] > 0){
                    printf("+%d(x-%d)^%d", c[i], r, i);
                }else if(c[i] < 0){
                    printf("%d(x-%d)^%d", c[i], r, i);
                }
            }else if(r < 0){
                if(c[i] < 0){
                    printf("+%d(x+%d)^%d", c[i], -r, i);
                }else if(c[i] < 0){
                    printf("%d(x+%d)^%d", c[i], -r, i);
                }
            }else{
                if(c[i] > 0){
                    printf("+%dx^%d", c[i], i );
                }else if(c[i] < 0){
                    printf("%dx^%d", c[i], i);
                }
            }
        }
    }

    if(size > 1){
        if(r > 0){
            if(c[1] < 0){
                printf("%d(x-%d)", c[1], r);
            }else if(c[1] > 0){
                printf("+%d(x-%d)", c[1], r);
            }
        }else if(r < 0){
            if(c[1] < 0){
                printf("%d(x+%d)", c[1], -r);
            }else if(c[1] > 0){
                printf("+%d(x-%d)", c[1], r);
            }
        }else{
            if(c[1] < 0){
                printf("%dx", c[1]);
            }else if(c[1] > 0){
                printf("+%d(x-%d)", c[1], r);
            }
        }
    }

    if(c[0] < 0){
        printf("%d", c[0]);
    }else if(c[0] > 0){
        printf("+%d", c[0]);
    }

    printf("\n");
}

void ImprimirPolinomio(int *p, int size){
    printf("\nPolinomio: ");

    if(size > 2){
        if(p[size - 1] != 0){
            printf("%dx^%d", p[size - 1], size - 1);
        }

        for(int i = size - 2; i > 1; i--){
            if(p[i] > 0){
                printf("+%dx^%d", p[i], i);
            }else if(p[i] < 0){
                printf("%dx^%d", p[i], i);
            }
        }
    }

    if(size > 1){
        if(p[1] < 0){
            printf("%dx", p[1]);
        }else if(p[1] > 0){
            printf("+%dx", p[1]);
        }
    }

    if(p[0] < 0){
        printf("%d", p[0]);
    }else if(p[0] > 0){
        printf("+%d", p[0]);
    }

    printf("\n");
}
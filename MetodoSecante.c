/**
 * @file MetodoSecante.c
 * @author Roberto Reyes Brito (roberto1500reyes@gmail.com)
 * @brief Este método imita al de Newton pero evita el cálculo de derivadas, para encontrar la raíz de f(x).
 * El método de la secante reemplaza f'(Xn) en Xn+1 = Xn - (f(Xn) / f'(Xn)) mediante una aproximación,
 * f'(Xn) ≈ (f(Xn-1) - f(Xn)) / (Xn-1 - Xn), cuando usamos esta aproximación, 
 * el resultado define el método de la secante: 
 * Xn+1 = Xn - ( (Xn - Xn-1) / (f(Xn) - f(Xn-1)) ) * f(Xn).
 * Funciona con ecuaciones en forma de polinomio.
 * 
 * @version 1
 * @date 2022-10-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define true 1

typedef struct TerminoPolinomio {
    int a;
    int pow;
}terP;

FILE *out; // archivo txt para regresar los datas obtenidos
// double 0.000000

/**
 * @brief Función para que el usuario ingrese un polinomio.
 * 
 * @param nTerm cantidad de terminos del polinomio.
 * @return int* arreglo que guarda los coeficientes del polinomio.
 */
terP *polinomio(int nTerm);

/**
 * @brief Imprime en la consola el polinimio y lo guarda en un archivo txt.
 * 
 * @param pol 
 * @param nTerm 
 */
void imprimirPol(terP *pol, int nTerm);

/**
 * @brief Método de la secante, dado dos puntos se obtiene la recta secante dada la función y 
 * se obtiene el punto donde la recta secante corta en el eje y.
 * 
 * @param pol Arreglo que guarda los términos del polinomio.
 * @param nTerm Cantidad de términos del polinomio.
 * @param raiz Raiz para determinar el error de la solución y para el algortimo
 * @return int 
 */
int metodoSecante(terP *pol, int nTerm, double raiz);

/**
 * @brief Función que evalua la ecuaion en un punto x.
 * 
 * @param pol arreglo para el polinomio.
 * @param nTerm cantidad de terminos del polinomio.
 * @param x punto a evualar la ecuación.
 * @return double regresa el valor de la ecuación en el punto x.
 */
double evaluarP(terP *pol, int nTerm, double x);

int main(void){
    srand(time(NULL));
    out = fopen("SalidaSecante.txt", "w");

    int nTerm;
    printf("\t---------- Metodo de Newton Rapson ----------\n\n");
    fprintf(out, "\t---------- Metodo de Newton Rapson ----------\n\n");
    printf("---------- Ingresar ecuacion ----------\n");

    printf("Ingrese la cantidad de terminos: ");
    scanf("%i", &nTerm);
    if(nTerm <= 0){
        printf("La ciantidad de terminos tiene que ser mayor que 0\n");
        return 0;
    }

    terP *pol = polinomio(nTerm);
    imprimirPol(pol, nTerm);

    double raiz;
    printf("Ingresa la raiz: ");
    scanf("%lf", &raiz);

    fprintf(out, "La raiz es: %lf\n", raiz);

    metodoSecante(pol, nTerm, raiz);

    fclose(out);
    return 0;
}

int metodoSecante(terP *pol, int nTerm, double raiz) {
    int a, b, ai, bi;
    double eAbsoluto, eRelativo, e;
    double fx, fxm, fa, fb;
    double Xk, Xkm, XkAux;

    printf("Ingresar intervalo [a,b]:\n");
    printf("Ingrese a: ");
    scanf("%i", &a);
    printf("Ingrese b: ");
    scanf("%i", &b);

    if(a == b) {
        printf("a tiene que ser diferente de b\n");
        return 0;
    }

    ai = a < b ? a : b;
    bi = b > a ? b : a;

    printf("- Intervalo de busqueda: [%i,%i]\n", ai, bi);
    fprintf(out, "- Intervalo de busqueda: [%i,%i]\n", ai, bi);

    // Comprobar que a o b sean solucion.
    fa = evaluarP(pol, nTerm, a);
    fb = evaluarP(pol, nTerm, b);

    if(fa == 0) {
        printf("a = %i, es raiz para la ecuacion\n", a);
        fprintf(out, "a = %i, es raiz para la ecuacion\n", a);
        return a;
    }
    if(fb == 0) {
        printf("b = %i, es raiz para la ecuacion\n", b);
        fprintf(out, "b = %i, es raiz para la ecuacion\n", b);
        return b;
    }

    // Comprobar que existe una raíz en el intervalo [a,b].
    // Se supone que solo deberia tener una raíz en el intervalo.
    if((fa*fb) > 0) {
        printf("No exixte una raiz en el intervalo [%i,%i]", a, b);
        fprintf(out, "No exixte una raiz en el intervalo [%i,%i]", a, b);
        return 0;
    }

    // Obtener dos puntos aleatorio dentro del intervalo [a,b].
    Xk = (int)ai + (rand() % (((int)bi - (int)ai) + 1));
    Xkm = (int)ai + (rand() % (((int)bi - (int)ai) + 1));
    while (Xk == Xkm) {
        Xkm = (int)ai + (rand() % (((int)bi - (int)ai) + 1));
    }

    int i = 0;
    while (true) {
        fx = evaluarP(pol, nTerm, Xk);
        fxm = evaluarP(pol, nTerm, Xkm);
        XkAux = Xk;
        // Obtener el punto donde la recta secante, dado dos puntos en la función f(x), intersesecta el eje y.
        // Xn+1 = Xn - ( (Xn - Xn-1) / (f(Xn) - f(Xn-1)) ) * f(Xn)
        Xk = Xk - ( ( (Xk - Xkm) / (fx - fxm) ) * fx );
        Xkm = XkAux;

        printf("n = %i || ", i); fprintf(out, "n = %i || ", i);
        printf("Xn = %lf || ", Xk); fprintf(out, "Xn = %lf || ", Xk);
        printf("Xn-1 = %lf || ", Xkm); fprintf(out, "Xn-1 = %lf || ", Xkm);
        printf("f(Xn) = %lf\n", fx); fprintf(out, "f(Xn) = %lf\n", fx);

        // Determinar el error relativo para regresar una solución con cierto error relativo.
        // Error absoluto = |valor exacto - valor aproximado|
        e = raiz - Xk;
        eAbsoluto = (e >= 0 ? e : -e);
        // Error relativo = error absoluto / |valor exacto|
        if(raiz != 0){
            eRelativo = eAbsoluto / (raiz > 0 ? raiz : -raiz);
        } else { // si el valor exacto = 0, entonces la división es indeterminada.
            eRelativo = eAbsoluto;
        }
        // Si f(Xk) == 0, entonces pi es raíz.
        // Si el error relativo de f(Xk); eRalativo esta 10^-3 > eRelativo,
        // entonce Xk es una solución aproximada.

        if(eRelativo < 0.00001 || fx == 0){
            printf("La raiz es P%i = %lf\n", i, Xk);
            printf("La raiz tiene un error relativo de %lf\n", eRelativo);
            fprintf(out, "La raiz es P%i = %lf\n", i, Xk);
            fprintf(out, "La raiz tiene un error relativo de %lf\n", eRelativo);
            return Xk;
        }
        i++;
    }   
}

double evaluarP(terP *pol, int nTerm, double x) {
    double r = 0;
    for (int i = 0; i < nTerm; i++) {
        r += pol[i].a * (pow(x, pol[i].pow));
    }
    return r;
}

terP *polinomio(int nTerm) {
    terP *pol = malloc(nTerm * sizeof(terP));
    for(int i = 0; i < nTerm; i++) {
        printf("------- Termino %i -------\n", (i+1));
        printf("Ingrese coeficiente del termino %i: ", (i+1));
        scanf("%i", &pol[i].a);
        printf("Ingrese la potencia del termino %i: ", (i+1));
        scanf("%i", &pol[i].pow);
    } 
    printf("----------------------------------------\n");
    return pol;
}

void imprimirPol(terP *pol, int nTerm) {
    printf("Ecuacion: ");
    fprintf(out, "Ecuacion: ");
    for (int i = nTerm - 1; i >= 0; i--) {
        if(pol[i].a < 0 && pol[i].pow > 1){
            printf(" %ix^%i", pol[i].a, pol[i].pow);
           fprintf(out, " %ix^%i", pol[i].a, pol[i].pow);
        }
        else if(pol[i].a > 0 && pol[i].pow > 1){
            printf(" +%ix^%i", pol[i].a, pol[i].pow);
            fprintf(out, " +%ix^%i", pol[i].a, pol[i].pow);
        }
        else if(pol[i].pow == 1){
            if(pol[i].a < 0){
                printf(" %ix", pol[i].a);
                fprintf(out, " %ix", pol[i].a);
            } 
            else if (pol[i].a > 0) {
                printf(" +%ix", pol[i].a);
                fprintf(out, " +%ix", pol[i].a);
            }
        }
        else if(pol[i].pow == 0){
            if(pol[i].a < 0){
                printf(" %i", pol[i].a);
                fprintf(out, " %i", pol[i].a);
            } 
            else if (pol[i].a > 0){
                printf(" +%i", pol[i].a);
                fprintf(out, " +%i", pol[i].a);
            }
        }
    }
    printf("\n\n");
    fprintf(out, "\n\n");
}
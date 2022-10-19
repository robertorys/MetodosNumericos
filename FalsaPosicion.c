/**
 * @file FalsaPosicion.c
 * @author Roberto Reyes Brito(roberto1500reyes@gmail.com)
 * @brief El maétodo de la falsa posición encuantra el punto dónde la racta secante que une
 * a (ak, f(ak)) con (bk, f(bk)) corta al eje X y después lo escoge como el nuevo punto extremo.
 * @version 0.1
 * @date 2022-10-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
 * @brief Método de la falsa posición, eregresa una raiz en un intervalo [a,b],
 *        puede regresar la solución exacta o una aproximación.
 * 
 * @param pol 
 * @param nTerm 
 * @param raiz 
 * @return int 
 */
int metodoFalsaPosicion(terP *pol, int nTerm, double raiz);

/**
 * @brief Método que evalua la ecuaion en un punto x.
 * 
 * @param pol arreglo para el polinomio.
 * @param nTerm cantidad de terminos del polinomio.
 * @param x punto a evualar la ecuación.
 * @return double regresa el valor de la ecuación en el punto x.
 */
double evaluarP(terP *pol, int nTerm, double x);

int main(void){
    out = fopen("SalidaFalsaPosicion.txt", "w");

    int nTerm;
    printf("\t---------- Metodo de la falsa posicion ----------\n\n");
    fprintf(out, "\t---------- Metodo de la falsa posicion ----------\n\n");
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

    metodoFalsaPosicion(pol, nTerm, raiz);

    fclose(out);
    return 0;
}

int metodoFalsaPosicion(terP *pol, int nTerm, double raiz) {
    double a, b;
    double eAbsoluto, eRelativo, e;
    double pi, ai, bi, fa, fb, fp;

    // pi sera el punto donde corte en x la recta secante de (ai, f(ai)) con (bi, f(bi)).

    printf("Ingresar intervalo [a,b]:\n");
    printf("Ingrese a: ");
    scanf("%lf", &a);
    printf("Ingrese b: ");
    scanf("%lf", &b);
    fprintf(out, "- Intervalo de busqueda: [%i,%i]\n", a, b);

    ai = a;
    bi = b;

    // Comprobar que a o b sean solucion.
    fa = evaluarP(pol, nTerm, a);
    fb = evaluarP(pol, nTerm, b);

    if(fa == 0) {
        printf("a = %i, es raiz para la ecuacion\n", a);
        fprintf(out, "a = %i, es raiz para la ecuacion\n", a);
        return(0);
    }
    if(fb == 0){
        printf("b = %i, es raiz para la ecuacion\n", b);
        fprintf(out, "b = %i, es raiz para la ecuacion\n", b);
        return(0);
    }

    // Comprobar que existe una raíz en el intervalo [a,b]
    // Se supone que solo deberia tener una raíz en el intervalo.
    if((fa*fb) > 0){
        printf("No exixte una raiz en el intervalo [%i,%i]", a, b);
        fprintf(out, "No exixte una raiz en el intervalo [%i,%i]", a, b);
        return(0);
    }

    // Bucle para el método de la falsa posición.
    int i = 0;
    while (true) {
        fa = evaluarP(pol, nTerm, ai); // Calcular f(ai).
        fb = evaluarP(pol, nTerm, bi); // Calcular f(bi).

        // Calcular el putno deonde la recta secante corta en el eje x.
        // x = af(b) - bf(a) / f(b) - f(a).
        pi = ((ai * fb) - (bi * fa)) / (fb - fa);

        fp = evaluarP(pol, nTerm, pi); // Calcular f(pi).

        printf("n = %i || ", i);fprintf(out, "n = %i || ", i);
        printf("a%i = %lf || ", i, ai);fprintf(out, "a%i = %lf || ", i, ai);
        printf("b%i = %lf || ", bi);fprintf(out, "b%i = %lf || ", i, bi);
        printf("[%lf,%lf] ||", ai, bi);fprintf(out, "[%lf,%lf] ||", ai, bi);
        printf("Pn = %lf || ", pi);fprintf(out, "Pn = %lf || ", pi);
        printf("f(Pn) = %lf || ", fp);fprintf(out, "f(Pn) = %lf || ", fp);
        printf("f(an) = %lf || ", fa);fprintf(out, "f(an) = %lf || ", fa);
        printf("f(bn) = %lf || ", fb);fprintf(out, "f(bn) = %lf || ", fb);
        printf("\n\n"); fprintf(out, "\n\n");

        // Determinar el error relativo para regresar una solución con cierto error relativo.
        // Error absoluto = |valor exacto - valor aproximado|
        e = raiz - pi;
        eAbsoluto = (e >= 0 ? e : -e);
        // Error relativo = error absoluto / |valor exacto|
        if(raiz != 0){
            eRelativo = eAbsoluto / (raiz > 0 ? raiz : -raiz);
        } else {
            eRelativo = eAbsoluto;
        }

        // Si f(pi) == 0, entonces pi es raíz.
        // Si el error relativo de f(pi) = eRalativo esta 10^-3 <= eRelativo < 0,
        // entonce pi es una solución aproximada.
        if(fp == 0 || pi == raiz){
            printf("La raiz es P%i = %lf\n", i, pi);
            // printf("La raiz tiene un error relativo de %lf\n", eRelativo);
            fprintf(out, "La raiz es P%i = %lf\n", i, pi);
            fprintf(out, "La raiz tiene un error relativo de %lf\n", eRelativo);
            return 0;
        }

        if(eRelativo < 0,001){
            printf("La raiz es P%i = %lf\n", i, pi);
            printf("La raiz tiene un error relativo de %lf\n", eRelativo);
            fprintf(out, "La raiz es P%i = %lf\n", i, pi);
            fprintf(out, "La raiz tiene un error relativo de %lf\n", eRelativo);
            return 0;
        }

        // Si f(pi)f(ai) > 0, entonces f(ai) y f(pi) tienen el mismo signo
        // y no exixte una raíz en (a, f(p)).
        if((fp*fa) > 0) {
            ai = pi;
        }
        // Si f(pi)f(ai) < 0, entonces f(ai) y f(pi) tienen diferente signo
        // por lo tanto exixte una raíz en (a, f(p)).
        else if((fa*fp) < 0) {
            bi = pi;
        }
        i++;
    }
}

double evaluarP(terP *pol, int nTerm, double x) {
    double r = 0;
    for (int i = nTerm - 1; i >= 0; i--) {
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
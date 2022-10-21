/**
 * @file MetodoNewtonRapson.c
 * @author Roberto Reyes Brito (roberto1500reyes@gmail.com)
 * @brief El método de Newton Rapson necesita que f:[a,b] -> R sea derivable, para encontrar una raíz.
 * En un punto dado (X0, f(X0)) en la gráfica de f, hay una tangente análiticametne,
 * esto significa que la función lineal l(x)=f'(X0)(x-X0)+f(X0) está cerca de la función dada f cecerca de X0, 
 * las dos funciones l y f coinciden. Tomamos el cedo de f como una aproximación del caero de l. 
 * El cero de l esta dado por x = x0 - (f(x0) / f'(x0))
 * Empezando con el punto x0 tal que podemos interpretar como una aproximación a la raíz buscasa, 
 * obtenemos a x1 de x = x0 - (f(x0) / f'(x0)), asi sucesivamente teniendo que:
 * Xk+1 = Xk - (f(Xk) / f'(Xk)).
 * Funciona con ecuaciones en forma de polinomio.     
 * @version 1
 * @date 2022-10-19
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
 * @brief Función que regresa la derivada del polinomio.
 * 
 * @param nTerm cantidad de terminos del polinomio.
 * @return terP* arreglo que guarda los coeficientes del polinomio, ya derivado.
 */
terP *derivada(terP *p,int nTerm);

/**
 * @brief Imprime en la consola el polinimio y lo guarda en un archivo txt.
 * 
 * @param pol 
 * @param nTerm 
 */
void imprimirPol(terP *pol, int nTerm);

/**
 * @brief Método de Newton Rapson, dado un punto se obtiene su recta tangente y 
 * se obtiene un nuevo punto que es el punto donde la recta tangente corta al eje x.
 * 
 * @param pol Arreglo que guarda los términos del polinomio.
 * @param nTerm Cantidad de términos del polinomio.
 * @param raiz Raiz para determinar el error de la solución y para el algortimo.
 * @return int 
 */
int metodoNewtonRapson(terP *pol, int nTerm, double raiz);

/**
 * @brief Función que evalua la ecuaion en un punto x.
 * 
 * @param pol Arreglo que guarda los términos del polinomio.
 * @param nTerm Cantidad de terminos del polinomio.
 * @param x Punto a evualar la ecuación.
 * @return double regresa el valor de la ecuación en el punto x.
 */
double evaluarP(terP *pol, int nTerm, double x);

int main(void){
    srand(time(NULL));
    out = fopen("SalidaNewtonRapson.txt", "w");

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

    metodoNewtonRapson(pol, nTerm, raiz);

    fclose(out);
    return 0;
}

int metodoNewtonRapson(terP *pol, int nTerm, double raiz){
    int a, b, ai, bi;
    double eAbsoluto, eRelativo, e;
    double fx, fdx, fa, fb;
    double Xk;

    // Obtener la derivada del polinomio.
    terP *df = derivada(pol, nTerm);
    printf("\nDerivada del polinomio:\n");
    fprintf(out, "\nDerivada del polinomio:\n");
    imprimirPol(df, nTerm);

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

    // Obtener un x aleatorio dentro del intervalo [a,b].
    Xk = (int)ai + (rand() % (((int)bi - (int)ai) + 1));
    
    int i = 0;
    // Bucle para el método de Newton Rapson
    while (true) {
        fx = evaluarP(pol, nTerm, Xk);
        fdx = evaluarP(df, nTerm, Xk);

        printf("n = %i || ", i); fprintf(out, "n = %i || ", i);
        printf("Xn = %lf || ", Xk); fprintf(out, "Xn = %lf || ", Xk);
        printf("f(Xn) = %lf || ", fx); fprintf(out, "f(Xn) = %lf || ", fx);
        printf("f'(Xn) = %lf\n", fdx); fprintf(out, "f'(Xn) = %lf\n", fdx);

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
        if(eRelativo < 0.001 || fx == 0){
            printf("La raiz es P%i = %lf\n", i, Xk);
            printf("La raiz tiene un error relativo de %lf\n", eRelativo);
            fprintf(out, "La raiz es P%i = %lf\n", i, Xk);
            fprintf(out, "La raiz tiene un error relativo de %lf\n", eRelativo);
            return Xk;
        }
        // Xk+1 = Xk - (f(Xk) / f'(Xk))
        Xk = Xk - (fx / fdx);
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

terP *derivada(terP *pol, int nTerm) {
    terP *d = malloc(nTerm * sizeof(terP));
    for(int i = 0; i < nTerm; i++) {
        if(pol[i].pow == 0) {
            d[i].pow = 0;
            d[i].a = 0;
        } else {
            d[i].a = pol[i].pow * pol[i].a;
            d[i].pow = pol[i].pow - 1;
        }
    }
    return d;
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
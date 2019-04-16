#include <stdio.h>
#include <stdlib.h>
#include "memoria.c"
#include "pila.c"

int main(){

    int res=inicializarMemoria(15);
    printf("Memoria consistente: %i\n",consistente2());

    void *r1=asignar(14);
    printf("Memoria consistente: %i\n",consistente2());

    void *r2=asignar(1);
    printf("Memoria consistente: %i\n",consistente2());

    liberar(r2);
    printf("Memoria consistente: %i\n",consistente2());

    liberar(r1);
    printf("Memoria consistente: %i\n",consistente2());

    void *r3=asignar(14);
    printf("Memoria consistente: %i\n",consistente2());

    void *r4=asignar(2);
    printf("Memoria consistente: %i\n",consistente2());

    liberar(r3);
    printf("Memoria consistente: %i\n",consistente2());
/*
    tPila *P=crearPila();
    int ap1=apilar(1,&P);
    int ap2=apilar(2,&P);
    int ap3=apilar(3,&P);

    printf("%i ",tope(P));
    printf("%i\n",desapilar(&P));

    printf("%i ",tope(P));
    printf("%i\n",desapilar(&P));

    printf("%i ",tope(P));
    printf("%i\n",desapilar(&P));

    printf("%i ",tope(P));
    printf("%i\n",pilaVacia(P));*/

    return 0;
}

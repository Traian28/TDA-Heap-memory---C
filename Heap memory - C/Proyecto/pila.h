#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

typedef struct Pila {
    int elem;
    struct Pila *next;
    }tPila;

tPila* crearPila();
int tope(tPila *P);
int apilar(int a, tPila **P);
int desapilar(tPila **P);
int pilaVacia(tPila *P);

#endif // PILA_H_INCLUDED

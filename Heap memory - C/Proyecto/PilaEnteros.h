#ifndef PILAENTEROS_H_INCLUDED
#define PILAENTEROS_H_INCLUDED


typedef struct PilaEnteros{
    tNodo *tope;
    int cantidad;
}tPila;


tPila* crearPila();
int tope(tPila *P);
int apilar(int a, tPila **P);
int desapilar(tPila **P);
int pilaVacia(tPila *P);

#endif // PILAENTEROS_H_INCLUDED

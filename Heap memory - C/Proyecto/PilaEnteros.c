#include "Pila.h"

tPila* crearPila(){
    int i=inicializarMemoria(64);
    tPila *p=(tPila*)asignar(sizeof(tPila));
    p->tope=NULL;
    p->cantidad=0;
    return p;
}
int apilar(int a, tPila **P){
    tNodo* n=(tNodo*)asignar(sizeof(tNodo));
    if(n!=NULL){
        n->sig=*P->tope;
        n->elem=a;
        *P->tope=n;
        *P->cantidad=p->cantidad+1;
        return 0;}
    return 1;
}
int desapilar(tPila **P){
    int elem=*P->tope->elem;
    tNodo *aux=*P->tope;
    *P->tope=*P->tope->sig;
    *P->cantidad=*P->cantidad-1;
    liberar(aux);
    return elem;
}
int tope(tPila *P){
    int elem=P->tope->elem;
    return elem;
}
int pilaVacia(tPila *P){
    if(p->cantidad==0)
        return 1;
    else
        return 0;
}

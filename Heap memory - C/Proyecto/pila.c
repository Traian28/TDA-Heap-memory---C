#include "Pila.h"

tPila* crearPila(){
    int mem=inicializarMemoria(64);//SE INICIALIZA LA MEMORIA
    tPila *p=(tPila*)asignar(sizeof(tPila));//SE CREA LA PILA VACIA
    if(p!=NULL){//SE CREO LA PILA EXITOSAMENTE
        p->elem=NULL;p->next=NULL;}
    return p;//SE DEVUELVE EL PUNTERO A LA PILA
}

int tope(tPila *P){
    return P->elem;//SE RETORNA EL ELEMENTO DEL TOPE
}

int desapilar(tPila **P){
    int elem=(*P)->elem;//ELEMENTO EN EL TOPE DE LA PILA
    tPila *elim=*P;//PILA A ELIMINAR
    *P=(*P)->next;//SE ACTUALIZA EL TOPE DE LA PILA
    liberar(elim);//SE LIBERA EL ESPACIO DE MEMORIA
    return elem;
}

int apilar(int a,tPila **P){
    tPila *nueva=(tPila*)asignar(sizeof(tPila));//SE RESERVA EL ESPACIO EN MEMORIA NECESARIO
    if(nueva!=NULL){//HAY ESPACIO DE MEMORIA SUFICIENTE
        nueva->elem=a;nueva->next=*P;
        *P=nueva;
        return 0;}//CREACION EXITOSA
    return 1;//LA INSERCION NO FUE EXITOSA
}

int pilaVacia(tPila *P){
    if(P->elem==NULL)
        return 1;//PILA VACIA
    else return 0;//PILA NO VACIA
}

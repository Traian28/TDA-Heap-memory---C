#include "lista.h"

tLista crearLista(){
    tLista lista={NULL,NULL,0};
    return lista;
}

void insertarAtras(tLista *L,tNodo *pos,tElemento x){
    tNodo *n=(tNodo*)malloc(sizeof(tNodo));
    n->elem=x;n->next=pos->next;
    pos->next=n;
    L->size=L->size+1;
    if(pos==L->tail)
        L->tail=n;
}

void insertarPpio(tLista *L,tElemento x){
    tNodo *n=(tNodo*)malloc(sizeof(tNodo));
    n->elem=x;n->next=L->header;
    L->header=n;
    L->size=L->size+1;
    if(L->size==1)
        L->tail=n;
}

tNodo* siguiente(tNodo *pos){
    if(pos==NULL)
        return NULL;
    else return pos->next;
}

tNodo* primera(tLista L){
    return L.header;
}

tNodo* ultima(tLista L){
    return L.tail;
}

void eliminar(tLista *L,tNodo *pos){
    if(L->size>0){
        if(L->header==pos)
            L->header=pos->next;
        else{tNodo *aux=L->header;
             while(aux->next!=pos)
                aux=aux->next;
             aux->next=pos->next;
             if(pos==L->tail)
                L->tail=aux;}
        L->size=L->size-1;
        if(L->size==0)
            L->tail=NULL;
        free(pos);}
}

tElemento* elemento(tNodo* pos){
    return &(pos->elem);
}

int listaVacia(tLista L){
    if(L.size==0)
        return 0;
    else return 1;
}

#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct Elemento{
    int a;
    int b;
    }tElemento;

typedef struct Nodo{
    tElemento elem;
    struct Nodo *next;
    }tNodo;

typedef struct Lista{
    tNodo *header;
    tNodo *tail;
    int size;
    }tLista;

tLista crearLista();
void insertarAtras(tLista *L,tNodo *pos,tElemento x);
void insertarPpio(tLista *L,tElemento x);
tNodo* siguiente(tNodo *pos);
tNodo *primera(tLista L);
tNodo *ultima(tLista L);
void eliminar(tLista *L,tNodo *pos);
tElemento* elemento(tNodo *pos);
int listaVacia(tLista L);


#endif // LISTA_H_INCLUDED

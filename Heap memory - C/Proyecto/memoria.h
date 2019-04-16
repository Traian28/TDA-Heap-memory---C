#ifndef MEMORIA_H_INCLUDED
#define MEMORIA_H_INCLUDED
#include "lista.c"




int inicializarMemoria(int max);
void* asignar(int cant);
void liberar(void *bloque);
int consistente();


#endif // MEMORIA_H_INCLUDED

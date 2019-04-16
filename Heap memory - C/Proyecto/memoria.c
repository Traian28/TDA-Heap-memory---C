#include <stdio.h>
#include <math.h>
#include "memoria.h"

typedef enum booleano{
    falso=0,verdadero=1
    }tBooleano;


char *mem;
tLista libres;
tLista ocupados;
unsigned char *mapa;
 int tamMemoria;

void actualizarMapaBits(int posEnMemoria,int tam){
    int i;unsigned char nroBit;
    for(i=0;i<tam;i++){
        nroBit=pow(2,posEnMemoria%8);//NUMERO PARA "TOOGLEAR" EL BIT CORRESPONDIENTE
        *(mapa+(posEnMemoria/8))=*(mapa+(posEnMemoria/8))^nroBit;//"TOOGLE" AL BIT
        posEnMemoria++;}
}

void ubicar(tLista *lista,tElemento x){
    if(listaVacia(*lista)==0)//LA LISTA ESTA VACIA, ENTONCES SE INSERTAR AL PRINCIPIO
        insertarPpio(lista,x);
    else if(x.a<(elemento(primera(*lista))->a))//SE DEBE INSERTAR AL PRINCIPIO DE LA LISTA
            insertarPpio(lista,x);
         else{tNodo *actual=primera(*lista);tBooleano seguir=verdadero;
              while((actual!=ultima(*lista))&&(seguir==verdadero))
                if(elemento(siguiente(actual))->a<x.a)//SI EL PUNTERO DEL SIGUIENTE AL ACTUAL ES MENOR QUE EL PUNTERO DEL BLOQUE A UBICAR
                    actual=siguiente(actual);
                else{insertarAtras(lista,actual,x);seguir=falso;}//SI NO ES MENOR, LO INSERTO ANTES DEL SIGUIENTE AL ACTUAL
              if(seguir==verdadero){//SE DEBE INSERTAR AL FINAL
                 insertarAtras(lista,actual,x);seguir=falso;}}
}

void fusion(){
    tNodo *actual=primera(libres);
    while(actual!=ultima(libres))
        if((elemento(actual)->a+elemento(actual)->b)==elemento(siguiente(actual))->a){//SON DOS BLOQUES LIBRES CONSECUTIVOS
            elemento(actual)->b=elemento(actual)->b+elemento(siguiente(actual))->b;//SE FUSIONAN LOS BLOQUES EN UNO SOLO
            eliminar(&libres,siguiente(actual));}//SE ELIMINA EL BLOQUE INNCESESARIO
        else actual=siguiente(actual);
}

int inicializarMemoria(int max){
    if(mem!=NULL)
        return 2;//MEMORIA YA INICIALIZADA
    else{ int tam=8*(max/8);
         if(max%8>0)//CALCULO EL TAMAÑO DE LA MEMORIA
            tam+=8;
         mem=(char*)malloc(sizeof(char)*tam);//CREO LA MEMORIA
         if(mem!=NULL){//SI HAY SUFICIENTE ESPACIO DE MEMORIA
            tamMemoria=tam;//ALMACENA EL TAMAÑO DE LA MEMORIA
            libres=crearLista();//SE CREA LA LISTA DE LIBRES
            ocupados=crearLista();//SE CREA LA LISTA DE OCUPADOS
            tElemento e1={(int)mem,tam};//SE CREA EL BLOQUE LIBRE
            insertarPpio(&libres,e1);//SE AGREGA EL BLOQUE LIBRE A LA LISTA DE BLOQUES LIBRES
            mapa=(char*)malloc(sizeof(char)*(tam/8));//SE CREA EL MAPA DE BITS
            int i;
            for(i=0;i<tam/8;i++)//INICIALIZACION DEL MAPA DE BITS
                *(mapa+i)=0;
            return 0;}//CREACION EXITOSA
         else return 1;}//NO HAY SUFICIENTE MEMEMORIA
    return 3;//OTRO ERROR
}

void* asignar(int cant){
    tNodo *actual=primera(libres);
    if(actual!=NULL){//HAY BLOQUES LIBRES DE MEMORIA
        tBooleano encontre=falso;
        while((actual!=NULL)&&(encontre==falso))
            if(elemento(actual)->b>=cant)//EXISTE UN BLOQUE LIBRE CON EL TAMAÑO SUFICIENTE
                encontre=verdadero;
            else actual=siguiente(actual);//SINO SE SIGUE BUSCANDO
        if(encontre==verdadero){//SE ENCONTRO UN BLOQUE LIBRE CON EL TAMAÑO SUFICIENTE
            tElemento x={elemento(actual)->a,cant};//REPRESENTA EL NUEVO BLOQUE OCUPADO
            if(cant==elemento(actual)->b)//EL BLOQUE LIBRE TIENE EXACTAMENTE EL TAMAÑO SOLICITADO
                eliminar(&libres,actual);//SE ELIMINA EL BLOQUE DE LA LISTA DE LIBRES
            else{elemento(actual)->a=elemento(actual)->a+cant;//SE REAJUSTA EL INICIO DEL BLOQUE LIBRE
                 elemento(actual)->b=elemento(actual)->b-cant;}//SE REAJUSTA EL TAMAÑO DEL BLOQUE LIBRE
            ubicar(&ocupados,x);//SE INSERTA EL BLOQUE EN LA LISTA DE BLOQUES OCUPADOS DE MANERA ORDENADA
            actualizarMapaBits(x.a-(int)mem,x.b);//SE ACTUALIZA EL MAPA DE BITS
            return (void*)x.a;}}//SE RETORNA EL PUNTERO AL PRIMER BYTE
    return NULL;//NO HAY BLOQUES LIBRES O NO SE ENCONTRO UN BLOQUE LIBRE CON EL TAMAÑO NECESARIO
}

void liberar(void *bloque){
    tNodo *actual=primera(ocupados);tBooleano encontre=falso;
    while((actual!=NULL)&&(encontre==falso))
        if(elemento(actual)->a==(int)bloque)//ES EL BLOQUE OCUPADO A ELIMINAR
            encontre=verdadero;
        else actual=siguiente(actual);//SINO SE SIGUE BUSCANDO
    tElemento x={elemento(actual)->a,elemento(actual)->b};//REPRESENTA EL NUEVO BLOQUE LIBRE
    eliminar(&ocupados,actual);//SE ELIMINA EL BLOQUE OCUPADO DE LA LISTA DE BLOQUES OCUPADOS
    ubicar(&libres,x);//SE INSERTA EL BLOQUE EN LA LISTA DE BLOQUES LIBRES DE MANERA ORDENADA
    actualizarMapaBits(x.a-(int)mem,x.b);//SE ACTUALIZA EL MAPA DE BITS
    fusion();//UNION DE LOS BLOQUES LIBRES CONSECUTIVOS, SI EXISTEN
}

int consistente2(){
    tNodo *actualLibres=primera(libres);tNodo *actualOcupados=primera(ocupados);//PRIMER BLOQUE DE CADA LISTA
    int pos=0;int aux;tBooleano iguales=verdadero;unsigned char bit;
    while((actualLibres!=NULL)&&(actualOcupados!=NULL)&&(iguales==verdadero))//MIENTRAS NO SE TERMINE NINGUNA DE LAS LISTAS Y LA MEMORIA SEA CONSISTENTE
        if(elemento(actualLibres)->a<elemento(actualOcupados)->a){//EL PUNTERO DEL BLOQUE LIBRE ES MENOR QUE EL PUNTERO DEL BLOQUE OCUPADO
            aux=0;
            while((aux<elemento(actualLibres)->b)&&(iguales==verdadero)){
                bit=pow(2,pos%8);//REPRESENTA AL BIT QUE DEBE ESTAR DESACTIVADO
                if((*(mapa+(pos/8))&bit)==bit)
                    iguales=falso;//INDICA QUE EL BLOQUE ESTA OCUPADO Y NO LIBRE
                else{pos++;aux++;}}//EL MAPA DE BITS INDICA CORRECTAMENTE QUE EL BLOQUE ESTA LIBRE
            if(iguales==verdadero)
                actualLibres=siguiente(actualLibres);}////SI LA MEMORIA ES CONSISTENTE CON EL BLOQUE LIBRE ANALIZADO, AVANZO AL SIGIUENTE BLOQUE EN LA LISTA DE BLOQUES LIBRES
        else{//EL PUNTERO DEL BLOQUE OCUPADO ES MENOR QUE EL PUNTERO DEL BLOQUE LIBRE
             aux=0;
             while((aux<elemento(actualOcupados)->b)&&(iguales==verdadero)){
                 bit=pow(2,pos%8);//REPRESENTA AL BIT QUE DEBE ESTAR ACTIVADO
                 if((*(mapa+(pos/8))&bit)==bit){
                    pos++;aux++;}//EL MAPA DE BITS INDICA CORRECTAMENTE QUE EL BLOQUE ESTA OCUPADO
                 else iguales=falso;}//INDICA QUE EL BLOQUE ESTA LIBRE Y NO OCUPADO
             if(iguales==verdadero)
                actualOcupados=siguiente(actualOcupados);}//SI LA MEMORIA ES CONSISTENTE CON EL BLOQUE OCUPADO ANALIZADO, AVANZO AL SIGUIENTE BLOQUE EN LA LISSTA DE BLOQUES OCUPADOS
    if((actualLibres!=NULL)&&(iguales==verdadero)){//QUEDAN BLOQUES PARA ANALIZAR EN LA LISTA DE BLOQUES LIBRES
        while((actualLibres!=NULL)&&(iguales==verdadero)){//MIENTRAS NO SE ACABE LA LISTA Y LA MEMORIA SEA CONSISTENTE
            aux=0;
            while((aux<elemento(actualLibres)->b)&&(iguales==verdadero)){
                 bit=pow(2,pos%8);//REPRESENTA AL BIT QUE DEBE ESTAR DESACTIVADO
                if((*(mapa+(pos/8))&bit)==bit)
                    iguales=falso;//INDICA QUE EL BLOQUE ESTA OCUPADO Y NO LIBRE
                else{pos++;aux++;}}//EL MAPA DE BITS INDICA CORRECTAMENTE QUE EL BLOQUE ESTA LIBRE
            if(iguales==verdadero)
                actualLibres=siguiente(actualLibres);}}//SI LA MEMORIA ES CONSISTENTE CON EL BLOQUE LIBRE ANALIZADO, AVANZO AL SIGIUENTE BLOQUE EN LA LISTA DE BLOQUES LIBRES
    else if((actualOcupados!=NULL)&&(iguales==verdadero)){//QUEDAN BLOQUES PARA ANALIZAR EN LA LISTA DE BLOQUES OCUPADOS
            while((actualOcupados!=NULL)&&(iguales==verdadero)){//MIENTRAS NO SE ACABE LA LISTA Y LA MEMORIA SEA CONSISTENTE
                aux=0;
                while((aux<elemento(actualOcupados)->b)&&(iguales==verdadero)){
                    bit=pow(2,pos%8);//REPRESENTA AL BIT QUE DEBE ESTAR ACTIVADO
                    if((*(mapa+(pos/8))&bit)==bit){
                        pos++;aux++;}//EL MAPA DE BITS INDICA CORRECTAMENTE QUE EL BLOQUE ESTA OCUPADO
                    else iguales=falso;}//INDICA QUE EL BLOQUE ESTA LIBRE Y NO OCUPADO
                if(iguales==verdadero)
                    actualOcupados=siguiente(actualOcupados);}}//SI LA MEMORIA ES CONSISTENTE CON EL BLOQUE OCUPADO ANALIZADO, AVANZO AL SIGUIENTE BLOQUE EN LA LISSTA DE BLOQUES OCUPADOS
    if(iguales==verdadero)
        return 1;//LA MEMORIA ES CONSISTENTE
    else return 0;//LA MEMORIA NO ES CONSISTENTE
}

int consistente(){
    tNodo *actualLibres=primera(libres);tNodo *actualOcupados=primera(ocupados);
    int pos=0;int aux;tBooleano iguales=verdadero;
    while((actualLibres!=NULL)&&(actualOcupados!=NULL)&&(iguales==verdadero))
        if(elemento(actualLibres)->a<elemento(actualOcupados)->a){//EL BLOQUE LIBRE ESTA ANTES
            aux=0;
            while((aux<elemento(actualLibres)->b)&&(iguales==verdadero)){
                if((*(mapa+(pos/8))&1)==1)
                    iguales=falso;//INDICA QUE EL BLOQUE ESTA OCUPADO Y NO LIBRE
                else{*(mapa+(pos/8))=(*(mapa+(pos/8))>>1);
                     pos++;aux++;}}//EL MAPA DE BITS INDICA QUE EL BLOQUE ESTA LIBRE
            if(iguales==verdadero)
                actualLibres=siguiente(actualLibres);}//AVANZO AL SIGIUENTE BLOQUE EN LA LISTA DE BLOQUES LIBRES
        else{//EL BLOQUE OCUPADO ESTA ANTES
             aux=0;
             while((aux<elemento(actualOcupados)->b)&&(iguales==verdadero)){
                 if((*(mapa+(pos/8))&1)==1){
                    *(mapa+(pos/8))=(*(mapa+(pos/8))>>1);
                    *(mapa+(pos/8))=(*(mapa+(pos/8)))|128;//EL MAPA DE BITS INDICA QUE EL BLOQUE ESTA OCUPADO
                    pos++;aux++;}
                 else iguales=falso;}//INDICA QUE EL BLOQUE ESTA LIBRE Y NO OCUPADO
             if(iguales==verdadero)
                actualOcupados=siguiente(actualOcupados);}//AVANZO AL SIGUIENTE BLOQUE EN LA LISSTA DE BLOQUES OCUPADOS
    if((actualLibres!=NULL)&&(iguales==verdadero)){//QUEDAN BLOQUES POR ANALIZAR EN LA LISTA DE BLOQUES LIBRES
        while((actualLibres!=NULL)&&(iguales==verdadero)){
            aux=0;
            while((aux<elemento(actualLibres)->b)&&(iguales==verdadero)){
                if((*(mapa+(pos/8))&1)==1)
                    iguales=falso;//INDICA QUE EL BLOQUE ESTA OCUPADO Y NO LIBRE
                else{*(mapa+(pos/8))=*(mapa+(pos/8))>>1;//EL MAPA DE BITS INDICA QUE EL BLOQUE ESTA LIBRE
                     pos++;aux++;}}
            if(iguales==verdadero)
                actualLibres=siguiente(actualLibres);}}//AVANZO AL SIGIUENTE BLOQUE EN LA LISTA DE BLOQUES LIBRES
    else if((actualOcupados!=NULL)&&(iguales==verdadero)){//QUEDAN BLOQUES POR ANALIZAR EN LA LISTA DE BLOQUES OCUPADOS
            while((actualOcupados!=NULL)&&(iguales==verdadero)){
                aux=0;
                while((aux<elemento(actualOcupados)->b)&&(iguales==verdadero)){
                    if((*(mapa+(pos/8))&1)==1){
                        *(mapa+(pos/8))=(*(mapa+(pos/8)))>>1;
                        *(mapa+(pos/8))=(*(mapa+(pos/8)))|128;//EL MAPA DE BITS INDICA QUE EL BLOQUE ESTA OCUPADO
                        pos++;aux++;}
                    else iguales=falso;}//INDICA QUE EL BLOQUE ESTA LIBRE Y NO OCUPADO
                if(iguales==verdadero)
                    actualOcupados=siguiente(actualOcupados);}}//AVANZO AL SIGUIENTE BLOQUE EN LA LISSTA DE BLOQUES OCUPADOS
    if(iguales==verdadero)
        return 1;
    else return 0;
}



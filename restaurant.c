#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include "restaurant.h"
#include "complemento.h"
const char MESA='T';
const char COCINA='C';
const char LINGUINI='L';
// const char MOPA='O';
// const char MONEDA='M';


const char VACIO=' ';

void reemplazar_elemento(char terreno[MAX_FILAS][MAX_COLUMNAS],char elemento, coordenada_t posicion){
    terreno[posicion.fil][posicion.col]=elemento;
}

bool coordenada_ocupada(juego_t juego, coordenada_t* posicion){
    // Comprobar si alguna mesa está en esa posición
    bool no_esta_ocupada=true;
    for (int i = 0; i < juego.cantidad_mesas; i++){
        for (int j = 0; j < juego.mesas[i].cantidad_comensales; j++){
            if (juego.mesas[i].posicion[j].fil==posicion->fil && juego.mesas[i].posicion[j].col==posicion->col) {
                no_esta_ocupada=false;  // Posición ocupada por una mesa
            }
        }
    }
    if (&juego.cocina.posicion==posicion){
        if ((posicion->fil==juego.cocina.posicion.fil) && (posicion->col==juego.cocina.posicion.col))
            no_esta_ocupada=false;
    }
    if (&juego.mozo.posicion==posicion){
        if ((posicion->fil==juego.mozo.posicion.fil) && (posicion->col==juego.mozo.posicion.col))
            no_esta_ocupada=false;
        
    }
    if (&juego.herramientas[0].posicion==posicion){
        if ((posicion->fil==juego.herramientas->posicion.fil) && (posicion->col==juego.herramientas->posicion.col))
            no_esta_ocupada=false;
    }
    int lugar_moneda = PRIMER_LUGAR_MONEDAS;
    while((no_esta_ocupada==true) && (lugar_moneda<=CANTIDAD_MONEDAS)){
        if (&juego.herramientas[lugar_moneda].posicion==posicion){
            coordenada_t posicion_herramienta=juego.herramientas[lugar_moneda].posicion;
            if ((posicion->fil==posicion_herramienta.fil) && (posicion->col==posicion_herramienta.col))
            no_esta_ocupada=false;
        }lugar_moneda++;   
    }
    int lugar_patin = PRIMER_LUGAR_PATINES;
    while ((no_esta_ocupada==true) && (lugar_patin<=juego.cantidad_herramientas)){
        if (&juego.herramientas[lugar_patin].posicion==posicion){
            coordenada_t posicion_herramienta=juego.herramientas[lugar_patin].posicion;
            if ((posicion->fil==posicion_herramienta.fil) && (posicion->col==posicion_herramienta.col))
                no_esta_ocupada=false;
        }lugar_patin++;
    }
    

    
    

    // Aquí también podrías verificar otros elementos (mopa, monedas, charcos, etc.)
    // Si tienes más objetos, repite el mismo tipo de comprobación

    return no_esta_ocupada;  // Si no está ocupada, la posición es válida
}



bool validar_espacio_alrededor_de_mesas(juego_t juego, mesa_t nueva_mesa, int numero_de_mesas) {
    bool mesas_cerca=true;
    for (int mesa_anterior = 0; mesa_anterior < numero_de_mesas; mesa_anterior++) {
        mesa_t mesa = juego.mesas[mesa_anterior];
        for (int i = 0; i < mesa.cantidad_comensales; i++) {
            int fil = mesa.posicion[i].fil;
            int col = mesa.posicion[i].col;
            for (int j = 0; j < nueva_mesa.cantidad_comensales; j++) {
                int nueva_fil = nueva_mesa.posicion[j].fil;
                int nueva_col = nueva_mesa.posicion[j].col;
                if ((abs(fil - nueva_fil) <= 1) && (abs(col - nueva_col) <= 1)) {
                    mesas_cerca=false;
                }
            }
        }
    }return mesas_cerca;
}
void modificar_posicion(coordenada_t posicion_reemplazante, coordenada_t* posicion_original){
    posicion_original->fil=posicion_reemplazante.fil;
    posicion_original->col=posicion_reemplazante.col;
}

bool chequeo_coordenada_valida(coordenada_t posicion){
    bool posicion_valida=false;
    if ((posicion.fil>=0 && posicion.fil<MAX_FILAS) && (posicion.col>=0 && posicion.col<MAX_COLUMNAS)){
        posicion_valida=true;
    }return posicion_valida;
}

bool validar_coordenada_mesa(mesa_t mesa){
    bool es_valido=true;
    if(mesa.cantidad_comensales==MIN_COMENSALES){
        if ((mesa.posicion->fil<0 || mesa.posicion->fil>=MAX_FILAS) || (mesa.posicion->col<0 || mesa.posicion->col>=MAX_COLUMNAS))
            es_valido=false;
    }
    else{
        for(int i=0; i<MAX_COMENSALES; i++)
            if ((mesa.posicion[i].fil<0 || mesa.posicion[i].fil>=MAX_FILAS) || (mesa.posicion[i].col<0 || mesa.posicion[i].col>=MAX_COLUMNAS))
                es_valido=false;
    }
    return es_valido;
}

void inicializar_juego(juego_t *juego){
    juego->herramientas->tipo=MOPA;
    
}
void mostrar_juego(juego_t juego){
    char terreno[MAX_FILAS][MAX_COLUMNAS];
    for (int i = 0; i < MAX_FILAS; i++){
        for (int j = 0; j < MAX_COLUMNAS; j++){
            terreno[i][j]=VACIO;
        }   
    }

    int tope_comensales=10;
    for(int i=0; i < tope_comensales; i++)
        if (juego.mesas[i].cantidad_comensales<=MIN_COMENSALES){
            reemplazar_elemento(terreno, MESA, juego.mesas[i].posicion[0]);
        }else if (juego.mesas[i].cantidad_comensales>=MAX_COMENSALES){
            for (int j = 0; j < MAX_COMENSALES; j++){
                reemplazar_elemento(terreno, MESA, juego.mesas[i].posicion[j]);
            }
        }
    terreno[juego.cocina.posicion.fil][juego.cocina.posicion.col]=COCINA;
    terreno[juego.mozo.posicion.fil][juego.mozo.posicion.col]=LINGUINI;
    terreno[juego.herramientas[0].posicion.fil][juego.herramientas[0].posicion.col]=MOPA;
    for (int moneda = 1; moneda <= CANTIDAD_MONEDAS; moneda++){
        coordenada_t posicion_moneda=juego.herramientas[moneda].posicion;
        terreno[posicion_moneda.fil][posicion_moneda.col]=juego.herramientas[moneda].tipo;
    }
    for (int patin = PRIMER_LUGAR_PATINES; patin < juego.cantidad_herramientas; patin++){
        coordenada_t posicion_patin=juego.herramientas[patin].posicion;
        terreno[posicion_patin.fil][posicion_patin.col]=juego.herramientas[patin].tipo;
    }
    
    for (int fila = 0; fila < MAX_FILAS; fila++){
        for (int columna = 0; columna < MAX_COLUMNAS; columna++){
            printf("|");
            printf(" %c ", terreno[fila][columna]);
            if (columna==(MAX_COLUMNAS-1))
                printf("|\n");
        }
    }

}
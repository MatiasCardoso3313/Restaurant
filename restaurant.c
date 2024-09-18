#include<stdio.h>
#include<stdbool.h>
#include "restaurant.h"

const int MIN_COMENSALES=1;
const int AREA_MESA_INDIVIDUAL=3;
const int AREA_MESA_PARA_CUATRO=4;
const char MESA='T';
const char VACIO=' ';

void reemplazar_elemento(char terreno[MAX_FILAS][MAX_COLUMNAS],char elemento, coordenada_t* posicion){
    terreno[posicion->fil][posicion->col]=elemento;
}
bool validar_coordenada_mesa(mesa_t mesa){
    bool es_valido=true;
    if(mesa.cantidad_comensales==1){
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
void modificar_posicion(coordenada_t* posicion_remplazante, coordenada_t* posicion_original){
    posicion_original->fil=posicion_remplazante->fil;
    posicion_original->col=posicion_remplazante->col;
}
bool puede_colocarse_mesa(char terreno[MAX_FILAS][MAX_COLUMNAS], mesa_t mesa){
    bool validacion=true;
    if (mesa.cantidad_comensales==MIN_COMENSALES){
        for (int i = -1; i < AREA_MESA_INDIVIDUAL; i++){
            for (int j = -1; j < AREA_MESA_INDIVIDUAL; j++){
                if ((terreno[mesa.posicion[0].fil + i][mesa.posicion[0].col + j]== MESA) || (terreno[mesa.posicion[0].fil][mesa.posicion[0].col]!=VACIO))
                    validacion=false;
            }
        }
    }if (mesa.cantidad_comensales==MAX_COMENSALES){
        int lugar_mesa_fil=0;
        int lugar_mesa_col=0;
        for (int i = -1; i < AREA_MESA_PARA_CUATRO; i++){
            for (int j = -1; i < AREA_MESA_PARA_CUATRO; i++){
                if (terreno[mesa.posicion[lugar_mesa_fil].fil + i][mesa.posicion[lugar_mesa_fil].col + j]==MESA)
                    validacion=false;
                else if ((lugar_mesa_fil<AREA_MESA_PARA_CUATRO && lugar_mesa_col<AREA_MESA_PARA_CUATRO) && 
                terreno[mesa.posicion[lugar_mesa_fil].fil][mesa.posicion[lugar_mesa_col].col]!=VACIO)
                    validacion=false;
                lugar_mesa_col++;
            }
            lugar_mesa_fil++;
            lugar_mesa_col=0;  
        }
    }return validacion;
}

void inicializar_juego(juego_t *juego){

}
void mostrar_juego(juego_t juego){
    char terreno[MAX_FILAS][MAX_COLUMNAS];
    for (int i = 0; i < MAX_FILAS; i++){
        for (int j = 0; j < MAX_COLUMNAS; j++){
            terreno[i][j]=VACIO;
        }   
    }
    int tope_comensales=10;
    for(int i; i < tope_comensales; i++)
        reemplazar_elemento(terreno, MESA, juego.mesas[i].posicion);
    for (int fila = 0; fila < MAX_FILAS; fila++){
        for (int columna = 0; columna < MAX_COLUMNAS; columna++){
            printf("| %c |", terreno[fila][columna]);
        }
    }
}
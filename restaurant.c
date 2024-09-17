#include<stdio.h>
#include<stdbool.h>
#include "restaurant.h"

const int MIN_COMENSALES=1;
const int AREA_MESA_INDIVIDUAL=3;
const int AREA_MESA_PARA_CUATRO=4;
const char MESA='T';
const char VACIO=' ';


void inicializar_terreno(char terreno[MAX_FILAS][MAX_COLUMNAS], int tope){
    for(int fila; fila<MAX_FILAS;fila++){
      for(int columna; columna<MAX_COLUMNAS;columna++){
        terreno[fila][columna]=VACIO;
      }
    }
}

bool validar_coordenada(mesa_t mesa){
    bool es_valido=true;
    if(mesa.cantidad_comensales==1)
        if ((mesa.posicion->fil<0 || mesa.posicion->fil>=MAX_FILAS) || (mesa.posicion->col<0 || mesa.posicion->col>=MAX_COLUMNAS))
            es_valido=false;
    else
        for(int i=0; i<MAX_COMENSALES; i++)
            if ((mesa.posicion[i].fil<0 || mesa.posicion[i].fil>=MAX_FILAS) || (mesa.posicion[i].col<0 || mesa.posicion[i].col>=MAX_COLUMNAS))
                es_valido=false;
    return es_valido;
}

void reemplazar_elemento(char terreno[MAX_FILAS][MAX_COLUMNAS], coordenada_t posicion, char elemento){
    terreno[posicion.fil][posicion.col]=elemento;
}
bool puede_colocarse_mesa(char terreno[MAX_FILAS][MAX_COLUMNAS], mesa_t mesa){
    bool validación=true;
    if (mesa.cantidad_comensales==MIN_COMENSALES){
        for (int i = -1; i < AREA_MESA_INDIVIDUAL; i++){
            for (int j = -1; j < AREA_MESA_INDIVIDUAL; j++){
                if ((terreno[mesa.posicion[0].fil + i][mesa.posicion[0].col + j]== MESA) || (terreno[mesa.posicion[0].fil][mesa.posicion[0].col]!=VACIO))
                    validación=false;
            }
        }
    }if (mesa.cantidad_comensales==MAX_COMENSALES){
        int lugar_mesa_fil=0;
        int lugar_mesa_col=0;
        for (int i = -1; i < AREA_MESA_PARA_CUATRO; i++){
            for (int j = -1; i < AREA_MESA_PARA_CUATRO; i++){
                if (terreno[mesa.posicion[lugar_mesa_fil].fil + i][mesa.posicion[lugar_mesa_fil].col + j]==MESA)
                    validación=false;
                else if ((lugar_mesa_fil<AREA_MESA_PARA_CUATRO && lugar_mesa_col<AREA_MESA_PARA_CUATRO) && 
                terreno[mesa.posicion[lugar_mesa_fil].fil][mesa.posicion[lugar_mesa_col].col]!=VACIO)
                    validación=false;
                lugar_mesa_col++;
            }
            lugar_mesa_fil++;
            lugar_mesa_col=0;  
        }
    }return validación;
}
void ingresar_posicion_mesa(mesa_t mesa, coordenada_t posición){
    if (mesa.cantidad_comensales==MIN_COMENSALES){
        mesa.posicion[0].fil=posición.fil;
        mesa.posicion[0].col=posición.col;
    }else if (mesa.cantidad_comensales==MAX_COMENSALES){
        for (int i = 0; i < MAX_COMENSALES; i++){
            for (int j = 0; j < 2; j++){
                for (int a = 0; a < 2; a++){
                    mesa.posicion[i].fil=(posición.fil + j);
                    mesa.posicion[i].col=(posición.col + a);
                }
            }
        }
    }
}
void colocar_mesas(char terreno[MAX_FILAS][MAX_COLUMNAS], mesa_t mesa, coordenada_t posicion){
    if (mesa.cantidad_comensales==MIN_COMENSALES){
        while ((!puede_colocarse_mesa(terreno[MAX_FILAS][MAX_COLUMNAS], mesa)) || !validar_coordenada(mesa)){
            mesa.posicion[0].fil=posicion.fil;
            mesa.posicion[0].col=posicion.col;
            puede_colocarse_mesa(terreno[MAX_FILAS][MAX_COLUMNAS], mesa);
            validar_coordenada(mesa);
        }reemplazar_elemento(terreno[MAX_FILAS][MAX_COLUMNAS], mesa.posicion[0], MESA);
    }else if (mesa.cantidad_comensales==MAX_COMENSALES){
        for (int i = 0; i < mesa.cantidad_comensales; i++){
            while ((!puede_colocarse_mesa(terreno[MAX_FILAS][MAX_COLUMNAS], mesa)) || !validar_coordenada(mesa)){
            mesa.posicion[i].fil=posicion.fil;
            mesa.posicion[i].col=posicion.col;
            puede_colocarse_mesa(terreno[MAX_FILAS][MAX_COLUMNAS], mesa);
            validar_coordenada(mesa);
        }reemplazar_elemento(terreno[MAX_FILAS][MAX_COLUMNAS], mesa.posicion[i], MESA);
        }   
    }   
}

void inicializar_juego(juego_t *juego){

    juego->cocina.posicion.fil;
    juego->cocina.posicion.col;
}
void mostrar_juego(juego_t juego){

}
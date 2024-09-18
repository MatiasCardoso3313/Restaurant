#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include "restaurant.h"
const int CANTIDAD_MESAS=10;
const int MIN_COMENSALES=1;
const int AREA_MESA_DE_CUATRO=2;
int main(){
    srand((unsigned)time(NULL));
    juego_t juego;
    for (int i = 0; i < CANTIDAD_MESAS; i++){
        if (i<6)
            juego.mesas[i].cantidad_comensales=1;
        else
            juego.mesas[i].cantidad_comensales=4;
    }
    for(int a; a<CANTIDAD_MESAS; a++){
        coordenada_t posicion;
        posicion.fil=-1;
        posicion.col=-1;
        if(juego.mesas->cantidad_comensales==MIN_COMENSALES){
            while (!(validar_coordenada(juego.mesas[a]))){
                posicion.fil = rand() % 20;
                posicion.col = rand() % 20;
                modificar_posicion(posicion, juego.mesas[a].posicion);
                validar_coordenada(juego.mesas[a]);
            }
        }else if (juego.mesas->cantidad_comensales==MAX_COMENSALES){
            while (!validar_coordenada(juego.mesas[a])){
                for(int j=0; j < MAX_COMENSALES;j++){
                    posicion.fil = (rand() % 20);
                    posicion.col = (rand() % 20);
                    if (j==1)
                        posicion.col++;
                    else if (j==2)
                        posicion.fil++;
                    else if (j==3){
                        posicion.fil++; posicion.col++;
                    }
                    modificar_posicion(posicion, juego.mesas[a].posicion[j]);
                    validar_coordenada(juego.mesas[a]);
                }
            }
        }
    }mostrar_juego(juego);
    return 0;
}

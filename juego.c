#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include "restaurant.h"
#include "complemento.h"
int main(){
    srand((unsigned)time(NULL));
    juego_t juego;
    /* MESAS */
    juego.cantidad_mesas=(TOTAL_MESAS_DE_CUATRO+TOTAL_MESAS_INDIVIDUALES);
    juego.cantidad_herramientas=(CANTIDAD_MONEDAS + CANTIDAD_PATINES + UNICA_MOPA);
    for (int i = 0; i < juego.cantidad_mesas; i++){
        if (i<TOTAL_MESAS_INDIVIDUALES)
            juego.mesas[i].cantidad_comensales=MIN_COMENSALES;
        else
            juego.mesas[i].cantidad_comensales=MAX_COMENSALES;
        
    }
    for(int a=0; a<juego.cantidad_mesas; a++){
        coordenada_t posicion;
        posicion.fil=-1;
        posicion.col=-1;
        if((juego.mesas[a].cantidad_comensales) == MIN_COMENSALES){
            do{
                posicion.fil = (rand() % 19);
                posicion.col = (rand() % 19);
                modificar_posicion(posicion, juego.mesas[a].posicion);
            }while (!(validar_coordenada_mesa(juego.mesas[a])) || !validar_espacio_alrededor_de_mesas(juego, juego.mesas[a], a));
        }else if (juego.mesas[a].cantidad_comensales==MAX_COMENSALES){
            posicion.fil = (rand() % 19);
            posicion.col = (rand() % 19);
            do{
                for(int j=0; j < MAX_COMENSALES;j++){
                    if (j==1)
                        posicion.col++;
                    else if (j==2){
                        posicion.fil++; posicion.col--;
                    }else if (j==3)
                        posicion.col++;
                    modificar_posicion(posicion, &juego.mesas[a].posicion[j]);
                }
            }while (!validar_coordenada_mesa(juego.mesas[a]) || !validar_espacio_alrededor_de_mesas(juego, juego.mesas[a], a));
        }
    }
    /* COCINA */
    do{
        juego.cocina.posicion.fil= (rand() % 19);
        juego.cocina.posicion.col= (rand() % 19);
    } while(!chequeo_coordenada_valida(juego.cocina.posicion) || !coordenada_ocupada(juego, &juego.cocina.posicion));
    /* LINGUINI */
    do{
        juego.mozo.posicion.fil=(rand() % 19);
        juego.mozo.posicion.col=(rand() % 19);
    } while(!coordenada_ocupada(juego, &juego.mozo.posicion));
    /* MOPA */
    do{
        juego.herramientas[POSICION_MOPA].posicion.fil=(rand() % 19);
        juego.herramientas[POSICION_MOPA].posicion.col=(rand() % 19);
    } while (!coordenada_ocupada(juego, &juego.herramientas[0].posicion));
    /* MONEDAS */
    for (int moneda = PRIMER_LUGAR_MONEDAS; moneda <= CANTIDAD_MONEDAS; moneda++){
        juego.herramientas[moneda].tipo=MONEDA;
        do{
            juego.herramientas[moneda].posicion.fil=(rand() % 19);
            juego.herramientas[moneda].posicion.col=(rand() % 19);
        } while (!coordenada_ocupada(juego, &juego.herramientas[moneda].posicion));
    }
    /* PATINES */
    for (int patin = PRIMER_LUGAR_PATINES; patin < juego.cantidad_herramientas; patin++){
        juego.herramientas[patin].tipo=PATIN;
        do{
            juego.herramientas[patin].posicion.fil=(rand() % 19);
            juego.herramientas[patin].posicion.col=(rand() % 19);
        } while (!coordenada_ocupada(juego, &juego.herramientas[patin].posicion));    
    }
    /* CHARCOS */
    
    
    inicializar_juego(&juego);
        
    mostrar_juego(juego);
    return 0;
}

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include "restaurant.h"
#include "complemento.h"

void reemplazar_elemento(char terreno[MAX_FILAS][MAX_COLUMNAS],char elemento, coordenada_t posicion){
    terreno[posicion.fil][posicion.col]=elemento;
}
bool mesa_en_el_camino(juego_t juego, coordenada_t* posicion){
    bool hay_mesa_en_camino=false;
    for (int i = 0; i < juego.cantidad_mesas; i++){
        for (int j = 0; j < juego.mesas[i].cantidad_comensales; j++){
            if (juego.mesas[i].posicion[j].fil==posicion->fil && juego.mesas[i].posicion[j].col==posicion->col) {
                hay_mesa_en_camino=true;
            }
        }
    }return hay_mesa_en_camino;
}
bool coordenada_ocupada(juego_t* juego, coordenada_t* posicion){
    bool no_esta_ocupada=true;
    if (mesa_en_el_camino(*juego, posicion)){
        no_esta_ocupada=false;
    }
    if (&juego->cocina.posicion!=posicion){
        if ((posicion->fil==juego->cocina.posicion.fil) && (posicion->col==juego->cocina.posicion.col))
            no_esta_ocupada=false;    
    }
    if (&juego->mozo.posicion!=posicion && !juego->mozo.tiene_mopa){
        if ((posicion->fil==juego->mozo.posicion.fil) && (posicion->col==juego->mozo.posicion.col)){
            no_esta_ocupada=false;
        }   
    }
    if (&juego->herramientas[0].posicion!=posicion){
        if ((posicion->fil==juego->herramientas->posicion.fil) && (posicion->col==juego->herramientas->posicion.col))
            no_esta_ocupada=false;
    }
    int lugar_moneda = PRIMER_LUGAR_MONEDAS;
    while((no_esta_ocupada==true) && (lugar_moneda<=CANTIDAD_MONEDAS)){
        if (&juego->herramientas[lugar_moneda].posicion!=posicion){
            coordenada_t posicion_herramienta=juego->herramientas[lugar_moneda].posicion;
            if ((posicion->fil==posicion_herramienta.fil) && (posicion->col==posicion_herramienta.col))
            no_esta_ocupada=false;
        }lugar_moneda++;   
    }
    int lugar_patin = PRIMER_LUGAR_PATINES;
    while ((no_esta_ocupada==true) && (lugar_patin<=juego->cantidad_herramientas)){
        if (&juego->herramientas[lugar_patin].posicion!=posicion){
            coordenada_t posicion_herramienta=juego->herramientas[lugar_patin].posicion;
            if ((posicion->fil==posicion_herramienta.fil) && (posicion->col==posicion_herramienta.col))
                no_esta_ocupada=false;
        }lugar_patin++;
    }
    int lugar_charco = 0;
    while ((no_esta_ocupada==true) && (lugar_charco<CANTIDAD_CHARCOS)){
        if (&juego->obstaculos[lugar_charco].posicion!=posicion){
            coordenada_t posicion_obstaculo=juego->obstaculos[lugar_charco].posicion;
            if ((posicion->fil==posicion_obstaculo.fil) && (posicion->col==posicion_obstaculo.col)){
                no_esta_ocupada=false;
            }
        }lugar_charco++;
    }
    return no_esta_ocupada;
}
bool validar_espacio_alrededor_de_mesas(juego_t juego, mesa_t nueva_mesa, int numero_de_mesas) {
    bool sin_mesas_cerca=true;
    for (int mesa_anterior = 0; mesa_anterior < numero_de_mesas; mesa_anterior++) {
        mesa_t mesa = juego.mesas[mesa_anterior];
        for (int i = 0; i < mesa.cantidad_comensales; i++) {
            coordenada_t posicion = mesa.posicion[i];
            for (int j = 0; j < nueva_mesa.cantidad_comensales; j++) {
                coordenada_t nueva_posicion = nueva_mesa.posicion[j];
                if ((abs(posicion.fil - nueva_posicion.fil) <= 1) && (abs(posicion.col - nueva_posicion.col) <= 1)) {
                    sin_mesas_cerca=false;
                }
            }
        }
    }return sin_mesas_cerca;
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
    coordenada_t posicion_mesa = *mesa.posicion;
    int comensal=0;
    while(es_valido && comensal < mesa.cantidad_comensales){
        if ((posicion_mesa.fil<0 || posicion_mesa.fil>=MAX_FILAS) || (posicion_mesa.col<0 || posicion_mesa.col>=MAX_COLUMNAS))
            es_valido=false;
        comensal++;
    }return es_valido;
}

void inicializar_juego(juego_t *juego){
    juego->dinero=0;
    juego->movimientos=0;
    juego->cantidad_mesas=0;
    juego->cantidad_herramientas=0;
    juego->cantidad_obstaculos=TOTAL_OBSTACULOS;
    /* MESAS */
    while(juego->cantidad_mesas<(TOTAL_MESAS_INDIVIDUALES + TOTAL_MESAS_DE_CUATRO)){
        juego->mesas[juego->cantidad_mesas].pedido_tomado=false;
        juego->mesas[juego->cantidad_mesas].paciencia=-1;
        if (juego->cantidad_mesas<TOTAL_MESAS_INDIVIDUALES){
            juego->mesas[juego->cantidad_mesas].cantidad_comensales=MIN_COMENSALES;
            juego->mesas[juego->cantidad_mesas].cantidad_lugares=MIN_COMENSALES;
        }else{
            juego->mesas[juego->cantidad_mesas].cantidad_comensales=MAX_COMENSALES;
            juego->mesas[juego->cantidad_mesas].cantidad_lugares=MAX_COMENSALES;
        }
        juego->cantidad_mesas++;
    }
    for(int a=0; a<juego->cantidad_mesas; a++){

        coordenada_t posicion;
        posicion.fil=-1;
        posicion.col=-1;
        if((juego->mesas[a].cantidad_comensales) == MIN_COMENSALES){
            do{
                posicion.fil = (rand() % 19);
                posicion.col = (rand() % 19);
                modificar_posicion(posicion, juego->mesas[a].posicion);
                // printf("Posicion de mesa de %i es %i|%i\n", *juego.mesas[a].cantidad_comensales, *juego.mesas[a].posicion->fil, *juego.mesas[a].posicion->col );
            }while (!(validar_coordenada_mesa(juego->mesas[a])) || !validar_espacio_alrededor_de_mesas(*juego, juego->mesas[a], a));
        }else if (juego->mesas[a].cantidad_comensales==MAX_COMENSALES){
            do{
                    posicion.col = (rand() % 19);
                    posicion.fil = (rand() % 19);
                for(int j=0; j < MAX_COMENSALES;j++){
                    if (j==1)
                        posicion.col++;
                    else if (j==2){
                        posicion.fil++; posicion.col--;
                    }else if (j==3)
                        posicion.col++;
                    modificar_posicion(posicion, &juego->mesas[a].posicion[j]);
                    //printf("Posicion de mesa de %i es %i|%i\n", juego->mesas[a].cantidad_comensales, juego->mesas[a].posicion->fil, juego->mesas[a].posicion->col );
                }
            }while (!validar_coordenada_mesa(juego->mesas[a]) || !validar_espacio_alrededor_de_mesas(*juego, juego->mesas[a], a));
        }
    }
    /* COCINA */
    do{
        juego->cocina.posicion.fil= (rand() % 19);
        juego->cocina.posicion.col= (rand() % 19);
    } while(!chequeo_coordenada_valida(juego->cocina.posicion) || !coordenada_ocupada(juego, &juego->cocina.posicion));
    /* LINGUINI */
    juego->mozo.tiene_mopa=false;
    juego->mozo.patines_puestos=false;
    juego->mozo.cantidad_pedidos=0;
    juego->mozo.cantidad_bandeja=0;
    for (int i = 0; i < juego->cantidad_mesas; i++){
        while (juego->mozo.cantidad_pedidos<MAX_PEDIDOS){
            juego->mozo.pedidos[juego->mozo.cantidad_pedidos].cantidad_platos=0;
            while(juego->mozo.pedidos[juego->mozo.cantidad_pedidos].cantidad_platos<MAX_PLATOS){
                int numero_plato=juego->mozo.pedidos[juego->mozo.cantidad_pedidos].cantidad_platos;
                juego->mozo.pedidos[juego->mozo.cantidad_pedidos].platos[numero_plato]=VACIO;
                juego->mozo.pedidos[juego->mozo.cantidad_pedidos].cantidad_platos++;
            }
            juego->mozo.pedidos[juego->mozo.cantidad_pedidos].id_mesa=juego->mesas[i].cantidad_comensales&i;
            juego->mozo.pedidos[juego->mozo.cantidad_pedidos].tiempo_preparacion=-1;
            juego->mozo.cantidad_pedidos++;
        }
        while (juego->mozo.cantidad_bandeja<MAX_BANDEJA){
            juego->mozo.bandeja[juego->mozo.cantidad_bandeja].cantidad_platos=0;
            while(juego->mozo.bandeja[juego->mozo.cantidad_bandeja].cantidad_platos<MAX_BANDEJA){
                int numero_plato=juego->mozo.bandeja[juego->mozo.cantidad_bandeja].cantidad_platos;
                juego->mozo.bandeja[juego->mozo.cantidad_bandeja].platos[numero_plato]=VACIO;
                juego->mozo.bandeja[juego->mozo.cantidad_bandeja].cantidad_platos++;
            }
            juego->mozo.bandeja[juego->mozo.cantidad_bandeja].id_mesa=juego->mesas[i].cantidad_comensales&i;
            juego->mozo.bandeja[juego->mozo.cantidad_bandeja].tiempo_preparacion=-1;
            juego->mozo.bandeja[juego->mozo.cantidad_bandeja].cantidad_platos=juego->mesas[i].cantidad_comensales;
            juego->mozo.cantidad_bandeja++;
        }
    }
    do{
        juego->mozo.posicion.fil=(rand() % 19);
        juego->mozo.posicion.col=(rand() % 19);
    } while(!coordenada_ocupada(juego, &juego->mozo.posicion));
    /* MOPA */
    do{
        juego->herramientas[LUGAR_MOPA].posicion.fil=(rand() % 19);
        juego->herramientas[LUGAR_MOPA].posicion.col=(rand() % 19);
    } while (!coordenada_ocupada(juego, &juego->herramientas[0].posicion));
    juego->cantidad_herramientas++;
    /* MONEDAS */
    for (int moneda = PRIMER_LUGAR_MONEDAS; moneda <= CANTIDAD_MONEDAS; moneda++){
        juego->herramientas[moneda].tipo=MONEDA;
        do{
            juego->herramientas[moneda].posicion.fil=(rand() % 19);
            juego->herramientas[moneda].posicion.col=(rand() % 19);
        } while (!coordenada_ocupada(juego, &juego->herramientas[moneda].posicion));
    }
    /* PATINES */
    for (int patin = PRIMER_LUGAR_PATINES; patin < juego->cantidad_herramientas; patin++){
        juego->herramientas[patin].tipo=PATIN;
        do{
            juego->herramientas[patin].posicion.fil=(rand() % 19);
            juego->herramientas[patin].posicion.col=(rand() % 19);
        } while (!coordenada_ocupada(juego, &juego->herramientas[patin].posicion));    
    }
    /* CHARCOS */
    for (int charco = 0; charco < CANTIDAD_CHARCOS; charco++){
        juego->obstaculos[charco].tipo=CHARCO;
        do{
            juego->obstaculos[charco].posicion.fil=(rand() % 19);
            juego->obstaculos[charco].posicion.col=(rand() % 19);
        } while (!coordenada_ocupada(juego, &juego->obstaculos[charco].posicion));
        
    }
    mostrar_juego(*juego);
}
void realizar_jugada(juego_t *juego , char accion){
    chequeo_coordenada_valida(juego->mozo.posicion);
    if (accion==ACCION_ABAJO && juego->mozo.posicion.fil!=(MAX_FILAS-1)){
        juego->mozo.posicion.fil++;
        juego->movimientos++;
        if (mesa_en_el_camino(*juego, &juego->mozo.posicion)){
            juego->mozo.posicion.fil--;
            juego->movimientos--;
        }
    }else if (accion==ACCION_ARRIBA && juego->mozo.posicion.fil!=0){
        juego->mozo.posicion.fil--;
        juego->movimientos++;
        if (mesa_en_el_camino(*juego, &juego->mozo.posicion)){
            juego->mozo.posicion.fil++;
            juego->movimientos--;

        }
    }else if (accion==ACCION_DERECHA && juego->mozo.posicion.col!=(MAX_COLUMNAS-1)){
        juego->mozo.posicion.col++;
        juego->movimientos++;
        if (mesa_en_el_camino(*juego, &juego->mozo.posicion)){
            juego->mozo.posicion.col--;
            juego->movimientos--;
        }
    }else if (accion==ACCION_IZQUIERDA && juego->mozo.posicion.col!=0){
        juego->mozo.posicion.col--;
        juego->movimientos++;
        if (mesa_en_el_camino(*juego, &juego->mozo.posicion)){
            juego->mozo.posicion.col++;
            juego->movimientos--;
        }
    }else if (accion==AGARRA_O_SOLTAR_MOPA){
        coordenada_t posicion_mopa=juego->herramientas[LUGAR_MOPA].posicion;
        coordenada_t posicion_mozo=juego->mozo.posicion;
        if (!juego->mozo.tiene_mopa && (posicion_mopa.fil!=posicion_mozo.fil || posicion_mopa.col!=posicion_mozo.col)){
            printf("     ---¡¡¡NO PUEDES RECOGER LA MOPA, NO TE ENCUENTRAS ENCIMA DE ELLA!!!---\n");
        }else if (!juego->mozo.tiene_mopa && (posicion_mopa.fil==posicion_mozo.fil && posicion_mopa.col==posicion_mozo.col)){
            printf("     ---RECOGISTE LA MOPA---\n");
            juego->mozo.tiene_mopa=true;
            juego->herramientas[LUGAR_MOPA].posicion.fil=-1;
            juego->herramientas[LUGAR_MOPA].posicion.col=-1;
        }else if (juego->mozo.tiene_mopa && coordenada_ocupada(juego, &juego->mozo.posicion)){
                juego->mozo.tiene_mopa=false;
                juego->herramientas[LUGAR_MOPA].posicion.fil=juego->mozo.posicion.fil;
                juego->herramientas[LUGAR_MOPA].posicion.col=juego->mozo.posicion.col;
                printf("     ---SOLTASTE LA MOPA EN TU POSICION ACTUAL---\n");
        }else
            printf("     ---¡¡¡NO PUEDES SOLTAR LA MOPA EN ESTA POSICION!!!---\n");  
    }
}
int estado_juego(juego_t juego){
    return 0;
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
    terreno[juego.herramientas[0].posicion.fil][juego.herramientas[0].posicion.col]=MOPA;
    for (int moneda = 1; moneda <= CANTIDAD_MONEDAS; moneda++){
        coordenada_t posicion_moneda=juego.herramientas[moneda].posicion;
        terreno[posicion_moneda.fil][posicion_moneda.col]=juego.herramientas[moneda].tipo;
    }
    for (int patin = PRIMER_LUGAR_PATINES; patin < juego.cantidad_herramientas; patin++){
        coordenada_t posicion_patin=juego.herramientas[patin].posicion;
        terreno[posicion_patin.fil][posicion_patin.col]=juego.herramientas[patin].tipo;
    }
    for (int charco = 0; charco < juego.cantidad_obstaculos; charco++){
        coordenada_t posicion_charco=juego.obstaculos[charco].posicion;
        terreno[posicion_charco.fil][posicion_charco.col]=juego.obstaculos[charco].tipo;
    }
    terreno[juego.mozo.posicion.fil][juego.mozo.posicion.col]=LINGUINI;
    
    printf("|ACCIONES VALIDAS|\n|MOVERSE IZQUIERDA = 'A' | MOVERSE DERECHA = 'D' | MOVERSE ARRIBA = W | MOVERSE ABAJO = S |\n\n");
    for (int i = 0; i < 81; i++){
        printf("=");
    }
    printf("\n");
    for (int fila = 0; fila < MAX_FILAS; fila++){
        for (int columna = 0; columna < MAX_COLUMNAS; columna++){
            printf("|");
            printf(" %c ", terreno[fila][columna]);
            if (columna==(MAX_COLUMNAS-1))
                printf("|\n");
        }
    }for (int i = 0; i < 81; i++){
        printf("=");
    }
    printf("\n");
    char mopa=VACIO;
    if (juego.mozo.tiene_mopa)
        mopa=MOPA;
    else
        mopa=VACIO  ;

    
    printf("[CANTIDAD DE ACCIONES: - %i -] ", juego.movimientos);
    printf("[MOPA:- %c -] ", mopa);
    printf("[DINERO: - %i -] ",juego.dinero);
    printf("\n");
}
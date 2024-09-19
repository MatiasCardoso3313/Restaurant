#ifndef __COMPLEMENTO_H__
#define __COMPLEMENTO_H__
#include "restaurant.h"
#define MOPA 'O'
#define MONEDA 'M'
#define PATIN 'P'
#define MESA 'T'
#define CHARCO 'H'
#define LINGUINI 'L'
#define COCINA 'C'
#define VACIO ' '
#define LUGAR_MOPA 0
#define PRIMER_LUGAR_MONEDAS 1
#define PRIMER_LUGAR_PATINES 9
#define TOTAL_HERRAMIENTAS 14
#define MIN_COMENSALES 1
#define TOTAL_MESAS_INDIVIDUALES 6
#define TOTAL_MESAS_DE_CUATRO 4
#define TOTAL_OBSTACULOS 5
#define CANTIDAD_CHARCOS 5
#define CANTIDAD_MONEDAS 8
#define CANTIDAD_PATINES 5
#define UNICA_MOPA 1
#define ACCION_DERECHA 'D'
#define ACCION_IZQUIERDA 'A'
#define ACCION_ARRIBA 'W'
#define ACCION_ABAJO 'S'
#define AGARRA_O_SOLTAR_MOPA 'O'

bool validar_coordenada_mesa(mesa_t mesa);
void modificar_posicion(coordenada_t posicion_remplazante, coordenada_t* posicion_original);
bool validar_espacio_alrededor_de_mesas(juego_t juego, mesa_t nueva_mesa, int numero_de_mesas);
bool coordenada_ocupada(juego_t* juego, coordenada_t* posicion);
bool chequeo_coordenada_valida(coordenada_t posicion);

#endif
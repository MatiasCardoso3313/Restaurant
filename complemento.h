#ifndef __COMPLEMENTO_H__
#define __COMPLEMENTO_H__
#include "restaurant.h"
#define MIN_COMENSALES 1

bool validar_coordenada_mesa(mesa_t mesa);
void modificar_posicion(coordenada_t posicion_remplazante, coordenada_t* posicion_original);
bool validar_espacio_alrededor_de_mesas(juego_t juego, mesa_t nueva_mesa, int numero_de_mesas);
bool coordenada_ocupada(juego_t juego, coordenada_t* posicion);
bool chequeo_coordenada_valida(coordenada_t posicion);

#endif
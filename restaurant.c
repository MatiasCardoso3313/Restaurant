#include<stdio.h>
#include<stdlib.h>
#include "restaurant.h"

/* ESTADO DE JUEGO */
const int JUEGO_EN_CURSO=0;
const int JUEGO_PERDIDO=-1;
const int JUEGO_GANADO=1;
/* CONVENCIONES */
const int LARGO_DEL_TERRENO_IMPRESO_EN_PANTALLA = 81;
const int ENTERO_INVALIDO=-1;
const int TOTAL_NUMEROS_ALEATORIOS=19;
const int DISTANCIA_MINIMA_MESAS=1;
const int SIN_COMENSALES=0;
const int MAX_MOVIMIENTOS = 200;
const int DINERO_NECESARIO = 150000;
/* ELEMENTOS VALIDOS */
const char MOPA='O';
const char MONEDA='M';
const char PATIN='P';
const char MESA='T';
const char CHARCO='H';
const char LINGUINI='L';
const char COCINA='C';
const char VACIO=' ';
/* POSICION EN VECTORES */
const int LUGAR_MOPA= 0;
const int PRIMER_LUGAR_MONEDAS= 1;
const int ULTIMO_LUGAR_MONEDAS= 8;
const int PRIMER_LUGAR_PATINES= 9;
const int ULTIMO_LUGAR_PATINES= 13;
const int PRIMER_LUGAR_CHARCO= 0;
const int ULTIMO_LUGAR_CHARCO= 4;
/* CANTIDAD Y TOTALIDAD DE ELEMENTOS */
const int MIN_COMENSALES= 1;
const int TOTAL_MESAS_INDIVIDUALES= 6;
const int TOTAL_MESAS_DE_CUATRO= 4;
const int CANTIDAD_CHARCOS= 5;
const int CANTIDAD_TOTAL_MONEDAS= 8;
const int CANTIDAD_TOTAL_PATINES= 5;
/* ACCIONES VALIDAS */
const char ACCION_DERECHA=  'D';
const char ACCION_IZQUIERDA=  'A';
const char ACCION_ARRIBA=  'W';
const char ACCION_ABAJO=  'S';
const char AGARRA_O_SOLTAR_MOPA=  'O';
/*
*   Pre condiciones: El terreno debe estar inicializado con elementos válidos, y el elemento que recibe debe 
*                   ser un ELEMENTO VÁLIDO.
*   Postcondiciones: Reemplaza el carácter que está en la fila y columna dados por la posición. 
*                   El carácter reemplazado es el del elemento.
*/
void reemplazar_elemento(char terreno[MAX_FILAS][MAX_COLUMNAS], char elemento, coordenada_t posicion){
    terreno[posicion.fil][posicion.col]=elemento;
}
/*
*   Pre condiciones: Las posiciones deben estar dentro de los límites del terreno.
*   Pos tcondiciones: Verifica si las dos posiciones son distintas; si es así, devuelve true. 
*                    En caso contrario, devuelve false.
*/
bool posiciones_distintas(coordenada_t primera_posicion, coordenada_t segunda_posicion){
    return ((primera_posicion.fil!=segunda_posicion.fil) || (primera_posicion.col!=segunda_posicion.col));
}
/*
*   Precondiciones: El juego debe tener al menos una mesa inicializada.
*   Postcondiciones: Verifica si hay una mesa en la posición ingresada. Si hay una mesa en esa posición, 
*                    devuelve un valor booleano con true; en caso contrario, devuelve false.
*/
bool posicion_sin_mesa(juego_t juego, coordenada_t* posicion){
    bool no_hay_mesa=true;
    int i=0;
    while((i<juego.cantidad_mesas) && (no_hay_mesa)){
        int j=0;
        while(j<juego.mesas[i].cantidad_lugares && (no_hay_mesa)){
            no_hay_mesa=posiciones_distintas(*posicion, juego.mesas[i].posicion[j]);
            j++;
        }i++;
    }return no_hay_mesa;
}
/*
*   Pre condiciones: El campo de posición del campo cocina de juego debe estar inicializado y posición debe
*                    ser una posición válida.
*   Post condiciones: Devuelve true si la dirección de posición y la dirección de la posición de la cocina son distintas, y si
*                     los valores tambien son distintos. Caso contrario devuelve false.
*/
bool coordenada_libre_de_cocina(juego_t* juego, coordenada_t* posicion){
    return ((&juego->cocina.posicion!=posicion) && (!posiciones_distintas(*posicion, juego->cocina.posicion)));
}
/*
*   Pre condiciones: El campo de posición del campo mozo de juego debe estar inicializado y posición debe
*                    ser una posición válida.
*   Post condiciones: Devuelve true si la dirección de posición y la dirección de la posicion del mozo son distintas, y si
*                     los valores tambien son distintos. Caso contrario devuelve false.
*/
bool coordenada_libre_de_mozo(juego_t* juego, coordenada_t* posicion){
    return ((&juego->mozo.posicion!=posicion) && (!posiciones_distintas(*posicion, juego->mozo.posicion)));
}
/*
*   Pre condiciones: El campo de posición del campo herramientas[LUGAR_MOPA] de juego debe estar inicializado y posición debe
*                    ser una posición válida.
*   Post condiciones: Devuelve true si la dirección de posición y la dirección de posición de la mopa son distintas, y si
*                     los valores tambien son distintos. Caso contrario devuelve false.
*/
bool coordenada_libre_de_mopa(juego_t* juego, coordenada_t* posicion){
    return ((&juego->herramientas[LUGAR_MOPA].posicion!=posicion) && (!posiciones_distintas(*posicion, juego->herramientas[LUGAR_MOPA].posicion)));
}
/*
*   Pre condiciones: El campo de posición de los campos de las monedas de juego debe estar inicializado y posición debe
*                    ser una posición válida.
*   Post condiciones: Devuelve true si la dirección de posición y la dirección de posición de las monedas son distintas, y si
*                     los valores tambien son distintos. Caso contrario devuelve false.
*/
bool coordenada_libre_de_moneda(juego_t* juego, coordenada_t* posicion){
    bool no_esta_ocupada=true;
    int lugar_moneda = PRIMER_LUGAR_MONEDAS;
    while((no_esta_ocupada) && (lugar_moneda<=ULTIMO_LUGAR_MONEDAS)){
        if (&juego->herramientas[lugar_moneda].posicion!=posicion){
            no_esta_ocupada=posiciones_distintas(*posicion, juego->herramientas[lugar_moneda].posicion);
        }lugar_moneda++;   
    }
    return no_esta_ocupada;
}
/*
*   Pre condiciones: El campo de posición de los campos de los patines de juego debe estar inicializado y posición debe
*                    ser una posición válida.
*   Post condiciones: Devuelve true si la dirección de posición y la dirección de posición de los patines son distintas, y si
*                     los valores tambien son distintos. Caso contrario devuelve false.
*/
bool coordenada_libre_de_patin(juego_t* juego, coordenada_t* posicion){
    bool no_esta_ocupada=true;
    int lugar_patin = PRIMER_LUGAR_PATINES;
    while ((no_esta_ocupada) && (lugar_patin<=ULTIMO_LUGAR_PATINES)){
        if (&juego->herramientas[lugar_patin].posicion!=posicion){
            no_esta_ocupada=posiciones_distintas(*posicion, juego->herramientas[lugar_patin].posicion);
        }lugar_patin++;
    }
    return no_esta_ocupada;
}
/*
*   Pre condiciones: El campo de posición de los campos de los charcos de juego debe estar inicializado y posición debe
*                    ser una posición válida.
*   Post condiciones: Devuelve true si la dirección de posición y la dirección de posición de los charcos son distintas, y si
*                     los valores tambien son distintos. Caso contrario devuelve false.
*/
bool coordenada_libre_de_charco(juego_t* juego, coordenada_t* posicion){
    bool no_esta_ocupada=true;
    int lugar_charco = PRIMER_LUGAR_CHARCO;
    while ((no_esta_ocupada) && (lugar_charco<ULTIMO_LUGAR_CHARCO)){
        if (&juego->obstaculos[lugar_charco].posicion!=posicion){
            no_esta_ocupada=posiciones_distintas(*posicion, juego->obstaculos[lugar_charco].posicion);
        }lugar_charco++;
    }
    return no_esta_ocupada;
}
/*
*   Pre condiciones: Juego debe tener elementos inicializados con sus respectivas posiciones válidas.
*   Post condiciones: Compara si posición es igual a las demas posiciones de cada elemento de juego
*                     si en algún elemento la posición coincide devuelve el valor false, caso contrario devolvera
*                     el valor true.
*/
bool coordenada_no_ocupada(juego_t* juego, coordenada_t* posicion){
    if(!posicion_sin_mesa(*juego, posicion))
        return false;
    if (coordenada_libre_de_cocina(juego, posicion))
        return false;
    if (coordenada_libre_de_mozo(juego, posicion))
        return false;
    if (coordenada_libre_de_mopa(juego, posicion))
        return false;
    if (!coordenada_libre_de_moneda(juego, posicion))
        return false;
    if (!coordenada_libre_de_patin(juego, posicion))
        return false;
    if (!coordenada_libre_de_charco(juego, posicion))
        return false;
    return true;
}
/*
*   Pre condiciones: La variable numero de mesas debe ser valido y estar en el rango del vector de mesas
*                    de juego.
*   Post condiciones: Chequea que alrededor de la nueva mesa no haya otras mesas, si hay una mesa al rededor
*                     devuelve el valor false de la variable sin_mesas_cerca, caso contrario devuelve el valor true. 
*/
bool validar_espacio_alrededor_de_mesas(juego_t juego, mesa_t nueva_mesa, int numero_de_mesas){
    bool sin_mesas_cerca=true;
    int mesa_anterior=0;
    while(mesa_anterior<numero_de_mesas && sin_mesas_cerca){
        mesa_t mesa = juego.mesas[mesa_anterior];
        int i=0;
        while(i < mesa.cantidad_lugares && sin_mesas_cerca){
            coordenada_t posicion = mesa.posicion[i];
            int j=0;
            while(j<nueva_mesa.cantidad_lugares && sin_mesas_cerca) {
                coordenada_t nueva_posicion = nueva_mesa.posicion[j];
                if ((abs(posicion.fil - nueva_posicion.fil) <= DISTANCIA_MINIMA_MESAS) && (abs(posicion.col - nueva_posicion.col) <= DISTANCIA_MINIMA_MESAS)) {
                    sin_mesas_cerca=false;
                }j++;
            }i++;
        }mesa_anterior++;
    }return sin_mesas_cerca;
}
/*
*   Pre condiciones: Las posiciones deben ser validas.
*   Post condiciones: Modifica la fila y la columna de la posicion a reemplazar con los de la posicion
*                     reemplazante.
*/
void modificar_posicion(coordenada_t posicion_reemplazante, coordenada_t* posicion_a_remplazar){
    posicion_a_remplazar->fil=posicion_reemplazante.fil;
    posicion_a_remplazar->col=posicion_reemplazante.col;
}
/*
*   Pre condiciones: -
*   Post condiciones: Chequea si la posicion dada es valida y esta dentro del terreno, si es asi
*                     devuelve el valor true de la variable posicion_valida, caso contrario devuelve 
*                     el valor false.
*/
bool chequeo_coordenada_valida(coordenada_t posicion){
    bool posicion_valida=false;
    if ((posicion.fil>=0 && posicion.fil<MAX_FILAS) && (posicion.col>=0 && posicion.col<MAX_COLUMNAS)){
        posicion_valida=true;
    }return posicion_valida;
}
/*
*   Pre condiciones: La posicion debe ser una posicion que corresponda a un elemento de juego.
*   Post condiciones: Cambia los valores de fila y columna de posicion con numeros aleatorios
*                     hasta que la posicion sea única.
*/
void cambiar_a_cordenadas_desocupadas(juego_t* juego, coordenada_t* posicion){
    do{
        posicion->fil= (rand() % TOTAL_NUMEROS_ALEATORIOS);
        posicion->col= (rand() % TOTAL_NUMEROS_ALEATORIOS);
    } while (!coordenada_no_ocupada(juego, posicion));
}
/*
*   Pre condiciones: -
*   Post condiciones: Inicializa los campos de las mesas y agrega la cantidad de mesas hasta llegar a 10 mesas.
*/
void inicializar_campos_mesas(juego_t* juego){
    while(juego->cantidad_mesas<(TOTAL_MESAS_INDIVIDUALES + TOTAL_MESAS_DE_CUATRO)){
        juego->mesas[juego->cantidad_mesas].pedido_tomado=false;
        juego->mesas[juego->cantidad_mesas].paciencia=0;
        if (juego->cantidad_mesas<TOTAL_MESAS_INDIVIDUALES){
            juego->mesas[juego->cantidad_mesas].cantidad_comensales=SIN_COMENSALES;
            juego->mesas[juego->cantidad_mesas].cantidad_lugares=MIN_COMENSALES;
        }else{
            juego->mesas[juego->cantidad_mesas].cantidad_comensales=SIN_COMENSALES;
            juego->mesas[juego->cantidad_mesas].cantidad_lugares=MAX_COMENSALES;
        }
        juego->cantidad_mesas++;
    }
}
/*
*   Pre condiciones: El campo cantidad_mesas de juego debe estar inicializado con valor 10.
*   Post condiciones: Asigna a las mesas sus posiciones.
*/
void inicializar_posiciones_mesas(juego_t* juego){
    for(int a=0; a<juego->cantidad_mesas; a++){
        coordenada_t posicion;
        posicion.fil=ENTERO_INVALIDO;
        posicion.col=ENTERO_INVALIDO;
        if((juego->mesas[a].cantidad_lugares) == MIN_COMENSALES){
            do{
                posicion.fil = (rand() % TOTAL_NUMEROS_ALEATORIOS);
                posicion.col = (rand() % TOTAL_NUMEROS_ALEATORIOS);
                modificar_posicion(posicion, juego->mesas[a].posicion);
            }while (!validar_espacio_alrededor_de_mesas(*juego, juego->mesas[a], a));
        }else if (juego->mesas[a].cantidad_lugares==MAX_COMENSALES){
            do{
                posicion.col = (rand() % TOTAL_NUMEROS_ALEATORIOS);
                posicion.fil = (rand() % TOTAL_NUMEROS_ALEATORIOS);
                for(int j=0; j < MAX_COMENSALES;j++){
                    if (j==1)
                        posicion.col++;
                    else if (j==2){
                        posicion.fil++; posicion.col--;
                    }else if (j==3)
                        posicion.col++;
                    modificar_posicion(posicion, &juego->mesas[a].posicion[j]);
                }
            }while (!(chequeo_coordenada_valida(*juego->mesas[a].posicion)) || !validar_espacio_alrededor_de_mesas(*juego, juego->mesas[a], a));
        }
    }
}
/*
*   Pre condiciones: -
*   Post condiciones: Asigna a la cocina una posición. 
*/
void inicializar_posicion_cocina(juego_t* juego){
    cambiar_a_cordenadas_desocupadas(juego, &juego->cocina.posicion);
}
/*
*   Pre condiciones: El campo cantidad_mesas de juego debe estar inicializada con valor 10.
*   Post condiciones: Inicializa los campos del campo mozo de juego.
*/
void inicializar_campos_mozo(juego_t* juego){
    juego->mozo.tiene_mopa=false;
    juego->mozo.patines_puestos=false;
    juego->mozo.cantidad_patines=0;
    juego->mozo.cantidad_pedidos=0;
    juego->mozo.cantidad_bandeja=0;
    for (int i = 0; i < juego->cantidad_mesas; i++){
        juego->mozo.pedidos[i].cantidad_platos=0;
        juego->mozo.bandeja[i].cantidad_platos=0;
    }
}
/*
*   Pre condiciones: -
*   Post condiciones: Asigna al mozo su posiciones.
*/
void inicializar_posicion_mozo(juego_t* juego){
    cambiar_a_cordenadas_desocupadas(juego, &juego->mozo.posicion);
}
/*
*   Pre condiciones: -
*   Post condiciones: Asigna la posicion de la mopa, inicializa el tipo de caracter de la mopa
*                     y aumenta la cantidad de herramientas en 1.
*/
void inicializar_mopa(juego_t* juego){
    juego->herramientas[LUGAR_MOPA].tipo=MOPA;
    cambiar_a_cordenadas_desocupadas(juego, &juego->herramientas[LUGAR_MOPA].posicion);
    juego->cantidad_herramientas++;
}
/*
*   Pre condiciones: -
*   Post condiciones: Inicializa el tipo de caracter de las monedas, asigna la posicion de cada moneda
*                     y aumenta la cantidad de herramientas 9.
*/
void inicializar_monedas(juego_t* juego){
    int cantidad_monedas=0;
    while(cantidad_monedas<CANTIDAD_TOTAL_MONEDAS){
        juego->herramientas[juego->cantidad_herramientas].tipo=MONEDA;
        cambiar_a_cordenadas_desocupadas(juego, &juego->herramientas[juego->cantidad_herramientas].posicion);
        cantidad_monedas++;
        juego->cantidad_herramientas++;
    }
}
/*
*   Pre condiciones: -
*   Post condiciones: Asigna la posicion de cada patin, inicializa el tipo de caracter de los patines y
*                     aumenta la cantidad de herramientas hasta 14.
*/
void inicializar_patines(juego_t* juego){
    int cantidad_patines=0;
    while(cantidad_patines<CANTIDAD_TOTAL_PATINES){
        juego->herramientas[juego->cantidad_herramientas].tipo=PATIN;
        cambiar_a_cordenadas_desocupadas(juego, &juego->herramientas[juego->cantidad_herramientas].posicion);
        cantidad_patines++; 
        juego->cantidad_herramientas++;   
    }
}
/*
*   Pre condiciones: -
*   Post condiciones: Inicializa el tipo de caracter de los charcos, asigna la posicion de cada charco y
*                     aumenta la cantidad de obstaculos hasta 5.
*/
void inicializar_charcos(juego_t* juego){
    int cantidad_charcos=0;
    while(cantidad_charcos<CANTIDAD_CHARCOS){
        juego->obstaculos[cantidad_charcos].tipo=CHARCO;
        cambiar_a_cordenadas_desocupadas(juego, &juego->obstaculos[juego->cantidad_obstaculos].posicion);
        cantidad_charcos++;
        juego->cantidad_obstaculos++;
    }
}
/*
* Pre condiciones: -
* Post condiciones: Inicializará el juego , cargando toda la información inicial de Linguini , las
* mesas , las herramientas y los obstáculos.
*/
void inicializar_juego(juego_t *juego){
    juego->dinero=0;
    juego->movimientos=0;
    juego->cantidad_mesas=0;
    juego->cantidad_herramientas=0;
    juego->cantidad_obstaculos=0;
    inicializar_campos_mesas(juego);
    inicializar_posiciones_mesas(juego);
    inicializar_posicion_cocina(juego);
    inicializar_campos_mozo(juego);
    inicializar_posicion_mozo(juego);
    inicializar_mopa(juego);
    inicializar_monedas(juego);
    inicializar_patines(juego);
    inicializar_charcos(juego);
}
/*
*   Pre condiciones: El terreno y juego debe estar previamente inicializado.
*   Post condiciones: Cambia el caracter del terreno en la posicion de cada elemento
*                     que tiene el juego.
*/
void cambiar_elementos_del_terreno(char terreno[MAX_FILAS][MAX_COLUMNAS], juego_t juego){
    for(int i=0; i < juego.cantidad_mesas; i++){
        for(int j=0; j < juego.mesas[i].cantidad_lugares; j++){
            reemplazar_elemento(terreno, MESA, juego.mesas[i].posicion[j]);
        }
    };
    reemplazar_elemento(terreno, COCINA, juego.cocina.posicion);
    reemplazar_elemento(terreno, juego.herramientas[LUGAR_MOPA].tipo, juego.herramientas[LUGAR_MOPA].posicion);
    for (int moneda = PRIMER_LUGAR_MONEDAS; moneda <= CANTIDAD_TOTAL_MONEDAS; moneda++){
        reemplazar_elemento(terreno, juego.herramientas[moneda].tipo, juego.herramientas[moneda].posicion);
    }
    for (int patin = PRIMER_LUGAR_PATINES; patin < juego.cantidad_herramientas; patin++){
        reemplazar_elemento(terreno, juego.herramientas[patin].tipo, juego.herramientas[patin].posicion);
    }
    for (int charco = 0; charco < juego.cantidad_obstaculos; charco++){
        reemplazar_elemento(terreno, juego.obstaculos[charco].tipo, juego.obstaculos[charco].posicion);
    }
    reemplazar_elemento(terreno, LINGUINI, juego.mozo.posicion);
}
/*
*   Pre condiciones: Juego debe estar inicializado y la acción debe ser una acción valida.
*   Post condiciones: Cancela el movimiento realizado, solo si a la posición que se dezplaza el mozo
*                     hay una mesa.
*/
void comprobar_dezplazamiento_valido(juego_t* juego, char accion){
    if (!posicion_sin_mesa(*juego, &juego->mozo.posicion) && accion==ACCION_ARRIBA){
        juego->mozo.posicion.fil++;
        juego->movimientos--;
    }
    if (!posicion_sin_mesa(*juego, &juego->mozo.posicion) && accion==ACCION_ABAJO){
        juego->mozo.posicion.fil--;
        juego->movimientos--;
    }
    if (!posicion_sin_mesa(*juego, &juego->mozo.posicion) && accion==ACCION_IZQUIERDA){
        juego->mozo.posicion.col++;
        juego->movimientos--;
    }
    if (!posicion_sin_mesa(*juego, &juego->mozo.posicion) && accion==ACCION_DERECHA){
        juego->mozo.posicion.col--;
        juego->movimientos--;
    }
}
/*
*   Pre condiciones: El campo mozo y movimientos de juego deben estar inicializados previamente.
*   Post condiciones: Dezplaza hacia arriba al mozo y suma un movimiento, luego comprueba que sea un
*                     dezplazamiento valido.
*/
void movimiento_hacia_arriba(juego_t* juego){
    juego->mozo.posicion.fil--;
    juego->movimientos++;
    comprobar_dezplazamiento_valido(juego, ACCION_ARRIBA);
}
/*
*   Pre condiciones: El campo mozo y movimientos de juego deben estar inicializados previamente.
*   Post condiciones: Dezplaza hacia abajo al mozo y suma un movimiento, luego comprueba que sea un
*                     dezplazamiento valido.
*/
void movimiento_hacia_abajo(juego_t* juego){
    juego->mozo.posicion.fil++;
    juego->movimientos++;
    comprobar_dezplazamiento_valido(juego, ACCION_ABAJO);
}
/*
*   Pre condiciones: El campo mozo y movimientos de juego deben estar inicializados previamente.
*   Post condiciones: Dezplaza hacia la derecha al mozo y suma un movimiento, luego comprueba que sea un
*                     dezplazamiento valido.
*/
void movimiento_hacia_derecha(juego_t* juego){
    juego->mozo.posicion.col++;
    juego->movimientos++;
    comprobar_dezplazamiento_valido(juego, ACCION_DERECHA);
}
/*
*   Pre condiciones: El campo mozo y movimientos de juego deben estar inicializados previamente.
*   Post condiciones: Dezplaza hacia la izquierda al mozo y suma un movimiento, luego comprueba que sea un
*                     dezplazamiento valido.
*/
void movimiento_hacia_izquierda(juego_t* juego){
    juego->mozo.posicion.col--;
    juego->movimientos++;
    comprobar_dezplazamiento_valido(juego, ACCION_IZQUIERDA);
}
/*
*   Pre condiciones: -
*   Post condiciones: Cambia el valor del campo tiene_mopa del campo mozo de juego a true, 
*                     luego establece la fila y columna de la posicion de la mopa en -1.
*/
void estado_mopa_recogida(juego_t* juego){
    juego->mozo.tiene_mopa=true;
    juego->herramientas[LUGAR_MOPA].posicion.fil=ENTERO_INVALIDO;
    juego->herramientas[LUGAR_MOPA].posicion.col=ENTERO_INVALIDO;
}
/*
*   Pre condiciones: -
*   Post condiciones: Cambia el valor del campo tiene_mopa del campo mozo de juego a false, 
*                     luego establece la fila y columna de la posicion de la mopa en la misma posición
*                     actual del mozo.
*/
void estado_mopa_soltada(juego_t* juego){
    juego->mozo.tiene_mopa=false;
    juego->herramientas[LUGAR_MOPA].posicion.fil=juego->mozo.posicion.fil;
    juego->herramientas[LUGAR_MOPA].posicion.col=juego->mozo.posicion.col;
}
/*
*   Pre condiciones: juego debe estar inicializado previamente con 'inicializar_juego', a su vez las poisiciones de la mopa
*                    y del mozo deben ser posiciones validas.
*   Post condiciones: Devuelve el valor booleano true si el mozo no tiene la mopa y  si las posiciones
*                     del mozo y la mopa son distintas. Caso contrario devuelve el valor false.
*/
bool mozo_sin_mopa_y_mozo_lejos_de_mopa(juego_t juego, coordenada_t posicion_mopa, coordenada_t posicion_mozo){
    return ((!juego.mozo.tiene_mopa) && (posicion_mopa.fil!=posicion_mozo.fil || posicion_mopa.col!=posicion_mozo.col));
}
/*
*   Pre condiciones: juego debe estar inicializado previamente con 'inicializar_juego', a su vez las poisiciones de la mopa
*                    y del mozo deben ser posiciones validas.
*   Post condiciones: Devuelve el valor booleano true si el mozo no tiene la mopa y  si las posiciones
*                     del mozo y la mopa son iguales. Caso contrario devuelve el valor false.
*/
bool mozo_sin_mopa_y_mozo_encima_de_mopa(juego_t juego, coordenada_t posicion_mopa, coordenada_t posicion_mozo){
    return ((!juego.mozo.tiene_mopa) && (posicion_mopa.fil==posicion_mozo.fil && posicion_mopa.col==posicion_mozo.col));
}
/*
*   Pre condiciones: juego debe estar inicializado previamente con 'inicializar_juego'.
*   Post condiciones: Devuelve el valor booleano true si el mozo tiene la mopa y  si las posiciones
*                     del mozo y la posicion del mozo no esta ocupada por otro elemento. 
*                     Caso contrario devuelve el valor false.
*/
bool mozo_con_mopa_y_coordenada_desocupada(juego_t* juego){
    return (juego->mozo.tiene_mopa && coordenada_no_ocupada(juego, &juego->mozo.posicion));
}
/*
*   Pre condiciones: Juego debe estar previamente inicializado con inicializar_juego.
*   Post condiciones: Evalua los casos de la mopa. Si el mozo no esta sobre la mopa y no se posee la mopa 
*                     imprime un mensaje al usuario. Dado el caso que no se posea mopa y el mozo esté encima   
*                     de la misma cambia el estado de la mopa e imprime un mensaje. En cambio si se posee la 
*                     mopa y no se esta encima de otro elemento se "suelta" la mopa en la posicion actual del
*                     mozo, ademas imrpime un mensaje al usuario, pero si esta encima de un elemento imprimira
*                     un mensaje al usuario.
*/
void accion_agarrar_o_soltar_mopa(juego_t* juego){
    coordenada_t posicion_mopa=juego->herramientas[LUGAR_MOPA].posicion;
    coordenada_t posicion_mozo=juego->mozo.posicion;
    if (mozo_sin_mopa_y_mozo_lejos_de_mopa(*juego, posicion_mopa, posicion_mozo)){
        printf("     ---¡¡¡NO PUEDES RECOGER LA MOPA, NO TE ENCUENTRAS ENCIMA DE ELLA!!!---\n");
    }else if (mozo_sin_mopa_y_mozo_encima_de_mopa(*juego, posicion_mopa, posicion_mozo)){
        estado_mopa_recogida(juego);
        printf("     ---RECOGISTE LA MOPA---\n");
    }else if (mozo_con_mopa_y_coordenada_desocupada(juego)){
        estado_mopa_soltada(juego);
        printf("     ---SOLTASTE LA MOPA EN TU POSICION ACTUAL---\n");
    }else
        printf("     ---¡¡¡NO PUEDES SOLTAR LA MOPA EN ESTA POSICION!!!---\n");  
}
/*
*   Pre condiciones: La accion debe ser una accion válida y la posicion debe ser el campo posicion del campo
*                    mozo de juego.
*   Post condiciones: Devuelve el valor booleano true si la accion es 'W' y la posicion no esta en la fila inicial,
*                     caso contrario devuelve el valor false.
*/
bool es_accion_arriba_y_no_sale_del_terreno(char accion, coordenada_t posicion){
    return ((accion==ACCION_ARRIBA) && (posicion.fil!=0));
}
/*
*   Pre condiciones: La accion debe ser una accion válida y la posicion debe ser el campo posicion del campo
*                    mozo de juego.
*   Post condiciones: Devuelve el valor booleano true si la accion es 'S' y la posicion no esta en la fila final,
*                     caso contrario devuelve el valor false.
*/
bool es_accion_abajo_y_no_sale_del_terreno(char accion, coordenada_t posicion){
    return ((accion==ACCION_ABAJO) && (posicion.fil!=(MAX_FILAS-1)));
}
/*
*   Pre condiciones: La accion debe ser una accion válida y la posicion debe ser el campo posicion del campo
*                    mozo de juego.
*   Post condiciones: Devuelve el valor booleano true si la accion es 'D' y la posicion no esta en la columna final,
*                     caso contrario devuelve el valor false.
*/
bool es_accion_derecha_y_no_sale_del_terreno(char accion, coordenada_t posicion){
    return ((accion==ACCION_DERECHA) && (posicion.col!=(MAX_COLUMNAS-1)));
}
/*
*   Pre condiciones: La accion debe ser una accion válida y la posicion debe ser el campo posicion del campo
*                    mozo de juego.
*   Post condiciones: Devuelve el valor booleano true si la accion es 'a' y la posicion no esta en la columna inicial,
*                     caso contrario devuelve el valor false.
*/
bool es_accion_izquierda_y_no_sale_del_terreno(char accion, coordenada_t posicion){
    return ((accion==ACCION_IZQUIERDA) && (posicion.col!=0));
}
/*
* Pre condiciones: El juego debe estar inicializado previamente con `inicializar_juego ` y la acción
* debe ser válida.
* Post condiciones: Realizará la acción recibida por parámetro. Para este primer TP solo se
* implementará el funcionamiento para mover al jugador y agarrar/soltar la mopa.
*/
void realizar_jugada(juego_t *juego , char accion){
    if (es_accion_arriba_y_no_sale_del_terreno(accion, juego->mozo.posicion)){
        movimiento_hacia_arriba(juego);
    }else if (es_accion_abajo_y_no_sale_del_terreno(accion, juego->mozo.posicion)){
        movimiento_hacia_abajo(juego);
    }else if (es_accion_derecha_y_no_sale_del_terreno(accion, juego->mozo.posicion)){
        movimiento_hacia_derecha(juego);
    }else if (es_accion_izquierda_y_no_sale_del_terreno(accion, juego->mozo.posicion)){
        movimiento_hacia_izquierda(juego);
    }else if (accion==AGARRA_O_SOLTAR_MOPA){
        accion_agarrar_o_soltar_mopa(juego);
    }
}
/*
* Pre condiciones: El juego deberá estar inicializado previamente con `inicializar_juego `
* Post condiciones: Devuelve:
*       --> 1 si es ganado
*       --> -1 si es perdido
*       --> 0 si se sigue jugando
* El juego se dará por ganado cuando se termina el día y se consiguieron las monedas necesarias.
* Se dará por perdido si se termina el día y no se llegó al monto.
*/
int estado_juego(juego_t juego){
    if (juego.movimientos==MAX_MOVIMIENTOS){
        return JUEGO_PERDIDO;
    }if (juego.dinero>=DINERO_NECESARIO){
        return JUEGO_GANADO;
    }
    return JUEGO_EN_CURSO;
}
/*
*   Pre condiciones: -
*   Post condiciones: Inicializa todas las posiciones de terreno con el elemento VACIO.
*/
void inicializar_terreno_vacio(char terreno[MAX_FILAS][MAX_COLUMNAS]){
    for (int i = 0; i < MAX_FILAS; i++){
        for (int j = 0; j < MAX_COLUMNAS; j++){
            terreno[i][j]=VACIO;
        }   
    }
}
/*
*   Pre condiciones: -
*   Post condiciones: Imprime por pantalla (por encima del terreno) las acciones validas para realizar.
*/
void imprimir_acciones_validas(){
    printf("\t\t\t---|ACCIONES VALIDAS|---\n");
    printf("|MOVERSE IZQUIERDA ⟹ 'A' | MOVERSE DERECHA ⟹ 'D' | MOVERSE ARRIBA ⟹ W | MOVERSE ABAJO ⟹ S | AGARRAR/SOLTAR MOPA ⟹ O|\n");
}
/*
*   Pre condiciones: -
*   Post condiciones: Imprime una linea entera del largo del terreno con el simbolo '='.
*/
void imprimir_barra(){
    for (int i = 0; i < LARGO_DEL_TERRENO_IMPRESO_EN_PANTALLA; i++){
        printf("=");
    }
    printf("\n");
}
/*
*   Pre condiciones: El terreno debe estar inicializado con los elementos de juego y juego debe estar
*                    inicializado con 'inicializar_juego'.
*   Post condiciones: Imprime por pantalla el terreno con una interfaz y a su vez a un costado la información
*                     de los pedidos.
*/
void imprimir_terreno_y_pedidos(char terreno[MAX_FILAS][MAX_COLUMNAS], juego_t juego){
    int mesa=0;
    for (int fila = 0; fila < MAX_FILAS; fila++){
        for (int columna = 0; columna < MAX_COLUMNAS; columna++){
            printf("|");
            printf(" %c ", terreno[fila][columna]);
            if (columna==(MAX_COLUMNAS-1)){
                printf("|  ");
                if ( fila%2==0){
                    printf("[PEDIDO MESA N°%i-%i]\n", (mesa+1), juego.mozo.pedidos[mesa].id_mesa);
                    mesa++;
                }else
                    printf("\n");
            }
        }   
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado con 'inicializar juego'.
*   Post condiciones: Devuelve el caracter VACIO si el mozo posee la mopa, caso contrario devuelve
*                     el caracter vacio.
*/
char caracter_mopa(juego_t juego){
    if (juego.mozo.tiene_mopa)
        return juego.herramientas[LUGAR_MOPA].tipo;
    return VACIO;
}
/*
*   Pre condiciones: juego debe estar previamente inicializado con 'inicializar juego'.
*   Post condiciones: Imprime por pantalla si el mozo posee la mopa, imprime la cantidad de movimientos
*                     realizados y el dinero obetnido.
*/
void imprimir_posesion_mopa_cant_mov_dinero(juego_t juego){
    printf("[MOPA:- %c -] ", caracter_mopa(juego));
    printf("[CANTIDAD DE MOVIMIENTOS: - %i -] ", juego.movimientos);
    printf("[DINERO: - $%i -] ",juego.dinero);
    printf("\n");
}
/*
* Pre condiciones: El juego debe estar inicializado previamente con `inicializar_juego `.
* Post condiciones: Imprime el juego por pantalla.
*/
void mostrar_juego(juego_t juego){
    char terreno[MAX_FILAS][MAX_COLUMNAS];
    inicializar_terreno_vacio(terreno);
    cambiar_elementos_del_terreno(terreno, juego);
    imprimir_acciones_validas();
    imprimir_barra();
    imprimir_terreno_y_pedidos(terreno, juego);
    imprimir_barra();
    imprimir_posesion_mopa_cant_mov_dinero(juego);
}
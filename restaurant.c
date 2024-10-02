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
*   Pre condiciones: El terreno tiene que estar inicializado con elementos validos, el elemento que recibe tiene que
*                    ser un ELEMENTO VALIDO.
*   Post condiciones: Reemplaza el caracter que esta en la fila y columna que vienen dados por posicion, el caracter
*                     reemplazado es el de elemento.   
*/
void reemplazar_elemento(char terreno[MAX_FILAS][MAX_COLUMNAS], char elemento, coordenada_t posicion){
    terreno[posicion.fil][posicion.col]=elemento;
}
/*
*   Pre condiciones: Las posiciones tienen que estar dentro de los limites del terreno.
*   Post condiciones: Chequea si las dos posiciones son distintas, si es asi devuelve true, caso
*                     contrario devuelve false.
*/
bool posiciones_distintas(coordenada_t primera_posicion, coordenada_t segunda_posicion){
    return ((primera_posicion.fil!=segunda_posicion.fil) || (primera_posicion.col!=segunda_posicion.col));
}
/*
*   Pre condiciones: Juego debe tener al menos una mesa inicializada.
*   Post condiciones: Chequea si hay una mesa en la posición ingresada, si hay una mesa en esa posicion
*                     devuelve un booleano con valor true, caso contrario devuelve el booleano con valor false.
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
*   Pre condiciones: Juego debe tener elementos inicializados con sus respectivas posiciones validas.
*   Post condiciones: Compara la posicion ingresada por referencia con cada posicion de cada elemento
*                     de juego, tambien establece que si tiene la misma direccion que con lo que se compara,
*                     procede a no compararar las posiciones, ya que si fueran exactamente la misma posicion siempre
*                     devolveria el booleano con valor falso. Luego si no hay elementos en la misma 
*                     posicion devuelve el valor true de la variable no_esta_ocupada, caso contrario 
*                     devuelve el valor false.
*/
bool coordenada_no_ocupada(juego_t* juego, coordenada_t* posicion){
    bool no_esta_ocupada=true;
    if (!posicion_sin_mesa(*juego, posicion)){
        no_esta_ocupada=false;
    }
    if (&juego->cocina.posicion!=posicion && no_esta_ocupada){
        no_esta_ocupada=posiciones_distintas(*posicion, juego->cocina.posicion);    
    }
    if (&juego->mozo.posicion!=posicion && no_esta_ocupada){
        no_esta_ocupada=posiciones_distintas(*posicion, juego->mozo.posicion); 
    }
    if (&juego->herramientas[LUGAR_MOPA].posicion!=posicion && no_esta_ocupada){
        no_esta_ocupada=posiciones_distintas(*posicion, juego->herramientas[LUGAR_MOPA].posicion);
    }
    int lugar_moneda = PRIMER_LUGAR_MONEDAS;
    while((no_esta_ocupada) && (lugar_moneda<=ULTIMO_LUGAR_MONEDAS)){
        if (&juego->herramientas[lugar_moneda].posicion!=posicion){
            no_esta_ocupada=posiciones_distintas(*posicion, juego->herramientas[lugar_moneda].posicion);
        }lugar_moneda++;   
    }
    int lugar_patin = PRIMER_LUGAR_PATINES;
    while ((no_esta_ocupada) && (lugar_patin<=ULTIMO_LUGAR_PATINES)){
        if (&juego->herramientas[lugar_patin].posicion!=posicion){
            no_esta_ocupada=posiciones_distintas(*posicion, juego->herramientas[lugar_patin].posicion);
        }lugar_patin++;
    }
    int lugar_charco = PRIMER_LUGAR_CHARCO;
    while ((no_esta_ocupada) && (lugar_charco<ULTIMO_LUGAR_CHARCO)){
        if (&juego->obstaculos[lugar_charco].posicion!=posicion){
            no_esta_ocupada=posiciones_distintas(*posicion, juego->obstaculos[lugar_charco].posicion);
        }lugar_charco++;
    }
    return no_esta_ocupada;
}
/*
*   Pre condiciones: La variable numero de mesas debe ser valido y estar en el rango del vector de mesas
*                    de juego.
*   Post condiciones: Chequea que alrededor de la nueva mesa no haya otras mesas, si hay una mesa al rededor
*                     devuelve el valor false de la variable sin_mesas_cerca, caso contrario devuelve el valor true. 
*/
bool validar_espacio_alrededor_de_mesas(juego_t juego, mesa_t nueva_mesa, int numero_de_mesas) {
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
*
 */
void cambiar_a_cordenadas_desocupadas(juego_t* juego, coordenada_t* posicion){
    do{
        posicion->fil= (rand() % TOTAL_NUMEROS_ALEATORIOS);
        posicion->col= (rand() % TOTAL_NUMEROS_ALEATORIOS);
    } while (!coordenada_no_ocupada(juego, posicion));
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
    /* MESAS */
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
    /* COCINA */
    cambiar_a_cordenadas_desocupadas(juego, &juego->cocina.posicion);
    /* LINGUINI */
    juego->mozo.tiene_mopa=false;
    juego->mozo.patines_puestos=false;
    juego->mozo.cantidad_patines=0;
    juego->mozo.cantidad_pedidos=0;
    juego->mozo.cantidad_bandeja=0;
    for (int i = 0; i < juego->cantidad_mesas; i++){
        juego->mozo.pedidos[i].cantidad_platos=0;
        juego->mozo.bandeja[i].cantidad_platos=0;
    }
    cambiar_a_cordenadas_desocupadas(juego, &juego->mozo.posicion);
    /* MOPA */
    juego->herramientas[LUGAR_MOPA].tipo=MOPA;
    cambiar_a_cordenadas_desocupadas(juego, &juego->herramientas[LUGAR_MOPA].posicion);
    juego->cantidad_herramientas++;
    /* MONEDAS */
    int cantidad_monedas=0;
    while(cantidad_monedas<CANTIDAD_TOTAL_MONEDAS){
        juego->herramientas[juego->cantidad_herramientas].tipo=MONEDA;
        cambiar_a_cordenadas_desocupadas(juego, &juego->herramientas[juego->cantidad_herramientas].posicion);
        cantidad_monedas++;
        juego->cantidad_herramientas++;
    }
    /* PATINES */
    int cantidad_patines=0;
    while(cantidad_patines<CANTIDAD_TOTAL_PATINES){
        juego->herramientas[juego->cantidad_herramientas].tipo=PATIN;
        cambiar_a_cordenadas_desocupadas(juego, &juego->herramientas[juego->cantidad_herramientas].posicion);
        cantidad_patines++; 
        juego->cantidad_herramientas++;   
    }
    /* CHARCOS */
    int cantidad_charcos=0;
    while(cantidad_charcos<CANTIDAD_CHARCOS){
        juego->obstaculos[cantidad_charcos].tipo=CHARCO;
        cambiar_a_cordenadas_desocupadas(juego, &juego->obstaculos[juego->cantidad_obstaculos].posicion);
        cantidad_charcos++;
        juego->cantidad_obstaculos++;
    }
}
/*
*   Pre condiciones: El terreno y juego debe estar previamente inicializado.
*   Post condiciones: Cambia el caracter del terreno en la posicion de cada elemento
*                     que tiene el juego.
*
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
* Pre condiciones: El juego debe estar inicializado previamente con `inicializar_juego ` y la acción
* debe ser válida.
* Post condiciones: Realizará la acción recibida por parámetro. Para este primer TP solo se
* implementará el funcionamiento para mover al jugador y agarrar/soltar la mopa.
*/
void realizar_jugada(juego_t *juego , char accion){

    while ((accion!= ACCION_ABAJO && accion!= ACCION_ARRIBA && accion!=ACCION_DERECHA && accion!=ACCION_IZQUIERDA && accion!=AGARRA_O_SOLTAR_MOPA)){
        mostrar_juego(*juego);
        printf("NO SE HA HECHO UNA ACCIÓN VALIDA, VUELVE A INTRODUCIR UNA ACCIÓN ⟹ ");
        scanf(" %c", &accion);
        system("clear");
    }
    chequeo_coordenada_valida(juego->mozo.posicion);
    if (accion==ACCION_ABAJO && juego->mozo.posicion.fil!=(MAX_FILAS-1)){
        juego->mozo.posicion.fil++;
        juego->movimientos++;
        if (!posicion_sin_mesa(*juego, &juego->mozo.posicion)){
            juego->mozo.posicion.fil--;
            juego->movimientos--;
        }
    }else if (accion==ACCION_ARRIBA && juego->mozo.posicion.fil!=0){
        juego->mozo.posicion.fil--;
        juego->movimientos++;
        if (!posicion_sin_mesa(*juego, &juego->mozo.posicion)){
            juego->mozo.posicion.fil++;
            juego->movimientos--;
        }
    }else if (accion==ACCION_DERECHA && juego->mozo.posicion.col!=(MAX_COLUMNAS-1)){
        juego->mozo.posicion.col++;
        juego->movimientos++;
        if (!posicion_sin_mesa(*juego, &juego->mozo.posicion)){
            juego->mozo.posicion.col--;
            juego->movimientos--;
        }
    }else if (accion==ACCION_IZQUIERDA && juego->mozo.posicion.col!=0){
        juego->mozo.posicion.col--;
        juego->movimientos++;
        if (!posicion_sin_mesa(*juego, &juego->mozo.posicion)){
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
            juego->herramientas[LUGAR_MOPA].posicion.fil=ENTERO_INVALIDO;
            juego->herramientas[LUGAR_MOPA].posicion.col=ENTERO_INVALIDO;
        }else if (juego->mozo.tiene_mopa && coordenada_no_ocupada(juego, &juego->mozo.posicion)){
                juego->mozo.tiene_mopa=false;
                juego->herramientas[LUGAR_MOPA].posicion.fil=juego->mozo.posicion.fil;
                juego->herramientas[LUGAR_MOPA].posicion.col=juego->mozo.posicion.col;
                printf("     ---SOLTASTE LA MOPA EN TU POSICION ACTUAL---\n");
        }else
            printf("     ---¡¡¡NO PUEDES SOLTAR LA MOPA EN ESTA POSICION!!!---\n");  
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
* Pre condiciones: El juego debe estar inicializado previamente con `inicializar_juego `.
* Post condiciones: Imprime el juego por pantalla.
*/
void mostrar_juego(juego_t juego){
    char terreno[MAX_FILAS][MAX_COLUMNAS];
    for (int i = 0; i < MAX_FILAS; i++){
        for (int j = 0; j < MAX_COLUMNAS; j++){
            terreno[i][j]=VACIO;
        }   
    }
    cambiar_elementos_del_terreno(terreno, juego);
    printf("     ---|ACCIONES VALIDAS|---\n");
    printf("|MOVERSE IZQUIERDA ⟹ 'A' | MOVERSE DERECHA ⟹ 'D' | MOVERSE ARRIBA ⟹ W | MOVERSE ABAJO ⟹ S | AGARRAR/SOLTAR MOPA ⟹ O|\n");
    for (int i = 0; i < LARGO_DEL_TERRENO_IMPRESO_EN_PANTALLA; i++){
        printf("=");
    }
    printf("\n");
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
    }for (int i = 0; i < LARGO_DEL_TERRENO_IMPRESO_EN_PANTALLA; i++){
        printf("=");
    }
    printf("\n");
    char mopa=VACIO;
    if (juego.mozo.tiene_mopa)
        mopa=MOPA;
    else
        mopa=VACIO;
    printf("[CANTIDAD DE MOVIMIENTOS: - %i -] ", juego.movimientos);
    printf("[MOPA:- %c -] ", mopa);
    printf("[DINERO: - $%i -] ",juego.dinero);
    printf("\n");
}
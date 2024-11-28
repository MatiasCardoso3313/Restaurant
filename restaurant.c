#include<stdio.h>
#include<stdlib.h>
#include "restaurant.h"

#define REINICIO_COLOR "\033[0m"
#define ROJO_COLOR "\033[31m"
#define VERDE_COLOR "\033[32m"
#define AMARILLO_COLOR "\033[33m"
#define AZUL_COLOR "\033[34m"
#define MAGENTA_COLOR "\033[35m"
#define CYAN_COLOR "\033[36m"
#define TEXTO_NEGRITA "\033[1m"

/* ESTADO DE JUEGO */
const int JUEGO_EN_CURSO=0;
const int JUEGO_PERDIDO=-1;
const int JUEGO_GANADO=1;
/* CONVENCIONES */
const int UNIDAD=1;
const int RANGO_DE_PACIENCIA=101;
const int RANGO_COMENSALES=4;
const int PACIENCIA_MINIMA=100;
const int MINIMOS_COMENSALES=1;
const int LARGO_DEL_TERRENO_IMPRESO_EN_PANTALLA = 81;
const int ENTERO_INVALIDO=-1;
const int DISTANCIA_MINIMA_MESAS=1;
const int DISTANCIA_MINIMA_CUCARACHA_DE_MESA=2;
const int TOTAL_NUMEROS_ALEATORIOS=19;
const int MAX_MOVIMIENTOS = 200;
const int TIEMPO_TERMINADO=0;
const int VALOR_NULO=0;
const int PIRMERA_POS=0;
const int SIN_COMENSALES=0;
const int SIN_PEDIDOS=0;
const int SIN_PLATOS=0;
const int DINERO_DE_MONEDAS=1000;
const int INDIVIDUAL_VALOR_MESA=5000;
const int CUATRO_VALOR_MESA=20000;
const int DINERO_NECESARIO = 150000;
const int FUNC_DESPLAZAMIENTO_CON_PATIN=5;
const int FUNC_REALIZAR_JUGADA=-5;
const int ANSIEDAD_POR_CUCARACHA=2;
const int TIEMPO_LLEGADA_COMENSAL=15;
const int TIEMPO_LLEGADA_CUCA=25;
const int PRIMERA_FILA=0;
const int PRIMERA_COLULMNA=0;
const int RANGO_PLATOS=4;
const int PEDIDO_MINIMO=1;
/* ELEMENTOS VALIDOS */
const char MOPA='O';
const char MONEDA='M';
const char PATIN='P';
const char MESA='T';
const char CHARCO='H';
const char LINGUINI='L';
const char COCINA='C';
const char CUCARACHA='U';
const char VACIO=' ';
const char LUGAR_OCUPADO='X';
/* POSICION EN VECTORES */
const int LUGAR_INICIAL_MOPA= 0;
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
const char TOMAR_PEDIDO='T';
const char PONERSE_PATINES='P';
/* RELACIONADO A PLATOS */
const char MILANESA_NAPO='M';
const int MILANESA_NAPO_REP=1;
const int TIMER_MILANESA_NAPO=30;
const char HAMBURGUESA='H';
const int HAMBURGUESA_REP=2;
const int TIMER_HAMBURGUESA=15;
const char PARRILLA='P';
const int PARRILLA_REP=3;
const int TIMER_PARRILLA=20;
const char RATATOUILLE='R';
const int RATATOUILLE_REP=4;
const int TIMER_RATATOUILLE=25;

/*
*   Pre condiciones: tope debe ser un numero mayor o igual a 0, elemento buscado debe ser un elemento valido.
*   Post condiciones: Devuelve true si el elemento buscado se encuentra en el vector objetos, en caso 
*                    contrario devuelve false.
*/
bool elemento_esta(objeto_t objetos[], int tope , char elemento_buscado){
	int i =VALOR_NULO;
	int esta = false;
	while((!esta ) && (i < tope ) ) {
		if ( objetos[i].tipo== elemento_buscado){
			esta = true;   
        }
		i++;
	}
	return esta;
}	
/*
*   Pre condiciones:tope debe ser mayor o igual a 0, elemento_buscado debe ser un elemento valido.
*   Post condiciones: Busca la primera posicion del elemento_buscado y lo devuelve, si no encuentra el 
*                    elemento devuelve -1.
*/
int primera_pos_elemento(objeto_t objetos[], int tope , char elemento_buscado){
	int i =VALOR_NULO;
    int pos_elemento=ENTERO_INVALIDO;
	bool esta = elemento_esta(objetos, tope, elemento_buscado);
	while((i<tope) && pos_elemento==ENTERO_INVALIDO && esta){
		if ( objetos[i].tipo==elemento_buscado){
			pos_elemento=i;
        }
		i++;
	}
    if (pos_elemento==ENTERO_INVALIDO){
        return ENTERO_INVALIDO;
    }
	return pos_elemento;
}	
/*
*   Pre condiciones: pos_elemento debe ser una posicion mayor o igual a 0 y menor que el valor de tope. Tope
*                   debe ser mayor o igual a cero.
*   Post condiciones: Se elimina fisica el elemento en la pos_elemento dada y disminuye el valor del tope en 1
*/
void eliminar_elemento_especifico(objeto_t objetos[], int pos_elemento, int* tope){
    for (int i = pos_elemento; i < *tope; i++){
        objetos[i].tipo=objetos[i+1].tipo;
        objetos[i].posicion=objetos[i+1].posicion;
    }*tope-=1;
    
}
/*
*   Pre condiciones: elemento_a_eliminar debe ser un elemento valido, tope debe ser un numero mayor o igual a 0.
*   Post condiciones: Elimina fisicamente el primero elemento que sea igual a elemento_a_eliminar, luego baja el valor de tope en 1.
*/
void eliminar_elemento( objeto_t objetos[] , char elemento_a_eliminar , int* tope ) {
	bool esta = elemento_esta(objetos, *tope, elemento_a_eliminar);
    int pos=ENTERO_INVALIDO;
    if(esta)
	    pos=primera_pos_elemento(objetos, *tope, elemento_a_eliminar);
	if(esta){
		for (int i = pos ; i < (*tope)-1 ; i++ ){
            objetos[i].tipo= objetos[i+1].tipo;
            objetos[i].posicion= objetos[i+1].posicion;
        }
        *tope-=1;
	}
}
/*
*   Pre condiciones: pos_pedido debe ser un numero mayor o igual a cero y menor que el valor de tope, tope debe ser
*                   mayor o igual a 0.
*   Post condiciones: Elimina el pedido en la posicion dada por parametro, luego baja el valor de tope en 1.
*/
void eliminar_pedido( pedido_t pedidos[] ,int pos_pedido, int* tope ) {
    for (int i = pos_pedido; i < *tope; i++){
        pedidos[i] = pedidos[i+1];
    }
    *tope-=UNIDAD;  
}
/*
*   Pre condiciones: tipo_elemento debe ser un elemento valido, tope_objetos debe ser mayor o igual a 0.
*   Post condiciones: Cuenta la cantidad de elementos que hay en objetos y devuelve esa cantidad.
*/
int cantidad_elemento(objeto_t objetos[], char tipo_elemento, int tope_objetos){
    int cant_elemento=VALOR_NULO;
    for (int i = 0; i < tope_objetos; i++){
        if (objetos[i].tipo==tipo_elemento)
            cant_elemento++;
    }
    return cant_elemento;
}
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
bool posicion_sin_mesa(mesa_t mesa[], coordenada_t* posicion, int cant_mesa){
    bool no_hay_mesa=true;
    int i=VALOR_NULO;
    while((i<cant_mesa) && (no_hay_mesa)){
        int j=VALOR_NULO;
        while(j<mesa[i].cantidad_lugares && (no_hay_mesa)){
            no_hay_mesa=posiciones_distintas(*posicion, mesa[i].posicion[j]);
            j++;
        }i++;
    }return no_hay_mesa;
}
/*
*   Pre condiciones: Ambas posiciones deben ser posiciones validas y perteneces a elementos de juego.
*   Post condiciones: Devuelve true si la dirección de primera_posicion y la dirección de segunda_posicion son 
*                     distintas, y si los valores de sus campos tambien son iguales. Caso contrario devuelve false.
*/
bool coordenada_ocupada(coordenada_t* primera_posicion, coordenada_t* segunda_posicion){
    return((primera_posicion!=segunda_posicion) && (!posiciones_distintas(*primera_posicion, *segunda_posicion)));
}
/*
*   Pre condiciones: -
*   Post condiciones: Devuelve true si pos es mayor a 0 (inclusive) y menor a tope (estricto), caso contrario devuelve false.
*/
bool pos_vector_valida(int pos, int tope){
    return pos>=PIRMERA_POS && pos<tope;
}
/*
*   Pre condiciones: El campo de posición de los campos de las monedas de juego debe estar inicializado y posición debe
*                    ser una posición válida.
*   Post condiciones: Devuelve true si la dirección de posición y la dirección de posición de las monedas son 
*                     distintas, y si los valores tambien son distintos. Caso contrario devuelve false.
*/
bool coordenada_libre_de_moneda(objeto_t herramientas[], coordenada_t* posicion, int cant_herramientas){
    bool no_esta_ocupada=true;
    int lugar_moneda;
    int cant_monedas=cantidad_elemento(herramientas, MONEDA, cant_herramientas);
    if (elemento_esta(herramientas, cant_herramientas, MONEDA))
        lugar_moneda = primera_pos_elemento(herramientas, cant_herramientas, MONEDA);
    else
        return no_esta_ocupada;
    while((no_esta_ocupada) && (lugar_moneda<(lugar_moneda+cant_monedas)) && pos_vector_valida(lugar_moneda, cant_herramientas)){
        if (&herramientas[lugar_moneda].posicion!=posicion){
            no_esta_ocupada=posiciones_distintas(*posicion, herramientas[lugar_moneda].posicion);
        }lugar_moneda++;   
    }
    return no_esta_ocupada;
}
/*
*   Pre condiciones: El campo de posición de los campos de los patines de juego debe estar inicializado y posición debe
*                    ser una posición válida.
*   Post condiciones: Devuelve true si la dirección de posición y la dirección de posición de los patines son 
*                     distintas, y si los valores tambien son distintos. Caso contrario devuelve false.
*/
bool coordenada_libre_de_patin(objeto_t herramientas[], coordenada_t* posicion, int cant_herramientas){
    bool no_esta_ocupada=true;
    int lugar_patin = primera_pos_elemento(herramientas, cant_herramientas, PATIN);
    int cant_patines=cantidad_elemento(herramientas, PATIN, cant_herramientas);
    while ((no_esta_ocupada) && (lugar_patin<(lugar_patin+cant_patines)) && pos_vector_valida(lugar_patin, cant_herramientas)){
        if (&herramientas[lugar_patin].posicion!=posicion){
            no_esta_ocupada=posiciones_distintas(*posicion, herramientas[lugar_patin].posicion);
        }lugar_patin++;
    }
    return no_esta_ocupada;
}
/*
*   Pre condiciones: El campo de posición de los campos de los charcos de juego debe estar inicializado y posición debe
*                    ser una posición válida.
*   Post condiciones: Devuelve true si la dirección de posición y la dirección de posición de los charcos son 
*                     distintas, y si los valores tambien son distintos. Caso contrario devuelve false.
*/
bool coordenada_libre_de_charco(objeto_t obstaculos[], coordenada_t* posicion, int cant_obstaculos){
    bool no_esta_ocupada=true;
    int lugar_charco = primera_pos_elemento(obstaculos, cant_obstaculos, CHARCO);
    int cant_charcos = cantidad_elemento(obstaculos, CHARCO, cant_obstaculos);
    while ((no_esta_ocupada) && (lugar_charco<(lugar_charco+cant_charcos)) && pos_vector_valida(lugar_charco, cant_obstaculos)){
        if (&obstaculos[lugar_charco].posicion!=posicion){
            no_esta_ocupada=posiciones_distintas(*posicion, obstaculos[lugar_charco].posicion);
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
    if(!(posicion_sin_mesa(juego->mesas, posicion, juego->cantidad_mesas)) || (coordenada_ocupada(&juego->cocina.posicion, posicion)) ||(coordenada_ocupada(&juego->mozo.posicion, posicion)) || (coordenada_ocupada(&juego->herramientas[primera_pos_elemento(juego->herramientas, juego->cantidad_herramientas, MOPA)].posicion, posicion)) || !(coordenada_libre_de_moneda(juego->herramientas, posicion, juego->cantidad_herramientas)) || (!coordenada_libre_de_patin(juego->herramientas, posicion, juego->cantidad_herramientas)) || !(coordenada_libre_de_charco(juego->obstaculos, posicion, juego->cantidad_obstaculos)))
        return false;
    return true;
}
/*
*   Pre condiciones: juego debe estar previamente inicializado, el valor de tope debe ser mayor o igual a 0, 
*                   elemento_a_insertar debe ser un elemento valido.
*   Post condiciones: Inserta el nuevo elemento al final de objetos.
*/
void insertar_elemento_final(juego_t* juego, objeto_t objetos[], int *tope, char elemento_a_insertar) {
    objetos[*tope].tipo= elemento_a_insertar;
    if (elemento_a_insertar==MOPA && coordenada_no_ocupada(juego, &juego->mozo.posicion)){
        objetos[*tope].posicion=juego->mozo.posicion;
    }
    (*tope)++;
}
/*
*   Pre condiciones: La variable numero de mesas debe ser valido y estar en el rango del vector de mesas
*                    de juego.
*   Post condiciones: Chequea que alrededor de la nueva mesa no haya otras mesas, si hay una mesa al rededor
*                     devuelve el valor false de la variable sin_mesas_cerca, caso contrario devuelve el valor true. 
*/
bool validar_espacio_alrededor_de_mesas(mesa_t mesas[], mesa_t nueva_mesa, int numero_de_mesas){
    bool sin_mesas_cerca=true;
    int mesa_anterior=PIRMERA_POS;
    while(mesa_anterior<numero_de_mesas && sin_mesas_cerca){
        mesa_t mesa = mesas[mesa_anterior];
        int i=VALOR_NULO;
        while(i < mesa.cantidad_lugares && sin_mesas_cerca){
            coordenada_t posicion = mesa.posicion[i];   
            int j=VALOR_NULO;
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
    if ((posicion.fil>=PIRMERA_POS && posicion.fil<MAX_FILAS) && (posicion.col>=0 && posicion.col<MAX_COLUMNAS)){
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
void inicializar_campos_mesas(mesa_t mesas[], int* cantidad_mesas){
    while(*cantidad_mesas<(TOTAL_MESAS_INDIVIDUALES + TOTAL_MESAS_DE_CUATRO)){
        mesas[*cantidad_mesas].pedido_tomado=false;
        mesas[*cantidad_mesas].paciencia=VALOR_NULO;
        if (*cantidad_mesas<TOTAL_MESAS_INDIVIDUALES){
            mesas[*cantidad_mesas].cantidad_comensales=SIN_COMENSALES;
            mesas[*cantidad_mesas].cantidad_lugares=MIN_COMENSALES;
        }else{
            mesas[*cantidad_mesas].cantidad_comensales=SIN_COMENSALES;
            mesas[*cantidad_mesas].cantidad_lugares=MAX_COMENSALES;
        }
        *cantidad_mesas+=1;
    }
}
/*
*   Pre codiciones: juego debe estar previamente inicializado. mesa debe ser mayor o igual a 0 y menor
*                 estricto que "juego->cantidad_mesas".
*   Post condiciones: Asigna una posicion valida en el campo posicion del campo mesa de juego hasta
*                    que se halle una posicion que no sea adyacente a otras mesas.
*/
void asignar_pos_mesas_individuales(coordenada_t posicion, mesa_t mesas[], int mesa){
    do{
        posicion.fil = (rand() % TOTAL_NUMEROS_ALEATORIOS);
        posicion.col = (rand() % TOTAL_NUMEROS_ALEATORIOS);
        modificar_posicion(posicion, mesas[mesa].posicion);
    }while (!validar_espacio_alrededor_de_mesas(mesas, mesas[mesa], mesa));
}
/*
*   Pre codiciones: juego debe estar previamente inicializado. mesa debe ser mayor o igual a 0 y menor
*                 estricto que "juego->cantidad_mesas".
*   Post condiciones: Asigna una posicion valida a cada campo posicion (04) del campo mesa de juego hasta
*                    que se hallen las posicion que no sean adyacente a otras mesas y no salgan del terreno.
*/
void asignar_pos_mesas_cuatro(coordenada_t posicion, mesa_t mesas[], int mesa){
    do{
        posicion.col = (rand() % TOTAL_NUMEROS_ALEATORIOS);
        posicion.fil = (rand() % TOTAL_NUMEROS_ALEATORIOS);
        for(int j=VALOR_NULO; j < MAX_COMENSALES;j++){
            if (j==1)
                posicion.col++;
            else if (j==2){
                posicion.fil++; posicion.col--;
            }else if (j==3)
                posicion.col++;
            modificar_posicion(posicion, &mesas[mesa].posicion[j]);
        }
    }while (!(chequeo_coordenada_valida(*mesas[mesa].posicion)) || !validar_espacio_alrededor_de_mesas(mesas, mesas[mesa], mesa));
}
/*
*   Pre condiciones: El campo cantidad_mesas de juego debe estar inicializado con un valor mayor a 0.
*   Post condiciones: Asigna a las mesas sus posiciones.
*/
void inicializar_posiciones_mesas(mesa_t mesas[], int cantidad_mesas){
    for(int a=VALOR_NULO; a<cantidad_mesas; a++){
        coordenada_t posicion;
        posicion.fil=ENTERO_INVALIDO;
        posicion.col=ENTERO_INVALIDO;
        if((mesas[a].cantidad_lugares) == MIN_COMENSALES){
            asignar_pos_mesas_individuales(posicion, mesas, a);
        }else if (mesas[a].cantidad_lugares==MAX_COMENSALES){
            asignar_pos_mesas_cuatro(posicion, mesas, a);
        }
    }
}
/*
*   Pre condiciones: -
*   Post condiciones: Inicializa los campos: cant_peparacion en 0, cantidad_listos en 0, 
*                    platos_preparacion en NULL, platos_listos en NULL, del campo cocina de juego.
*/
void inicializar_campos_cocina(cocina_t* cocina){
    cocina->cantidad_preparacion=VALOR_NULO;
    cocina->cantidad_listos=VALOR_NULO;
    cocina->platos_preparacion=NULL;
    cocina->platos_listos=NULL;
}

/*
*   Pre condiciones: -
*   Post condiciones: Asigna a la cocina una posición. 
*/
void inicializar_posicion_cocina(juego_t* juego){
    cambiar_a_cordenadas_desocupadas(juego, &juego->cocina.posicion);
}
/*
*   Pre condiciones: El campo cantidad_mesas de juego debe estar inicializada con un valor mayor a 0.
*   Post condiciones: Inicializa los campos del campo mozo de juego.
*/
void inicializar_campos_mozo(mozo_t* mozo){
    mozo->tiene_mopa=false;
    mozo->patines_puestos=false;
    mozo->cantidad_patines=VALOR_NULO;
    mozo->cantidad_pedidos=VALOR_NULO;
    mozo->cantidad_bandeja=VALOR_NULO;
    for (int i = VALOR_NULO; i < MAX_PEDIDOS; i++){
        mozo->pedidos[i].cantidad_platos=VALOR_NULO;
        mozo->bandeja[i].cantidad_platos=VALOR_NULO;
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
    juego->herramientas[LUGAR_INICIAL_MOPA].tipo=MOPA;
    cambiar_a_cordenadas_desocupadas(juego, &juego->herramientas[LUGAR_INICIAL_MOPA].posicion);
    juego->cantidad_herramientas++;
}
/*
*   Pre condiciones: -
*   Post condiciones: Inicializa el tipo de caracter de las monedas, asigna la posicion de cada moneda
*                     y aumenta la cantidad de herramientas 9.
*/
void inicializar_monedas(juego_t* juego){
    int cantidad_monedas=VALOR_NULO;
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
    int cantidad_patines=VALOR_NULO;
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
    int cantidad_charcos=VALOR_NULO;
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
    juego->dinero=VALOR_NULO;
    juego->movimientos=VALOR_NULO;
    juego->cantidad_mesas=VALOR_NULO;
    juego->cantidad_herramientas=VALOR_NULO;
    juego->cantidad_obstaculos=VALOR_NULO;
    inicializar_campos_mesas(juego->mesas, &juego->cantidad_mesas);
    inicializar_posiciones_mesas(juego->mesas, juego->cantidad_mesas);
    inicializar_campos_cocina(&juego->cocina);
    inicializar_posicion_cocina(juego);
    inicializar_campos_mozo(&juego->mozo);
    inicializar_posicion_mozo(juego);
    inicializar_mopa(juego);
    inicializar_monedas(juego);
    inicializar_patines(juego);
    inicializar_charcos(juego);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado con inicializar_juego.
*   Post condiciones:
*/
void colocar_mesas(mesa_t mesas[], int cantidad_mesas, char terreno[MAX_FILAS][MAX_COLUMNAS]){
        for(int i=0; i < cantidad_mesas; i++){
        for(int j=0; j < mesas[i].cantidad_lugares; j++){
            if (mesas[i].cantidad_comensales>SIN_COMENSALES && j<mesas[i].cantidad_comensales)
                reemplazar_elemento(terreno, LUGAR_OCUPADO, mesas[i].posicion[j]);
            else
                reemplazar_elemento(terreno, MESA, mesas[i].posicion[j]);
        }
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado con inicializar_juego.
*   Post condiciones: Cambia el caracter del terreno en las posiciones de cada mesa.
*/
void colocar_mopa(objeto_t herramientas[], char terreno[MAX_FILAS][MAX_COLUMNAS], int cantidad_herramientas, bool mozo_con_mopa){
    if(!mozo_con_mopa)
        reemplazar_elemento(terreno, herramientas[primera_pos_elemento(herramientas, cantidad_herramientas, MOPA)].tipo, herramientas[primera_pos_elemento(herramientas, cantidad_herramientas, MOPA)].posicion);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado con inicializar_juego.
*   Post condiciones: Cambia el caracter del terreno en las posiciones de cada moneda.
*/
void colocar_monedas(objeto_t herramientas[], char terreno[MAX_FILAS][MAX_COLUMNAS], int cantidad_herramientas){
    int primer_lugar_moneda=primera_pos_elemento(herramientas, cantidad_herramientas, MONEDA);
    int cant_monedas=cantidad_elemento(herramientas, MONEDA, cantidad_herramientas);
    for (int moneda = primer_lugar_moneda; moneda <( primer_lugar_moneda+cant_monedas); moneda++){
        reemplazar_elemento(terreno, herramientas[moneda].tipo, herramientas[moneda].posicion);
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado con inicializar_juego.
*   Post condiciones: Cambia el caracter del terreno en las posiciones de cada patin.
*/
void colocar_patines(objeto_t herramientas[], char terreno[MAX_FILAS][MAX_COLUMNAS], int cantidad_herramientas){
    int primer_lugar_patines=primera_pos_elemento(herramientas, cantidad_herramientas, PATIN);
    int cant_patines=cantidad_elemento(herramientas, PATIN, cantidad_herramientas);
    for (int patin = primer_lugar_patines; patin < (primer_lugar_patines+cant_patines); patin++)
        reemplazar_elemento(terreno, herramientas[patin].tipo, herramientas[patin].posicion);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado con inicializar_juego.
*   Post condiciones: Cambia el caracter del terreno en las posiciones de cada charco.
*/
void colocar_charcos(objeto_t obstaculos[], char terreno[MAX_FILAS][MAX_COLUMNAS], int cantidad_obstaculos){
    for (int charco = VALOR_NULO; charco < cantidad_obstaculos; charco++)
        reemplazar_elemento(terreno, obstaculos[charco].tipo, obstaculos[charco].posicion);
}
/*
*   Pre condiciones: El terreno y juego debe estar previamente inicializado, juego con 'inicializar_juego'.
*   Post condiciones: Cambia el caracter del terreno en la posicion de cada elemento
*                     que tiene el juego.
*/
void cambiar_elementos_del_terreno(char terreno[MAX_FILAS][MAX_COLUMNAS], juego_t juego){
    colocar_mesas(juego.mesas, juego.cantidad_mesas, terreno);
    reemplazar_elemento(terreno, COCINA, juego.cocina.posicion);
    colocar_mopa(juego.herramientas, terreno, juego.cantidad_herramientas, juego.mozo.tiene_mopa);
    colocar_monedas(juego.herramientas, terreno, juego.cantidad_herramientas);
    colocar_patines(juego.herramientas, terreno, juego.cantidad_herramientas);
    colocar_charcos(juego.obstaculos, terreno, juego.cantidad_obstaculos);
    reemplazar_elemento(terreno, LINGUINI, juego.mozo.posicion);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado y accion debe ser
*                   una acción valida.
*   Post condiciones: Devuelve false si en la posicion a la que se desplaza el mozo
*                    hay una mesa en el camino. En otro caso devuelve true.
*/
bool chequeo_dezplazamiento_valido(mesa_t mesas[], coordenada_t* pos_mozo, int cantidad_mesas, char accion){
    bool fue_valido=true;
    if (!posicion_sin_mesa(mesas, pos_mozo, cantidad_mesas) && accion==ACCION_ARRIBA){
        fue_valido=false;
    }
    if (!posicion_sin_mesa(mesas, pos_mozo, cantidad_mesas) && accion==ACCION_ABAJO){
        fue_valido=false;
    }
    if (!posicion_sin_mesa(mesas, pos_mozo, cantidad_mesas) && accion==ACCION_IZQUIERDA){
        fue_valido=false;
    }
    if (!posicion_sin_mesa(mesas, pos_mozo, cantidad_mesas) && accion==ACCION_DERECHA){
        fue_valido=false;
    }return fue_valido;
}
/*
*   Pre condiciones: Juego debe estar inicializado y la acción debe ser una acción valida.
*   Post condiciones: Cancela el movimiento realizado, solo si a la posición que se dezplaza el mozo
*                     hay una mesa.
*/
void comprobar_dezplazamiento_valido(mesa_t mesas[], coordenada_t* pos_mozo, int cantidad_mesas, int* movimientos, char accion){
    if (!posicion_sin_mesa(mesas, pos_mozo, cantidad_mesas) && accion==ACCION_ARRIBA){
        pos_mozo->fil+=UNIDAD;
        *movimientos-=UNIDAD;
    }
    if (!posicion_sin_mesa(mesas, pos_mozo, cantidad_mesas) && accion==ACCION_ABAJO){
        pos_mozo->fil-=UNIDAD;
        *movimientos-=UNIDAD;
    }
    if (!posicion_sin_mesa(mesas, pos_mozo, cantidad_mesas) && accion==ACCION_IZQUIERDA){
        pos_mozo->col+=UNIDAD;
        *movimientos-=UNIDAD;
    }
    if (!posicion_sin_mesa(mesas, pos_mozo, cantidad_mesas) && accion==ACCION_DERECHA){
        pos_mozo->col-=UNIDAD;
        *movimientos-=UNIDAD;
    }
}
/*
*   Pre condiciones: cant_comensales_entrantes debe ser un numero entre 1 y 4, ambos inclusives. pos_mesa debe ser un numero
*                   mayor o igual a 0 y menor que 10, juego debe estar previamente inicializado.
*   Post condiciones: Devuelve true si la cant_comensales_entrantes es igual a 1 y si la mesa no tiene comensales ocupandola, caso
*                    contrario devuelve false.
*/
bool un_comensal_y_mesa_sin_comensales(mesa_t mesas[], int cant_comensales_entrantes, int pos_mesa){
    return(cant_comensales_entrantes==MIN_COMENSALES && mesas[pos_mesa].cantidad_comensales==SIN_COMENSALES);
}
/*
*   Pre condiciones: cant_comensales_entrantes debe ser un numero entre 1 y 4, ambos inclusives. pos_mesa debe ser un numero
*                   mayor o igual a 0 y menor que 10, juego debe estar previamente inicializado.
*   Post condiciones: Devuelve true si la cant_comensales_entrantes es mayor a 1 y si la mesa no tiene comensales ocupandola, caso
*                    contrario devuelve false.
*/
bool mas_de_un_comensal_y_mesa_sin_comensales(mesa_t mesas[], int cant_comensales_entrantes, int pos_mesa){
    return (cant_comensales_entrantes>=MIN_COMENSALES && mesas[pos_mesa].cantidad_comensales==SIN_COMENSALES);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado, pos_mesa debe ser mayor o igual a cero y menor que 10, 
*                   cant_comensales_entrantes deben ser mayor o igual a 1 o menor o igual a 4.
*   Post condiciones: Establece los campos cant_comensales, pedido_tomado y paciencia del campo mesas de juego.
*/
void asignar_comensales_mesa(mesa_t mesas[], int pos_mesa, int cant_comensales_entrantes){
    mesas[pos_mesa].cantidad_comensales=cant_comensales_entrantes;
    mesas[pos_mesa].pedido_tomado=false;
    mesas[pos_mesa].paciencia=(rand() % RANGO_DE_PACIENCIA) + PACIENCIA_MINIMA;
}
/*
*   Pre condiciones: juego debe estar previamente inicializado, cant_comensales_entrantes debe
*                   ser un entero entre 1 y 4 ambos inclusives, mesa debe ser un entero mayor igual
*                   a 0 y menor que juego->cantidad_mesas.
*   Post condiciones: Si los comensales son igual a 1 se asignan en mesas de 1 lugar, salvo caso que 
*                    todas las mesas de 1 estén llenas se colocan en una de 4 lugares. En caso que los
*                    comensales sean mayor a 1 se asignan en mesas de 4 lugares. Si no hay mesas disponibles.
*                    para los comensales se iran.
*/
void comensales_buscan_mesas(mesa_t mesas[], int cant_comensales_entrantes, int mesa, bool* mesa_encontrada){
    if (un_comensal_y_mesa_sin_comensales(mesas, cant_comensales_entrantes, mesa)){
        asignar_comensales_mesa(mesas, mesa, cant_comensales_entrantes);
        *mesa_encontrada=true;
    }else if (mas_de_un_comensal_y_mesa_sin_comensales(mesas, cant_comensales_entrantes, mesa) && mesas[mesa].cantidad_lugares>MIN_COMENSALES){
        asignar_comensales_mesa(mesas, mesa, cant_comensales_entrantes);
        *mesa_encontrada=true;
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Busca las mesas disponibles para luego asignar los correspondientes comensales si es posible.
*/
void llegada_comensales(mesa_t mesas[], int cantidad_mesas){
    int cant_comensales_entrantes=(rand() % RANGO_COMENSALES) + MINIMOS_COMENSALES;
    int contador=VALOR_NULO;
    bool mesa_encontrada=false;
    while(!mesa_encontrada && contador<cantidad_mesas){
        comensales_buscan_mesas(mesas, cant_comensales_entrantes, contador, &mesa_encontrada);
        contador++;
    }
    printf(AMARILLO_COLOR TEXTO_NEGRITA"\t\t\t--LLEGARON COMENSALES-"REINICIO_COLOR);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado, tamanio debe ser un numero positivo.
*   Post condiciones: Asigna memoria al campo platos_preparacion del campo cocina de juego, si el mismo falla
*                    imprime un mensaje por pantalla y libera el puntero.
*/
void platos_preparacion_asignar_memoria(juego_t* juego, int tamanio){
    juego->cocina.platos_preparacion=(pedido_t*)malloc((size_t)((size_t)(tamanio)*sizeof(pedido_t)));
    if (juego->cocina.platos_preparacion==NULL){
        printf(ROJO_COLOR"ERROR AL ASIGNAR MEMORIA (PLATOS_PREPARACION)"TEXTO_NEGRITA);
        free(juego->cocina.platos_preparacion);
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado, tamanio debe ser un numero positivo.
*   Post condiciones: Redimensiona el campo platos_preparacion del campo cocina de juego, si el mismo falla
*                    imprime un mensaje de error, libera el puntero y lo iguala a NULL.
*/
void platos_preparacion_redimensionar(juego_t* juego, int tamanio){
    pedido_t* repuesto_pedido=NULL;
    repuesto_pedido=(pedido_t*)realloc(juego->cocina.platos_preparacion, (size_t)((size_t)tamanio*sizeof(pedido_t)));
    if (repuesto_pedido==NULL){
        printf(ROJO_COLOR"ERROR EN MEMORIA (REDIMENSION )"TEXTO_NEGRITA);
        free(juego->cocina.platos_preparacion);
        juego->cocina.platos_preparacion=NULL;
    }else{
        juego->cocina.platos_preparacion=repuesto_pedido;
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado, tamanio debe ser un numero positivo.
*   Post condiciones: Asigna memoria al campo platos_listos del campo cocina de juego, si el mismo falla
*                    imprime un mensaje por pantalla y libera el puntero.
*/
void platos_listos_asignar_memoria(juego_t* juego, int tamanio){
    juego->cocina.platos_listos=(pedido_t*)malloc((size_t)((size_t)(tamanio)*sizeof(pedido_t)));
    if (juego->cocina.platos_listos==NULL){
        printf(ROJO_COLOR"ERROR AL ASIGNAR MEMORIA (PLATOS_PREPARACION)"TEXTO_NEGRITA);
        free(juego->cocina.platos_listos);
        juego->cocina.platos_listos=NULL;
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado, tamanio debe ser un numero positivo.
*   Post condiciones: Redimensiona el campo platos_listos del campo cocina de juego, si el mismo falla
*                    imprime un mensaje de error, libera el puntero y lo iguala a NULL.
*/
void platos_listos_redimensionar(juego_t* juego, int tamanio){
    pedido_t* repuesto_pedido=NULL;
    repuesto_pedido=(pedido_t*)realloc(juego->cocina.platos_listos, (size_t)((size_t)tamanio*sizeof(pedido_t)));
    if (repuesto_pedido==NULL){
        printf(ROJO_COLOR"ERROR EN MEMORIA (REDIMENSION )"TEXTO_NEGRITA);
        free(juego->cocina.platos_listos);
        juego->cocina.platos_listos=NULL;
    }else{
        juego->cocina.platos_listos=repuesto_pedido;
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Devuelve true si el mozo tiene la misma fila y columna que la cocina, sino devuelve false.
*/
bool mozo_encima_cocina(coordenada_t pos_mozo, coordenada_t pos_cocina){
    return((pos_mozo.fil==pos_cocina.fil) && (pos_mozo.col==pos_cocina.col));
}
/*
*   Pre condiciones: -
*   Post condiciones: Devuelve true si cantidad_pedidos es mayor a 0, caso contrario devuelve false.
*/
bool mozo_con_pedidos(int cantidad_pedidos){
    return (cantidad_pedidos>SIN_PEDIDOS);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Asigna memoria a platos.preparacion si es primera vez que se llama la funcion, 
*                    sino redimensiona platos.preparacion. 
*/
void preparacion_asignar_o_redimensionar_memoria(juego_t* juego){
    if (juego->cocina.platos_preparacion==NULL){
        platos_preparacion_asignar_memoria(juego, juego->mozo.cantidad_pedidos);
    }else{
        platos_preparacion_redimensionar(juego, juego->mozo.cantidad_pedidos+juego->cocina.cantidad_preparacion);
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Coloca los platos del pedido del mozo en la cocina para prepararse.
*/
void colocar_pedidos_en_cocina(juego_t* juego){
    int platos_a_prepararse=juego->cocina.cantidad_preparacion + juego->mozo.cantidad_pedidos;
    bool pedidos_colocados=false;
    while (juego->cocina.cantidad_preparacion<(platos_a_prepararse)){
        juego->cocina.platos_preparacion[juego->cocina.cantidad_preparacion]=juego->mozo.pedidos[0];
        eliminar_pedido(juego->mozo.pedidos, PIRMERA_POS, &juego->mozo.cantidad_pedidos);
        juego->cocina.cantidad_preparacion++;
        pedidos_colocados=true;
    }
    if (pedidos_colocados)
        printf(VERDE_COLOR TEXTO_NEGRITA"\t\t--COLOCASTE PEDIDOS EN LA COCINA-");
    juego->mozo.cantidad_pedidos=SIN_PEDIDOS;
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Asigna o redimensiona el puntero platos_preparacion luego coloca los pedidos en la cocina.
*/
void ingresar_pedidos_a_cocina_para_preparar(juego_t* juego){   
    preparacion_asignar_o_redimensionar_memoria(juego);
    colocar_pedidos_en_cocina(juego);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Cuenta cuantos platos en platos_preparacion cumplieron el tiempo de preparacion y devuelve esa cantidad.
*/
int cantidad_pedidos_listos_en_cocina(int cantidad_preparacion, pedido_t platos_preparacion[]){
    int pedidos_listos=SIN_PEDIDOS;
    for(int i=VALOR_NULO; i<cantidad_preparacion; i++){
        if ((platos_preparacion[i].tiempo_preparacion<=TIEMPO_TERMINADO))
            pedidos_listos++;
    }return pedidos_listos;
}
/*
*   Pre condiciones: cant_platos_listos debe ser mayor o igual a 0.
*   Post condiciones: Devuelve true si cant_platos_listos es igual a cero, si es mayor devuelve false.
*/
bool platos_listos_vacio(int cant_platos_listos){
    return (cant_platos_listos==SIN_PLATOS);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Asigna memoria a platos_listos si es primera vez que se llama la funcion, 
*                    sino redimensiona platos_listos. 
*/
void listos_asignar_o_redimensionar_memoria(juego_t* juego){
    if (juego->cocina.platos_listos==NULL)
        platos_listos_asignar_memoria(juego, cantidad_pedidos_listos_en_cocina(juego->cocina.cantidad_preparacion,juego->cocina.platos_preparacion));
    else
        platos_listos_redimensionar(juego, juego->cocina.cantidad_listos+(cantidad_pedidos_listos_en_cocina(juego->cocina.cantidad_preparacion, juego->cocina.platos_preparacion)));
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Devuelve true si la cantidad de pedidos listos en la cocina son mayores a cero, sino devuelve false.
*/
bool hay_pedidos_listos(int cantidad_listos){
    return ((cantidad_listos)>SIN_PEDIDOS);
}
/*
*   Pre condiciones: -
*   Post condiciones: Devuelve true si cant_bandeja es menor a MAX_BANDEJA, sino devuelve false.
*/
bool mozo_con_espacio_bandeja(int cant_bandeja){
    return(cant_bandeja<MAX_BANDEJA);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Mueve los platos del campo platos_preparacion al campo platos_listos.
*/
void mover_platos(cocina_t* cocina, int pos_plato){
    int contador=VALOR_NULO;
    int cant_pedidos_listos=cantidad_pedidos_listos_en_cocina(cocina->cantidad_preparacion, cocina->platos_preparacion)+cocina->cantidad_listos;
    while(cocina->cantidad_preparacion>SIN_PLATOS && cocina->cantidad_listos<=cant_pedidos_listos && contador<cant_pedidos_listos){
        if (cocina->platos_preparacion[pos_plato].tiempo_preparacion<=TIEMPO_TERMINADO){
            cocina->platos_listos[cocina->cantidad_listos]=*cocina->platos_preparacion;
            eliminar_pedido(cocina->platos_preparacion, pos_plato, &cocina->cantidad_preparacion);
            cocina->cantidad_listos+=1;
            contador++;
        }else
            contador++;
    }
    if (cant_pedidos_listos>SIN_PEDIDOS)
        printf(VERDE_COLOR TEXTO_NEGRITA"\t\t--HAY PLATOS LISTOS EN LA COCINA-"REINICIO_COLOR);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado,
*   Post condiciones: Si hay platos preparandose llama a la funcion que redimensiona el campo platos_preparacion,
*                    si no hay mas platos para prepararse se libera la memoria.
*/
void actualizar_platos_preparacion(juego_t* juego){
    if (juego->cocina.cantidad_preparacion>SIN_PEDIDOS)
        platos_preparacion_redimensionar(juego, juego->cocina.cantidad_preparacion);
    else{
        free(juego->cocina.platos_preparacion);
        juego->cocina.platos_preparacion=NULL;
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado,
*   Post condiciones: Redimensiona platos_listos si hay platos que no se pasaron a la bandeja,
*                    si ya no hay platos listos libera la memoria.
*/
void actualizar_platos_listos(juego_t* juego){
    if (juego->cocina.cantidad_listos>SIN_PEDIDOS)
        platos_listos_redimensionar(juego, juego->cocina.cantidad_listos);
    else{
        free(juego->cocina.platos_listos);
        juego->cocina.platos_listos=NULL;
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Mueve los platos listos y actualiza el tamaño del campo platos_preparacion.
*/
void mover_platos_listos_en_preparacion_a_listos(juego_t* juego, int pos_plato_prep){ 
    mover_platos(&juego->cocina, pos_plato_prep);
    actualizar_platos_preparacion(juego);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: El mozo recoge los pedidos listos de la cocina y los pone en su bandeja.
*/
void recoger_pedidos_listos(juego_t* juego){
    bool se_agarro_pedidos=false;
    while (mozo_con_espacio_bandeja(juego->mozo.cantidad_bandeja) && !platos_listos_vacio(juego->cocina.cantidad_listos)){
        juego->mozo.bandeja[juego->mozo.cantidad_bandeja]=*juego->cocina.platos_listos;
        eliminar_pedido(juego->cocina.platos_listos, PIRMERA_POS, &juego->cocina.cantidad_listos);
        juego->mozo.cantidad_bandeja+=1;
        printf(VERDE_COLOR TEXTO_NEGRITA"\t\t--HAS RECOGIDO EL/LOS PEDIDO/S DE LA/S MESA/S-:"REINICIO_COLOR);
        se_agarro_pedidos=true;
    }
    if(se_agarro_pedidos)
        actualizar_platos_listos(juego);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: disminuye el tiempo de los platos que se encuentran en la cocina preparandose, en caso de que algun plato
*                    esté listo se lo mueve al lugar de los platos listos.
*/
void reducir_tiempo_platos_en_preparacion(juego_t* juego){
    int platos_listos_actuales = juego->cocina.cantidad_preparacion;
    for (int i = VALOR_NULO; i < platos_listos_actuales; i++)
        juego->cocina.platos_preparacion[i].tiempo_preparacion--;
    for (int i = VALOR_NULO; i < platos_listos_actuales; i++){
        if (juego->cocina.platos_preparacion[i].tiempo_preparacion<=TIEMPO_TERMINADO && platos_listos_actuales>SIN_PEDIDOS){
            listos_asignar_o_redimensionar_memoria(juego);
            mover_platos_listos_en_preparacion_a_listos(juego, i);
            platos_listos_actuales--;
        }
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Realiza todas las interacciones del mozo con la cocina mientras se cumplan las condiciones.
*/
void interaccion_mozo_con_cocina(juego_t* juego){
    if(mozo_con_pedidos(juego->mozo.cantidad_pedidos))
        ingresar_pedidos_a_cocina_para_preparar(juego);
    if (mozo_con_espacio_bandeja(juego->mozo.cantidad_bandeja) && hay_pedidos_listos(juego->cocina.cantidad_listos)){
        recoger_pedidos_listos(juego);
    }
}
/*
*   Pre condiciones: cant_comensales debe estar entre 0 y 4, ambos inclusives. posicion debe ser la posicion de una mesa
*                   del campo mesas de juego. pos_mozo debe ser la posicion del mozo del campo mozo de juego.
*   Post condiciones: Devuelve true si cant_comensales es mayor a 0 y si el mozo se encuentra al lado de la mesa
*                    donde se encuentran estos comensales.   
*/
bool mesa_con_comensales_y_mozo_cerca(int cant_comensales, coordenada_t posicion, coordenada_t pos_mozo){
    return(cant_comensales>SIN_COMENSALES && ((abs(posicion.fil - pos_mozo.fil) <= DISTANCIA_MINIMA_MESAS) && (abs(posicion.col - pos_mozo.col) <= DISTANCIA_MINIMA_MESAS)));
}
/*
*   Pre condiciones: juego debe estar previamente inicializado, pos_mesa debe ser un numero mayor o igual a 0 y menor a 10.
*   Post condiciones: Devuelve true si mozo esta al lado de una mesa, caso contrario devuelve false.
*/
bool mozo_al_lado_mesa(mesa_t mesas[], mozo_t mozo, int pos_mesa){
    bool mozo_cerca_mesa=false;
    mesa_t mesa = mesas[pos_mesa];
    int i=VALOR_NULO;
    while(i < mesa.cantidad_lugares && !mozo_cerca_mesa){
        coordenada_t posicion = mesa.posicion[i];   
        coordenada_t pos_mozo = mozo.posicion;   
        if (mesa_con_comensales_y_mozo_cerca(mesas[pos_mesa].cantidad_comensales, posicion, pos_mozo)) {
            mozo_cerca_mesa=true;
        }i++;   
    }return mozo_cerca_mesa;
}
/*
*   Pre condiciones: 
*   Post condiciones:
*/
bool mesa_coincide_con_el_id__del_pedido_y_el_pedido_esta_tomado(mozo_t mozo, mesa_t mesas[], int pos_mesa, int pedido){
    return(pos_mesa==mozo.bandeja[pedido].id_mesa && mesas[pos_mesa].pedido_tomado);
}
/*
*   Pre condiciones: 
*   Post condiciones:
*/
void cobrar_precio_mesa(int* dinero, int cantidad_lugares){
    if (cantidad_lugares==MIN_COMENSALES)
        *dinero+=INDIVIDUAL_VALOR_MESA;
    else
        *dinero+=CUATRO_VALOR_MESA;
}
/*
*   Pre condiciones: 
*   Post condiciones:
*/
void plato_entregado_comensales_se_van(mesa_t mesas[], mozo_t* mozo, int pos_mesa, int pedido){
    eliminar_pedido(mozo->bandeja, pedido, &mozo->cantidad_bandeja);
    mesas[pos_mesa].cantidad_comensales=SIN_COMENSALES;
    mesas[pos_mesa].paciencia=VALOR_NULO;
    mesas[pos_mesa].pedido_tomado=false;
    printf(VERDE_COLOR TEXTO_NEGRITA"\t\t\t--PEDIDO ENTREGADO %i-" REINICIO_COLOR, pos_mesa);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado. pos_mesa debe ser un número de 0 a la (cantidad de mesas - 1).
*   Post condiciones: El mozo entrega el pedido respectivo a la mesa correspondiente.
*/
void entregar_platos_listo(mesa_t mesas[], mozo_t* mozo, int* dinero, int pos_mesa){
    for(int pedido=VALOR_NULO; pedido<mozo->cantidad_bandeja; pedido++){
        if(mesa_coincide_con_el_id__del_pedido_y_el_pedido_esta_tomado(*mozo, mesas, pos_mesa, pedido)){
            cobrar_precio_mesa(dinero, mesas[pos_mesa].cantidad_lugares);
            plato_entregado_comensales_se_van(mesas, mozo, pos_mesa, pedido);
        }
    }pos_mesa++;
}
/*
*   Pre condiciones: objetos debe tener elementos validos e inicializados. tipo_elemento debe ser un
*                   elemento valido. pos_elemento tiene que tener un valor mayor o igual a 0 y menos que tope_objetos.
*                   tope_objetos debe ser un numero maor o igual a 0. pos_mozo debe ser una posicion valida.
*   Post condiciones: Devuelve true si pos_mozo tiene los campos col y fil iguales a la posicion del objeto.
*                    caso contrario devuelve false.
*/
bool mozo_encima_elemento(objeto_t objetos[], char tipo_elemento ,int* pos_elemento, int tope_objetos, coordenada_t pos_mozo){
    bool mozo_sobre_elemento=false;
    int primera_pos = primera_pos_elemento(objetos, tope_objetos, tipo_elemento);
    int ultima_pos_elemento=(primera_pos+cantidad_elemento(objetos, tipo_elemento, tope_objetos));
    while(primera_pos<ultima_pos_elemento && !mozo_sobre_elemento){
        if (!posiciones_distintas(pos_mozo, objetos[primera_pos].posicion)){
            mozo_sobre_elemento=true;
            *pos_elemento=primera_pos;
        }primera_pos++;
    }return mozo_sobre_elemento;
}
/*
*   Pre condiciones: juego debe estar previamente inicializado, pos_moneda debe pertenecer
*                   a la posicion de una moneda en el campo vector 'herramientas' de juego.
*   Post condiciones: Elimina fisicamente al elemento ubicado en pos_moneda del campo vector
*                    'herramientas' de juego (una moneda) y suma 1000 al campo dinero de juego. 
*/
void recoger_moneda(objeto_t herramientas[], int* cantidad_herramientas, int pos_moneda, int* dinero){
    eliminar_elemento_especifico(herramientas, pos_moneda, cantidad_herramientas);
    *dinero+=DINERO_DE_MONEDAS;
}
/*
*   Pre condiciones: -
*   Post condiciones: Imprime por pantalla un mensaje si se intento dejar platos en la cocina
*                    con el mozo teniendo la mopa.
*/
void dejar_platos_con_mopa_mensaje(){
    printf(AMARILLO_COLOR TEXTO_NEGRITA"\t--TIENES LA MOPA -> NO PUEDES ENTREGAR PLATOS A ESTA MESA-"REINICIO_COLOR);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado. pos_patin debe pertenecer
*                   a la posicion de un elemento del campo vector 'herramientas'.
*   Post condiciones: Elimina fisicamente el elemento ubicado en pos_patin del campo vector
*                    'herramientas' de juego (un patin) y suma en 1 el campo cantidad_patines
*                    del campo mozo de juego.
*/
void recoger_patines(objeto_t herramientas[], int* cantidad_herramientas, int pos_patin, int* cantidad_patines){
    eliminar_elemento_especifico(herramientas, pos_patin, cantidad_herramientas);
    *cantidad_patines+=1;
    printf(VERDE_COLOR TEXTO_NEGRITA"\t\t\t  --RECOGISTE UN PATIN-"REINICIO_COLOR);
}
/*
*   Pre condiciones: pedido debe pertenecer a algun campo de un campo de juego. id_mesa debe
*                   ser el numero de una mesa entre 0 inclusive y la cantidad de mesas. cant_pedidos
*                   debe tener valor mayor o igual 0.
*   Post condiciones: Elimina fisicamente el pedido que tiene el campo id_mesa igual al parametro id_mesa.
*/
void descartar_pedidos_y_platos(pedido_t* pedido, int id_mesa, int* cant_pedidos){
    for (int i = VALOR_NULO; i < *cant_pedidos; i++){
        if (pedido[i].id_mesa==id_mesa)
            eliminar_pedido(pedido, i, cant_pedidos);
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado. num_id_mesa debe ser un numero
*                   mayor o igual a 0 y menor a juego->cantidad_mesas.
*   Post condiciones: Reinicia los campos cantidad_comensales y pedido_tomado de la mesa correspondiente.
*                    Luego descarta el pedido que era de la mesa esté donde esté.
*/
void comensales_se_van(juego_t* juego, int num_id_mesa){
    juego->mesas[num_id_mesa].cantidad_comensales=SIN_COMENSALES;
    juego->mesas[num_id_mesa].pedido_tomado=false;
    juego->mesas[num_id_mesa].paciencia=VALOR_NULO;
    descartar_pedidos_y_platos(juego->mozo.pedidos, num_id_mesa, &juego->mozo.cantidad_pedidos);
    descartar_pedidos_y_platos(juego->mozo.bandeja, num_id_mesa, &juego->mozo.cantidad_bandeja);
    descartar_pedidos_y_platos(juego->cocina.platos_preparacion, num_id_mesa, &juego->cocina.cantidad_preparacion);
    descartar_pedidos_y_platos(juego->cocina.platos_listos, num_id_mesa, &juego->cocina.cantidad_listos);
}
/*
*   Pre condiciones: primera_pos y segunda_pos deben ser posiciones validas. dis_minima debe ser un
*                   número mayor o igual a 0.
*   Post condiciones: Devuelve true  si la suma de la diferencia de las filas y columnas de cada uno
*                    es menor o igual a dis_minima, caso contrario devuelve false.
*/
bool distancia_manhattan(coordenada_t primera_pos, coordenada_t segunda_pos, int dis_minima){
    return((abs(primera_pos.fil-segunda_pos.fil)+abs(primera_pos.col- segunda_pos.col))<=dis_minima);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado. num_mesa debe ser un numero mayor o
*                   igual a 0 y menor que juego->cantidad_mesas.
*   Post condiciones: Devuelve false si una cucaracha esta a distancia manhattan 2 de la mesa en
*                    la posicion num_mesa del campo vector mesas de juego. Caso contrario devuelve true.
*/
bool cucaracha_lejos_mesa(objeto_t obstaculos[], mesa_t mesas[], int num_mesa, int cantidad_obstaculos){
    bool cucaracha_lejos=true;
    int pos_cucaracha=primera_pos_elemento(obstaculos, cantidad_obstaculos, CUCARACHA);
    int cant_cucarachas=cantidad_elemento(obstaculos, CUCARACHA, cantidad_obstaculos);
    while (pos_cucaracha<(pos_cucaracha+cant_cucarachas) && pos_vector_valida(pos_cucaracha, cantidad_obstaculos) && cucaracha_lejos){
        for (int i = VALOR_NULO; i < mesas[num_mesa].cantidad_lugares; i++){
            cucaracha_lejos=!distancia_manhattan(obstaculos[pos_cucaracha].posicion, mesas[num_mesa].posicion[i], DISTANCIA_MINIMA_CUCARACHA_DE_MESA);
        }pos_cucaracha++;
    }return cucaracha_lejos;
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Disminuye la paciencia de las mesas en 1, si hay una cucaracha cerca de
*                    la mesa disminuye en total 3 de paciencia. Si la paciencia de una mesa llega a 0
*                    los comensales se van.
*/
void bajar_paciencia_mesa_por_mov(juego_t* juego){
    int i=VALOR_NULO;
    bool comensales_se_fueron=false;
    while (i<juego->cantidad_mesas){
        if (juego->mesas[i].cantidad_comensales>SIN_COMENSALES){
            juego->mesas[i].paciencia--;
            if (!cucaracha_lejos_mesa(juego->obstaculos, juego->mesas, i, juego->cantidad_obstaculos)){
                juego->mesas[i].paciencia-=ANSIEDAD_POR_CUCARACHA;
            }
            if (juego->mesas[i].paciencia<=VALOR_NULO){
                comensales_se_van(juego, i);
                comensales_se_fueron=true;
            }
        }i++;
    }
    if (comensales_se_fueron)
        printf(AMARILLO_COLOR TEXTO_NEGRITA"\t\t--COMENSALES SE QUEDARON SIN PACIENCIA Y SE FUERON-"REINICIO_COLOR);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Si el mozo tiene mopa y se encuentra encima de un charco lo elimina.
*                    En caso de que el mozo no tenga mopa y tenga pedidos en la bandeja estos
*                    se le caen y los comensales con aquellos pedidos se van.
*/
void mozo_pisa_charco(juego_t* juego){
    int pos_charco=ENTERO_INVALIDO;
    if (juego->mozo.tiene_mopa){
        for (int i = VALOR_NULO; i < cantidad_elemento(juego->obstaculos, CHARCO, juego->cantidad_obstaculos); i++){
            if (!posiciones_distintas(juego->mozo.posicion, juego->obstaculos[i].posicion)){
                pos_charco=i;
            }   
        }
        eliminar_elemento_especifico(juego->obstaculos, pos_charco, &juego->cantidad_obstaculos);
        printf(VERDE_COLOR TEXTO_NEGRITA"\t\t\t ---HAS LIMPIADO UN CHARCO--"REINICIO_COLOR);
    }else if(juego->mozo.cantidad_bandeja>SIN_PEDIDOS){
        for (int i = VALOR_NULO; i < juego->mozo.cantidad_bandeja; i++)
            comensales_se_van(juego, juego->mozo.bandeja[i].id_mesa);
        printf(AMARILLO_COLOR TEXTO_NEGRITA"\t\t--PISASTE UN CHARCO Y TENIAS PLATOS EN BANDEJA, SE TE CALLERON, LOS COMENSALES SE VAN-"REINICIO_COLOR);
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Agrega un elemento CUCARACHA en el campo vector obstaculos de juego y
*                    se le asigna una posicion, tambien se suma 1 a la cantidad de obstaculos.
*/
void aparece_cucaracha(juego_t* juego){
    juego->obstaculos[juego->cantidad_obstaculos].tipo=CUCARACHA;
    cambiar_a_cordenadas_desocupadas(juego, &juego->obstaculos[juego->cantidad_obstaculos].posicion);
    juego->cantidad_obstaculos+=UNIDAD;
    printf(AMARILLO_COLOR TEXTO_NEGRITA"\t\t--APARECIO UNA CUCARACHA EN EL RESTAURANT-"REINICIO_COLOR);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Si aux_mov es distinto al campo movimientos de juego baja la paciencia
*                    de las mesas y reduce los platos en preparacion que estan en la cocina.
*/
void bajar_paciencia_y_reducir_tiempo_platos_preparacion(juego_t* juego, int aux_mov){
    if (aux_mov!=juego->movimientos){
        bajar_paciencia_mesa_por_mov(juego);
        reducir_tiempo_platos_en_preparacion(juego);
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Si aux_mov es distinto al campo movimientos de juego y el mismo multiplo de 15
*                    llegan comensales al juego.
*/
void llegaron_comensales(mesa_t mesas[], int movimientos, int cantidad_mesas, int aux_mov){
    if (aux_mov!=movimientos && (movimientos % TIEMPO_LLEGADA_COMENSAL)==VALOR_NULO)
        llegada_comensales(mesas, cantidad_mesas);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Si aux_mov es distinto al campo movimientos de juego y el mismo es multiplo de 25
*                    aparece una cucaracha en el terreno.
*/
void empieza_a_venir_la_cucaracha(juego_t* juego, int aux_mov){
    if (aux_mov!=juego->movimientos && (juego->movimientos % TIEMPO_LLEGADA_CUCA)==VALOR_NULO)
        aparece_cucaracha(juego);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Si el mozo esta encima de la cocina y el mozo no tiene la mopa, el mozo
*                    procede a interactuar con la cocina.
*/
void interactuar_con_cocina(juego_t* juego){
    if (mozo_encima_cocina(juego->mozo.posicion, juego->cocina.posicion) && !juego->mozo.tiene_mopa)
        interaccion_mozo_con_cocina(juego);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado, pos_mesa debe ser un numero entero mayor
*                   o igual a 0 y menor a la cantidad de mesas.
*   Post condiciones: Si el mozo tiene la mopa se imprime un mensaje de error al entregar el pedido,
*                    caso contrario se entrega el pedido.
*/
void mozo_quiere_entregar_pedido(mesa_t mesas[], mozo_t* mozo, int* dinero, int pos_mesa){
    if (mozo->tiene_mopa){
        dejar_platos_con_mopa_mensaje();
    }else{
        entregar_platos_listo(mesas, mozo, dinero, pos_mesa);
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Si el mozo tiene pedidos en la bandeja y esta al lado de la mesa
*                    del respectivo pedido lo intenta entregar.
*/
void acercandose_a_mesa_para_entrgar_platos_listos(int cantidad_mesas, mozo_t* mozo, mesa_t mesas[], int* dinero){
    for (int pos_mesa = VALOR_NULO; pos_mesa < cantidad_mesas; pos_mesa++){
        if(mozo->cantidad_bandeja>SIN_PEDIDOS && mozo_al_lado_mesa(mesas, *mozo, pos_mesa)){
            mozo_quiere_entregar_pedido(mesas, mozo, dinero, pos_mesa);
        }
    }
}
/*
*   Pre condiciones: La accion debe ser una accion válida y la posicion debe ser el campo posicion del campo
*                    mozo de juego.
*   Post condiciones: Devuelve el valor booleano true si la accion es 'W' y la posicion no esta en la fila inicial,
*                     caso contrario devuelve el valor false.
*/
bool es_accion_arriba_y_no_sale_del_terreno(char accion, coordenada_t posicion){
    return ((accion==ACCION_ARRIBA) && (posicion.fil!=PRIMERA_FILA));
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
    return ((accion==ACCION_IZQUIERDA) && (posicion.col!=PRIMERA_COLULMNA));
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Si el mozo esta encima de una moneda y el mozo no tiene mopa, recoge la moneda.
*/
void mozo_pisa_moneda(mozo_t mozo, objeto_t herramientas[], int* cantidad_herramientas, int* dinero, int* pos_aux){
    if(mozo_encima_elemento(herramientas, MONEDA, pos_aux, *cantidad_herramientas, mozo.posicion) && !mozo.tiene_mopa){
        recoger_moneda(herramientas, cantidad_herramientas, *pos_aux, dinero);
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Si el mozo se encuentra encima de un patin y el mozo no tiene la mopa, recoge el patin.
*/
void mozo_pisa_patines(mozo_t* mozo, objeto_t herramientas[], int* cantidad_herramientas, int* pos_aux){
    if (mozo_encima_elemento(herramientas, PATIN, pos_aux, *cantidad_herramientas, mozo->posicion) && !mozo->tiene_mopa){
        recoger_patines(herramientas, cantidad_herramientas, *pos_aux, &mozo->cantidad_patines);
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Si el mozo se encuentra encima de un charco el mismo interactua con el.
*/
void mozo_en_charco(juego_t* juego, int* pos_aux){
    if (mozo_encima_elemento(juego->obstaculos, CHARCO, pos_aux, juego->cantidad_obstaculos, juego->mozo.posicion)){
        mozo_pisa_charco(juego);
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Si el mozo se encuentra encima de una cucaracha y el mozo no tiene la mopa, 
*                    la cucaracha es eliminada del vector donde se encuentra (La cucaracha muere).
*/
void mozo_pisa_cucaracha(mozo_t mozo, objeto_t obstaculos[], int* cantidad_obstaculos, int* pos_aux){
    if (mozo_encima_elemento(obstaculos, CUCARACHA, pos_aux, *cantidad_obstaculos, mozo.posicion) && !mozo.tiene_mopa){
        eliminar_elemento_especifico(obstaculos, *pos_aux, cantidad_obstaculos);
    }   
}
/*
*   Pre condiciones: juego debe estar inicializado anteriormente
*   Post condiciones: Dismninuye en 1 el campo fil, del campo posiciones,
*                    del campo mozo de juego.
*/
void desplazar_arriba(juego_t* juego){
    juego->mozo.posicion.fil--;
}
/*
*   Pre condiciones: juego debe estar inicializado anteriormente
*   Post condiciones: Suma en 1 el campo fil, del campo posiciones, del campo mozo de juego.
*/
void desplazar_abajo(juego_t* juego){
    juego->mozo.posicion.fil++;
}
/*
*   Pre condiciones: juego debe estar inicializado anteriormente
*   Post condiciones: Disminuye en 1 el campo col, del campo posicion,
*                    del campo mozo de juego.
*/
void desplazar_izquiera(juego_t* juego){
    juego->mozo.posicion.col--;
}
/*
*   Pre condiciones: juego debe estar inicializado anteriormente
*   Post condiciones: Suma en 1 el campo col, del campo posicion, del campo mozo de juego.
*/
void desplazar_derecha(juego_t* juego){
    juego->mozo.posicion.col++;
}
/*
*   Pre condiciones: juego debe estar previamente inicializado. accion debe ser una accion
*                   de movimiento valida.
*   Post condiciones: Devuelve true si donde_es_llada es FUNC_DESPLAZAMIENTO_CON_PATIN,
*                    si el mozo no se choca con una mesa y no sale del terreno. Caso contrario
*                    devuelve false.
*/
bool no_es_llamada_desde_realizar_jugada_no_choca_con_mesa_ni_sale_del_terreno(int donde_es_llamada, juego_t* juego, char accion){
    bool chequeo=false;
    if (accion==ACCION_ARRIBA)
        chequeo=(donde_es_llamada==FUNC_DESPLAZAMIENTO_CON_PATIN && (chequeo_dezplazamiento_valido(juego->mesas, &juego->mozo.posicion, juego->cantidad_mesas, ACCION_IZQUIERDA) && es_accion_arriba_y_no_sale_del_terreno(accion, juego->mozo.posicion)));
    if (accion==ACCION_ABAJO)
        chequeo=(donde_es_llamada==FUNC_DESPLAZAMIENTO_CON_PATIN && (chequeo_dezplazamiento_valido(juego->mesas, &juego->mozo.posicion, juego->cantidad_mesas, ACCION_IZQUIERDA) && es_accion_abajo_y_no_sale_del_terreno(accion, juego->mozo.posicion)));
    if (accion==ACCION_DERECHA)
        chequeo=(donde_es_llamada==FUNC_DESPLAZAMIENTO_CON_PATIN && (chequeo_dezplazamiento_valido(juego->mesas, &juego->mozo.posicion, juego->cantidad_mesas, ACCION_IZQUIERDA) && es_accion_derecha_y_no_sale_del_terreno(accion, juego->mozo.posicion)));
    if (accion==ACCION_IZQUIERDA)
        chequeo=(donde_es_llamada==FUNC_DESPLAZAMIENTO_CON_PATIN && (chequeo_dezplazamiento_valido(juego->mesas, &juego->mozo.posicion, juego->cantidad_mesas, ACCION_IZQUIERDA) && es_accion_izquierda_y_no_sale_del_terreno(accion, juego->mozo.posicion)));
    return chequeo;
}
/*
*   Pre condiciones: juego debe estar previamente inicializado, accion debe ser una accion valida.
*   Post condiciones: Si pasa que no_es_llamada_desde_realizar_jugada_no_choca_con_mesa_ni_sale_del_terreno 
*                    es true se disminuye los movimientos y aux en 1.
*                    Sino si, chequeo_dezplazamiento_valido es true y donde_es_llamada es igual a 
*                    FUNC_DESPLAZAMIENTO_CON_PATIN se realiza un movimiento normalmente.
*                    En otro cualquier caso se realiza un movimiento normalmente.
*/
void funcionamiento_respecto_donde_es_llamada(juego_t* juego, int* aux, int donde_es_llamada, char accion){
    if (no_es_llamada_desde_realizar_jugada_no_choca_con_mesa_ni_sale_del_terreno(donde_es_llamada,juego, accion)){
        juego->movimientos--;*aux-=UNIDAD;
    }else if(!chequeo_dezplazamiento_valido(juego->mesas, &juego->mozo.posicion, juego->cantidad_mesas, accion) && donde_es_llamada==FUNC_DESPLAZAMIENTO_CON_PATIN){
        juego->movimientos++;
        comprobar_dezplazamiento_valido(juego->mesas, &juego->mozo.posicion, juego->cantidad_mesas, &juego->movimientos, accion);
        llegaron_comensales(juego->mesas, juego->movimientos, juego->cantidad_mesas, *aux);
        empieza_a_venir_la_cucaracha(juego, *aux);    
    }else{ 
        comprobar_dezplazamiento_valido(juego->mesas, &juego->mozo.posicion, juego->cantidad_mesas, &juego->movimientos, accion);
        bajar_paciencia_y_reducir_tiempo_platos_preparacion(juego, *aux);
        llegaron_comensales(juego->mesas, juego->movimientos, juego->cantidad_mesas, *aux);
        empieza_a_venir_la_cucaracha(juego, *aux);    
    }
}
/*
*   Pre condiciones: El campo mozo y movimientos de juego deben estar inicializados previamente.
*   Post condiciones: Dezplaza hacia arriba al mozo y suma un movimiento, luego comprueba que sea un
*                     dezplazamiento valido.
*/
void movimiento_hacia_arriba(juego_t* juego, int donde_es_llamada){
    int aux=juego->movimientos;
    int pos_aux=ENTERO_INVALIDO;
    desplazar_arriba(juego);
    juego->movimientos++;
    funcionamiento_respecto_donde_es_llamada(juego, &aux, donde_es_llamada, ACCION_ARRIBA);
    interactuar_con_cocina(juego);
    acercandose_a_mesa_para_entrgar_platos_listos(juego->cantidad_mesas, &juego->mozo, juego->mesas, &juego->dinero);
    mozo_pisa_moneda(juego->mozo, juego->herramientas, &juego->cantidad_herramientas, &juego->dinero, &pos_aux);
    mozo_pisa_patines(&juego->mozo, juego->herramientas, &juego->cantidad_herramientas, &pos_aux);
    mozo_en_charco(juego, &pos_aux);
    mozo_pisa_cucaracha(juego->mozo, juego->obstaculos, &juego->cantidad_obstaculos, &pos_aux);
}
/*
*   Pre condiciones: El campo mozo y movimientos de juego deben estar inicializados previamente.
*   Post condiciones: Dezplaza hacia abajo al mozo y suma un movimiento, luego comprueba que sea un
*                     dezplazamiento valido.
*/
void movimiento_hacia_abajo(juego_t* juego, int donde_es_llamada){
    int aux=juego->movimientos;
    int pos_aux=ENTERO_INVALIDO;
    desplazar_abajo(juego);
    juego->movimientos++;
    funcionamiento_respecto_donde_es_llamada(juego, &aux, donde_es_llamada, ACCION_ABAJO);
    interactuar_con_cocina(juego);
    acercandose_a_mesa_para_entrgar_platos_listos(juego->cantidad_mesas, &juego->mozo, juego->mesas, &juego->dinero);
    mozo_pisa_moneda(juego->mozo, juego->herramientas, &juego->cantidad_herramientas, &juego->dinero, &pos_aux);
    mozo_pisa_patines(&juego->mozo, juego->herramientas, &juego->cantidad_herramientas, &pos_aux);
    mozo_en_charco(juego, &pos_aux);
    mozo_pisa_cucaracha(juego->mozo, juego->obstaculos, &juego->cantidad_obstaculos, &pos_aux);
}
/*
*   Pre condiciones: El campo mozo y movimientos de juego deben estar inicializados previamente.
*   Post condiciones: Dezplaza hacia la derecha al mozo y suma un movimiento, luego comprueba que sea un
*                     dezplazamiento valido.
*/
void movimiento_hacia_derecha(juego_t* juego, int donde_es_llamada){
    int aux=juego->movimientos;
    int pos_aux=ENTERO_INVALIDO;
    desplazar_derecha(juego);
    juego->movimientos++;
    funcionamiento_respecto_donde_es_llamada(juego, &aux, donde_es_llamada, ACCION_DERECHA);
    interactuar_con_cocina(juego);
    acercandose_a_mesa_para_entrgar_platos_listos(juego->cantidad_mesas, &juego->mozo, juego->mesas, &juego->dinero);
    mozo_pisa_moneda(juego->mozo, juego->herramientas, &juego->cantidad_herramientas, &juego->dinero, &pos_aux);
    mozo_pisa_patines(&juego->mozo, juego->herramientas, &juego->cantidad_herramientas, &pos_aux);
    mozo_en_charco(juego, &pos_aux);
    mozo_pisa_cucaracha(juego->mozo, juego->obstaculos, &juego->cantidad_obstaculos, &pos_aux);
}
/*
*   Pre condiciones: El campo mozo y movimientos de juego deben estar inicializados previamente.
*   Post condiciones: Dezplaza hacia la izquierda al mozo y suma un movimiento, luego comprueba que sea un
*                     dezplazamiento valido.
*/
void movimiento_hacia_izquierda(juego_t* juego, int donde_es_llamada){
    int aux=juego->movimientos;
    int pos_aux=ENTERO_INVALIDO;
    desplazar_izquiera(juego);
    juego->movimientos++;
    funcionamiento_respecto_donde_es_llamada(juego, &aux, donde_es_llamada, ACCION_IZQUIERDA);
    interactuar_con_cocina(juego);
    acercandose_a_mesa_para_entrgar_platos_listos(juego->cantidad_mesas, &juego->mozo, juego->mesas, &juego->dinero);
    mozo_pisa_moneda(juego->mozo, juego->herramientas, &juego->cantidad_herramientas, &juego->dinero, &pos_aux);
    mozo_pisa_patines(&juego->mozo, juego->herramientas, &juego->cantidad_herramientas, &pos_aux);
    mozo_en_charco(juego, &pos_aux);
    mozo_pisa_cucaracha(juego->mozo, juego->obstaculos, &juego->cantidad_obstaculos, &pos_aux);
}
/*
*   Pre condiciones: -
*   Post condiciones: Cambia el valor del campo tiene_mopa del campo mozo de juego a true, 
*                     luego establece la fila y columna de la posicion de la mopa en -1.
*/
void estado_mopa_recogida(mozo_t* mozo, objeto_t herramientas[], int* cantidad_herramientas){
    mozo->tiene_mopa=true;
    eliminar_elemento(herramientas, MOPA, cantidad_herramientas);
}
/*
*   Pre condiciones: -
*   Post condiciones: Cambia el valor del campo tiene_mopa del campo mozo de juego a false, 
*                     luego establece la fila y columna de la posicion de la mopa en la misma posición
*                     actual del mozo.
*/
void estado_mopa_soltada(juego_t* juego){
    juego->mozo.tiene_mopa=false;
    insertar_elemento_final(juego, juego->herramientas, &juego->cantidad_herramientas, MOPA);
}
/*
*   Pre condiciones: juego debe estar inicializado previamente con 'inicializar_juego', a su vez las poisiciones de la mopa
*                    y del mozo deben ser posiciones validas.
*   Post condiciones: Devuelve el valor booleano true si el mozo no tiene la mopa y  si las posiciones
*                     del mozo y la mopa son distintas. Caso contrario devuelve el valor false.
*/
bool mozo_sin_mopa_y_mozo_lejos_de_mopa(bool tiene_mopa, coordenada_t posicion_mopa, coordenada_t posicion_mozo){
    return ((!tiene_mopa) && (posicion_mopa.fil!=posicion_mozo.fil || posicion_mopa.col!=posicion_mozo.col));
}
/*
*   Pre condiciones: juego debe estar inicializado previamente con 'inicializar_juego', a su vez las poisiciones de la mopa
*                    y del mozo deben ser posiciones validas.
*   Post condiciones: Devuelve el valor booleano true si el mozo no tiene la mopa y  si las posiciones
*                     del mozo y la mopa son iguales. Caso contrario devuelve el valor false.
*/
bool mozo_sin_mopa_y_mozo_encima_de_mopa(bool tiene_mopa, coordenada_t posicion_mopa, coordenada_t posicion_mozo){
    return ((!tiene_mopa) && (posicion_mopa.fil==posicion_mozo.fil && posicion_mopa.col==posicion_mozo.col));
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
    coordenada_t posicion_mopa=juego->herramientas[primera_pos_elemento(juego->herramientas, juego->cantidad_herramientas, MOPA)].posicion;
    coordenada_t posicion_mozo=juego->mozo.posicion;
    if (mozo_sin_mopa_y_mozo_lejos_de_mopa(juego->mozo.tiene_mopa, posicion_mopa, posicion_mozo)){
        printf(AMARILLO_COLOR"     ---¡¡¡NO PUEDES RECOGER LA MOPA, NO TE ENCUENTRAS ENCIMA DE ELLA!!!---"TEXTO_NEGRITA);
    }else if (mozo_sin_mopa_y_mozo_encima_de_mopa(juego->mozo.tiene_mopa, posicion_mopa, posicion_mozo)){
        estado_mopa_recogida(&juego->mozo, juego->herramientas, &juego->cantidad_herramientas);
        printf(VERDE_COLOR"     ---RECOGISTE LA MOPA---"TEXTO_NEGRITA);
    }else if (mozo_con_mopa_y_coordenada_desocupada(juego)){
        estado_mopa_soltada(juego);
        printf(VERDE_COLOR"     ---SOLTASTE LA MOPA EN TU POSICION ACTUAL---"TEXTO_NEGRITA);
    }else
        printf(AMARILLO_COLOR"     ---¡¡¡NO PUEDES SOLTAR LA MOPA EN ESTA POSICION!!!---"TEXTO_NEGRITA);  
}
/*
*   Pre condiciones: plato_comensal debe ser un plato del campo pedido de una mesa. plato_pedido debe ser
*                   una plato valido. tiempo_plato debe ser un tiempo de preparacion correspondiente a un 
*                   plato valido, el mismo que plato pedido.
*   Post condiciones: Asigna el plato_pedido en el valor de plato_comensal y si el tiempo_prep es menor al tiempo_plato
*                    iguala el valor de tiempo_prep a tiempo_plato-
*/
void asignar_plato_comensal_y_tiempo_total_preparacion(char* plato_comensal, char plato_pedido, int* tiempo_prep, int tiempo_plato){
    *plato_comensal=plato_pedido;
    if (*tiempo_prep<tiempo_plato)
        *tiempo_prep=tiempo_plato;
}
/*
*   Pre condiciones: juego debe estar previamente inicializado. plato debe ser una posicion del campo vector platos
*                   del campo pedidos del campo mozo de juegos menor a la cantidad de comensales y mayor o igual a 0.
*   Post condiciones: Asigna plato que es pedido en el pedido del mozo.
*/
void preguntar_plato(mozo_t* mozo, int* tiempo_mayor_preapracion_platos, int plato){
    int pedido=(rand() % RANGO_PLATOS) + PEDIDO_MINIMO;
    if (pedido==MILANESA_NAPO_REP)
        asignar_plato_comensal_y_tiempo_total_preparacion(&mozo->pedidos[mozo->cantidad_pedidos].platos[plato], MILANESA_NAPO, tiempo_mayor_preapracion_platos, TIMER_MILANESA_NAPO);
    else if (pedido==HAMBURGUESA_REP)
        asignar_plato_comensal_y_tiempo_total_preparacion(&mozo->pedidos[mozo->cantidad_pedidos].platos[plato], HAMBURGUESA, tiempo_mayor_preapracion_platos, TIMER_HAMBURGUESA);        
    else if (pedido==PARRILLA_REP)
        asignar_plato_comensal_y_tiempo_total_preparacion(&mozo->pedidos[mozo->cantidad_pedidos].platos[plato], PARRILLA, tiempo_mayor_preapracion_platos, TIMER_PARRILLA);
    else if (pedido==RATATOUILLE_REP)
        asignar_plato_comensal_y_tiempo_total_preparacion(&mozo->pedidos[mozo->cantidad_pedidos].platos[plato], RATATOUILLE, tiempo_mayor_preapracion_platos, TIMER_RATATOUILLE);
}
/*
*   Pre condiciones: juego debe estar previamente inicializado y pos_mesa debe ser un numero entero entre
*                   0 inclusive y menor que juego->cantidad_mesas.
*   Post condiciones: Obtiene el pedido correspondiente de la mesa con comensales que no se les tomo el pedido.
*/
void tomar_pedido(mozo_t* mozo, mesa_t mesas[], int pos_mesa){
    int tiempo_mayor_preparacion_platos=VALOR_NULO;
    mozo->pedidos[mozo->cantidad_pedidos].cantidad_platos=mesas[pos_mesa].cantidad_comensales;
    mozo->pedidos[mozo->cantidad_pedidos].id_mesa=pos_mesa;
    for (int i = VALOR_NULO; i < mesas[pos_mesa].cantidad_comensales; i++)
        preguntar_plato(mozo, &tiempo_mayor_preparacion_platos, i);
    mozo->pedidos[mozo->cantidad_pedidos].tiempo_preparacion=(tiempo_mayor_preparacion_platos);
    mozo->cantidad_pedidos+=1;
}
/*
*   Pre condiciones: juego debe estar previamente inicializado. pos_mesa debe ser un numero entero
*                   mayor o igual a 0 y menor que juego->cantidad_mesas.
*   Post condiciones: El mozo toma el pedido si es que el mozo tiene espacio para mas pedidos, sino
*                    se imprime un mensaje por pantalla.
*/
void intento_de_tomar_pedido(mozo_t* mozo, mesa_t mesas[], int cantidad_mesas, int* pos_mesa, bool* pedido_tomado){
    if ((mozo->cantidad_pedidos)>=MAX_PEDIDOS){
        printf(AMARILLO_COLOR TEXTO_NEGRITA"\t\t--HAY PEDIDOS POR TOMAR, PERO NO PUEDES TOMARLOS PORQUE NO CABEN EN TUS MANOS-" REINICIO_COLOR);
        *pos_mesa=cantidad_mesas;
    }else{
        mesas[*pos_mesa].pedido_tomado=true;
        tomar_pedido(mozo, mesas, *pos_mesa);
        printf(VERDE_COLOR TEXTO_NEGRITA"\t\tHAZ TOMADO EL PEDIDO DE LA MESA N°-%i\n" REINICIO_COLOR, *pos_mesa);
        *pedido_tomado=true;
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado.
*   Post condiciones: Si el mozo esta al lado de una mesa con comensales y el pedido de la mesa
*                    no esta tomado intenta tomar el pedido. Sino se imprime un mensaje.
*/
void accion_tomar_pedido(int cantidad_mesas, mesa_t mesas[], mozo_t* mozo){
    int pos_mesa;
    bool un_pedido_tomado=false;
    for (pos_mesa=VALOR_NULO; pos_mesa<cantidad_mesas ; pos_mesa++){
        if (mozo_al_lado_mesa(mesas, *mozo, pos_mesa) && !mesas[pos_mesa].pedido_tomado){
            intento_de_tomar_pedido(mozo, mesas, cantidad_mesas, &pos_mesa, &un_pedido_tomado);
        }else if (!un_pedido_tomado && !mozo_al_lado_mesa(mesas, *mozo, pos_mesa) && pos_mesa==(cantidad_mesas-1))
            printf(AMARILLO_COLOR"\t--NO HAS TOMADO NINGUN PEDIDO, LEJOS DE MESA CON COMENSALES SIN PEDIDO TOMADO-"TEXTO_NEGRITA REINICIO_COLOR);
    }
}
/*
*   Pre condiciones: -
*   Post condiciones: Se imprime un mensaje por pantalla.
*/
void cocina_mensaje_por_tener_mopa(){
    printf(AMARILLO_COLOR TEXTO_NEGRITA"\t--NO PUEDES DEJAR PEDIDOS NI AGARRA PLATOS LISTOS YA QUE TIENES LA MOPA--"REINICIO_COLOR);
}
/*
*   Pre condiciones: accion debe ser una accion valida de movimiento(W, A, S, D).
*   Post condiciones: Devuelve true si accion es W, A, S o D. Caso contrario devuelve false.
*/
bool es_accion_de_movimiento(char accion){
    return(accion==ACCION_ARRIBA || accion==ACCION_ABAJO || accion==ACCION_DERECHA || accion==ACCION_IZQUIERDA);
}
/*
*   Pre condiciones: mesas debe ser el campo vector mesas de juego. tope_mesas debe ser un numero
*                   mayor o igual a 0 y menor que la cantidad de mesas.
*   Post condiciones: Inicializa repuestos_mesas igual a mesas.
*/
void asignar_respuesto_mesa(mesa_t repuesto_mesas[], mesa_t mesas[], int tope_mesas){
    for(int i=VALOR_NULO; i<tope_mesas;i++){
        repuesto_mesas[i]=mesas[i];
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado. accion debe ser una accion
*                   valida. pos_mozo_anterior debe ser una coordenada valida.
*   Post condiciones: Desplaza al mozo hasta que choque con una mesa o salga del terreno.
*/
void realizar_movimientos_consecutivos(juego_t* juego, char accion, coordenada_t* pos_mozo_anterior){
    while (chequeo_dezplazamiento_valido(juego->mesas, &juego->mozo.posicion, juego->cantidad_mesas, accion) && posiciones_distintas(*pos_mozo_anterior, juego->mozo.posicion) && es_accion_de_movimiento(accion)){
        *pos_mozo_anterior=juego->mozo.posicion;
        if (es_accion_arriba_y_no_sale_del_terreno(accion, juego->mozo.posicion)){
            movimiento_hacia_arriba(juego, FUNC_DESPLAZAMIENTO_CON_PATIN);
        }else if (es_accion_abajo_y_no_sale_del_terreno(accion, juego->mozo.posicion)){
            movimiento_hacia_abajo(juego, FUNC_DESPLAZAMIENTO_CON_PATIN);
        }else if (es_accion_derecha_y_no_sale_del_terreno(accion, juego->mozo.posicion)){
            movimiento_hacia_derecha(juego, FUNC_DESPLAZAMIENTO_CON_PATIN);
        }else if (es_accion_izquierda_y_no_sale_del_terreno(accion, juego->mozo.posicion))
            movimiento_hacia_izquierda(juego, FUNC_DESPLAZAMIENTO_CON_PATIN);
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado. accion debe ser una accion valida.
*   Post condiciones: Realiza un dezplazamiento del mozo por todo el terreno hasta chocarse con el limite
*                    del mismo o con una (en una sola dirección). En su camino interactua con todo.
*/
void desplazamiento_con_patin(juego_t* juego, char accion){
    int cant_movimientos_actuales=juego->movimientos;
    coordenada_t pos_mozo_anterior;
    pos_mozo_anterior.fil=ENTERO_INVALIDO;
    pos_mozo_anterior.col=ENTERO_INVALIDO;
    if(es_accion_de_movimiento(accion) || (accion!=AGARRA_O_SOLTAR_MOPA && accion!=TOMAR_PEDIDO && accion!=PONERSE_PATINES))
        juego->mozo.patines_puestos=false;
    else if(accion==AGARRA_O_SOLTAR_MOPA)
        accion_agarrar_o_soltar_mopa(juego);
    realizar_movimientos_consecutivos(juego, accion, &pos_mozo_anterior);
    bajar_paciencia_y_reducir_tiempo_platos_preparacion(juego, cant_movimientos_actuales);
}
/*
* Pre condiciones: El juego debe estar inicializado previamente con `inicializar_juego ` y la acción
* debe ser válida.
* Post condiciones: Realizará la acción recibida por parámetro. Para este primer TP solo se
* implementará el funcionamiento para mover al jugador y agarrar/soltar la mopa.
*/
void realizar_jugada(juego_t *juego , char accion){
    if (juego->mozo.patines_puestos){
        desplazamiento_con_patin(juego, accion);
    }else if (es_accion_arriba_y_no_sale_del_terreno(accion, juego->mozo.posicion)){
        movimiento_hacia_arriba(juego, FUNC_REALIZAR_JUGADA);
    }else if (es_accion_abajo_y_no_sale_del_terreno(accion, juego->mozo.posicion)){
        movimiento_hacia_abajo(juego, FUNC_REALIZAR_JUGADA);
    }else if (es_accion_derecha_y_no_sale_del_terreno(accion, juego->mozo.posicion)){
        movimiento_hacia_derecha(juego, FUNC_REALIZAR_JUGADA);
    }else if (es_accion_izquierda_y_no_sale_del_terreno(accion, juego->mozo.posicion)){
        movimiento_hacia_izquierda(juego, FUNC_REALIZAR_JUGADA);
    }else if (accion==AGARRA_O_SOLTAR_MOPA){
        accion_agarrar_o_soltar_mopa(juego);
    }else if (accion==TOMAR_PEDIDO){
        if(!juego->mozo.tiene_mopa)
            accion_tomar_pedido(juego->cantidad_mesas, juego->mesas, &juego->mozo);
        else
            cocina_mensaje_por_tener_mopa();
    }else if (accion==PONERSE_PATINES && juego->mozo.cantidad_patines>VALOR_NULO && !juego->mozo.patines_puestos && !juego->mozo.tiene_mopa){
        juego->mozo.patines_puestos=true;
        juego->mozo.cantidad_patines--;
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
    if (juego.movimientos==MAX_MOVIMIENTOS && juego.dinero<DINERO_NECESARIO){
        return JUEGO_PERDIDO;
    }
    else if (juego.movimientos==MAX_MOVIMIENTOS && juego.dinero>=DINERO_NECESARIO){
        return JUEGO_GANADO;
    }
    return JUEGO_EN_CURSO;
}
/*
*   Pre condiciones: -
*   Post condiciones: Inicializa todas las posiciones de terreno con el elemento VACIO.
*/
void inicializar_terreno_vacio(char terreno[MAX_FILAS][MAX_COLUMNAS]){
    for (int i = VALOR_NULO; i < MAX_FILAS; i++){
        for (int j = VALOR_NULO; j < MAX_COLUMNAS; j++){
            terreno[i][j]=VACIO;
        }   
    }
}
/*
*   Pre condiciones: -
*   Post condiciones: Imprime por pantalla (por encima del terreno) las acciones validas para realizar.
*/
void imprimir_acciones_validas(){
    printf(CYAN_COLOR"\t\t\t\t\t\t    ---|ACCIONES VALIDAS|---\n"REINICIO_COLOR);
    printf(CYAN_COLOR"    |IZQUIERDA ⟹ 'A' | DERECHA ⟹ 'D' | ARRIBA ⟹ W | ABAJO ⟹ S | AGARRAR/SOLTAR MOPA ⟹ O | ACTIVAR PATIN ⟹ 'P' | TOMAR PEDIDO ⟹ 'P'|\n"REINICIO_COLOR);
}
/*
*   Pre condiciones: -
*   Post condiciones: Imprime una linea entera del largo del terreno con el simbolo '='.
*/
void imprimir_barra(){
    for (int i = VALOR_NULO; i < LARGO_DEL_TERRENO_IMPRESO_EN_PANTALLA; i++){
        printf("=");
    }
    printf("\n");
}
/*
*   Pre condiciones: juego debe estar previamente inicializado y pedido debe ser un numero
*                   mayor o igual a 0.
*   Post condiciones: Imprime los pedidos que tenga el mozo.
*/
void imprimir_pedidos(mozo_t mozo, int pedido){
    if (mozo.cantidad_pedidos>SIN_PEDIDOS && pedido<mozo.cantidad_pedidos){
        printf("\033[3%im[PEDIDO MESA N°%i]\t"REINICIO_COLOR, (pedido+1), mozo.pedidos[pedido].id_mesa);
    }else
        printf("\t\t  ");
}
/*
*   Pre condiciones: juego debe estar previamente inicializado y pedido debe ser un numero
*                   mayor o igual a 0.
*   Post condiciones: Imprime los pedidos que estén preparandose en la cocina.
*/
void imprimir_pedidos_en_preparacion(cocina_t cocina, int pedido){
    if (cocina.cantidad_preparacion>SIN_PEDIDOS && pedido<cocina.cantidad_preparacion){
        printf("\033[3%im[PEDIDO MESA N°%i -Listo en MOV->%i]"REINICIO_COLOR, (pedido+1), cocina.platos_preparacion[pedido].id_mesa, cocina.platos_preparacion[pedido].tiempo_preparacion);
    }
}
/*
*   Pre condiciones: fila debe ser un numero positivo entre 0 y 19, ambos inclusives.
*                   juego debe estar previamente inicializado. pedido debe ser un numero
*                   mayor o igual a 0.
*   Post condiciones: Imprime una barra lateral dependiendo de los pedidos.
*/
void imprimir_barra_de_pedidos(int fila, mozo_t mozo, cocina_t cocina, int* pedido){
    if ((fila%2==VALOR_NULO)){
        imprimir_pedidos(mozo, *pedido);
        imprimir_pedidos_en_preparacion(cocina, *pedido);
        printf("\n");
        *pedido+=UNIDAD;
    }else
        printf("\n");
}
/*
*   Pre condiciones: fila debe ser un numero positivo entre 0 y 19, ambos inclusives.
*                   juego debe estar previamente inicializado. cant_mesas debe ser un numero 
*                   mayor a 0. mesa debe tener valor mayor o igual a 0 y menor a cant_mesas.
*   Post condiciones: Imprime en el lateral las mesas y su paciencia cuando tienen comensales.
*/
void imprimir_paciencia_mesas(int* mesa, int fila, mesa_t mesas[], int cant_mesas){
    if ((fila%2!=VALOR_NULO) && *mesa<cant_mesas){
        printf(MAGENTA_COLOR TEXTO_NEGRITA"PACIENCIA DE MESA %i [%i]" REINICIO_COLOR, *mesa, mesas[*mesa].paciencia);
        *mesa+=UNIDAD;
    }
}
/*
*   Pre condiciones: El terreno debe estar inicializado con los elementos de juego y juego debe estar
*                    inicializado con 'inicializar_juego'.
*   Post condiciones: Imprime por pantalla el terreno con una interfaz y a su vez a un costado la información
*                     de los pedidos.
*/
void imprimir_terreno_y_pedidos(char terreno[MAX_FILAS][MAX_COLUMNAS], mozo_t mozo, cocina_t cocina, mesa_t mesas[] ,int cant_mesas){
    int pedido=VALOR_NULO;
    int mesa=VALOR_NULO;
    for (int fila = VALOR_NULO; fila < MAX_FILAS; fila++){
        for (int columna = VALOR_NULO; columna < MAX_COLUMNAS; columna++){
            printf("|");
            if (terreno[fila][columna]==LUGAR_OCUPADO){
                printf("\033[31m %c \033[0m", terreno[fila][columna]);
            }
            else
                printf(" %c ", terreno[fila][columna]);
            if (columna==(MAX_COLUMNAS-1)){
                printf("|  ");
                imprimir_paciencia_mesas(&mesa, fila, mesas, cant_mesas);
                imprimir_barra_de_pedidos(fila, mozo, cocina, &pedido);
            }
        }   
    }
}
/*
*   Pre condiciones: juego debe estar previamente inicializado con 'inicializar juego'.
*   Post condiciones: Devuelve el caracter MOPA si el mozo posee la mopa, caso contrario devuelve
*                     el caracter VACIO.
*/
char caracter_mopa(bool tiene_mopa){
    if (tiene_mopa)
        return MOPA;
    return VACIO;
}
/*
*   Pre condiciones: juego debe estar previamente inicializado con 'inicializar_juego'.
*   Post condiciones: Devuelve el caracter PATIN si el mozo tiene un patin puesto, caso contrario
*                    devuelve el caracter vacio.
*/
char caracter_patin(bool patines_puestos){
    if (patines_puestos)
        return PATIN;
    return VACIO;
    
}
/*
*   Pre condiciones: juego debe estar previamente inicializado con 'inicializar juego'.
*   Post condiciones: Imprime por pantalla si el mozo posee la mopa, imprime la cantidad de movimientos
*                     realizados y el dinero obetnido.
*/
void imprimir_posesion_mopa_cant_mov_dinero_patines_pedidos(mozo_t mozo, int dinero, int movimientos, int cant_pedidos, int cant_bandeja){
    printf("[MOPA: -%c-] ", caracter_mopa(mozo.tiene_mopa));
    printf("[CANTIDAD DE MOVIMIENTOS: -%i-] ", movimientos);
    printf("[DINERO: -$%i-] ",dinero);
    printf("[PATINES: -%i-] [PATIN PUESTO: -%c-] ", mozo.cantidad_patines, caracter_patin(mozo.patines_puestos));
    printf("[MOZO[PEDIDOS -%i- | BANDEJA -%i-]]", cant_pedidos, cant_bandeja);
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
    printf(AMARILLO_COLOR "-\n" REINICIO_COLOR);
    imprimir_acciones_validas();
    imprimir_barra();
    imprimir_terreno_y_pedidos(terreno, juego.mozo, juego.cocina, juego.mesas, juego.cantidad_mesas);
    imprimir_barra();
    imprimir_posesion_mopa_cant_mov_dinero_patines_pedidos(juego.mozo, juego.dinero, juego.movimientos, juego.mozo.cantidad_pedidos, juego.mozo.cantidad_bandeja);
}

/*  Pre condiciones: Los campos `platos_preparacion` y `platos_listos` del campo `cocina` del juego deben estar inicializados.
    Post condiciones: Libera la memoria dinámica reservada para el juego.
*/
void destruir_juego(juego_t *juego){
    free(juego->cocina.platos_preparacion);
    free(juego->cocina.platos_listos);
}

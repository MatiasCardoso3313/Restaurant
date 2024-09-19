#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include "restaurant.h"
#include "complemento.h"
int main(){
    srand((unsigned)time(NULL));
    system("clear");
    juego_t juego;
    inicializar_juego(&juego);
    return 0;
}

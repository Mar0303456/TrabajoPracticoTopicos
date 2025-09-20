#include <stdio.h>
#include <stdlib.h>
#include "cabecera.h"
#include<SDL2/SDL.h>

int main(int argc, char *argv[])
{
   // printf("Hello world!\n");
    SDL_Window* ventana= NULL;
    SDL_Renderer* renderer =NULL;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(640, 480, 0, &ventana, &renderer);//creacion y renderizado de la ventana(tamaño q quiero que tenga la venatana)


    SDL_SetRenderDrawColor(renderer,0,0,0,255);//acá le digo q quiero que empiece con la ventana total black
    SDL_RenderClear(renderer);//aca hago limpieza de la ventana

    SDL_SetRenderDrawColor(renderer,255,255,255,255);//con estos parametros le digo q quiero el color blanco
    SDL_RenderDrawPoint(renderer,640/2,480/2);//dibujo un punto en el centro de la pantalla ancho/2 y altura/2

    SDL_RenderPresent(renderer);//aca lo q hace es MOSTRAR la ventana asi el usuario la ve
    SDL_Delay(10000);//para asegurarnos que se muestra se retrasa la ventana 10000milisegundos
    return 0;
}

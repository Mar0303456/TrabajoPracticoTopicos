/*
Apellido: Videla Fernando Martin
DNI: 39464751
Entrega: Si
Apellido:Mogni Santiago
DNI: 43718566
Entrega: Si
Apellido:Veliz Marianella Geraldine
DNI:
Entrega: Si
*/


#include <stdio.h>
#include <stdlib.h>
#include "cabecera.h"
#include <SDL2/SDL.h>

/*typedef struct MenuI
{
    const char opcion[20];
    int x;
    int y;
    MenuI *prev;
    MenuI *next;

}MenuI;*/

int main(int argc, char *argv[])
{

    SDL_Init (SDL_INIT_VIDEO);

    int contacto = 1;
    SDL_Window *ventana = SDL_CreateWindow("Juegito",
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           TAM_GRILLA * TAM_PIXEL * PIXELES_X_LADO + TAM_GRILLA * PAX_PADDING,
                                           TAM_GRILLA * TAM_PIXEL * PIXELES_X_LADO + TAM_GRILLA * PAX_PADDING,
                                           2);


    while(contacto)
    {
        SDL_Event e;
        if(SDL_WaitEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                contacto = 0;
            }
        }
    }

    SDL_DestroyWindow(ventana);
    SDL_Quit();

   // printf("Hello world!\n");
    /*SDL_Window* ventana= NULL;
    SDL_Renderer* renderer =NULL;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(640, 480, 0, &ventana, &renderer);//creacion y renderizado de la ventana(tama�o q quiero que tenga la venatana)


    SDL_SetRenderDrawColor(renderer,0,0,0,255);//ac� le digo q quiero que empiece con la ventana total black
    SDL_RenderClear(renderer);//aca hago limpieza de la ventana

    SDL_SetRenderDrawColor(renderer,255,255,255,255);//con estos parametros le digo q quiero el color blanco
    SDL_RenderDrawPoint(renderer,640/2,480/2);//dibujo un punto en el centro de la pantalla ancho/2 y altura/2

    SDL_RenderPresent(renderer);//aca lo q hace es MOSTRAR la ventana asi el usuario la ve
    SDL_Delay(10000);//para asegurarnos que se muestra se retrasa la ventana 10000milisegundos
    */

    return 0;
}

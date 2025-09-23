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
#include<time.h>
#include "cabecera.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>//Incluyo la biblioteca para poner texto
/*typedef struct MenuI
{
    const char opcion[20];
    int x;
    int y;
    MenuI *prev;
    MenuI *next;

}MenuI;*/


// Matriz 12x12: corazón (R = rojo, T = transparente)
/*
const int corazon[12][12] = {
    {T, T, R, R, T, T, T, T, R, R, T, T},
    {T, R, R, R, R, T, T, R, R, R, R, T},
    {R, R, R, R, R, R, R, R, R, R, R, R},
    {R, R, R, R, R, R, R, R, R, R, R, R},
    {T, R, R, R, R, R, R, R, R, R, R, T},
    {T, T, R, R, R, R, R, R, R, R, T, T},
    {T, T, T, R, R, R, R, R, R, T, T, T},
    {T, T, T, T, R, R, R, R, T, T, T, T},
    {T, T, T, T, T, R, R, T, T, T, T, T},
    {T, T, T, T, T, R, R, T, T, T, T, T},
    {T, T, T, T, T, T, T, T, T, T, T, T},
    {T, T, T, T, T, T, T, T, T, T, T, T}
};
*/
int main(int argc, char *argv[])
{

    SDL_Init (SDL_INIT_VIDEO);// inicializa sdl en formato video nada más(Acá se podria hacer una verificacion si no lo abre q tire error, con in if)
    TTF_Init();//inicializa la biblioteca para crear texto(Acá se podria hacer una verificacion si no lo abre q tire error, con in if)
    SDL_Window* ventana= NULL;
    SDL_Renderer* renderer =NULL;



      ////creación de la ventana"SDL_CreateWindow"
      int tamanoAncho=TAM_GRILLA * TAM_PIXEL * PIXELES_X_LADO + TAM_GRILLA * PX_PADDING;
    ventana = SDL_CreateWindow("Juegito",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               TAM_GRILLA * TAM_PIXEL * PIXELES_X_LADO + TAM_GRILLA * PX_PADDING,
                               TAM_GRILLA * TAM_PIXEL * PIXELES_X_LADO + TAM_GRILLA * PX_PADDING,
                               2);


   /*
   //entiendo que no deberia ir, porque con este while la ventana se queda esperando un evento, y nosotros no queremso tocar algo para que ahi recien me tire el menu,sino automaticamente apenas entras
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
    //SDL_DestroyWindow(ventana);
    //SDL_Quit();*/


   // SDL_CreateWindowAndRenderer(640, 480, 0, &ventana, &renderer);//creacion y renderizado de la ventana(tamaï¿½o q quiero que tenga la venatana)

    renderer = SDL_CreateRenderer(ventana,-1,SDL_RENDERER_ACCELERATED);//crea SOLAMENTE EL RENDERER


    SDL_SetRenderDrawColor(renderer,0,0,0,255);//acï¿½ le digo q quiero que empiece con la ventana total black
    SDL_RenderClear(renderer);//aca hago limpieza de la ventana


   // SDL_CreateWindowAndRenderer(640, 480, 0, &ventana, &renderer);//creacion y renderizado de la ventana(tamaño q quiero que tenga la venatana)




    TTF_Font *fuente = TTF_OpenFont("fuentes/arial.ttf", 72);//acá le pongo la ruta donde tengo la fuenwte que yo elegí
    if (!fuente)
    {
    printf("Error al abrir fuente: %s\n", TTF_GetError());
    return 1;
    }
/*
    //SDL_SetRenderDrawColor(renderer,0,0,0,255);//acá le digo q quiero que empiece con la ventana total black
    //SDL_RenderClear(renderer);//aca hago limpieza de la ventana

    //SDL_SetRenderDrawColor(renderer,255,255,255,255);//con estos parametros le digo q quiero el color blanco
    //SDL_RenderDrawPoint(renderer,640/2,480/2);//dibujo un punto en el centro de la pantalla ancho/2 y altura/2
*/
      int corriendo = 1;
      while (corriendo==1)
      {
            // bucle de EVENTOS
            SDL_Event e;
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)//e.type me dice el tipo de evento que hubo. SDL_QUIT=ocurre cuando el usuario hace click en la “X” de la ventana para cerrarla-> if(el tipo de interaccion==cerrar ventana) no corre el prog,asi que deberia cerrarse
                {
                    corriendo = 0;
                }
                //Es como un seguro extra para detectar el cierre de la ventana en todas las situaciones.
                else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE)//el “cerrar ventana” también llega como evento de tipo SDL_WINDOWEVENT
                     {
                         corriendo = 0;
                     }
            }


            // limpiar pantalla
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // dibujar texto
            SDL_Surface *surfTexto = TTF_RenderText_Blended(fuente, "MENU", colores[2]);//dibuja el texto en "formato vector"
            SDL_Texture *texTexto = SDL_CreateTextureFromSurface(renderer, surfTexto);
            SDL_FreeSurface(surfTexto);


            //destino indica dónde y de qué tamaño se va a dibujar la textura del texto “MENU”(posx,posy,ancho,alto)
            SDL_Rect destino = {(tamanoAncho-300)/2, 150, 300, 100};
            SDL_RenderCopy(renderer, texTexto, NULL, &destino);
            SDL_DestroyTexture(texTexto);

            // mostrar todo
            SDL_RenderPresent(renderer);//muestra la ventana para que el usuario la pueda ver
     }


    // limpieza
    TTF_CloseFont(fuente);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

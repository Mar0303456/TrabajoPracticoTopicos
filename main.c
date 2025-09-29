/*
Apellido: Videla Fernando Martin
DNI: 39464751
Entrega: Si
Apellido:Mogni Santiago
DNI: 43718566
Entrega: Si
Apellido:Veliz Marianella Geraldine
DNI:43301267
Entrega: Si
*/

#include "cabecera.h"



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

    renderer = SDL_CreateRenderer(ventana,-1,SDL_RENDERER_ACCELERATED);//crea SOLAMENTE EL RENDERER


    SDL_SetRenderDrawColor(renderer,0,0,0,255);//acï¿½ le digo q quiero que empiece con la ventana total black
    SDL_RenderClear(renderer);//aca hago limpieza de la ventana




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


     }


    // limpieza

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);

    SDL_Quit();
    return 0;
}

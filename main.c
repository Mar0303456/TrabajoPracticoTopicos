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
    Ventana ventana;
    sdl_inicializar(&ventana); // aca llamo a la funcion sdl_inicializar que crea la ventana y el render
    if (sdl_inicializar(&ventana) == false)
    {
        return -1;
    }
    // int tamanoAncho=TAM_GRILLA * TAM_PIXEL * PIXELES_X_LADO + TAM_GRILLA * PX_PADDING;

  //  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // ac� le digo q quiero que empiece con la ventana total black
    //SDL_RenderClear(renderer);                      // aca hago limpieza de la ventana

    int corriendo = 1;
    while (corriendo == 1)
    {
        // bucle de EVENTOS
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) // e.type me dice el tipo de evento que hubo. SDL_QUIT=ocurre cuando el usuario hace click en la �X� de la ventana para cerrarla-> if(el tipo de interaccion==cerrar ventana) no corre el prog,asi que deberia cerrarse
            {
                corriendo = 0;
            }
            // Es como un seguro extra para detectar el cierre de la ventana en todas las situaciones.
            else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE) // el �cerrar ventana� tambi�n llega como evento de tipo SDL_WINDOWEVENT
            {
                corriendo = 0;
            }
        }
    }
    // limpieza
    finalizar(&ventana); // aca llamo a la funcion finalizar que destruye el render y la ventana
    return 0;
}

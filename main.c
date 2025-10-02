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
    /*
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
    */
//-----------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------//

// Inicializacion de SDL (video + timer porque usamos SDL_GetTicks)
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    SDL_Window*   ventana  = NULL;
    SDL_Renderer* renderer = NULL;

    ventana = SDL_CreateWindow("SIMON",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               ancho,
                               alto,
                               2);

    renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);

    /* =======================
       Configuracion inicial
       ======================= */
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


    //----------------------------------------------------------------------------------------

    srand((unsigned)time(NULL));


    SimonJuego juego = {0};      //  deja todo en NULL/0
    simon_inicializar(&juego);   // ahora el free es seguro (puntero NULL)

    bool corriendo = true;
    SDL_Log("Presione 'Espacio para iniciar'");
    while (corriendo) {
        /* ---- EVENTOS ---- */
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) corriendo = false;
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        corriendo = false;
                        break;

                    case SDLK_SPACE:
                        // SPACE inicia desde LISTO, o reinicia despues de FIN_JUEGO
                        if (juego.estado == FIN_JUEGO) {
                            simon_inicializar(&juego);
                            simon_iniciar_ronda(&juego);
                            SDL_Log("Reinicio tras FIN_JUEGO: nueva secuencia");
                        } else if (juego.estado == LISTO) {
                            simon_iniciar_ronda(&juego);
                            SDL_Log("Inicio desde LISTO: mostrando secuencia");
                        }
                        break;

                    case SDLK_r:
                        if (juego.estado == FIN_JUEGO) simon_inicializar(&juego);
                        break;

                    case SDLK_1: simon_presionar_boton(&juego, botones, 0); break;
                    case SDLK_2: simon_presionar_boton(&juego, botones, 1); break;
                    case SDLK_3: simon_presionar_boton(&juego, botones, 2); break;
                    case SDLK_4: simon_presionar_boton(&juego, botones, 3); break;
                }
            }
                    // Mouse: iluminar el boton que clickeo
                    else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            int mx = e.button.x, my = e.button.y;
            for (int i = 0; i < 4; i++) {
                if (punto_en_rect(mx, my, &botones[i].rect)) {
                    simon_presionar_boton(&juego, botones, i); // usa la misma logica que el teclado
                        }
                    }
                }

        }

        /* ---- LOGICA ---- */
        actualizar_destellos(botones);

        if (juego.estado == MOSTRAR_SECUENCIA) {
            simon_actualizar_mostrar(&juego, botones);
        }
        else if (juego.estado == ENTRE_RONDAS) {
            Uint32 ahora = SDL_GetTicks();
            if (ahora >= juego.proximo_tick) {
                // Pausa cumplida -> preparar y comenzar la nueva secuencia
                apagar_todos_los_botones(botones);
                simon_agregar_paso(&juego);

                juego.indice_mostrar = 0;
                juego.fase_encendido = true;
                juego.proximo_tick   = ahora + TIEMPO_ON_MS;
                juego.estado         = MOSTRAR_SECUENCIA;
            }
        }

        /* ---- RENDER ---- */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        for (int i = 0; i < 4; i++)
            dibujar_boton(renderer, &botones[i]);

        SDL_RenderPresent(renderer);
    }
    SDL_Log("Juego finalizado!");
    //----------------------------------------------------------------------------------------



    simon_liberar(&juego); //libero la memoria que use para el juego
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(ventana);
    SDL_Quit();
    return 0;
}

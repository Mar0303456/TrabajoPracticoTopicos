#include "cabecera.h"

SDL_Color colores[] =
    {
        {0, 0, 0, 255},       // N[0] - Negro
        {255, 255, 0, 255},   // Y[1] - Amarillo
        {255, 255, 255, 255}, // B[2] - Blanco
        {0, 150, 60, 255},    // V[3] - Verde
        {255, 0, 0, 255},     // R[4] - Rojo
        {0, 0, 0, 0}          // T[5] - Transparente
};

bool sdl_inicializar(Ventana *v)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        prinf("Error iniciando SDL %s\n", SDL_GetError());
        return false;
    }

    v->window = SDL_CreateWindow("Juegito",
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 TAM_GRILLA * TAM_PIXEL * PIXELES_X_LADO + TAM_GRILLA * PX_PADDING,
                                 TAM_GRILLA * TAM_PIXEL * PIXELES_X_LADO + TAM_GRILLA * PX_PADDING,
                                 2);
    if (!v->window)
    {
        printf("Error iniciando SDL %s\n",SDL_GetError());
        return false;
    }
    
    v->render = SDL_CreateRenderer (v->window,-1,SDL_RENDERER_ACCELERATED);

    if (!v->render)
    {
        printf("Error creando render %s\n",SDL_GetError());
        return false;
    }
    
    return true;
}

void finalizar(Ventana *v)
{
    SDL_DestroyRenderer(v->render);
    SDL_DestroyWindow(v->window);
    SDL_Quit();
}
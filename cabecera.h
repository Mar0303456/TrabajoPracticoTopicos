#ifndef CABECERA_H_INCLUDED
#define CABECERA_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define TAM_GRILLA 6
#define PX_PADDING 4
#define PIXELES_X_LADO 12
#define TAM_PIXEL 10


#define NEGRO 0
#define AMARILLO 1
#define BLANCO 2
#define VERDE 3
#define ROJO 4
#define TRANSPARENTE 5

extern SDL_Color colores[];//extern solo declara que EXISTE un array, no lo define

#endif // CABECERA_H_INCLUDED

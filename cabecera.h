#ifndef CABECERA_H_INCLUDED
#define CABECERA_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <stdbool.h>
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

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *render;
}Ventana;

bool sld_inicializar(Ventana *);

void finalizar(Ventana *);


//-------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------//


/* =======================
   Tiempos y pausas (ms)
   ======================= */
#define TIEMPO_ON_MS             300   // cuánto dura encendido cada paso
#define TIEMPO_OFF_MS            200   // pausa apagado entre pasos
#define PAUSA_EXTRA_REPETIDO     150   // pausa extra si se repite el mismo botón
#define PAUSA_ENTRE_RONDAS       500   // pausa antes de iniciar una nueva ronda

/* =======================
   Estructuras
   ======================= */



// Botón del tablero(rectangulo)
typedef struct {
    SDL_Rect  rect;          // posición y tamaño
    SDL_Color color_base;    // color normal
    SDL_Color color_luz;     // color iluminado
    bool      encendido;     // ¿está iluminado ahora?
    Uint32    apagar_en_ms;  // instante (ms) en el que debe apagarse
} Boton;

// Estados del juego
typedef enum {
    LISTO,               // listo para empezar
    MOSTRAR_SECUENCIA,   // mostrando la secuencia (ON/OFF por paso)
    ESPERAR_ENTRADA,     // esperando que el jugador repita
    FIN_JUEGO,           // se equivocó
    ENTRE_RONDAS         // pausa entre ronda superada y la siguiente
} EstadoJuego;

// Estado global del Simon (con secuencia dinamica)
typedef struct {
    int        *secuencia;         // array dinamico con los pasos (0..3)
    int         longitud;          // cantidad de pasos guardados
    int         capacidad;         // capacidad reservada
    int         indice_mostrar;    // que paso estamos mostrando ahora
    int         indice_entrada;    // cuanto lleva ingresado el jugador
    bool        fase_encendido;    // ON (true) / OFF (false) durante MOSTRAR_SECUENCIA
    Uint32      proximo_tick;      // proximo cambio de fase/paso (en ms)
    EstadoJuego estado;            // estado actual del juego
} SimonJuego;

    // Botones (rectangulos)
    Boton botones[4] = {
        { .rect = {100,  80, 200, 200}, .color_base = {255,   0,   0,255}, .color_luz = {255,120,120,255} }, // rojo
        { .rect = {400,  80, 200, 200}, .color_base = {255, 165,   0,255}, .color_luz = {255,200,100,255} }, // naranja
        { .rect = {100, 500, 200, 200}, .color_base = {  0, 255,   0,255}, .color_luz = {160,255,160,255} }, // verde
        { .rect = {400, 500, 200, 200}, .color_base = {  0,   0, 255,255}, .color_luz = {160,160,255,255} }, // azul
    };


const int ancho = TAM_GRILLA * TAM_PIXEL * PIXELES_X_LADO + TAM_GRILLA * PX_PADDING;
const int alto  = TAM_GRILLA * TAM_PIXEL * PIXELES_X_LADO + TAM_GRILLA * PX_PADDING;


static bool punto_en_rect(int x, int y, const SDL_Rect* r);
void simon_presionar_boton(SimonJuego *sj, Boton botones[4], int k);
static void apagar_todos_los_botones(Boton botones[4]);
void simon_actualizar_mostrar(SimonJuego *sj, Boton botones[4]);
void simon_iniciar_ronda(SimonJuego *sj);
void simon_agregar_paso(SimonJuego *sj);
void simon_liberar(SimonJuego *sj);
void simon_inicializar(SimonJuego *sj);
void actualizar_destellos(Boton botones[4]);
void dibujar_boton(SDL_Renderer *renderer, Boton *b);





//-------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------//
#endif // CABECERA_H_INCLUDED

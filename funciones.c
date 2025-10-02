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

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//


/* =======================
   Dibujo y temporizacion
   ======================= */

// Dibuja un boton segun su estado (encendido/apagado)
void dibujar_boton(SDL_Renderer *renderer, Boton *b) {
    SDL_Color c = b->encendido ? b->color_luz : b->color_base;
    SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(renderer, &b->rect);

    // borde gris
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderDrawRect(renderer, &b->rect);
}

// Apaga automaticamente los botones cuyo tiempo ya vencio
void actualizar_destellos(Boton botones[4]) {
    Uint32 ahora = SDL_GetTicks();
    for (int i = 0; i < 4; i++) {
        if (botones[i].encendido && ahora >= botones[i].apagar_en_ms) {
            botones[i].encendido = false;
        }
    }
}

/* =======================
   Logica del Simon
   ======================= */

// Inicializa/Resetea el juego a LISTO con secuencia vacia
void simon_inicializar(SimonJuego *sj) {
    if (sj->secuencia) free(sj->secuencia);  // por si se viene de un reinicio
    sj->secuencia       = NULL;
    sj->longitud        = 0;
    sj->capacidad       = 0;
    sj->indice_mostrar  = 0;
    sj->indice_entrada  = 0;
    sj->fase_encendido  = false;
    sj->proximo_tick    = 0;
    sj->estado          = LISTO;
}

// Libera memoria (por si cierro el programa)
void simon_liberar(SimonJuego *sj) {
    free(sj->secuencia);
    sj->secuencia = NULL;
    sj->longitud  = 0;
    sj->capacidad = 0;
}

// Agrega un paso aleatorio (0..3) a la secuencia, usando realloc
void simon_agregar_paso(SimonJuego *sj) {
    if (sj->longitud >= sj->capacidad) {
        int nueva_cap = (sj->capacidad == 0) ? 4 : sj->capacidad * 2;
        int *tmp = realloc(sj->secuencia, nueva_cap * sizeof(int));
        if (!tmp) { fprintf(stderr, "Error de memoria!\n"); exit(1); }
        sj->secuencia = tmp;
        sj->capacidad = nueva_cap;
    }
    sj->secuencia[sj->longitud++] = rand() % 4;
}

// Comienza una ronda: agrega un paso y prepara MOSTRAR_SECUENCIA
void simon_iniciar_ronda(SimonJuego *sj) {
    simon_agregar_paso(sj);
    sj->indice_mostrar = 0;
    sj->fase_encendido = true;                      // empezamos encendiendo
    sj->proximo_tick   = SDL_GetTicks() + 400;      // primer ON un poquito mas largo
    sj->estado         = MOSTRAR_SECUENCIA;
    sj->indice_entrada = 0;
}

// Avanza la animacion de MOSTRAR_SECUENCIA (no bloqueante)
void simon_actualizar_mostrar(SimonJuego *sj, Boton botones[4]) {
    Uint32 ahora = SDL_GetTicks();

    if (sj->fase_encendido) {
        int k = sj->secuencia[sj->indice_mostrar];
        // prendo el boton del paso actual hasta proximo_tick
        botones[k].encendido   = true;
        botones[k].apagar_en_ms = sj->proximo_tick;

        if (ahora >= sj->proximo_tick) {
            // paso a OFF y apago todo para que se note el “negro”
            sj->fase_encendido = false;
            for (int i = 0; i < 4; ++i) botones[i].encendido = false;

            // OFF base
            Uint32 pausa_off = TIEMPO_OFF_MS;

            // si el proximo paso existe y es el mismo boton, agrego pausa extra
            if (sj->indice_mostrar + 1 < sj->longitud) {
                int siguiente = sj->secuencia[sj->indice_mostrar + 1];
                if (siguiente == k) pausa_off += PAUSA_EXTRA_REPETIDO;
            }
            sj->proximo_tick = ahora + pausa_off;
        }
    } else {
        // Fase OFF: cuando se cumple la pausa, avanzamos al siguiente paso
        if (ahora >= sj->proximo_tick) {
            sj->indice_mostrar++;
            if (sj->indice_mostrar >= sj->longitud) {
                // Termino de mostrar, ahora espera la entrada del jugador
                sj->estado         = ESPERAR_ENTRADA;
                sj->indice_entrada = 0;
            } else {
                // Proximo paso: prendemos de nuevo por TIEMPO_ON_MS
                sj->fase_encendido = true;
                sj->proximo_tick   = ahora + TIEMPO_ON_MS;
            }
        }
    }
}

// Apaga todos los botones (util al cambiar de estado)
static void apagar_todos_los_botones(Boton botones[4]) {
    for (int i = 0; i < 4; i++) {
        botones[i].encendido   = false;
        botones[i].apagar_en_ms = 0;
    }
}

// Procesa un boton presionado por el jugador (k = 0..3)
void simon_presionar_boton(SimonJuego *sj, Boton botones[4], int k) {
    // feedback visual corto del boton presionado
    botones[k].encendido    = true;
    botones[k].apagar_en_ms = SDL_GetTicks() + 250;

    if (sj->estado != ESPERAR_ENTRADA) return;

    // Si no coincide con lo esperado -> error
    if (k != sj->secuencia[sj->indice_entrada]) {
        for (int i = 0; i < 4; i++) {
            botones[i].encendido    = true;
            botones[i].apagar_en_ms = SDL_GetTicks() + 600; // “pantallazo” de error
        }
        sj->estado = FIN_JUEGO;
        return;
    }

    // Acierto: avanzamos el indice de entrada
    sj->indice_entrada++;

    // Si completo toda la secuencia actual, pasamos a ENTRE_RONDAS
    if (sj->indice_entrada >= sj->longitud) {
        Uint32 ahora       = SDL_GetTicks();
        Uint32 espera_input = (botones[k].apagar_en_ms > ahora)
                            ? (botones[k].apagar_en_ms - ahora) : 0;

        // Respetamos el flash del ultimo input y la pausa entre rondas
        Uint32 espera_total = (espera_input > PAUSA_ENTRE_RONDAS)
                            ? espera_input : PAUSA_ENTRE_RONDAS;

        sj->estado       = ENTRE_RONDAS;
        sj->proximo_tick = ahora + espera_total;
    }
}


// Funcion auxiliar: ¿un punto (x,y) esta dentro de un rectangulo?
static bool punto_en_rect(int x, int y, const SDL_Rect* r) {
    return (x >= r->x && x < r->x + r->w && y >= r->y && y < r->y + r->h);
}



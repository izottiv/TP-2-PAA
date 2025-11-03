#ifndef MAPA_H
#define MAPA_H

#include <stdio.h>

//Tipos de células do mapa
typedef enum {
    INTRANSITAVEL,
    DESCANSO,
    INIMIGO,
    ANCORA
} TipoCelula;

//Estrutura que representa uma célula do mapa
typedef struct {
    TipoCelula tipo;
    int valor; //0 para descanso/âncora/intransitável; número se for inimigo
} Celula;

// Aloca um mapa (matriz h x w)
Celula **alocarMapa(int h, int w);

// Libera memória do mapa
void liberarMapa(Celula **mapa, int h);

// Lê um mapa do arquivo e interpreta as células
void lerMapa(FILE *arquivo, Celula **mapa, int h, int w);

// Imprime o mapa(pra testar só, pode apagar depois)
void imprimirMapa(Celula **mapa, int h, int w);

#endif

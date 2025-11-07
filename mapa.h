#ifndef MAPA_H
#define MAPA_H

#include <stdio.h>

typedef char string;
int linhas, colunas;

#define INF 99999

//Tipos de células do mapa
typedef enum {
    DESCANSO,
    INIMIGO,
    ANCORA
} TipoCelula;

typedef enum {
    PRESENTE,
    PASSADO
} Tempo;

//Estrutura que representa uma célula do mapa
typedef struct {
    TipoCelula tipo;
    int valor; //0 para descanso/âncora/intransitável; número se for inimigo
} Celula;

typedef struct {
    int linha; 
    int coluna;
    int eAncora;
    Tempo mapa;
} posicao;


// Aloca um mapa (matriz h x w)
Celula **alocarMapa(int h, int w);

// Lê um mapa do arquivo e interpreta as células
void lerMapa(FILE *arquivo, char mapa[linhas][colunas][4], int h, int w);

void juntarMapas(int h, int w, char mapaPresente[h][w][4], char mapaPassado[h][w][4], char total[2 * h + 1][w][4]);

void identificaVertices(char mapaChar[linhas*2+1][colunas][4], posicao* posicoes, int slotsDiponiveis);

// Como é um grafo, queremos saber quantos vértices ele tem
int calculaSlotsDisponiveis(char mapa[linhas*2+1][colunas][4], int h, int w);

void iniciaGrafo(Celula** mapaGrafo, int slotsDisponiveis);

void conectaMapa(char mapaChar[linhas*2+1][colunas][4], Celula** mapaGrafo, int h, int w, int slotsDisponiveis, posicao* posicoes, int D);

void imprimeGrafo(Celula** mapaGrafo, int slotsDinponiveis);

// Libera memória do mapa
void liberarGrafo(Celula **mapa, int h);

#endif

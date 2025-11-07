#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>

int** alocarMapaInt(int tam);

void floyds(Celula** total, int** next, int tam);

void imprimirPontoColoridoP(int h, int w, char mapa[h][w][4], int linhaAtual, int colunaAtual);

void imprimirPontoColoridoPP(int h, int w, char mapa[h][w][4], int linhaAtual, int colunaAtual);

void imprimeCaminho(int h, int w, char mapaPresente[h][w][4],char mapaPassado[h][w][4], int u, int v, int** next, Celula** total, posicao* posicoes, int F, int N);
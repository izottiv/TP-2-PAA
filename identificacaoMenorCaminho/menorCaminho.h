#include "../manipulacaoMapa/mapa.h"
#include <stdlib.h>
#include <stdio.h>

int** alocarMapaInt(int tam);

double floyds(Celula** total, int** next, int tam);

void imprimirMapaInteiroColoridoP(int h, int w, char mapa[h][w][4], posicao caminho[], int tamanho);

void imprimirMapaInteiroColoridoPP(int h, int w, char mapa[h][w][4], posicao caminho[], int tamanho);

void imprimeCaminho(int escolha, int h, int w, char mapaPresente[h][w][4], char mapaPassado[h][w][4], int u, int v, int** next, Celula** total, posicao* posicoes, int F, int N);
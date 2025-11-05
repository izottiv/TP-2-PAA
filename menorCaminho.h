#include "mapa.h"
#include <stdlib.h>
#include <stdio.h>

int** alocarMapaInt(int tam);

void floyds(Celula** total, int** next, int tam);

void imprimeCaminho(int u, int v, int** next, posicao* posicoes, int h);
#ifndef MOVIMENTO_H
#define MOVIMENTO_H

#include "mapa.h"

//Movimentação
void movimento(Celula **mapaPresente, Celula **mapaPassado, int h, int w, int F, int D, int N, int **caminho, int tamanho_caminho);

#endif
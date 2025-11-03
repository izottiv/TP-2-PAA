#include "mapa.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Celula **alocarMapa(int h, int w) {
    Celula **mapa = malloc(h * sizeof(Celula *));
    for (int i = 0; i < h; i++) {
        mapa[i] = malloc(w * sizeof(Celula));
    }
    return mapa;
}

void liberarMapa(Celula **mapa, int h) {
    for (int i = 0; i < h; i++) {
        free(mapa[i]);
    }
    free(mapa);
}

void lerMapa(FILE *arquivo, Celula **mapa, int h, int w) {
    char buffer[4];
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (fscanf(arquivo, "%3s", buffer) != 1) {
                fprintf(stderr, "Erro ao ler célula (%d, %d).\n", i, j);
                exit(EXIT_FAILURE);
            }

            if (strcmp(buffer, "***") == 0) {
                mapa[i][j].tipo = INTRANSITAVEL;
                mapa[i][j].valor = 0;
            } else if (strcmp(buffer, "000") == 0) {
                mapa[i][j].tipo = DESCANSO;
                mapa[i][j].valor = 0;
            } else if (strcmp(buffer, "AAA") == 0) {
                mapa[i][j].tipo = ANCORA;
                mapa[i][j].valor = 0;
            } else {
                mapa[i][j].tipo = INIMIGO;
                mapa[i][j].valor = atoi(buffer); //"005" → 5
            }
        }
    }
}


void imprimirMapa(Celula **mapa, int h, int w) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            switch (mapa[i][j].tipo) {
                case INTRANSITAVEL: printf("*** "); break;
                case DESCANSO:      printf("000 "); break;
                case ANCORA:        printf("AAA "); break;
                case INIMIGO:       printf("%03d ", mapa[i][j].valor); break;
            }
        }
        printf("\n");
    }
}



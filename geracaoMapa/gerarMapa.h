#ifndef GERARMAPA_H_
#define GERARMAPA_H_


void gerarMapa();

int gerarNumeroAleatorio(int limite);

void gerarCaminhos(int altura, int largura, char* mapa[altura][largura], int xInicial, int yInicial, int xFinal, int yFinal, int quantidadeInimigos);

void gerarCaminhos2(int altura, int largura, char* mapa[altura][largura], int xInicial, int yInicial, int xFinal, int yFinal, int quantidadeInimigos);

#endif
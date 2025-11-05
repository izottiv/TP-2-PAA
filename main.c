#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menorCaminho.h"

#define TAM_NOME_ARQUIVO 50

int main() {
    char nome_arquivo[TAM_NOME_ARQUIVO];
    
    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", nome_arquivo);
    
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return EXIT_FAILURE;
    }

    int h, w, F, D, N;
    fscanf(arquivo, "%d %d %d %d %d", &h, &w, &F, &D, &N);

    linhas = h; colunas = w;
    char mapaPresente[linhas][colunas][4];
    char mapaPassado[linhas][colunas][4];


    lerMapa(arquivo, mapaPresente, h, w);

    char separador[4];
    fscanf(arquivo, "%3s", separador); //Lê o "///"
    
    lerMapa(arquivo, mapaPassado, h, w);
    fclose(arquivo);

    char mapasCombinados[linhas*2+1][colunas][4];
    juntarMapas(h,w,mapaPresente,mapaPassado,mapasCombinados);

    int slotsDisponiveis;
    slotsDisponiveis = calculaSlotsDisponiveis(mapasCombinados, h*2+1, w);


    Celula** mapaComoGrafo;
    mapaComoGrafo = alocarMapa(slotsDisponiveis, slotsDisponiveis);

    posicao posicoes[slotsDisponiveis];
    identificaVertices(mapasCombinados, posicoes, slotsDisponiveis);


    iniciaGrafo(mapaComoGrafo, slotsDisponiveis);
    conectaMapa(mapasCombinados, mapaComoGrafo, h*2+1, w, slotsDisponiveis, posicoes, D);
    

    int** guardarCaminho;
    guardarCaminho = alocarMapaInt(slotsDisponiveis);

    floyds(mapaComoGrafo, guardarCaminho, slotsDisponiveis); 
    // imprimeGrafo(mapaComoGrafo, slotsDisponiveis);

    imprimeCaminho(0, slotsDisponiveis-1, guardarCaminho, posicoes, h);

    liberarGrafo(mapaComoGrafo, slotsDisponiveis);

    // Teste de leitura
    /*printf("Altura: %d, Largura: %d\n", h, w);
    printf("Força inicial: %d, Descanso: %d, Força de Nikador: %d\n", F, D, N);

    printf("\n=== Mapa do Presente ===\n");
    imprimirMapa(mapaPresente, h, w);

    printf("\n=== Mapa do Passado ===\n");
    imprimirMapa(mapaPassado, h, w);

    liberarMapa(mapaPresente, h);
    liberarMapa(mapaPassado, h);
*/
    return 0;
}
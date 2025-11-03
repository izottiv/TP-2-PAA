#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"
#include "movimento.h"

#define TAM_NOME_ARQUIVO 50

//não me julgue por pedir o deep para criar um caminho exemplo pra teste, é só pra facilitar minha vida mesmo
//btw, copilot é bom demais pra comentario, nu, ele completa bonitinho o trem

int **criarCaminhoExemplo() {
    int **caminho = malloc(5 * sizeof(int *));
    for (int i = 0; i < 5; i++) {
        caminho[i] = malloc(2 * sizeof(int));
    }
    
    caminho[0][0] = 2; caminho[0][1] = 0;
    caminho[1][0] = 1; caminho[1][1] = 1;
    caminho[2][0] = 1; caminho[2][1] = 2;
    caminho[3][0] = 0; caminho[3][1] = 3;
    caminho[4][0] = 1; caminho[4][1] = 4;
    
    return caminho;
}

int main() {
    char nome_arquivo[TAM_NOME_ARQUIVO];
    
    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", nome_arquivo);
    
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    int h, w, F, D, N;
    fscanf(arquivo, "%d %d %d %d %d", &h, &w, &F, &D, &N);

    Celula **mapaPresente = alocarMapa(h, w);
    Celula **mapaPassado  = alocarMapa(h, w);

    lerMapa(arquivo, mapaPresente, h, w);

    char separador[4];
    fscanf(arquivo, "%3s", separador);
    
    lerMapa(arquivo, mapaPassado, h, w);
    fclose(arquivo);

    //Teste do movimento com caminho srtificial
    int **caminho = criarCaminhoExemplo();
    movimento(mapaPresente, mapaPassado, h, w, F, D, N, caminho, 5);
    
    //Libera memória
    for (int i = 0; i < 5; i++) {
        free(caminho[i]);
    }
    free(caminho);

    liberarMapa(mapaPresente, h);
    liberarMapa(mapaPassado, h);

    return 0;
}
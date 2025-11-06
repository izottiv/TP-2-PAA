#include "menorCaminho.h"

int** alocarMapaInt(int tam){
    int **mapa = malloc(tam * sizeof(int *));
    for (int i = 0; i < tam; i++) {
        mapa[i] = malloc(tam * sizeof(int));
    }
    return mapa;
}

void floyds(Celula** total, int** next, int tam) {
    int i, j, k;

    // Inicializa a matriz next, que serve para guardar o caminho que encontrarmos
    for (i = 0; i < tam; i++) {
        for (j = 0; j < tam; j++) {
            if (total[i][j].valor != INF && i != j)
                next[i][j] = j; // há aresta direta
            else
                next[i][j] = -1; // sem caminho direto
        }
    }

    int novoCaminho;

    // Algoritmo principal
    // Para todos os vértices, percorre procurando um menor caminho, e armazenando na matriz esse valor de menor caminho
    for (k = 0; k < tam; k++) {
        for (i = 0; i < tam; i++) {
            for (j = 0; j < tam; j++) {
                // Se existir caminho i->k e k->j, vê se ele é o melhor para chegar em i -> j
                if (total[i][k].valor != INF && total[k][j].valor != INF && i != j) {
                    novoCaminho = total[i][k].valor + total[k][j].valor;
                    //Se for, vai atualizar o menor valor
                    if (novoCaminho < total[i][j].valor) {
                        total[i][j].valor = novoCaminho;
                        //Armazena falando tipo, "para chegar em j passando por i, vamos olhar pro menor caminho usando i -> k"
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }
}


void imprimeCaminho(int u, int v, int** next, Celula** total, posicao* posicoes, int h, int F, int N) {
    if (next[u][v] == -1 ) {
        printf("A calamidade de Nikador e inevitavel");
        return;
    }
    posicao caminho[100];
    int inicio = 0;
    int i=0;
    while (u != v) {
        if(next[u][v] == v){
            break;
        }
        u = next[u][v];
        if(posicoes[u].coluna < h){
            caminho[i].linha = posicoes[u].linha; 
            caminho[i].coluna = posicoes[u].coluna;
            i++;
        } else if(posicoes[u].eAncora == 0) {
            caminho[i].linha = posicoes[u].linha; 
            caminho[i].coluna = posicoes[u].coluna -h -1;
            i++;
        } 
    } 
    int custo = total[inicio][v].valor;
    F -= custo;
    if (F <= 0) {
        printf("A calamidade de Nikador e inevitavel\n");
        return;
    }

    for (int j = 0; j < i; j++) {
        printf("%d %d\n", caminho[j].coluna, caminho[j].linha);
    }

    if(F>=N){
        printf("A ruina de Nikador e iminente\n");
    }
    else{
        printf("Sera necessario mais planejamento para parar a calamidade\n");
    }
}

#include "menorCaminho.h"
#include <string.h>
#include <time.h>
#if _WIN32 || _WIN64
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

int** alocarMapaInt(int tam){
    int **mapa = malloc(tam * sizeof(int *));
    for (int i = 0; i < tam; i++) {
        mapa[i] = malloc(tam * sizeof(int));
    }
    return mapa;
}

double floyds(Celula** total, int** next, int tam) {
    int i, j, k;
    clock_t t1, t2;
    t1 = clock();
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
    t2 = clock();
    double diff = (float)(t2 - t1) / CLOCKS_PER_SEC;
    return diff; 
}

void imprimirPontoColorido(int h, int w, char mapa[h][w][4], int linhaAtual, int colunaAtual) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (i == linhaAtual && j == colunaAtual) {
                if (strcmp(mapa[i][j],"TTT") == 0){
                    printf("\033[1;35m%s\033[0m ", mapa[i][j]);
                }
                else{
                    printf("\033[1;32m%s\033[0m ", mapa[i][j]);
                }
            } else {
                printf("%s ", mapa[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void imprimirMapaInteiroColoridoP(int h, int w, char mapa[h][w][4], posicao caminho[], int tamanho) {
    printf("PRESENTE:\n");
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int k;
            for (k = 0; k < tamanho; k++) {
                if (caminho[k].mapa == PRESENTE && i == caminho[k].linha && j == caminho[k].coluna) {
                    if (strcmp(mapa[i][j],"TTT") == 0){
                    printf("\033[1;35m%s\033[0m ", mapa[i][j]);
                    }
                    else{
                        printf("\033[1;32m%s\033[0m ", mapa[i][j]);
                    }
                    break;
                }
            }
            if (k == tamanho) {
                printf("%s ", mapa[i][j]);
            }
        }
        printf("\n");
    } printf("\n");
}

void imprimirMapaInteiroColoridoPP(int h, int w, char mapa[h][w][4], posicao caminho[], int tamanho) {
    printf("PASSADO:\n");
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int k;
            for (k = 0; k < tamanho; k++) {
                if (caminho[k].mapa == PASSADO && i == caminho[k].linha && j == caminho[k].coluna) {
                    if (strcmp(mapa[i][j],"TTT") == 0){
                    printf("\033[1;35m%s\033[0m ", mapa[i][j]);
                    }
                    else{
                        printf("\033[1;32m%s\033[0m ", mapa[i][j]);
                    }
                    break;
                }
            }
            if (k == tamanho) {
                printf("%s ", mapa[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void imprimeCaminho(int escolha, int h, int w, char mapaPresente[h][w][4], char mapaPassado[h][w][4], int u, int v, int** next, Celula** total, posicao* posicoes, int F, int N) {
    if (next[u][v] == -1 ) {
        printf("A calamidade de Nikador e inevitavel\n");
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
        if(posicoes[u].linha < h){
            caminho[i].coluna = posicoes[u].coluna; 
            caminho[i].linha = posicoes[u].linha;
            caminho[i].mapa = PRESENTE;
            caminho[i].eTunel = posicoes[u].eTunel;
            i++;
        } else if(posicoes[u].eAncora == 0) {
            caminho[i].coluna = posicoes[u].coluna; 
            caminho[i].linha = posicoes[u].linha -h -1;
            caminho[i].mapa = PASSADO;
            caminho[i].eTunel = posicoes[u].eTunel;
            i++;
        } 
    } 
    int custo = total[inicio][v].valor;
    F -= custo;
    if (F <= 0) {
        printf("A calamidade de Nikador e inevitavel\n");
        return;
    }
    if(escolha == 2){
    for (int j = 0; j < i; j++) {
        printf("%d %d\n", caminho[j].linha, caminho[j].coluna);
        if(caminho[j].mapa == PRESENTE){
            printf("PRESENTE:\n");
            imprimirPontoColorido(h, w, mapaPresente, caminho[j].linha, caminho[j].coluna);}
        else{
            printf("PASSADO:\n");
            imprimirPontoColorido(h, w, mapaPassado, caminho[j].linha, caminho[j].coluna);
        }
        #if _WIN32 || _WIN64
        Sleep(500);
        #else
        usleep(500*1000);  
      #endif
    }
    printf("CAMINHO FINAL:\n\n");
    #if _WIN32 || _WIN64
        Sleep(500);
        #else
        usleep(500*1000);  
      #endif
    imprimirMapaInteiroColoridoP(h,w,mapaPresente,caminho,i);

    #if _WIN32 || _WIN64
        Sleep(500);
        #else
        usleep(500*1000);  
      #endif
     imprimirMapaInteiroColoridoPP(h,w,mapaPassado,caminho,i);
    #if _WIN32 || _WIN64
        Sleep(500);
        #else
        usleep(500*1000);  
      #endif
    if(F>=N){
        printf("A ruina de Nikador e iminente\n\n");
    }
    else{
        printf("Sera necessario mais planejamento para parar a calamidade\n\n");
    }
    #if _WIN32 || _WIN64
        Sleep(500);
        #else
        usleep(500*1000);  
      #endif
    }
    else{
        for (int j = 0; j < i; j++) {
        printf("%d %d\n", caminho[j].linha, caminho[j].coluna);
        if (caminho[j].eTunel){
            printf("Encontramos Nikador na saida do tunel\n");
        }
        
    }
    printf("\n");
    if(F>=N){
        printf("A ruina de Nikador e iminente\n\n");
    }
    else{
        printf("Sera necessario mais planejamento para parar a calamidade\n\n");
    }
}
}

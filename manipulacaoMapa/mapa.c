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

void liberarGrafo(Celula **mapa, int h){
    for (int i = 0; i < h; i++) {
        free(mapa[i]);
    }
    free(mapa);
}

void lerMapa(FILE *arquivo, char mapa[linhas][colunas][4], int h, int w) {
    char buffer[4];
    int ajuda = -1; 
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < w; j++) {
            if (fscanf(arquivo, "%3s", buffer) != 1) {
                fprintf(stderr, "Erro ao ler célula (%d, %d).\n", i, j);
                exit(EXIT_FAILURE);
            }
            strcpy(mapa[i][j], buffer);
        }
    }
}

void juntarMapas(int h, int w, char mapaPresente[h][w][4], char mapaPassado[h][w][4], char total[2 * h + 1][w][4]) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            strcpy(total[i][j], mapaPresente[i][j]);
        }
    }

    for(int i = 0; i < w; i++){
        strcpy(total[h][i], "///");
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            strcpy(total[i + h + 1][j], mapaPassado[i][j]);
        }
    }
}


int calculaSlotsDisponiveis(char mapa[linhas*2+1][colunas][4], int h, int w){
    int total = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if(strcmp(mapa[i][j], "///") == 0){
                continue;
            } else if(strcmp(mapa[i][j], "***") == 1){
                total++;
            } 
        }
    }

    return total + 2;
    // Porque tem o vértice final e inicial
}

void iniciaGrafo(Celula** mapaGrafo, int slotsDisponiveis){
    for(int i = 0; i < slotsDisponiveis; i++){
        for(int j = 0; j <slotsDisponiveis; j++){
            if(i == j){
                mapaGrafo[i][j].valor = 0;
            } else {
                mapaGrafo[i][j].valor = INF;     
            }
        }
    }
}

//Identifica a posição na matriz de caracteres de todos os vértices válidos e vê se eles são âncora
void identificaVertices(char mapaChar[linhas*2+1][colunas][4], posicao* posicoes, int slotsDiponiveis){
    int preechidos = 1; 
    posicoes[0].coluna = -1; posicoes[0].linha = -1; 
    posicoes[slotsDiponiveis-1].coluna = -2; posicoes[slotsDiponiveis-1].linha = -2;

    for(int i = 0; i <colunas; i++){
        for(int j = 0; j<linhas*2+1; j++){
            if(strcmp(mapaChar[j][i], "***") == 1 && strcmp(mapaChar[j][i], "///") == 1){
                    posicoes[preechidos].linha = j;
                    posicoes[preechidos].coluna = i;
                
                if(strcmp(mapaChar[j][i], "AAA") == 0){
                    posicoes[preechidos].eAncora = 1;
                    posicoes[preechidos].eTunel = 0;
                }else if (strcmp(mapaChar[j][i], "TTT") == 0){
                    posicoes[preechidos].eAncora = 0;
                    posicoes[preechidos].eTunel = 1;
                }
                else {
                    posicoes[preechidos].eAncora = 0;
                    posicoes[preechidos].eTunel = 0;
                }
                preechidos++;
            }
        }
    }
}


TipoCelula defineTipoCelula(char tipo[4]){
    if(strcmp(tipo, "AAA") == 0){
        return ANCORA;
    } else if(strcmp(tipo, "000") == 0){
        return DESCANSO;
    } else if(strcmp(tipo, "TTT") == 0){
        return TUNEL; 
    } else {
        return INIMIGO;
    }
}

//preenche a matriz de adjacência usando o mapa que é um char e as posições dos vértices no mapa
void conectaMapa(char mapaChar[linhas*2+1][colunas][4], Celula** mapaGrafo, int h, int w, int slotsDisponiveis, posicao* posicoes, int D){


    //procura todas as conexão de todos os vérties
    /*O código procura se existe conexão de todos os vértices para todos os vértices, sendo i o vertice de origem e j o de destino*/
    for(int i = 0; i < slotsDisponiveis - 1; i++){ 
        for(int j = 0; j <slotsDisponiveis; j++){
            /*Caso i seja o primeiro vértice e estejamos percorrendo a primeira linha do mapa do presente*/
            /*Ou*/
            /*Se existir nos disponíves um vértice cuja linha que seja igual à (linha do vertice de origem)+1 ao mesmo tempo que sua coluna seja igual à coluna do vertice de origem (quando fica na frente/a direita)*/
            /*Ou*/
            /*Se existir nos disponíves um vértice cuja linha seja igual à (linha do vertice de origem)+1 ao mesmo tempo que sua coluna seja igual à (coluna do vertice de origem) - 1 (quando fica em cima)*/
            /*Ou*/
            /*Se existir nos disponíves um vértice cuja linha seja igual à (linha do vertice de origem)+1 ao mesmo tempo que sua coluna seja igual à (coluna do vertice de origem) + 1 (quando fica em baixo)*/
            /*Ele define o tipo de celula, se for descanso ele ele coloca como negativo o valor que recuperamos, pra indicar uma escolher que diminiu o caminho no grafo
            Se não for descanso, vai colocar o valor que está no char usando atoi (005 -> 5)*/
            if((i == 0 && posicoes[j].coluna == 0 && posicoes[j].linha < h/2) ||
            (posicoes[i].coluna+1 == posicoes[j].coluna && posicoes[i].linha == posicoes[j].linha) ||
            (posicoes[i].coluna+1 == posicoes[j].coluna && posicoes[i].linha-1 == posicoes[j].linha) ||
            (posicoes[i].coluna+1 == posicoes[j].coluna && posicoes[i].linha+1 == posicoes[j].linha)){
                
                mapaGrafo[i][j].tipo = defineTipoCelula(mapaChar[posicoes[j].linha][posicoes[j].coluna]);
                if(mapaGrafo[i][j].tipo == DESCANSO){
                    mapaGrafo[i][j].valor = -1 * D;
                } else {
                    mapaGrafo[i][j].valor = atoi(mapaChar[posicoes[j].linha][posicoes[j].coluna]);
                }
                
            }


            /*Depois, ao verificar todas as conexões normais, procura pelas conexões de âncoras
            Caso eles tenham correspondentes na mesma linha e em uma linha (h/2)-1 acima, e forem do tipo âncora, então vão ter uma conexão*/

            if(posicoes[i].linha+(h/2)+1 == posicoes[j].linha && posicoes[i].coluna == posicoes[j].coluna && strcmp(mapaChar[posicoes[i].linha][posicoes[i].coluna], "AAA") == 0){
                mapaGrafo[i][j].valor = 0;
                mapaGrafo[j][i].valor = 0;
            }

            if (posicoes[i].eTunel){
                if (i % 2 == 0){
                    mapaGrafo[i][0].valor = 0;
                }else{
                    mapaGrafo[i][slotsDisponiveis - 1].valor = 0;
                }
            }

            /*Se eles estão na linha da esquerda da matriz de mapa, eles vão ser conectados ao vértice final (o boss)*/
            if(posicoes[i].coluna == w - 1){
                mapaGrafo[i][slotsDisponiveis - 1].valor = 0; 
            }

        }
    }

}

void imprimeGrafo(Celula** mapaGrafo, int slotsDinponiveis){
    for(int i = 0; i < slotsDinponiveis; i++){
        for(int j = 0; j <slotsDinponiveis; j++){
          printf("%d ", mapaGrafo[i][j].valor);
        } printf("\n");
    }
}
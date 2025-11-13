#include "gerarMapa.h"
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include  "../manipulacaoMapa/mapa.h"

void gerarMapa(){
    srand(time(NULL));
    static int contador = 1;
    char nomeArquivo[100];
    sprintf(nomeArquivo, "arquivosDeEntrada/ArquivoGerado%d.txt", contador);
    contador++;
    FILE* file = fopen(nomeArquivo, "w");
    int altura, largura, forcaIncial, recuperacao, forcaNikador, inimigos, caminhos, linha, coluna, escolha, escolha2, escolha3, quantidadeInimigos;
    if(file){
        printf("==== BEM VINDO A GERACAO DE MAPAS ====\n");
        printf("Gostaria de gerar o arquivo escolhendo apenas a dificuldade do mapa ou gostaria de montar o mapa manualmente?\n");
        printf("1 - Dificuldades\n2 - Configuracao Total\nEscolha: ");
        scanf("%d", &escolha);
        printf("Gostaria de adicionar tuneis?\n1 - Sim\n2 - Nao\nEscolha: ");
        scanf("%d", &escolha3);
        if(escolha == 1){
            printf("Escolha a dificuldade:\n1 - Facil (Forca alta / Mapa pequeno)\n2 - Medio (Forca media / Mapa medio)\n3 - Dificil (Forca baixa / Mapa grande)\nEscolha: ");
            scanf("%d", &escolha2);
            switch(escolha2){
                case 1: 
                    altura = rand() % 3 + 4;   
                    largura = rand() % 3 + 4; 
                    forcaIncial = 100;
                    recuperacao = 6;
                    forcaNikador = 35;
                    quantidadeInimigos = 15;
                    break;

                case 2:
                    altura = rand() % 3 + 6;  
                    largura = rand() % 3 + 6;
                    forcaIncial = 90;
                    recuperacao = 3;
                    forcaNikador = 45;
                    quantidadeInimigos = 25;
                    break;

                case 3:
                    altura = rand() % 6 + 5;   
                    largura = rand() % 6 + 5;
                    forcaIncial = 80;
                    recuperacao = 2;
                    forcaNikador = rand() % 11 + 50; 
                    quantidadeInimigos = 30;
                    break;
            }
        }
        else{
        printf("Qual deve ser a altura e largura do mapa (separados por espaco)?\n");
        scanf("%d %d", &altura, &largura);
        printf("Qual deve ser a forca inicial da tripulacao?\n");
        scanf("%d", &forcaIncial);
        printf("Qual e o valor recuperado a cada descanso?\n");
        scanf("%d", &recuperacao);
        printf("Qual a forca de Nikador?\n");
        scanf("%d", &forcaNikador);
        printf("Qual deve ser a quantidade maxima de inimigos em um quadrante (ate 999)?\n");
        scanf("%d", &quantidadeInimigos);
        if(quantidadeInimigos>999){
            quantidadeInimigos == 999;
        }}
        fprintf(file, "%d %d %d %d %d\n", altura, largura, forcaIncial, recuperacao, forcaNikador);
        char* mapa[altura][largura];
        char* mapa2[altura][largura]; 
        int quantidade;
            if (altura < 3) {
                quantidade = 1; 
            } else {
                quantidade = rand() % (altura - 3)+2; 
            }
        int quantidade2;
            if (altura < 3) {
                quantidade2 = 1; 
            } else {
                quantidade2 = rand() % (altura - 3)+2; 
            }
        int tuneis = (rand()%3)+1;
        posicao ancoras[2];
        posicao posicoesI[quantidade];
        posicao posicoesF[quantidade];
        posicao posicoesI2[quantidade2];
        posicao posicoesF2[quantidade2];
        posicao tuneisL[tuneis];

        for (int i = 0; i < altura; i++) {
            for (int j = 0; j < largura; j++) {
                mapa[i][j] = malloc(4 * sizeof(char)); 
                mapa2[i][j] = malloc(4 * sizeof(char));
                strcpy(mapa[i][j], "***");
                strcpy(mapa2[i][j], "***");
            }
        } 
        for (int i = 0; i < 2 * quantidade; i++) {
        int linha = gerarNumeroAleatorio(altura); 
        if (i < quantidade) { 
            if (strcmp(mapa[linha][0], "***") == 0 && strcmp(mapa[linha][0], "AAA") != 0) {
                int inimigos = rand() % quantidadeInimigos;  
                char str[12];
                sprintf(str, "%03d", inimigos);
                strcpy(mapa[linha][0], str);
                posicoesI[i].linha = linha; posicoesI[i].coluna = 0;
            } else {
                i--; 
            }
        } else {
            if (strcmp(mapa[linha][largura - 1], "***") == 0 && strcmp(mapa[linha][largura - 1], "AAA") != 0) {
                int inimigos = rand() % quantidadeInimigos;  
                char str[12];
                sprintf(str, "%03d", inimigos);
                strcpy(mapa[linha][largura - 1], str);
                posicoesF[i - quantidade].linha = linha; 
                posicoesF[i - quantidade].coluna = largura - 1;    
            } else {
                i--; 
            }
        }
    }

    for (int i = 0; i < 2 * quantidade2; i++) {
    int linha = gerarNumeroAleatorio(altura); 
        if (i < quantidade2) { 
            if (strcmp(mapa2[linha][0], "***") == 0 && strcmp(mapa2[linha][0], "AAA") != 0) {
                int inimigos = rand() % quantidadeInimigos;  
                char str[12];
                sprintf(str, "%03d", inimigos);
                strcpy(mapa2[linha][0], str);
                 posicoesI2[i].linha = linha; posicoesI2[i].coluna = 0;
            } else {
                i--; 
            }
        } else {
            if (strcmp(mapa2[linha][largura - 1], "***") == 0 && strcmp(mapa2[linha][largura - 1], "AAA") != 0) {
                int inimigos = rand() % quantidadeInimigos;  
                char str[12];
                sprintf(str, "%03d", inimigos);
                strcpy(mapa2[linha][largura - 1], str);
                posicoesF2[i - quantidade2].linha = linha; 
                posicoesF2[i - quantidade2].coluna = largura - 1;
            } else {
                i--; 
            }
        }
    }


        for(int i=0;i<2;i++){
        linha = gerarNumeroAleatorio(altura);
        coluna = gerarNumeroAleatorio(largura-2)+1;
            if(strcmp(mapa[linha][coluna], "***") == 0 && strcmp(mapa2[linha][coluna], "***") == 0){
                strcpy(mapa[linha][coluna], "AAA");
                ancoras[i].linha = linha; ancoras[i].coluna= coluna; 
                strcpy(mapa2[linha][coluna],"AAA");
            }
            else{
                i--;
            }
        }
        if(escolha3 == 1){
        
        for(int i=0;i<tuneis;i++){
        linha = gerarNumeroAleatorio(altura);
        coluna = gerarNumeroAleatorio(largura-2)+1;
        printf("ue");
        int escolhaMapa = rand()%2;
            if(escolhaMapa==0){
                 if(strcmp(mapa[linha][coluna], "***") == 0){
                strcpy(mapa[linha][coluna], "TTT");
                tuneisL[i].linha = linha; tuneisL[i].coluna = coluna;tuneisL[i].mapa = PRESENTE;
            }
            }else if(escolhaMapa == 1){
                if(strcmp(mapa2[linha][coluna], "***") == 0){
                strcpy(mapa2[linha][coluna],"TTT");
                tuneisL[i].linha = linha; tuneisL[i].coluna = coluna;tuneisL[i].mapa = PASSADO;
                }
            }
            else{
                i--;
            }
        }}

        for(int i=0;i<quantidade;i++){
            for(int j=0;j<2;j++){
            gerarCaminhos(altura, largura, mapa, posicoesI[i].linha, posicoesI[i].coluna, ancoras[j].linha, ancoras[j].coluna, quantidadeInimigos);
            gerarCaminhos2(altura, largura, mapa,ancoras[j].linha, ancoras[j].coluna, posicoesF[i].linha, posicoesF[i].coluna, quantidadeInimigos);
        }
    }

     for(int i=0;i<quantidade2;i++){
            for(int j=0;j<2;j++){
            gerarCaminhos2(altura, largura, mapa2, posicoesI2[i].linha, posicoesI2[i].coluna, ancoras[j].linha, ancoras[j].coluna, quantidadeInimigos);
            gerarCaminhos(altura, largura, mapa2,ancoras[j].linha, ancoras[j].coluna, posicoesF2[i].linha, posicoesF2[i].coluna, quantidadeInimigos);
        }
    }

    if(escolha3 == 1){
    for(int j=0;j<tuneis;j++){
        if(tuneisL[j].mapa == PRESENTE){
            for(int i=0;i<quantidade;i++){
            gerarCaminhos(altura, largura, mapa, posicoesI[i].linha, posicoesI[i].coluna, tuneisL[j].linha, tuneisL[j].coluna, quantidadeInimigos);
            }}
        if(tuneisL[j].mapa == PASSADO){
            for(int i=0;i<quantidade2;i++){
                gerarCaminhos2(altura, largura, mapa2, posicoesI2[i].linha, posicoesI2[i].coluna, tuneisL[j].linha, tuneisL[j].coluna, quantidadeInimigos);
            }}
        }}
    
        for(int i=0;i<altura;i++){
            for(int j=0;j<largura;j++){
                fprintf(file, "%s ", mapa[i][j]);
            }fprintf(file, "\n");
        }
        fprintf(file, "///\n");
        for(int i=0;i<altura;i++){
            for(int j=0;j<largura;j++){
                fprintf(file, "%s ", mapa2[i][j]);
            }fprintf(file, "\n");
        }
        
        for (int i = 0; i < altura; i++) {
            for (int j = 0; j < largura; j++) {
                free(mapa[i][j]);
                free(mapa2[i][j]);
            }
        }

    }
    fclose(file);
}

int gerarNumeroAleatorio(int limite){
    return rand() % limite;
}

void gerarCaminhos(int altura, int largura, char* mapa[altura][largura], int xInicial, int yInicial, int xFinal, int yFinal, int quantidadeInimigos){
    int x = xInicial, y = yInicial;
    while (x != xFinal || y != yFinal) {
            if (x < xFinal && y < yFinal && x + 1 < altura && y + 1 < largura) {
                x++; y++;
                if (strcmp(mapa[x][y], "***")==0){
                    int inimigos = rand() % quantidadeInimigos;  
                    char str[12];
                    sprintf(str, "%03d", inimigos);
                    strcpy(mapa[x][y], str);}
            }
            else if (x > xFinal && y < yFinal && x - 1 >= 0 && y + 1 < largura) {
                x--; y++;
                if (strcmp(mapa[x][y], "***")==0){
                    int inimigos = rand() % quantidadeInimigos;  
                    char str[12];
                    sprintf(str, "%03d", inimigos);
                    strcpy(mapa[x][y], str);}
            }
            else if (x < xFinal && x + 1 < altura) {
                x++;
                if (strcmp(mapa[x][y], "***")==0){
                    int inimigos = rand() % quantidadeInimigos;  
                    char str[12];
                    sprintf(str, "%03d", inimigos);
                    strcpy(mapa[x][y], str);}
            } 
            else if (x > xFinal && x - 1 >= 0) {
                x--;
                if (strcmp(mapa[x][y], "***")==0){
                    int inimigos = rand() % quantidadeInimigos;  
                    char str[12];
                    sprintf(str, "%03d", inimigos);
                    strcpy(mapa[x][y], str);}
            } 
            else if (y < yFinal && y + 1 < largura ) {
                y++;
                if (strcmp(mapa[x][y], "***")==0){
                    int inimigos = rand() % quantidadeInimigos;  
                    char str[12];
                    sprintf(str, "%03d", inimigos);
                    strcpy(mapa[x][y], str);}
            } 
            else if (y > yFinal && y - 1 >= 0) {
                y--;
                if (strcmp(mapa[x][y], "***")==0){
                    int inimigos = rand() % quantidadeInimigos;  
                    char str[12];
                    sprintf(str, "%03d", inimigos);
                    strcpy(mapa[x][y], str);}
            }
    }
}

void gerarCaminhos2(int altura, int largura, char* mapa[altura][largura], int xInicial, int yInicial, int xFinal, int yFinal, int quantidadeInimigos){
    int x = xInicial, y = yInicial;
    while (x != xFinal || y != yFinal) {
            if (x < xFinal && y < yFinal && x + 1 < altura && y + 1 < largura) {
                x++; y++;
                if (strcmp(mapa[x][y], "***")==0){
                    int inimigos = rand() % quantidadeInimigos;  
                    char str[12];
                    sprintf(str, "%03d", inimigos);
                    strcpy(mapa[x][y], str);}
            }
            else if (x > xFinal && y < yFinal && x - 1 >= 0 && y + 1 < largura) {
                x--; y++;
                if (strcmp(mapa[x][y], "***")==0){
                    int inimigos = rand() % quantidadeInimigos;  
                    char str[12];
                    sprintf(str, "%03d", inimigos);
                    strcpy(mapa[x][y], str);}
            }
            else if (y < yFinal && y + 1 < largura ) {
                y++;
                if (strcmp(mapa[x][y], "***")==0){
                    int inimigos = rand() % quantidadeInimigos;  
                    char str[12];
                    sprintf(str, "%03d", inimigos);
                    strcpy(mapa[x][y], str);}
            } 
            else if (y > yFinal && y - 1 >= 0) {
                y--;
                if (strcmp(mapa[x][y], "***")==0){
                    int inimigos = rand() % quantidadeInimigos;  
                    char str[12];
                    sprintf(str, "%03d", inimigos);
                    strcpy(mapa[x][y], str);}
            }
            else if (x < xFinal && x + 1 < altura) {
                x++;
                if (strcmp(mapa[x][y], "***")==0){
                    int inimigos = rand() % quantidadeInimigos;  
                    char str[12];
                    sprintf(str, "%03d", inimigos);
                    strcpy(mapa[x][y], str);}
            } 
            else if (x > xFinal && x - 1 >= 0) {
                x--;
                if (strcmp(mapa[x][y], "***")==0){
                    int inimigos = rand() % quantidadeInimigos;  
                    char str[12];
                    sprintf(str, "%03d", inimigos);
                    strcpy(mapa[x][y], str);}
            } 
    }
}


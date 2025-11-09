#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menorCaminho.h"
#include "gerarMapa.h"

#define TAM_NOME_ARQUIVO 50

int main() {
    int escolha = 0;
    while (escolha != 3) {
    printf("==== BEM-VINDO AO EXPRESSO INTERESTELAR ====\n");
    printf("Deseja:\n");
    printf("1 - Inserir e executar um novo arquivo\n");
    printf("2 - Gerar um mapa teste\n");
    printf("3 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &escolha);
    getchar();

    if(escolha == 1){
        FILE *arquivo = NULL;
        char nome_arquivo[TAM_NOME_ARQUIVO];
        
        while (arquivo == NULL)
        {
            printf("Digite o nome do arquivo de entrada: ");
            scanf("%s", nome_arquivo);
            nome_arquivo[strcspn(nome_arquivo, "\n")] = 0;
            
            arquivo = fopen(nome_arquivo, "r");
            if (!arquivo) {
            printf("Arquivo nao encontrado\n");
            }
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
        int escolha;
        printf("Deseja visualizar o resultado de que maneira:\n1 - Apenas o caminho realizado (caso exista)\n2 - Mapa mostrando as movimentacoes (caso exista)\nEscolha: ");
        scanf("%d", &escolha);
        printf("\n");
        imprimeCaminho(escolha, h, w, mapaPresente, mapaPassado, 0, slotsDisponiveis-1, guardarCaminho, mapaComoGrafo, posicoes, F, N);

        liberarGrafo(mapaComoGrafo, slotsDisponiveis);
    }

    if(escolha == 2){
        gerarMapa();
    }

    if (escolha == 3) {
        printf("Encerrando o programa...\n");
        break;
    }
    

    // Teste de leitura
    /*printf("Altura: %d, Largura: %d\n", h, w);
    printf("Força inicial: %d, Descanso: %d, Força de Nikador: %d\n", F, D, N);

    printf("\n=== Mapa do Presente ===\n");
    imprimirMapa(mapaPresente, h, w);

    printf("\n=== Mapa do Passado ===\n");
    imprimirMapa(mapaPassado, h, w);

    liberarMapa(mapaPresente, h);
    liberarMapa(mapaPassado, h);
*/}
    return 0;
}
#include "movimento.h"
#include <stdio.h>


void movimento(Celula **mapaPresente, Celula **mapaPassado, int h, int w, int F, int D, int N, int **caminho, int tamanho_caminho) {
    int forca_atual = F;
    int mapa_atual = 0; //0 = presente, 1 = passado
    int linha_atual = caminho[0][0];
    int coluna_atual = caminho[0][1];
    
    printf("Inicio: linha %d, coluna %d - Forca: %d\n", linha_atual, coluna_atual, forca_atual);
    
    for (int passo = 1; passo < tamanho_caminho; passo++) {
        int prox_linha = caminho[passo][0];
        int prox_coluna = caminho[passo][1];
        
        //só pode ir para coluna seguinte, seja na mesma linha, acima ou abaixo
        if (prox_coluna != coluna_atual + 1) {
            printf("Erro: movimento invalido da coluna %d para %d\n", coluna_atual, prox_coluna);
            return;
        }
        //limitando movimento pra linha
        if (prox_linha < 0 || prox_linha >= h) {
            printf("Erro: movimento invalido para linha %d\n", prox_linha);
            return;
        }
        
        //Escolher mapa correto
        Celula **mapa_uso = (mapa_atual == 0) ? mapaPresente : mapaPassado;
        Celula celula_destino = mapa_uso[prox_linha][prox_coluna];
        
        //Verificar se célula é transitável
        if (celula_destino.tipo == INTRANSITAVEL) {
            printf("Erro: celula (%d, %d) é intransitavel\n", prox_linha, prox_coluna);
            return;
        }
        
        //Aplica efeito da célula
        if (celula_destino.tipo == INIMIGO) {
            forca_atual -= celula_destino.valor;
            printf("Movimento para (%d, %d) - Inimigo! Perdeu %d de forca - Forca: %d\n", 
                   prox_linha, prox_coluna, celula_destino.valor, forca_atual);
        }
        else if (celula_destino.tipo == DESCANSO) {
            forca_atual += D;
            printf("Movimento para (%d, %d) - Descanso! Ganhou %d de forca - Forca: %d\n", 
                   prox_linha, prox_coluna, D, forca_atual);
        }
        else if (celula_destino.tipo == ANCORA) {
            mapa_atual = 1 - mapa_atual; // Troca de mapa
            printf("Movimento para (%d, %d) - Ancora! Troca para mapa %s - Forca: %d\n", 
                   prox_linha, prox_coluna, (mapa_atual == 0) ? "PRESENTE" : "PASSADO", forca_atual);
        }
        else {
            printf("Movimento para (%d, %d) - Celula normal - Forca: %d\n", 
                   prox_linha, prox_coluna, forca_atual);
        }
        
        //Verifica se força acabou
        if (forca_atual <= 0) {
            printf("A calamidade de Nikador e inevitavel\n");
            return;
        }
        
        //Atualizar posição
        linha_atual = prox_linha;
        coluna_atual = prox_coluna;
    }
    
    // Chegou ao final
    printf("Chegou ao destino com forca: %d\n", forca_atual);
    if (forca_atual >= N) {
        printf("A ruina de Nikador e iminente\n");
    } else {
        printf("Sera necessario mais planejamento para parar a calamidade\n");
    }
}
/*
Este arquivo tem funções que calculam e exibem as métricas da árvore:
altura, total de nós, eventos ativos, fator de balanceamento médio e
contagem de rotações. Fica separado porque é uma responsabilidade
distinta, ele consulta sem modificar nada.
*/

#include "metricas.h"
#include "avl.h"

#include <stdio.h>
#include <stdlib.h>

// percore a árvore pela esquerda e pela direita fazendo uma contagem dos eventos
int totalNos(Evento *raiz){
    if(raiz == NULL){
        return 0;
    }

    return 1 + (totalNos(raiz->esq) + totalNos(raiz->dir));
}

// retorna o total de ativos eventos ativos
int totalAtivos(Evento *raiz){
    if(raiz == NULL){
        return 0;
    }
    
    int contEsq = totalAtivos(raiz->esq);
    int contDir = totalAtivos(raiz->dir);

    if(raiz->status == ATIVO){
        return 1 + contEsq + contDir;
    }

    return contEsq + contDir;
}

// função auxiliar de fatorBalanceamentoMedio
int somaFatores(Evento *raiz){
    if(raiz == NULL){
        return 0;
    }

    return abs(fatorBalanceamento(raiz)) + somaFatores(raiz->esq) + somaFatores(raiz->dir);
}

// fator de balanceamento médio
float fatorBalanceamentoMedio(Evento *raiz){
    if(raiz == NULL){
        return 0.0;
    }

    return ((float)somaFatores(raiz) / totalNos(raiz));
}

void exibirMetricas(Evento *raiz){
    printf("\n======= METRICAS DA ARVORE DE EVENTOS =======\n");
    printf("Altura da Arvore: %d\n", altura(raiz));
    printf("Total de Eventos: %d\n", totalNos(raiz));
    printf("Total de Eventos Ativos: %d\n", totalAtivos(raiz));
    printf("Fator de Balanceamento medio: %f\n", fatorBalanceamentoMedio(raiz));
    printf("Total de Rotacoes: %d\n", totalRotacoes);
}
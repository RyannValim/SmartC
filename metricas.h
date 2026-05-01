/*
Este arquivo tem funções que calculam e exibem as métricas da árvore:
altura, total de nós, eventos ativos, fator de balanceamento médio e
contagem de rotações. Fica separado porque é uma responsabilidade
distinta, ele consulta sem modificar nada.
*/

#ifndef METRICAS_H
#define METRICAS_H
#include "evento.h"

// funções que competem às métricas
int totalNos(Evento *raiz);
int totalAtivos(Evento *raiz);
float fatorBalanceamentoMedio(Evento *raiz);
void exibirMetricas(Evento *raiz);

#endif
/*
Este arquivo é o núcleo do sistema. Contém toda a lógica da árvore:
inserção, remoção, busca, rotações e rebalanceamento. Não sabe nada
de menu ou de como os dados chegam, só cuida da estrutura.
*/
#ifndef AVL_H
#define AVL_H

#include "evento.h"

// padrões da estrutura Evento
extern int totalRotacoes;

int altura(Evento *no);
int fatorBalanceamento(Evento *no);
Evento *rotacaoLL(Evento *raiz);
Evento *rotacaoRR(Evento *raiz);
Evento *rotacaoLR(Evento *raiz);
Evento *rotacaoRL(Evento *raiz);
Evento *balancear(Evento *raiz);
Evento *inserir(Evento *raiz, Evento *novo);
Evento *buscarPorId(Evento *raiz, int id);
Evento *menorNo(Evento *raiz);
Evento *remover(Evento *raiz, int id);

// consultas avançadas de Evento
void listarPorSeveridade(Evento *raiz, int min, int max);
void listarPorRegiao(Evento *raiz, char *regiao);
void listarPorIntervaloId(Evento *raiz, int idMin, int idMax);

// operações de atualização
void atualizarStatus(Evento *raiz, int id);
void atualizarSeveridade(Evento *raiz, int id, int novaSeveridade);

#endif
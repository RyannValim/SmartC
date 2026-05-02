/*
Este arquivo é a camada de interface com o usuário. Exibe os menus,
lê entradas, valida dados e chama as funções da árvore AVL. Ele é o
único arquivo que interage diretamente com stdin/stdout para as
operações do usuário.
*/

#ifndef MENU_H
#define MENU_H

#include "avl.h"
#include "metricas.h"

void opcoesIniciais();
void opcoesEventos();
void opcoesConsultas();
void opcoesMetricas();
void exibirMenuEventos(Evento **raiz);
void exibirMenuConsultas(Evento **raiz);
void exibirMenuAtualizacao(Evento **raiz);
void exibirMenuMetricas(Evento **raiz);
void exibirMenuPrincipal(Evento **raiz);

#endif
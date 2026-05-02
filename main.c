/*
A main é o ponto de entrada do programa, é ela quem inicializa a
árvore, chama o loop principal do menu e libera a memória ao sair.
*/
#include "menu.h"

#include <stdio.h>

int main(){
    Evento *raiz = NULL;

    exibirMenuPrincipal(&raiz);
    freeTree(raiz);

    return 0;
}
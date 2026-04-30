/*
Este arquivo é o núcleo do sistema. Contém toda a lógica da árvore:
inserção, remoção, busca, rotações e rebalanceamento. Não sabe nada
de menu ou de como os dados chegam, só cuida da estrutura.
*/
#include "avl.h"
#include <stdio.h>
#include <string.h>

int totalRotacoes = 0;

int altura(Evento *no){
    if(no == NULL){
        return -1;
    }

    return no->altura;
}

int fatorBalanceamento(Evento *no){
    if(no == NULL){
        return 0;
    }

    return altura(no->esq) - altura(no->dir);
}

// rotação direita simples
Evento* rotacaoLL(Evento *raiz){
    if(raiz == NULL){
        return NULL;
    }

    Evento *filho = raiz->esq;
    raiz->esq = filho->dir;
    filho->dir = raiz;

    raiz->altura = (altura(raiz->esq) > altura(raiz->dir) ? altura(raiz->esq) : altura(raiz->dir)) + 1;
    filho->altura = (altura(filho->esq) > altura(filho->dir) ? altura(filho->esq) : altura(filho->dir)) + 1;

    totalRotacoes++;

    return filho;
}

// rotação esquerda simples
Evento* rotacaoRR(Evento *raiz){
    if(raiz == NULL){
        return NULL;
    }

    Evento *filho = raiz->dir;
    raiz->dir = filho->esq;
    filho->esq = raiz;

    raiz->altura = (altura(raiz->dir) > altura(raiz->esq) ? altura(raiz->dir) : altura(raiz->esq)) + 1;
    filho->altura = (altura(filho->dir) > altura(filho->esq) ? altura(filho->dir) : altura(filho->esq)) + 1;

    totalRotacoes++;

    return filho;
}

// rotação direita dupla
Evento* rotacaoLR(Evento *raiz){
    raiz->esq = rotacaoRR(raiz->esq);
    return rotacaoLL(raiz);
}

// rotação esquerda dupla
Evento* rotacaoRL(Evento *raiz){
    raiz->dir = rotacaoLL(raiz->dir);
    return rotacaoRR(raiz);
}

Evento* balancear(Evento *raiz){
    if(raiz == NULL){
        return NULL;
    }

    if(fatorBalanceamento(raiz) > 1){
        if(fatorBalanceamento(raiz->esq) >= 0){
            return rotacaoLL(raiz);
        } else{
            return rotacaLR(raiz);
        }
    }

    if(fatorBalanceamento(raiz) < -1){
        if(fatorBalanceamento(raiz->dir) <= 0){
            return rotacaoRR(raiz);
        } else{
            return rotacaoRL(raiz);
        }
    }

    return raiz;
}

Evento* inserir(Evento *raiz, Evento *novo){
    if(raiz == NULL){
        return novo;
    }

    if(novo->id_evento > raiz->id_evento){
        raiz->dir = inserir(raiz->dir, novo);
    } else if(novo->id_evento < raiz->id_evento){
        raiz->esq = inserir(raiz->esq, novo);
    }

    raiz->altura = (altura(raiz->dir) > altura(raiz->esq) ? altura(raiz->dir) : altura(raiz->esq)) + 1;

    return balancear(raiz);
}

Evento* buscarPorId(Evento *raiz, int id){
    if(raiz == NULL){
        return NULL;
    }

    if(id == raiz->id_evento) {
        return raiz;
    } else if(id < raiz->id_evento){
        return buscarPorId(raiz->esq, id);
    }

    return buscarPorId(raiz->dir, id);
}

Evento* menorNo(Evento *raiz){
    if(raiz->esq == NULL){
        return raiz;
    }

    return menorNo(raiz->esq);
}

Evento* remover(Evento *raiz, int id){
    if(raiz == NULL){
        return NULL;
    }

    if(id == raiz->id_evento && raiz->status == ATIVO){
        return raiz;
    }

    if(id < raiz->id_evento){
        raiz->esq = remover(raiz->esq, id);
    } else if(id > raiz->id_evento){
        raiz->dir = remover(raiz->dir, id);
    }

    if(raiz->esq != NULL && raiz->dir != NULL){
        Evento *menor = menorNo(raiz->dir);
        raiz->id_evento = menor->id_evento;
        raiz->tipo_evento = menor->tipo_evento;
        raiz->severidade = menor->severidade;
        raiz->datetime = menor->datetime;
        strcpy(raiz->regiao, menor->regiao);
        raiz->status = menor->status;
        raiz->dir = remover(raiz->dir, menor->id_evento);
    } else if(raiz->esq != NULL || raiz->dir != NULL){
        if(raiz->esq != NULL){
            Evento *filho = raiz->esq;
            free(raiz);
            return filho;
        }

        if(raiz->dir != NULL){
            Evento *filho = raiz->dir;
            free(raiz);
            return filho;
        }
    } else if(raiz->esq == NULL && raiz->dir == NULL){
        free(raiz);
        return NULL;
    }

    raiz->altura = (altura(raiz->dir) > altura(raiz->esq) ? altura(raiz->dir) : altura(raiz->esq)) + 1;

    return balancear(raiz);
}
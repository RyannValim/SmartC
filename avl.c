/*
Este arquivo é o núcleo do sistema. Contém toda a lógica da árvore:
inserção, remoção, busca, rotações e rebalanceamento. Não sabe nada
de menu ou de como os dados chegam, só cuida da estrutura.
*/
#include "avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// padrões da estrutura Evento
// variável global para contagem de rotações
int totalRotacoes = 0;

// retorna a altura de um nó
int altura(Evento *no){
    if(no == NULL){
        return -1;
    }

    return no->altura;
}

// calcula o fator de balanceamento de um nó
int fatorBalanceamento(Evento *no){
    if(no == NULL){
        return 0;
    }

    return altura(no->esq) - altura(no->dir);
}

// rotaciona a árvore para a direita, recalcula a altura da raiz e do filho
Evento *rotacaoLL(Evento *raiz){
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

// rotaciona a árvore para a esquerda, recalcula a altura da raiz e do filho
Evento *rotacaoRR(Evento *raiz){
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
Evento *rotacaoLR(Evento *raiz){
    raiz->esq = rotacaoRR(raiz->esq);
    return rotacaoLL(raiz);
}

// rotação esquerda dupla
Evento *rotacaoRL(Evento *raiz){
    raiz->dir = rotacaoLL(raiz->dir);
    return rotacaoRR(raiz);
}

// balanceia a árvore baseado no fator de balanceamento
Evento *balancear(Evento *raiz){
    // caso base
    if(raiz == NULL){
        return NULL;
    }

    // caso de a árvore estar pesada para a direita
    if(fatorBalanceamento(raiz) > 1){
        if(fatorBalanceamento(raiz->esq) >= 0){
            return rotacaoLL(raiz);
        } else{
            return rotacaoLR(raiz);
        }
    }

    // caso de a árvore estar pesada para a esquerda
    if(fatorBalanceamento(raiz) < -1){
        if(fatorBalanceamento(raiz->dir) <= 0){
            return rotacaoRR(raiz);
        } else{
            return rotacaoRL(raiz);
        }
    }

    return raiz;
}

// insere um novo evento, calcula a altura e balanceia a árvore
Evento *inserir(Evento *raiz, Evento *novo){
    // caso base
    if(raiz == NULL){
        return novo;
    }

    // caso recursivo
    if(novo->id_evento > raiz->id_evento){
        raiz->dir = inserir(raiz->dir, novo);
    } else if(novo->id_evento < raiz->id_evento){
        raiz->esq = inserir(raiz->esq, novo);
    }

    raiz->altura = (altura(raiz->dir) > altura(raiz->esq) ? altura(raiz->dir) : altura(raiz->esq)) + 1;

    return balancear(raiz);
}

// busca um evento pelo id do evento
Evento *buscarPorId(Evento *raiz, int id){
    // caso base
    if(raiz == NULL){
        return NULL;
    }

    // caso recursivo
    if(id == raiz->id_evento) {
        return raiz;
    } else if(id < raiz->id_evento){
        return buscarPorId(raiz->esq, id);
    }

    return buscarPorId(raiz->dir, id);
}

// desce pela esquerda até achar o menor id da árvore
Evento *menorNo(Evento *raiz){
    if(raiz->esq == NULL){
        return raiz;
    }

    return menorNo(raiz->esq);
}

// remove um evento, recalcula a altura e balanceia a árvore
Evento *remover(Evento *raiz, int id){
    // caso base
    if(raiz == NULL){
        return NULL;
    }

    // caso o evento esteja ativo, não remove
    if(id == raiz->id_evento && raiz->status == ATIVO){
        return raiz;
    }

    // caso recursivo
    if(id < raiz->id_evento){
        raiz->esq = remover(raiz->esq, id);
    } else if(id > raiz->id_evento){
        raiz->dir = remover(raiz->dir, id);
    }

    // verificação se o nó é folha, tem um ou dois filhos
    if(raiz->esq != NULL && raiz->dir != NULL){ // nó com dois filhos
        Evento *menor = menorNo(raiz->dir);
        raiz->id_evento = menor->id_evento;
        raiz->tipo_evento = menor->tipo_evento;
        raiz->severidade = menor->severidade;
        raiz->datetime = menor->datetime;
        strcpy(raiz->regiao, menor->regiao);
        raiz->status = menor->status;
        raiz->dir = remover(raiz->dir, menor->id_evento);
    }
    else if(raiz->esq != NULL || raiz->dir != NULL){ // nó com um filho
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
    }
    else if(raiz->esq == NULL && raiz->dir == NULL){ // nó folha (sem filhos)
        free(raiz);
        return NULL;
    }

    // recalcula a altura da árvore e rebalanceia a raiz
    raiz->altura = (altura(raiz->dir) > altura(raiz->esq) ? altura(raiz->dir) : altura(raiz->esq)) + 1;

    return balancear(raiz);
}

// consultar avançadas de Evento
// percorre a árvore em-ordem e lista os eventos ativos e dentro do range de severidade
int listarPorSeveridade(Evento *raiz, int min, int max){
    // caso base
    if(raiz == NULL){
        return 0;
    }

    // percorre a árvore em-ordem
    int encontrados = 0;
    encontrados += listarPorSeveridade(raiz->esq, min, max);

    if(raiz->status == ATIVO){
        if(raiz->severidade >= min && raiz->severidade <= max){
            imprimirEvento(raiz);
            encontrados++;
        }
    }

    encontrados += listarPorSeveridade(raiz->dir, min, max);
    return encontrados;
}

// percorre a árvore em-ordem e lista os eventos pela região
int listarPorRegiao(Evento *raiz, char *regiao){
    if(raiz == NULL) {
        return 0;
    }

    // percorre a árvore em ordem realizando a contagem dos encontrados
    int encontrados = 0;
    encontrados += listarPorRegiao(raiz->esq, regiao);

    if(raiz->status == ATIVO && strcmp(raiz->regiao, regiao) == 0){
        imprimirEvento(raiz);
        encontrados++;
    }

    encontrados += listarPorRegiao(raiz->dir, regiao);
    return encontrados;
}

// lista os eventos por um intervalo de ids
int listarPorIntervaloId(Evento *raiz, int idMin, int idMax){
    // caso base
    if(raiz == NULL){
        return 0;
    }
    
    // limita a busca pelo id mínimo para melhor eficiência
    int encontrados = 0;
    
    if(raiz->id_evento >= idMin){
        encontrados += listarPorIntervaloId(raiz->esq, idMin, idMax);
    }

    if(raiz->id_evento >= idMin && raiz->id_evento <= idMax){
        imprimirEvento(raiz);
        encontrados++;
    }

    // limita a busca pelo id máximo para melhor eficiência
    if(raiz->id_evento <= idMax){
        encontrados += listarPorIntervaloId(raiz->dir, idMin, idMax);
    }

    return encontrados;
}

// atualiza o status de um evento pelo id do evento
void atualizarStatus(Evento *raiz, int id){
    if(raiz == NULL){
        return;
    }
    Evento *no = buscarPorId(raiz, id);

    if(no != NULL){
        if(no->status != RESOLVIDO){
            no->status = RESOLVIDO;
        }
    }
}

// atualiza a severidade de um evento pelo id do evento
void atualizarSeveridade(Evento *raiz, int id, int novaSeveridade){
    if(raiz == NULL){
        return;
    }

    Evento *no = buscarPorId(raiz, id);

    if(no != NULL){
        if(novaSeveridade > 0 && novaSeveridade < 6){
            no->severidade = novaSeveridade;
        }
    }
}

// libera a árvore inteira
void freeTree(Evento *raiz){
    if(raiz == NULL){
        return;
    }

    freeTree(raiz->esq);
    freeTree(raiz->dir);
    free(raiz);
}
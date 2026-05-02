/*
Este arquivo define o que é um evento, os enums (EventType, Status),
a struct DateTime, e a struct do nó da AVL. É o vocabulário central
do projeto; todos os outros arquivos dependem deste.
*/
#ifndef EVENTO_H
#define EVENTO_H
#define TAM_REGIAO 35

typedef enum TipoEvento{
    ACIDENTE_DE_TRANSITO,
    FALHA_EM_SEMAFORO,
    INTERRUPCAO_DE_ENERGIA,
    ALAGAMENTO,
    INCENDIO
} TipoEvento;

typedef enum Status{
    ATIVO,
    RESOLVIDO
} Status;

typedef struct DateTime{
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int segundo;
} DateTime;

typedef struct evento{
    int id_evento;
    TipoEvento tipo_evento;
    int severidade;
    DateTime datetime;
    char regiao[TAM_REGIAO];
    Status status;
    int altura;
    struct evento *esq;
    struct evento *dir;
} Evento;

void imprimirEvento(Evento *e);

#endif
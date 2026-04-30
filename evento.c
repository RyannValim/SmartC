/*
Este arquivo define o que é um evento, os enums (EventType, Status),
a struct DateTime, e a struct do nó da AVL. É o vocabulário central
do projeto; todos os outros arquivos dependem deste.
*/
#include "evento.h"
#include <stdio.h>

// consulta o tipo de um evento e retorna como string
const char* getTipoEventoString(TipoEvento tipo){
    switch(tipo){
    case ACIDENTE_DE_TRANSITO:
        return "Acidente de Transito";
    case FALHA_EM_SEMAFORO:
        return "Falha em Semaforo";
    case INTERRUPCAO_DE_ENERGIA:
        return "Interrupcao de Energia";
    case ALAGAMENTO:
        return "Alagamento";
    case INCENDIO:
        return "Incendio";
    default:
        return "Desconhecido";
    }
}

// consulta o status de um evento e retorna como string
const char* getStatusString(Status status){
    switch(status){
        case ATIVO:
            return "Ativo";
        case RESOLVIDO:
            return "Resolvido";
        default:
            return "Desconhecido";
    }
}

// imprime as informações de um evento
void imprimirEvento(Evento *e){
    printf("Id do Evento: %d\n", e->id_evento);
    printf("Tipo do Evento: %s\n", getTipoEventoString(e->tipo_evento));
    printf("Nivel de Severidade: %d\n", e->severidade);
    printf("Data/Hora: %02d/%02d/%04d %02d:%02d:%02d\n", 
        e->datetime.dia, e->datetime.mes, e->datetime.ano,
        e->datetime.hora, e->datetime.minuto, e->datetime.segundo);
    printf("Região: %s\n", e->regiao);
    printf("Status: %s\n", getStatusString(e->status));
}
/*
Este arquivo é a camada de interface com o usuário. Exibe os menus,
lê entradas, valida dados e chama as funções da árvore AVL. Ele é o
único arquivo que interage diretamente com stdin/stdout para as
operações do usuário.
*/
#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// opções para o menu inicial
void opcoesIniciais(){
    printf("============= SMARTC =============\n");
    printf("|     1. Eventos                 |\n");
    printf("|     2. Consultas               |\n");
    printf("|     3. Metricas                |\n");
    printf("|                                |\n");
    printf("|     0. Sair                    |\n");
    printf("==================================\n");
    printf("Escolha:  ");
}

// opções para o menu de evento
void opcoesEventos(){
    printf("\n======== SMARTC - EVENTOS ========\n");
    printf("|     1. Inserir                 |\n");
    printf("|     2. Buscar (por ID)         |\n");
    printf("|     3. Atualizar               |\n");
    printf("|     4. Remover                 |\n");
    printf("|                                |\n");
    printf("|     0. Voltar                  |\n");
    printf("==================================\n");
    printf("Escolha:  ");
}

// opções para o menu de consulta
void opcoesConsultas(){
    printf("\n======= SMARTC - CONSULTAS =======\n");
    printf("|     1. Listar por Severidade   |\n");
    printf("|     2. Listar por Regiao       |\n");
    printf("|     3. Listar por Intervalo    |\n");
    printf("|                                |\n");
    printf("|     0. Voltar                  |\n");
    printf("==================================\n");
    printf("Escolha:  ");
}

// opções para o menu de atualização
void opcoesAtualizacao(){
    printf("\n====== SMARTC - ATUALIZACAO ======\n");
    printf("|     1. Atualizar Status        |\n");
    printf("|     2. Atualizar Severidade    |\n");
    printf("|                                |\n");
    printf("|     0. Voltar                  |\n");
    printf("==================================\n");
    printf("Escolha:  ");
}

// opções para o menu de métricas
void opcoesMetricas(){
    printf("\n======== SMARTC - METRICAS =======\n");
    printf("|     1. Exibir Metricas         |\n");
    printf("|                                |\n");
    printf("|     0. Voltar                  |\n");
    printf("==================================\n");
    printf("Escolha:  ");
}

// função auxiliar de limpeza de buffer
void limparBuffer(){
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// função auxiliar para ler inteiros
int lerInteiro(){
    int inteiro;
    while(scanf("%d", &inteiro) != 1){
        limparBuffer();
        printf("Entrada invalida. Insira um numero: ");
    }
    limparBuffer();
    return inteiro;
}

// função auxiliar para ler strings
void lerRegiao(char *destino){
    printf("Insira a regiao: ");
    fgets(destino, TAM_REGIAO, stdin);
    // remove o \n que fgets inclui no final
    int len = strlen(destino);
    if(len > 0 && destino[len-1] == '\n'){
        destino[len-1] = '\0';
    }
}

// função para ler datetime
void lerDateTime(DateTime *dt){
    // data
    do{
        printf("Insira o dia: ");
        dt->dia = lerInteiro();

        if(dt->dia < 1 || dt->dia > 31){
            printf("O dia precisa ser entre 1 e 31.\n");
        }
    } while(dt->dia < 1 || dt->dia > 31);

    do{
        printf("Insira o mes: ");
        dt->mes = lerInteiro();

        if(dt->mes < 1 || dt->mes > 12){
            printf("O mes precisa ser entre 1 e 12.\n");
        }
    } while(dt->mes < 1 || dt->mes > 12);

    int ano_base = 1880;

    time_t agora = time(NULL);
    struct tm *tm_agora = localtime(&agora);
    int ano_atual = tm_agora->tm_year + 1900;

    do{
        printf("Insira o ano (entre 1880 e %d): ", ano_atual);
        dt->ano = lerInteiro();

        if(dt->ano > ano_atual){
            printf("Nao pode ser no futuro!\n");
        }
        if(dt->ano < ano_base){
            printf("Nao pode ser tao antigo!\n");
        }
    } while(dt->ano < ano_base || dt->ano > ano_atual);

    // hora
    do{
        printf("Insira a hora (00~23): ");
        dt->hora = lerInteiro();

        if(dt->hora < 0 || dt->hora > 23){
            printf("A hora precisa ser entre 0 e 23.\n");
        }
    } while(dt->hora < 0 || dt->hora > 23);

    // minuto
    do{
        printf("Insira o minuto (00~59): ");
        dt->minuto = lerInteiro();

        if(dt->minuto < 0 || dt->minuto > 59){
            printf("O minuto precisa ser entre 0 e 59.\n");
        }
    } while(dt->minuto < 0 || dt->minuto > 59);

    // segundo
    do{
        printf("Insira o segundo (00~59): ");
        dt->segundo = lerInteiro();

        if(dt->segundo < 0 || dt->segundo > 59){
            printf("O segundo precisa ser entre 0 e 59.\n");
        }
    } while(dt->segundo < 0 || dt->segundo > 59);

    // validação final: datetime completo não pode ser no futuro
    struct tm tm_input = {0};
    tm_input.tm_year = dt->ano - 1900;
    tm_input.tm_mon  = dt->mes - 1;   /* tm_mon: 0 a 11 */
    tm_input.tm_mday = dt->dia;
    tm_input.tm_hour = dt->hora;
    tm_input.tm_min  = dt->minuto;
    tm_input.tm_sec  = dt->segundo;

    while(mktime(&tm_input) > agora){
        printf("A data/hora nao pode ser no futuro. Insira novamente:\n");

        // relê só hora, minuto e segundo se o ano/mes/dia já é hoje
        // mas para simplicidade, relê o datetime inteiro
        do{
            printf("Insira o dia: ");
            dt->dia = lerInteiro();
        } while(dt->dia < 1 || dt->dia > 31);

        do{
            printf("Insira o mes: ");
            dt->mes = lerInteiro();
        } while(dt->mes < 1 || dt->mes > 12);

        do{
            printf("Insira o ano (entre 1880 e %d): ", ano_atual);
            dt->ano = lerInteiro();
        } while(dt->ano < ano_base || dt->ano > ano_atual);

        do{
            printf("Insira a hora (00~23): ");
            dt->hora = lerInteiro();
        } while(dt->hora < 0 || dt->hora > 23);

        do{
            printf("Insira o minuto (00~59): ");
            dt->minuto = lerInteiro();
        } while(dt->minuto < 0 || dt->minuto > 59);

        do{
            printf("Insira o segundo (00~59): ");
            dt->segundo = lerInteiro();
        } while(dt->segundo < 0 || dt->segundo > 59);

        // atualiza tm_input para a próxima checagem do while
        tm_input.tm_year = dt->ano - 1900;
        tm_input.tm_mon  = dt->mes - 1;
        tm_input.tm_mday = dt->dia;
        tm_input.tm_hour = dt->hora;
        tm_input.tm_min  = dt->minuto;
        tm_input.tm_sec  = dt->segundo;
    }
}

// menu para os eventos
void exibirMenuEventos(Evento **raiz){
    int opcaoEvento;

    do{
        opcoesEventos();
        opcaoEvento = lerInteiro();

        switch(opcaoEvento){
            case 0:
                break;
            case 1: { // Inserir um evento
                // criação do novo evento
                Evento *novo = (Evento*) malloc(sizeof(Evento));
                novo->esq = NULL;
                novo->dir = NULL;
                novo->altura = 0;

                // coletando os campos
                printf("\nPreencha os dados do novo evento:\n");

                // coletando id_evento e fazendo verificações
                do{
                    printf("Id (ex: 123): ");
                    novo->id_evento = lerInteiro();

                    if(novo->id_evento < 0){
                        printf("O ID não pode ser negativo.\n");
                    }
                } while(novo->id_evento < 0);

                // checando se o evento já existe
                if(buscarPorId(*raiz, novo->id_evento) != NULL){
                    printf("Ja existe um evento com este ID.\n");
                    free(novo);
                    break;
                }

                // coletando o campo tipo_evento e fazendo verificações
                int tipo_evento = -1;
                do{
                    printf("Tipo (ex: 1: ACIDENTE DE TRANSITO, 2: FALHA EM SEMAFORO, 3: INTERRUPCAO DE ENERGIA, 4: ALAGAMENTO, 5: INCENDIO): ");
                    tipo_evento = lerInteiro();
                    
                    switch(tipo_evento){
                        case 1:
                            novo->tipo_evento = ACIDENTE_DE_TRANSITO;
                            break;
                        case 2:
                            novo->tipo_evento = FALHA_EM_SEMAFORO;
                            break;
                        case 3:
                            novo->tipo_evento = INTERRUPCAO_DE_ENERGIA;
                            break;
                        case 4:
                            novo->tipo_evento = ALAGAMENTO;
                            break;
                        case 5:
                            novo->tipo_evento = INCENDIO;
                            break;
                        default:
                            printf("Insira um valor dentro do intervalo correto entre 1 e 5.\n");
                            break;
                    }
                } while(tipo_evento == -1);

                // coletando o campo severidade e fazendo verificações
                do{
                    printf("Severidade (entre 1 e 5): ");
                    novo->severidade = lerInteiro();

                    if(novo->severidade < 1 || novo->severidade > 5){
                        printf("Insira um valor dentro do intervalo correto entre 1 e 5.\n");
                    }
                } while(novo->severidade < 1 || novo->severidade > 5);
                
                // coletando o campo datetime e fazendo verificações via função (pois é muito grande)
                lerDateTime(&novo->datetime);
                
                // coletando o campo região e fazendo verificações via função
                lerRegiao(novo->regiao);

                // coletando o campo status_evento e fazendo verificações
                int status_evento;
                do{
                    printf("Status (ex: 1: ATIVO, 2: RESOLVIDO): ");
                    status_evento = lerInteiro();

                    if(status_evento == 1){
                        novo->status = ATIVO;
                    } else if(status_evento == 2){
                        novo->status = RESOLVIDO;
                    } else{
                        printf("Tipo invalido, insira 1 para ATIVO ou 2 para RESOLVIDO.\n");
                    }
                } while(status_evento != 1 && status_evento != 2);

                *raiz = inserir(*raiz, novo);
                break;
            }
            case 2: { // Buscar por id
                printf("\nInsira o id para busca: ");
                int id_busca = lerInteiro();

                Evento *encontrado = buscarPorId(*raiz, id_busca);
                
                if(encontrado == NULL){
                    printf("Evento nao encontrado!\n");
                } else{
                    imprimirEvento(encontrado);
                }
                break;
            }
            case 3: // Atualizar um evento
                exibirMenuAtualizacao(raiz);
                break;
            case 4: { // Remoção
                printf("\nInsira o id do evento para remover: ");
                int id_evento = lerInteiro();

                Evento *encontrado = buscarPorId(*raiz, id_evento);

                if(encontrado == NULL){
                    printf("Evento nao encontrado.\n");
                } else if(encontrado->status == ATIVO){
                    printf("Evento nao pode ser removido. Status ainda esta ativo.\n");
                } else {
                    *raiz = remover(*raiz, id_evento);
                    printf("Evento removido com sucesso!\n");
                }
                break;
            }
            default:
                printf("\nOpcao invalida, tente novamente!\n");
                break;
        }
    } while(opcaoEvento != 0);
}

// menu para as consultas
void exibirMenuConsultas(Evento **raiz){
    int opcaoConsulta;

    do{
        opcoesConsultas();
        opcaoConsulta = lerInteiro();

        switch(opcaoConsulta){
            case 0:
                break;
            case 1: { // listar por severidade
                printf("Insira o valor minimo: ");
                int min = lerInteiro();

                printf("Insira o valor maximo: ");
                int max = lerInteiro();

                int encontrados = listarPorSeveridade(*raiz, min, max);
                if(encontrados == 0){
                    printf("\nNenhum evento ativo encontrado pela severidade informada.\n");
                }
                
                break;
            }
            case 2: { // listar por regiao
                char regiao[TAM_REGIAO];
                lerRegiao(regiao);

                int encontrados = listarPorRegiao(*raiz, regiao);
                if(encontrados == 0){
                    printf("\nNenhum evento ativo encontrado para a regiao informada.\n");
                }
                break;
            }
            case 3: { // listar por intervalo de id
                printf("Insira o id minimo do intervalo: ");
                int id_min = lerInteiro();
                
                printf("Insira o id maximo do intervalo: ");
                int id_max = lerInteiro();

                int encontrados = listarPorIntervaloId(*raiz, id_min, id_max);
                if(encontrados == 0){
                    printf("\nNenhum evento foi encontrado neste intervalo de IDs.\n");
                }
                break;
            }
            default:
                printf("Opcao invalida, tente novamente!\n");
                break;
        }
    } while(opcaoConsulta != 0);
}

// menu para as atualizacoes
void exibirMenuAtualizacao(Evento **raiz){
    int opcaoAtualizacao;

    do{
        opcoesAtualizacao();
        opcaoAtualizacao = lerInteiro();
        
        switch(opcaoAtualizacao){
            case 0:
                break;
            case 1: {
                printf("Insira o id do evento para atualizar: ");
                int id = lerInteiro();
                Evento *no = buscarPorId(*raiz, id);
                if(no == NULL){
                    printf("Evento nao encontrado.\n");
                } else if(no->status == RESOLVIDO){
                    printf("Evento ja esta com status Resolvido.\n");
                } else {
                    atualizarStatus(*raiz, id);
                    printf("Status atualizado para Resolvido.\n");
                }
                break;
            }
            case 2: {
                printf("Insira o id do evento: ");
                int id = lerInteiro();
                Evento *no = buscarPorId(*raiz, id);
                if(no == NULL){
                    printf("Evento nao encontrado.\n");
                } else if(no->status == RESOLVIDO){
                    printf("Nao e possivel alterar severidade de evento Resolvido.\n");
                } else {
                    printf("Nova severidade (1 a 5): ");
                    int novaSeveridade = lerInteiro();
                    atualizarSeveridade(*raiz, id, novaSeveridade);
                    printf("Severidade atualizada com sucesso.\n");
                }
                break;
            }
            default:
                printf("Opcao invalida, tente novamente!\n");
                break;
        }
    } while(opcaoAtualizacao != 0);
}

// menu para as métricas
void exibirMenuMetricas(Evento **raiz){
    int opcaoMetrica;

    do{
        opcoesMetricas();
        opcaoMetrica = lerInteiro();

        switch(opcaoMetrica){
            case 0:
                break;
            case 1:
                exibirMetricas(*raiz);
                break;
            default:
                printf("Opcao invalida, tente novamente!\n");
        }
    }while(opcaoMetrica != 0);
}

// menu principal do programa
void exibirMenuPrincipal(Evento **raiz){
    int opcaoSwitch;
    do{
        opcoesIniciais();
        opcaoSwitch = lerInteiro();

        switch(opcaoSwitch){
            case 0:
                break;
            case 1: // opcao de eventos
                exibirMenuEventos(raiz);
                printf("\n");
                break;
            case 2: // opcao de consultas
                exibirMenuConsultas(raiz);
                printf("\n");
                break;
            case 3: // opcao de metricas
                exibirMenuMetricas(raiz);
                printf("\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente!\n");
                break;
        }
    } while(opcaoSwitch != 0);

    printf("\nEncerrando o programa...\n\nAte uma proxima!\n");
}
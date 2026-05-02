
# SmartC

Sistema eficiente para registro, priorização e resolução de eventos críticos urbanos em tempo real. O núcleo do projeto é focado em alta performance no gerenciamento de dados utilizando estruturas de dados avançadas.

* **Core:** Implementado inteiramente sobre uma Árvore AVL customizada
* **Performance:** Operações de busca, inserção e remoção com complexidade O(log n)
* **Linguagem:** C puro (foco em alocação dinâmica de memória e manipulação de ponteiros)
* **Recursos:** Filtros de eventos por severidade, relatórios por região, rebalanceamento automático e rastreamento de métricas da árvore

---

## Estrutura do projeto

```
SmartC/
├── main.c          — ponto de entrada do programa
├── avl.h / avl.c   — núcleo da Árvore AVL
├── evento.h / evento.c — estrutura e impressão de eventos
├── menu.h / menu.c — interface do usuário
├── metricas.h / metricas.c — cálculo de métricas da árvore
└── Makefile
```

---

## Compilação

### Com GCC (recomendado — funciona em todos os sistemas)

```bash
gcc avl.c evento.c metricas.c menu.c main.c -o SmartC
```

### Com Make (Linux / macOS)

```bash
make
```

### Com Make no Windows (MinGW)

Se o MinGW estiver instalado, use:

```bash
mingw32-make
```

> No Windows, `make` não está disponível por padrão. A compilação direta com `gcc` é a forma mais simples.

---

## Execução

### Windows

```bash
.\SmartC.exe
```

### Linux / macOS

```bash
./SmartC
```

---

## Funcionalidades

**Gerenciamento de eventos**

* Inserir evento com validação de todos os campos
* Buscar evento por ID
* Atualizar status (Ativo → Resolvido) e severidade
* Remover evento (apenas eventos com status Resolvido)

**Consultas avançadas**

* Listar eventos ativos por intervalo de severidade
* Listar eventos ativos por região
* Listar eventos por intervalo de ID

**Métricas da árvore**

* Altura total
* Total de nós
* Total de eventos ativos
* Fator de balanceamento médio
* Total de rotações realizadas

---

## Licença

MIT License — Copyright (c) 2026 Ryann Valim

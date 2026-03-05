#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "imovel.h"
#include "utils.h"

No *inicio = NULL;
No *fim = NULL;
int ultimo_codigo = 0;

// Insere um nó no início
void inserir_inicio(Imovel i) {
    No *novo = (No*)malloc(sizeof(No));

    novo->valor = i;
    novo->prox = inicio; // O novo nó que agora é o início, tem que apontar pro nó que era o início pois foi inserido antes dele
    inicio = novo; // O novo nó se torna o início

    if (fim == NULL) { // Se não houver fim declarado, o início também é o fim
        fim = inicio;
    }
}

// Cria um novo nó com o valor passado e insere no fim
void inserir_fim(Imovel i) {
    No *novo = (No*)malloc(sizeof(No));

    novo->valor = i;
    novo->prox = NULL; // É o fim, portanto, não tem próximo.

    if (fim != NULL) { // Se já existir, o nó que era o fim, agora aponta pro novo nó inserido
        fim->prox = novo;
    }

    fim = novo; // O fim agora é o novo nó inserido
    
    if (inicio == NULL) { // Se não houver início, ou seja, se não tiver nada na lista, o nó vai ser o início e o fim
        inicio = fim;
    } 
}

// Para remover um nó, o ponteiro "prox" do nó anterior ao removido aponta para o ponteiro "prox" do nó removido
void remover_no(No *anterior, No *removido) {
    anterior->prox = removido->prox;
    
    if (removido == fim) {
        fim = anterior;
    }
    
    free(removido);
}

// Itera por todos os nós até achar o que tem o código
No* buscar_ponteiro_por_codigo(int codigo) {
    No *p = inicio;
    
    while (p != NULL) {
        if (p->valor.codigo == codigo) {
            return p;
        }
        p = p->prox;
    }
    
    return NULL;
}

// Exclui um elemento da lista pelo código, retorna true se achou e excluiu
bool remover_imovel(int codigo) {
     if (inicio == NULL) {
        return false;
    }
 
    No *p = inicio;
    if (p->valor.codigo == codigo) { // Se o nó inicial já tiver o valor que eu quero
        inicio = p->prox;

        if (p == fim) { // Se o início for igual ao fim
            fim = NULL; 
        }

        free(p);
        return true;
    }

    while (p->prox != NULL) {
        if (p->prox->valor.codigo == codigo) {
            remover_no(p, p->prox);
            return true;
        }

        p = p->prox;
    }

    return false;
}

void ler_imovel(Imovel *imovel) {
    printf("Informe a descricao do imovel:\n");
    fgets(imovel->descricao, MAX_STR, stdin);
    imovel->descricao[strcspn(imovel->descricao, "\n")] = '\0';

    printf("Informe a localizacao do imovel:\n");
    fgets(imovel->localizacao, MAX_STR, stdin);
    imovel->localizacao[strcspn(imovel->localizacao, "\n")] = '\0';

    while (true) { // Loop infinito, até algo quebrar pra fora dele
        printf("Informe o tipo de operacao ('venda' ou 'aluguel'):\n");
        fgets(imovel->tipo_operacao, 10, stdin);
        para_minusculo(imovel->tipo_operacao); // Transformar em minúsculo pra garantir
        imovel->tipo_operacao[strcspn(imovel->tipo_operacao, "\n")] = '\0'; // Cortar o \n da string para nao dar loop infinito

        if ((strcmp(imovel->tipo_operacao, "venda") == 0) || (strcmp(imovel->tipo_operacao, "aluguel") == 0)) {
            break; // Se tipo de operação informada é "venda" ou "operacao", sai do loop
        } else {
            printf("\nPor favor, informe um tipo de operacao valido!\n");
        }
    }

    printf("Informe o valor do imovel em reais (R$):\n");
    scanf("%f", &imovel->valor);

    limpar_buffer(); // Tem que limpar o buffer, porque esse scanf pula linha, o que faria o próximo fgets() não ler nada

    if (strcmp(imovel->tipo_operacao, "aluguel") == 0) {
        printf("Informe o nome do inquilino (ou ENTER para deixar disponivel):\n");
        fgets(imovel->cliente, MAX_STR, stdin);
        
        // Se só apertou ENTER, limpa a string
        if (imovel->cliente[0] == '\n') {
            imovel->cliente[0] = '\0';
        }
    } else {
        imovel->cliente[0] = '\0'; // venda nunca tem cliente no cadastro
    }
}

void imprimir_imovel(Imovel imovel) {
    printf("Codigo: %d\n", imovel.codigo);
    printf("Descricao: %s\n", imovel.descricao);
    printf("Localizacao: %s\n", imovel.localizacao);
    printf("Tipo de operacao: %s\n", imovel.tipo_operacao);
    printf("Valor: R$ %.2f\n", imovel.valor);
    if (imovel.cliente[0] == '\0') {
        if (strcmp(imovel.tipo_operacao, "aluguel") == 0) {
            printf("Inquilino: (disponivel para aluguel)\n");
        } else {
            printf("Comprador: (disponivel para venda)\n");
        }
    } else {
        if (strcmp(imovel.tipo_operacao, "aluguel") == 0) {
            printf("Inquilino: %s\n", imovel.cliente);
        } else {
            printf("Comprador: %s\n", imovel.cliente);
        }
    }
}

void cadastrar() {
    Imovel i;

    ler_imovel(&i);
    i.codigo = ++ultimo_codigo;
    inserir_fim(i);

    printf("Imovel inserido com sucesso!\n");
    imprimir_imovel(i);
}

void excluir(int codigo) {
    bool removeu = remover_imovel(codigo);

    if (removeu) {
        printf("Imovel de codigo %d deletado com sucesso.\n", codigo);
    } else {
        printf("Nao foi possível encontrar um imovel com o codigo %d.\n", codigo);
    }
}

void consultar(int codigo) {
    No *consulta = buscar_ponteiro_por_codigo(codigo);
    
    if (consulta != NULL) {
        imprimir_imovel(consulta->valor);
    } else {
        printf("Imovel nao encontrado.\n");
    }
}

void alterar(int codigo) {
    No *no = buscar_ponteiro_por_codigo(codigo);

    if (no == NULL) {
        printf("Imovel com codigo %d nao encontrado.\n", codigo);
        return;
    }

    printf("Imovel encontrado. Informe os novos dados:\n");
    ler_imovel(&no->valor);
    no->valor.codigo = codigo; // preserva o código original

    printf("Imovel alterado com sucesso!\n");
    imprimir_imovel(no->valor);
}

void registrar_venda(int codigo) {
    No *no = buscar_ponteiro_por_codigo(codigo);

    if (no == NULL) {
        printf("Imovel com codigo %d nao encontrado.\n", codigo);
        return;
    }

    if (strcmp(no->valor.tipo_operacao, "venda") != 0) {
        printf("Este imovel nao esta disponivel para venda.\n");
        return;
    }

    printf("Informe o nome do comprador:\n");
    fgets(no->valor.cliente, MAX_STR, stdin);

    printf("Venda registrada com sucesso!\n");
    imprimir_imovel(no->valor);

    excluir(codigo); 
}

void registrar_aluguel(int codigo) {
    No *no = buscar_ponteiro_por_codigo(codigo);

    if (no == NULL) {
        printf("Imovel com codigo %d nao encontrado.\n", codigo);
        return;
    }

    if (strcmp(no->valor.tipo_operacao, "aluguel") != 0) {
        printf("Este imovel nao esta disponivel para aluguel.\n");
        return;
    }

    if (no->valor.cliente[0] != '\0') {
        printf("Este imovel ja possui um inquilino: %s\n", no->valor.cliente);
        return;
    }

    printf("Informe o nome do inquilino:\n");
    fgets(no->valor.cliente, MAX_STR, stdin);

    printf("Aluguel registrado com sucesso!\n");
    imprimir_imovel(no->valor);
}

void listar_todos() {
    if (inicio == NULL) {
        printf("Nao existem imoveis cadastrados.\n");
        return;
    }

    No* p = inicio;
    while (p != NULL) {
        imprimir_imovel(p->valor);
        printf("\n");
        p = p->prox;
    }
}

void listar_alugueis() {
    if (inicio == NULL) {
        printf("Nao existem imoveis cadastrados.\n");
        return;
    }

    bool imprimiu = false;
    No* p = inicio;
    while (p != NULL) {
        if (strcmp(p->valor.tipo_operacao, "aluguel") == 0) {  // Se é um imóvel alugado
            imprimir_imovel(p->valor);
            printf("\n");
            imprimiu = true;
        }
        p = p->prox;
    }

    if (!imprimiu) {
        printf("Nao foram encontrados imoveis com a operacao de aluguel.");
    }
}

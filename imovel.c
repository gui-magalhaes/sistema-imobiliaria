#include <stdlib.h>
#include <stdbool.h>
#include "imovel.h"

No *inicio = NULL;
No *fim = NULL;

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
void inserir_fim(Imovel a) {
    No *novo = (No*)malloc(sizeof(No));

    novo->valor = a;
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
bool excluir(int codigo) {
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

Imovel* consultar(int codigo) {
    No *consulta = buscar_ponteiro_por_codigo(codigo);
    
    if (consulta != NULL) {
        return &consulta->valor;
    }

    return NULL;
}

void listar_inquilinos_aluguel() {
    No *p = inicio;
    printf("\n Inquilinos que moram de aluguel:");
    while (p != NULL) {
        if (p->valor.tipo_operacao == "aluguel") {
            printf("\n %s", p->valor.cliente);
        }
    }
}
void vender(int codigo) {
    Imovel imovel = consultar(codigo);
    if (imovel == NULL) {
        return;
    }
    if (imovel.valor.tipo_operacao == "aluguel") {
        printf("\n Imóvel não disponível para venda");
        return;
    }
    excuir(codigo);
    printf("\n Imóvel vendido")
    return;
}

void main () {

}
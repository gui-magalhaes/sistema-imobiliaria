#ifndef IMOVEL_H
#define IMOVEL_H
    
#define MAX_STR 100
#define NULL 0

typedef struct {
    int codigo;
    char descricao[MAX_STR];
    char localizacao[MAX_STR];
    char tipo_operacao[10]; // "venda" ou "aluguel"
    float valor;
    char cliente[MAX_STR];
} Imovel;

typedef struct no {
    Imovel valor;
    struct no *prox;
} No;


void cadastrar();
bool excluir(int codigo);
void alterar(int codigo);
Imovel consultar(int codigo);
void listar_todos();
void listar_alugueis();

#endif
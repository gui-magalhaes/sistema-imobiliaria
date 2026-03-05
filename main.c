#include <stdio.h>
#include "imovel.h"
#include "utils.h"


int main(){
    int opcao;
    int id;

    do {
        printf("\n=============Menu=============\n");
        printf("Digite o numero para executar a funcao\n");
        printf("1 - Cadastrar imovel\n");
        printf("2 - Listar todos\n");
        printf("3 - Listar por ID\n");
        printf("4 - Listar todos os alugueis\n");
        printf("5 - Alterar dados imovel\n");
        printf("6 - Excluir imovel\n");
        printf("7 - Registrar venda\n");
        printf("8 - Registrar aluguel\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao)
        {
        case 1:
            cadastrar();
            break;
        
        case 2:
            listar_todos();
            break;
        
        case 3:
            printf("Digite o ID do imovel a ser consultado\n");
            scanf("%d", &id);
            limpar_buffer();
            consultar(id);
            break;
        
        case 4:
            listar_alugueis();
            break;
        
        case 5:
            printf("Digite o ID do imovel a ser alterado\n");
            scanf("%d", &id);
            limpar_buffer();
            alterar(id);
            break;

        case 6:
            printf("Digite o ID do imovel a ser excluido\n");
            scanf("%d", &id);
            limpar_buffer();
            excluir(id);
            break;

        case 7:
            printf("Digite o ID do imovel a ser vendido\n");
            scanf("%d", &id);
            limpar_buffer();
            registrar_venda(id);
            break;

        case 8:
            printf("Digite o ID do imovel a ser alugado\n");
            scanf("%d", &id);
            limpar_buffer();
            registrar_aluguel(id);
            break;
        
        default:
            break;
        }
    } while(opcao != 0);
}
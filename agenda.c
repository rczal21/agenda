//Agenda de contatos em C
//Essse programa tem como objetivo criar uma lista de até 50 contatos
//Cada contato possui nome, telefone e email
//O programa permite visualizar, adicionar, remover, buscar e alterar contatos, tudo salvo em um arquivo de texto

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

#define ARQUIVO "agenda.txt"

struct st_contato{
    char nome[100];
    char telefone[15]; 
    char email[100];
}contato[50];

struct st_agenda{
    struct st_contato contato[50];
}agenda;

int total_contatos = 0;
int opcao;

void criarContato(int i);
void menu();
void visualizarAgenda();
void salvarAgenda();
void carregarAgenda();
void removerContato(int i);
void buscarContato(char *nome);
void alterarContato(int i);
void inicializarAgenda();
void limparNovaLinha(char *texto);


int main(){
    inicializarAgenda();

    do{
        system("cls");
        menu();

        switch(opcao){
            case 1:
                visualizarAgenda();
                break;
            case 2:
                if(total_contatos < 50){
                    criarContato(total_contatos);
                    total_contatos++;
                    salvarAgenda();
                }else{
                    printf("Agenda cheia!\n");
                }
                break;
            case 3:
                removerContato(total_contatos - 1);
                break;
            case 4:
            {
                char nome[100];
                printf("Digite o nome do contato a ser buscado: ");
                fgets(nome, 100, stdin);
                limparNovaLinha(nome);
                buscarContato(nome);
                break;
            }
            case 5:
               alterarContato(total_contatos - 1);
                break;
            case 0:
                printf("Saindo da agenda...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

        system("pause");
    }while(opcao != 0);

}

void criarContato(int i){
    printf("Nome:\n"); 
    fgets(agenda.contato[i].nome, 100, stdin);
    limparNovaLinha(agenda.contato[i].nome);

    printf("Telefone:\n"); 
    fgets(agenda.contato[i].telefone, 15, stdin);
    limparNovaLinha(agenda.contato[i].telefone);

    printf("Email:\n"); 
    fgets(agenda.contato[i].email, 100, stdin);
    limparNovaLinha(agenda.contato[i].email);

    printf("Contato adicionado com sucesso!\n");
}

void menu(){
    printf("==========AGENDA DE CONTATOS==========\n\n");
    printf("1. Visualizar agenda\n");
    printf("2. Adiconar contato\n"); 
    printf("3. Remover contato\n"); 
    printf("4. Buscar contato\n"); 
    printf("5. Alterar dados de um contato\n"); 
    printf("0. Sair\n");
    printf("\nEscolha: ");
    scanf("%d", &opcao);

     int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        //descarta o restante da linha
    }
}

void visualizarAgenda(){
    printf("==========AGENDA DE CONTATOS==========\n\n");
    for(int i = 0; i < total_contatos; i++){
        printf("Contato %d\n", i+1);
        printf("Nome: %s\n", agenda.contato[i].nome);
        printf("Telefone: %s\n", agenda.contato[i].telefone);
        printf("Email: %s\n", agenda.contato[i].email);
        printf("\n");
    }
}

void salvarAgenda(void) {
    FILE *arquivo = fopen(ARQUIVO, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (int i = 0; i < total_contatos; i++) {
        fprintf(arquivo, "%s\n", agenda.contato[i].nome);
        fprintf(arquivo, "%s\n", agenda.contato[i].telefone);
        fprintf(arquivo, "%s\n", agenda.contato[i].email);
    }

    fclose(arquivo);
}

void carregarAgenda(void) {
    FILE *arquivo = fopen(ARQUIVO, "r");

    if (arquivo == NULL) {
        return;  //ainda não existe arquivo; a agenda começa vazia.
    }

    total_contatos = 0;

    while (total_contatos < 50) {
        struct st_contato *c = &agenda.contato[total_contatos];

        if (fgets(c->nome, sizeof c->nome, arquivo) == NULL) {
            break;
        }
        if (fgets(c->telefone, sizeof c->telefone, arquivo) == NULL) {
            break;
        }
        if (fgets(c->email, sizeof c->email, arquivo) == NULL) {
            break;
        }

        limparNovaLinha(c->nome);
        limparNovaLinha(c->telefone);
        limparNovaLinha(c->email);

        total_contatos++;
    }

    fclose(arquivo);
}

void removerContato(int i){
    if(i < 0 || i >= total_contatos){
        printf("Contato invalido!\n");
        return;
    }

    for(int j = i; j < total_contatos - 1; j++){
        agenda.contato[j] = agenda.contato[j + 1];
    }
    total_contatos--;
    salvarAgenda();
    printf("Contato removido com sucesso!\n");
}

void buscarContato(char *nome){
    int encontrado = 0;
    for(int i = 0; i < total_contatos; i++){
        if(strstr(agenda.contato[i].nome, nome) != NULL){
            printf("Contato %d:\n", i+1);
            printf("Nome: %s", agenda.contato[i].nome);
            printf("Telefone: %s", agenda.contato[i].telefone);
            printf("Email: %s", agenda.contato[i].email);
            printf("\n");
            encontrado = 1;
        }
    }
    if(!encontrado){  //nao encontrou nenhum contato com o nome informado
        printf("Contato nao encontrado!\n");
    }
}

void alterarContato(int i){
    if(i < 0 || i >= total_contatos){
        printf("Contato invalido!\n");
        return;
    }

    printf("Alterar contato %d:\n", i+1);
    printf("Nome atual: %s", agenda.contato[i].nome);
    printf("Novo nome:\n");
    fgets(agenda.contato[i].nome, 100, stdin);
    limparNovaLinha(agenda.contato[i].nome);

    printf("Telefone atual: %s", agenda.contato[i].telefone);
    printf("Novo telefone:\n");
    fgets(agenda.contato[i].telefone, 15, stdin);
    limparNovaLinha(agenda.contato[i].telefone);

    printf("Email atual: %s", agenda.contato[i].email);
    printf("Novo email:\n");
    fgets(agenda.contato[i].email, 100, stdin);
    limparNovaLinha(agenda.contato[i].email);

    salvarAgenda();
    printf("Contato alterado com sucesso!\n");
}

void inicializarAgenda(){
    total_contatos = 0;
    carregarAgenda();
}

void limparNovaLinha(char *texto){
    texto[strcspn(texto, "\n")] = '\0';  //remove o caractere de nova linha do final da string
}


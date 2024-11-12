#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//Definindo a estrutura do livro
typedef struct {
    char titulo[100];
    char autor[100];
    int ano;
} Livro;

//Funções para o sistema de biblioteca
void adicionarLivro(Livro livros[], int *quantidade);
void visualizarLivros(Livro livros[], int quantidade);
void procurarLivro(Livro livros[], int quantidade, char *titulo);

int main() {

	setlocale(LC_ALL, "Portuguese"); //Permite acentuação no código
    int escolha;
    int quantidade = 0;
    Livro livros[100];  //Array para armazenar até 100 livros

    while (1) {
        printf("\nSistema de Gerenciamento de Biblioteca\n");
        printf("1. Adicionar Livro\n");
        printf("2. Visualizar Todos os Livros\n");
        printf("3. Procurar Livro pelo Título\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);
        getchar();  //Limpar o buffer do teclado

        switch (escolha) {
            case 1:
                adicionarLivro(livros, &quantidade);
                break;
            case 2:
                visualizarLivros(livros, quantidade);
                break;
            case 3: {
                char titulo[100];
                printf("Digite o título do livro: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';  //Remover a nova linha
                procurarLivro(livros, quantidade, titulo);
                break;
            }
            case 4:
                exit(0);
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }

    return 0;
}

void adicionarLivro(Livro livros[], int *quantidade) {
    if (*quantidade >= 100) {
        printf("Limite de livros atingido!\n");
        return;
    }

    printf("Digite o título do livro: ");
    fgets(livros[*quantidade].titulo, sizeof(livros[*quantidade].titulo), stdin);
    livros[*quantidade].titulo[strcspn(livros[*quantidade].titulo, "\n")] = '\0';  // Remover a nova linha

    printf("Digite o autor do livro: ");
    fgets(livros[*quantidade].autor, sizeof(livros[*quantidade].autor), stdin);
    livros[*quantidade].autor[strcspn(livros[*quantidade].autor, "\n")] = '\0';  // Remover a nova linha

    printf("Digite o ano de publicação: ");
    scanf("%d", &livros[*quantidade].ano);
    getchar();  //Limpar o buffer do teclado

    (*quantidade)++;
    printf("Livro adicionado com sucesso!\n");
}

void visualizarLivros(Livro livros[], int quantidade) {
    if (quantidade == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    printf("\nLista de Livros:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Título: %s\n", livros[i].titulo);
        printf("Autor: %s\n", livros[i].autor);
        printf("Ano de Publicação: %d\n", livros[i].ano);
        printf("-------------------------\n");
    }
}

void procurarLivro(Livro livros[], int quantidade, char *titulo) {
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(livros[i].titulo, titulo) == 0) {
            printf("Livro encontrado:\n");
            printf("Título: %s\n", livros[i].titulo);
            printf("Autor: %s\n", livros[i].autor);
            printf("Ano de Publicação: %d\n", livros[i].ano);
            return;
        }
    }

    printf("Livro não encontrado.\n");
}

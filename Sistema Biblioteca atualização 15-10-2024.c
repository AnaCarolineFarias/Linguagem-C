#include <stdio.h>  // Biblioteca de entrada e saída padrão.
#include <stdlib.h> // Biblioteca para alocação de memória.
#include <string.h> // Biblioteca para manipulação de strings.
#include <locale.h> // Biblioteca que permite a acentuação no código.

// Definindo a estrutura da mensagem de boas-vindas da Biblioteca
char MENSAGEM[] = "Bem Vindo(a) á Biblioteca Online!";
int largura; // Definindo a variável largura
int altura = 7; // Altura do quadrado (inclui a linha de cima e de baixo); (um número ímpar facilita a centralização vertical)

// Definindo a estrutura do usuário
typedef struct {
    char usuario[50];
    char senha[50];
    int Admin; // 1 para admin, 0 para usuário comum
} Usuario;

// Definindo a estrutura do livro
typedef struct {
    char titulo[100];
    char autor[100];
    int ano;
} Livro;

// Função que limpa o buffer do teclado
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Funções para o sistema de biblioteca
void adicionarLivro(Livro livros[], int *quantidade);
void visualizarLivros(Livro livros[], int quantidade);
void procurarLivro(Livro livros[], int quantidade, char *titulo);
void cadastrarUsuario(Usuario usuarios[], int *qtdUsuarios);
int verificarLogin(Usuario usuarios[], int qtdUsuarios, char *usuario, char *senha, int *Admin);

// Função para cadastrar novos usuários
void cadastrarUsuario(Usuario usuarios[], int *qtdUsuarios) {
    if (*qtdUsuarios >= 100) {

        system("cls"); //Limpar o terminal

        printf("Limite de usuários atingido!\n");
        return;
    }

    printf("\nCadastro de novo usuário\n");
    printf("Nome do usuário: ");
    fgets(usuarios[*qtdUsuarios].usuario, sizeof(usuarios[*qtdUsuarios].usuario), stdin);
    usuarios[*qtdUsuarios].usuario[strcspn(usuarios[*qtdUsuarios].usuario, "\n")] = '\0';  // Remover a nova linha

    printf("Senha: ");
    fgets(usuarios[*qtdUsuarios].senha, sizeof(usuarios[*qtdUsuarios].senha), stdin);
    usuarios[*qtdUsuarios].senha[strcspn(usuarios[*qtdUsuarios].senha, "\n")] = '\0';  // Remover a nova linha

    printf("Você é um administrador? (1 para sim, 0 para não): ");
    scanf("%d", &usuarios[*qtdUsuarios].Admin);
    clearInputBuffer();  // Limpar o buffer do teclado

    system("cls"); //Limpar o terminal

    (*qtdUsuarios)++;
    printf("Usuário cadastrado com sucesso!\n");
}

// Função para verificar o login
int verificarLogin(Usuario usuarios[], int qtdUsuarios, char *Usuario, char *senha, int *Admin) {
    for (int i = 0; i < qtdUsuarios; i++) {
        if (strcmp(usuarios[i].usuario, Usuario) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            *Admin = usuarios[i].Admin;  // Verifica se o usuário é admin
            return 1;  // Login bem-sucedido
        }
    }
    return 0;  // Login falhou
}

int main() {
    setlocale(LC_ALL, "Portuguese"); // Permite acentuação no código

    // 2 Espaços de cada lado da mensagem
    largura = strlen(MENSAGEM) + 4;

    Usuario usuarios[100];  // Array para armazenar até 100 usuários
    int qtdUsuarios = 0;    // Contador de usuários cadastrados

    // Desenha a parte superior do quadrado
    for (int i = 0; i < largura; i++) {
        printf("*");
    }
    printf("\n");

    // Desenha o meio do quadrado com a mensagem
    for (int i = 0; i < altura - 2; i++) {
        printf("*"); // Lado esquerdo do quadrado

        if (i == (altura - 2) / 2) {
            int espacos_esquerda = (largura - strlen(MENSAGEM) - 2) / 2; // Espaços antes da mensagem
            int espacos_direita = largura - strlen(MENSAGEM) - espacos_esquerda - 2; // Espaços depois da mensagem
            for (int j = 0; j < espacos_esquerda; j++) {
                printf(" ");
            }
            printf("%s", MENSAGEM); // Mostra a mensagem centralizada
            for (int j = 0; j < espacos_direita; j++) {
                printf(" ");
            }
        } else {
            for (int j = 0; j < largura - 2; j++) {
                printf(" "); // Espaços vazios
            }
        }
        printf("*\n"); // Lado direito do quadrado
    }

    // Desenha a parte inferior do quadrado
    for (int i = 0; i < largura; i++) {
        printf("*");
    }
    printf("\n");

    // Variáveis para verificar se o Login e Senha correspondem com os cadastrados
    char usuarioInput[50];
    char senhaInput[50];
    int escolha, Admin;

    printf("\nSistema de login para bibliotecários\n");
    printf("----------------\n");

    printf("Você já possui cadastro no sistema?\n");
    printf("1. Sim\n");
    printf("2. Não, efetuar cadastro\n");
    printf("Escolha uma opção, de 1 a 2: \n");
    scanf("%d", &escolha);
    clearInputBuffer();  // Limpar o buffer do teclado

    if (escolha == 2) {
        cadastrarUsuario(usuarios, &qtdUsuarios);
    }

    // Tentativa de login
    printf("Nome do usuário: ");
    fgets(senhaInput, sizeof(usuarioInput), stdin);
    usuarioInput[strcspn(usuarioInput, "\n")] = '\0';  // Remover a nova linha

    printf("Senha: ");
    fgets(senhaInput, sizeof(senhaInput), stdin);
    senhaInput[strcspn(senhaInput, "\n")] = '\0';  // Remover a nova linha

    if (verificarLogin(usuarios, qtdUsuarios, usuarioInput, senhaInput, &Admin)) {

        system("cls"); //Limpar o terminal

        printf("Login bem-sucedido!\n");
    } else {

        printf("Nome de usuário ou senha incorretos.\n");
        return 1;
    }

    // Para limpar a tela
    system("cls");

    int quantidade = 0;
    Livro livros[100];  // Array para armazenar até 100 livros

    // Looping de escolhas da biblioteca
    while (1) {
        printf("\nSistema de Gerenciamento de Biblioteca\n");
        printf("----------------\n");

        printf("1. Adicionar Livro\n");
        printf("2. Visualizar Todos os Livros\n");
        printf("3. Procurar Livro pelo Título\n");
        printf("4. Sair\n");
        printf("Escolha uma opção, de 1 a 4: \n");
        scanf("%d", &escolha);
        clearInputBuffer();  // Limpar o buffer do teclado

        switch (escolha) {
            case 1:
                if (Admin) {
                    adicionarLivro(livros, &quantidade);
                } else {
                    system("cls"); //Limpar o terminal

                    printf("Acesso negado! Apenas administradores podem adicionar livros.\n");
                }
                break;
            case 2:
                visualizarLivros(livros, quantidade);
                break;
            case 3: {
                char titulo[100];
                printf("Digite o título do livro: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0';  // Remover a nova linha
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

// Função para adicionar livros ao sistema
void adicionarLivro(Livro livros[], int *quantidade) {
    if (*quantidade >= 100) {

        system("cls"); //Limpar o terminal

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
    clearInputBuffer();  // Limpar o buffer do teclado

    (*quantidade)++;
    printf("Livro adicionado com sucesso!\n");
}

// Função para visualizar todos os livros
void visualizarLivros(Livro livros[], int quantidade) {
    if (quantidade == 0) {

        system("cls"); //Limpar o terminal

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

// Função para procurar um livro pelo título
void procurarLivro(Livro livros[], int quantidade, char *titulo) {
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(livros[i].titulo, titulo) == 0) {
            printf("Livro encontrado!\n");
            printf("Título: %s\n", livros[i].titulo);
            printf("Autor: %s\n", livros[i].autor);
            printf("Ano de Publicação: %d\n", livros[i].ano);
            return;
        }
    }
    system("cls"); //Limpar o terminal

    printf("Livro não encontrado.\n");
}

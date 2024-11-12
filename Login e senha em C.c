#include <stdio.h>
#include <string.h>
#include <locale.h>


//define os usuarios e senha
#define USERNAME "Usuario"
#define PASSWORD "Senha"

void clearInputBuffer() {

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main (void){
	
	char username[50];
	char password[50];
	setlocale(LC_ALL, "Portuguese");
	
	printf("Sistema de login\n");
	printf("----------------\n");
	
//pede o nome do usuario

    printf("Nome do usuário: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';  // Remover o caractere de nova linha
    
//pede a senha

    printf("Senha: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';  // Remover o caractere de nova linha
	
// Verificar as credenciais

    if (strcmp(username, USERNAME) != 0 && strcmp(password, PASSWORD) != 0) {
        printf("Login bem-sucedido!\n");
    } else {
        printf("Nome de usuário ou senha incorretos.\n");
    }

    return 0;

}

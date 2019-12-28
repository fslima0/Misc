#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*   Programa que cadastra vários produtos, mostra o catálogo e pode
 *   ser utilizado para fazer consultas de produtos através do seu código.
 */
 
int num_produtos;                // Váriavel global que armazena a quantidade total de produtos

typedef struct Produto {
    char nome[30];
    char codigo[10];
    float preco;
} Produto;

void cabecalho(void);                          // Mostra nome e versão do programa
Produto *cadastrar_produtos();                 // Cadastra produtos, retorna endereço dos produtos
void catalogo(struct Produto *produto);        // Catalogo dos produtos registrados no sistema
void consultar_preco(struct Produto *produto); // Consulta preço através do código do produto

int main(void)
{
    Produto *produto;           // Ponteiro para a alocação dinámica da quantidade de produtos

    cabecalho();                
  
    produto = cadastrar_produtos();
    catalogo(produto);              
    consultar_preco(produto);    
    
    free(produto);             // Libera o espaço da memória alocada dinamicamente

    return EXIT_SUCCESS;
}

void cabecalho(void)
{
    printf("Bem vindo ao programa de controle de estoque v0.01\n\n");
}

Produto *cadastrar_produtos()
{
 
    Produto *p = malloc(num_produtos * sizeof(Produto));          // Aloca memória dinamicamente

    printf("Quantos produtos deseja cadastrar? ");
    scanf(" %d", &num_produtos);
 
    for (int i = 0; i < num_produtos; i++) {      // Laço que pergunta as informações ao usuário
        printf("Nome: ");
        scanf(" %s", p[i].nome);

        printf("Código: ");
        scanf(" %s", p[i].codigo);

        printf("Preco: ");
        scanf(" %f", &p[i].preco);

        putchar('\n');
    }

    return p;                     // Retorna o endereço do espaço da memória criada nesta função
}

void catalogo(struct Produto *produto) 
{
    system("clear");            

    printf("Código\tNome\n");

    for (int i = 0; i < num_produtos; i++)     // Laço que mostra as informações do usuário
        printf("%s\t%s\n", produto[i].codigo, produto[i].nome);
}

void consultar_preco(struct Produto *produto)
{
    char codigo[10];                    // Váriavel para armezenar dados de consulta do usuário
    char resposta;                      // Váriavel para continuar ou encerrar laço
    int i;

    do {
        printf("\nDigite código do produto para consultar seu preço: ");
        scanf(" %s", codigo);

        for (i = 0; i < num_produtos; i++) {
            if (strcmp(produto[i].codigo, codigo) == 0) {
                printf("\nPreco do produto %s é %.2f\n", produto[i].nome, produto[i].preco);
                break;
            }
        }

        if (i == num_produtos) {               // Caso produto não for achado
            printf("\nCódigo do produto não foi achado!\n");
        }

        printf("Deseja consultar um novo produto? [S/N]: ");
        scanf(" %c", &resposta);
        
        system("clear");

    } while (resposta != 'N');
}

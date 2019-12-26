#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SAIR     '0'
#define DEPOSITO '1'
#define SAQUE    '2'

/*   O programa armazena contas bancárias para quantidade de clientes informados
 *   pelo usuário. O sistema possibilita a realização de saques ou depósitos
 *   nas contas.
 */

int num_clientes;        // Váriavel global que armazena a quantidade total de clientes 
int id = 50;             // Incrementa o número da conta corrente e retorna para cliente

typedef struct Conta {                  // Estrutura que armazena contas dos clientes
    int id;                             // Número da conta corrente
    char nome[30];                      // Nome completo
    char cpf[15];                       // Consulta Pessoa Física
    float conta_corrente;               // Saldo da conta corrente                 
    float valor;                        // Valor monetário para depositar ou sacar da conta
    unsigned int pin;                   // PIN da conta corrente
} Conta;

void cabecalho(void);                   // Mostra o nome e versão do programa
Conta *cadastrar_contas(void);          // Cadastra contas, retorna endereço base
void menu_principal(struct Conta *cliente);                  // Menu de transação
void transacao(struct Conta *cliente, char tipo_transacao);  // Depósito ou Saque
int numero_conta_corrente(void);    // Usa a váriavel id para retorna oi número da conta
void imprimir_dados(const struct Conta *cliente);            // Imprime dados do cliente

int main(void)
{
    Conta *cliente;            // Ponteiro que armazena informações de todos os clientes

    srand(time(NULL));         // Para gerar números aleatórios de contas com 2 digitos
    
    cabecalho();               // Mostra o nome e versão do programa

    cliente = cadastrar_contas();
    menu_principal(cliente);
 
    free(cliente);             // Libera o espaço da memória alocada dinamicamente
 
    return EXIT_SUCCESS;
}

void cabecalho(void)
{
    printf("Simulador de contas bancárias v0.01\n\n");
}

Conta *cadastrar_contas()
{
    Conta *cliente;
    unsigned int pin;
    
    printf("Número de clientes que precisam de contas bancárias para criação: ");
    scanf(" %d", &num_clientes);
    getchar();

    cliente = malloc(num_clientes * sizeof(Conta));  // Aloca dinamicamente memória no 'heap'
 
    for (int i = 0; i < num_clientes; i++) {
        memset(&cliente[i], 0, sizeof(cliente[i]));      // Inicializa a estrutura do cliente 
        
        cliente[i].id = numero_conta_corrente();
        printf("\nNúmero da Conta Corrente: %d\n", cliente[i].id);

        printf("Nome completo: ");                       // Armazena o nome completo do cliente 
        fgets(cliente[i].nome, 30, stdin);

        printf("Número de CPF: ");                       // Armazena o CPF do cliente 
        scanf(" %s", cliente[i].cpf);
        getchar();

        do {
            printf("Digite um novo PIN: ");              // Armazena o PIN do cliente
            scanf(" %d", &cliente[i].pin);

            printf("Redigite um novo PIN: ");
            scanf(" %d", &pin);

            if (cliente[i].pin != pin) {                // Checa se os dois não são iguais
                printf("\nPINs não são iguais. Por favor digite novamente.\n\n");
            }

        } while (cliente[i].pin != pin);                // Se forem iguais, saia do laço

        
        printf("\nPor favor, deposite uma quantia na sua conta recem-criada.\n");

        do {
            printf("Valor da quantia: ");              // Deposito do valor inicial ao criar conta                                                    
            scanf(" %f", &cliente[i].valor);                                                        
            getchar();

            if (cliente[i].valor < 0) {                // Se valor for negativo, mostra valor inválido                                             
                printf("valor inválido!\n");                                                        
            }                                                                                       

        } while (cliente[i].valor < 0);                // Laço roda novamente caso valor for negativo                                                    

        cliente[i].conta_corrente += cliente[i].valor; // Deposita o valor na conta corrente                                                   
    }                                                                                               

    return cliente;
}

void menu_principal(struct Conta *cliente)                                        
{                                                                                                   
    char escolha;   

    do {                                                                                            
        system("clear");                         

        printf("Menu Principal\n\n");                                                               
        printf("[1] - Depósito\n");                                                                 
        printf("[2] - Saque\n");                                                                    
        printf("[0] - Sair\n\n");                                                                     
        printf("Digite uma opção: ");                                                               

        scanf(" %c", &escolha);                                                                     
        getchar();

        switch (escolha) {                                                                          
            case DEPOSITO:                                                                          
                transacao(cliente, DEPOSITO);                                                     
                break;                                                                               
            case SAQUE:                                                                             
                transacao(cliente, SAQUE);                                                        
                break;                                                                               
            case SAIR:                                                                              
                exit(0);                                                                             
            default:                                                                                
                printf("\nOpção inválida! Pressione uma tecla para ir ao Menu Principal...\n");
                getchar();
                continue;
        }                                                                                           

        printf("\nDeseja fazer outra transação? [S/N] ");                                  
        scanf(" %c", &escolha);                                                                     

    } while (escolha != 'N'); 
}

void transacao(struct Conta *cliente, char tipo_transacao)
{
    int id;                           // Armazena o número da conta para consulta
    int pin;                          // Armazena o número do PIN para consulta
    char achou_conta;                 // Atribui valor 1 a variável se achar conta e PIN válidos
    char acao[12];                    // Armazena o string "depositado" ou "sacado" 
    int i;

    if (tipo_transacao == DEPOSITO) { // Armazena ação para mostrar depois o tipo de transação
        strcpy(acao, "depositado");
    }
    else if (tipo_transacao == SAQUE) { 
        strcpy(acao, "sacado");
    }

    printf("Digite seu número de conta corrente para efetuar transação: ");
    scanf(" %d", &id);

    printf("Digite seu PIN: ");
    scanf(" %d", &pin);

    for (i = 0; i < num_clientes; i++) {
        if (cliente[i].id == id && cliente[i].pin == pin) {
            achou_conta = 1;
            break;
        }
    }

    if (achou_conta) {
        printf("Digite o valor a ser %s: ", acao);
        scanf(" %f", &cliente[i].valor);
        getchar();

        if (tipo_transacao == DEPOSITO) {
            cliente[i].conta_corrente += cliente[i].valor;
        }
        else {
            cliente[i].conta_corrente -= cliente[i].valor;
        }

        imprimir_dados(&cliente[i]);
    }
    else {
        printf("\nNão achamos o número da conta corrente ou PIN está incorreto.\n");
        printf("Por favor tente novamente.\n");
    }
}

int numero_conta_corrente(void)
{
    return id++;
}

void imprimir_dados(const struct Conta *cliente)
{
    system("clear");

    printf("Número da Conta Corrente: %d\n", cliente->id);
    printf("Nome Completo: %s", cliente->nome);
    printf("Saldo final da conta corrente: %.2f\n", cliente->conta_corrente);

}

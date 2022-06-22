#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define qtdVeiculosDaLocadora 500

int retornaCodigoVeiculo();
void cadastraVeiculo();

struct cadastroCliente
{
    char cliente[50];
    int ddd;
    int telefone;
    char rua[10];
    char bairro[20];
    int numero;
    char complemento[20];
};

typedef struct cadastroCliente cliente;

int main()
{
    setlocale (LC_ALL, "portuguese");
    srand(time(NULL));

    exibeTelaBoasVindas(void); // esse void deve ser o parâmetro que a função recebe!
    cadastraVeiculo();
    cadastrarCliente();

    return 0;
}

int exibeTelaBoasVindas(void); // esse void deve ser o parâmetro que a função recebe!
void registraFilial(void);
void realizaLogin(char login, char senha); // in.login & in.senha?

struct login                           // before the first use of `l`.
{
    char filial[50];
    char login[30];
    char senha[20];
};

int exibeTelaBoasVindas(void) // posso fazer int main()? 
{
    int opcao;

    printf("Olá!\n");
    printf("Escolha '1' para registrar\t\tEscolha '2' para informar login e senha\n\n");
    printf("Sua escolha: ");
    scanf("%d",&opcao);

    getchar();

    if(opcao == 1)
    {
        system("CLS");
        return registraFilial(char login, char senha); // quais parâmetros essa função deve receber?
    }
    else 
    {
        if(opcao == 2)
        {
            system("CLS");
            return realizaLogin(void); // quais parâmetros essa função deve receber?
        }
    }
}

void registraFilial(void)
{
    FILE *log;

    log=fopen("contemLoginESenha.txt","w");

    if (log == NULL)
    {
        fputs("Error at opening File!", stderr); // stderr é o quê???????????
        exit(1);
    }

    struct login in;

    printf("\nSeja bem vindX ao sistema inteligente da LocaMais! \nPara começar, precisamos de algumas informações para o registro.\n\n");
    printf("Escolha um login e uma senha para entrar no sistema.\n");
    printf("O login não deve ter mais do que 50 caracteres.\n");
    printf("A senha deve ter 8 caracteres e conter letras minúsculas, maiúsculas, números e caracteres especiais.\n"); 

    printf("\nInforme um login: ");
    scanf("%s",in.login);
    printf("\nInforme uma senha: ");
    scanf("%s",in.senha);


    fwrite(&in,sizeof(in),1,log);
    fclose(log);

    printf("\nConfirmando detalhes...\n...\nSeja sem vinda, filial %s!\n\n", filial);
    printf("\nRegistration Successful!\n");
    printf("Press any key to continue...");
    getchar();
    system("CLS");
    return realizaLogin(in.login, in.senha); // por que não reconhece o in?
}

void realizaLogin(char login, char senha) // como informar os parâmetros aqui?
{
    char login[50],senha[20];
    FILE *log;

    log = fopen("contemLoginESenha.txt","r");
    if (log == NULL)
    {
        fputs("Error at opening File!", stderr);
        exit(1);
    }

    struct login in;

    printf("\nOlá!\n\nInforme abaixo seu login e senha para entrar no sistema\n\n");
    printf("Login:  ");
    fgets(login, 50, stdin);
    printf("\nSenha: ");
    printf("\n");
    fgets(senha, 20, stdin);

    while(fread(&in,sizeof(in),1,log))
    {
        if(strcmp(login,in.login)==0 && strcmp(senha,in.senha)==0)
        {
            printf("\nOlá, %s, seja bem vinda!\nA seguir você será direcionada ao menu principal.\n");
            menuPrincipal();
        }
        else 
        {
            printf("\nInformações incorretas.\nPor favor, informe novamente.\n");
            realizaLogin(char login, char senha);     // função recursiva!
        }
    }
}


void menuPrincipal();
void saiDoPrograma();
int cadastraCliente(/*precisa de parâmetros?*/);


void menuPrincipal()
{
    int op;

    printf("\n\n");
    printf("+---------------------------------------------------+\n");
    printf("\t\t    MENU PRINCIPAL");
    printf("\n");
    printf("+---------------------------------------------------+\n");
    printf("|\n");
    printf("| Favor escolher uma das opções abaixo:");
    printf("\n|\n");
    printf("| 0. Sair do programa!\n");
    printf("| 1. Cadastro de cliente\n");
    printf("| 2. Cadastro de veículo\n");
    printf("| 3. Cadastro de locação\n");
    printf("| 4. Baixa na locação\n"); // [DÚVIDA SOBRE FUNÇÃO]
    printf("| 5. Pesquisar cliente\n");
    printf("| 6. Pesquisar veículo\n");
    printf("| 7. Visualizar locação por cliente\n");
    printf("|\n");
    printf("+---------------------------------------------------+\n");
    printf("|\n| Sua escolha: ");
    scanf("%d", &op);

    switch (inputMenuPrincipal)
    {
    case 0:
        printf("|\n|\nVocê escolheu:\n| 0. Sair do programa!\n");
        saiDoPrograma();
        break;
    
    case 1:
        printf("|\n|\nVocê escolheu:\n| 1. Cadastro de cliente\n");
        cadastrarCliente();
        break;

    case 2:
        printf("|\n|\nVocê escolheu:\n| 2. Cadastro de veículo\n");
        cadastraVeiculo();
        break;
    
    case 3:
        printf("|\n|\nVocê escolheu:\n| 3. Cadastro de locação\n");
        break;
    
    case 4:
        printf("|\n|\nVocê escolheu:\n| 4. Baixa na locação\n");
        break;
    
    case 5:
        printf("|\n|\nVocê escolheu:\n| 5. Pesquisar cliente\n");
        break;
    
    case 6:
        printf("|\n|\nVocê escolheu:\n| 6. Pesquisar veículo\n");
        break;

    case 7:
        printf("|\n|\nVocê escolheu:\n| 7. Visualizar locação por cliente\n");
        break;

    default:
        break;
    }
    
    return 0;
}

void saiDoPrograma()
{
    printf("\n\nFIM DO PROGRAMA!");
}


struct Veiculo
{
    int codigoVeiculo;
    char descricao[50];
    char modelo[20];
    char cor[10];
    int placa;
    float valorDiaria;
    int qtdMaxOcupantes;
    char status[5];
};

void cadastraVeiculo()
{
    FILE *ponteiroVeiculos = fopen("veiculosCadastrados.txt", "a");

    if (ponteiroVeiculos == NULL)
    {
        printf("O arquivo não pode ser aberto!\nO programa vai te redirecionar automaticamente para o menu principal.\n");
        menuPrincipal()
    }
    else
    {
        struct Veiculo veiculo;

        veiculo.codigoVeiculo = retornaCodigoVeiculo();

        printf("Informe a descrição do veículo: ");
        fgets(veiculo.descricao, 50, stdin);
        fflush(stdin);
        
        printf("Informe o modelo do veículo: ");
        fgets(veiculo.modelo, 20, stdin);
        fflush(stdin);

        printf("Informe a cor do veículo: ");
        fgets(veiculo.cor, 10, stdin);
        fflush(stdin);

        printf("Informe o status atual do veículo (ocup/disp): ");
        fgets(veiculo.status, 5, stdin);
        fflush(stdin);

        printf("Informe a placa do veículo: ");
        scanf("%d", &veiculo.placa);
        fflush(stdin);

        printf("Informe o valor da diária deste veículo: R$");
        scanf("%f", &veiculo.valorDiaria);
        fflush(stdin);

        printf("Informe a capacidade máxima de ocupantes para este veículo: ");
        scanf("%d", &veiculo.qtdMaxOcupantes);

        fprintf(ponteiroVeiculos, "Código do veículo: %d\n", veiculo.codigoVeiculo);
        fprintf(ponteiroVeiculos, "Descrição: %s", veiculo.descricao);
        fprintf(ponteiroVeiculos, "Modelo: %s", veiculo.descricao);
        fprintf(ponteiroVeiculos, "Cor: %s", veiculo.cor);
        fprintf(ponteiroVeiculos, "Placa: %d\n", veiculo.placa);
        fprintf(ponteiroVeiculos, "Valor da diária: R$%.2f\n", veiculo.valorDiaria);
        fprintf(ponteiroVeiculos, "Capacidade máxima de ocupantes para este veículo: %i\n", veiculo.qtdMaxOcupantes);
        fprintf(ponteiroVeiculos, "Status do veículo: %s\n", veiculo.status);
        fprintf(ponteiroVeiculos, "\n\n");

        printf("\nVEÍCULO CADASTRADO COM SUCESSO!");
    }

    fclose(ponteiroVeiculos);
}

int retornaCodigoVeiculo()
{
    int codigoVeiculo;

    for (int i = 0; i <= 999; i++)
    {
        codigoVeiculo = (rand() % (999 - 100 + 1) + 100);
        return codigoVeiculo;
    }
}

void cadastrarCliente()
{
    FILE *arquivoCadastroClientes;
    cliente c;
    printf("\tBem vindo ao cadastro de clientes!\n");
    printf("\t----------------------------------\n");
    printf("\n\tNome do cliente: ");
    gets(c.cliente);
    fflush(stdin);
    printf("\t----------------------------------\n");
    printf("\n\t\tTelefone\n");
    printf("\n\tDDD: ");
    scanf("%i", &c.ddd);
    printf("\tNúmero: ");
    scanf("%i", &c.telefone);
    printf("\t----------------------------------\n");
    printf("\n\t\tEndereço");
    printf("\n\n\tRua: ");
    fflush(stdin);
    gets(c.rua);
    fflush(stdin);
    printf("\tBairro: ");
    fflush(stdin);
    gets(c.bairro);
    fflush(stdin);
    printf("\tNúmero: ");
    scanf("%i", &c.numero);
    printf("\tComplemento: ");
    fflush(stdin);
    gets(c.complemento);
    fflush(stdin);
    printf("\n\tCadastro realizado com sucesso!");

    if ((arquivoCadastroClientes = fopen("arquivoCadastroClientes.txt", "a")) == NULL)
    {
        printf("Erro na abertura do arquivo.");
    }
    else
    {
        fprintf(arquivoCadastroClientes, "\t------------------\n\t[Informações Gerais]\n\n\tNome do cliente: %s\n\n", c.cliente);
        fprintf(arquivoCadastroClientes, "\t[Telefone]\n\n\tNúmero: (%i)%i\n\n", c.ddd, c.telefone);
        fprintf(arquivoCadastroClientes, "\t[Endereço]\n\n\tRua: %s\n\tBairro: %s\n\tNúmero: %i\n\tComplemento: %s\n\n\n", c.rua, c.bairro, c.numero, c.complemento);
        fclose(arquivoCadastroClientes);
    }
}

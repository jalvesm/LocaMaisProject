#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

struct TClientes
{
    char nome[50];
    int codigo;
    int ddd;
    int telefone;
    char rua[10];
    char bairro[20];
    int numero;
    char complemento[20];
};

typedef struct TClientes cliente;

struct TVeiculo
{
    int codigoVeiculo;
    char descricao[50];
    char modelo[20];
    char cor[10];
    int placa;
    float valorDiaria;
    int capacidadeMaxOcupantes;
    char status[20];
};
typedef struct TVeiculo veiculo;

struct TLocacao
{
    int codigoVeiculo;
    int codigo;
    int codigoLoc;
    int dataRetirada;
    int dataDevReal;
    int dataDevPrevista;
    int qtdOcupantes;
    float multa;
    char seguro[5];
    int diasDeAtraso;
    float totalPagar;
};

typedef struct TLocacao locacao;

// outros prototipos de funções

void imprimirLinha();

// prototipo funções cliente

int menuClientes();
int localizarClientes(FILE *clientePtr, int codigo);
void cadastrarClientes(FILE *clientePtr);
void listarClientes(FILE *clientePtr);
void pesquisarClientes(FILE *clientePtr);

// prototipo funções veiculo

int menuVeiculos();
int localizarVeiculos(FILE *veiculoPtr, int codigo);
void cadastrarVeiculos(FILE *veiculoPtr);
void listarVeiculos(FILE *veiculoPtr);
void pesquisarVeiculos(FILE *veiculoPtr);

// prototipo funções locação

int menuLocacao();
void cadastrarLocacao();

int main()
{
    setlocale(LC_ALL, "portuguese");
    int op;
    do
    {
        imprimirLinha();
        printf("\t\t\t    MENU PRINCIPAL");
        imprimirLinha();

        printf("\n\n\tFavor escolher uma das opções abaixo:\n\n");
        printf("\t\t0. Sair do programa!\n");
        printf("\t\t1. Menu cliente\n");
        printf("\t\t2. Menu veículo\n");
        printf("\t\t3. Menu locação\n\n");
        /*printf("\t\t4. Pesquisar cliente\n");
        printf("\t\t5. Pesquisar veículo\n");
        printf("\t\t6. Visualizar locação por cliente\n\n");*/

        printf("\n\t\tSua escolha: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            printf("\n\t\t>> 1. Cadastro de cliente\n\n");
            imprimirLinha();
            menuClientes();
            break;

        case 2:
            printf("\n\t\t>> 2. Cadastro de veículo\n\n");
            imprimirLinha();
            menuVeiculos();
            break;

        case 3:
            printf("\n\t\t>> 3. Cadastro de locação\n\n");
            imprimirLinha();
            menuLocacao();
            break;

            /*case 4:
                printf("\n\t\t>> 4. Pesquisar cliente\n\n");
                //imprimirLinha();

                break;

            case 5:
                printf("\n\t\t>> 5. Pesquisar veículo\n\n");
                imprimirLinha();
                break;

            case 6:
                printf("\n\t\t>> 6. Visualizar locação por cliente\n\n");
                imprimirLinha();
                // função;
                break;*/
        }
    } while (op != 0);

    return 0;
}

void imprimirLinha()
{
    printf("\n\t+---------------------------------------------------+\n");
}

/* Parte do cliente */

int menuClientes()
{
    FILE *clientePtr;
    int op;
    if ((clientePtr = fopen("clientesCadastrados.dat", "r+b")) == NULL)
    {
        printf("\tArquivo n�o existia... Criando arquivo...\n");

        if ((clientePtr = fopen("clientesCadastrados.dat", "w+b")) == NULL)
        {
            printf("Erro na cria��o do arquivo!");
            exit(1);
        }
    }

    do
    {
        printf("\n\tBem vindo ao cadastro de cliente!\n\n");
        printf("\t1 - Cadastrar cliente\n");
        printf("\t2 - Alterar cliente\n");
        printf("\t3 - Listar clientes\n");
        printf("\t4 - Pesquisar clientes\n");
        printf("\t0 - Voltar ao menu principal\n");
        printf("\tEscolha: ");
        scanf("%i", &op);
        switch (op)
        {
        case 1:
            printf("\n\tVocê escolheu cadastrar um cliente!\n\n");
            cadastrarClientes(clientePtr);
            break;

        case 2:
            printf("\n\tVocê escolheu alterar os dados do cliente!\n\n");
            // alteraCliente(clientePtr);
            break;

        case 3:
            printf("\n\tVocê escolheu listar todos os clientes!\n\n");
            listarClientes(clientePtr);
            break;

        case 4:
            printf("\n\tVocê escolheu pesquisar os clientes!\n\n");
            pesquisarClientes(clientePtr);
            system("pause");
            break;
        }
    }

    while (op != 0);
    fclose(clientePtr);
    return 0;
}

int localizarClientes(FILE *clientePtr, int codigo) // função para verificar se o codigo do cliente ja foi cadastrado antes
{
    int posicao = -1, achou = 0;
    cliente c;
    fseek(clientePtr, 0, SEEK_SET);
    fread(&c, sizeof(c), 1, clientePtr);
    while (!feof(clientePtr) && !achou)
    {
        posicao++;

        if (c.codigo == codigo)
        {
            achou = 1;
        }
        fread(&c, sizeof(c), 1, clientePtr);
    }

    if (achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}

void cadastrarClientes(FILE *clientePtr) // Cadastra os clientes
{
    cliente c;
    int posicao;
    printf("\n\tC�digo do cliente: ");
    fflush(stdin);
    scanf("%i", &c.codigo);
    posicao = localizarClientes(clientePtr, c.codigo);
    if (posicao == -1)
    {
        printf("\tNome do cliente: ");
        fflush(stdin);
        gets(c.nome);
        printf("\tDDD e Telefone: ");
        fflush(stdin);
        scanf("%i%i", &c.ddd, &c.telefone);
        printf("\tRua: ");
        fflush(stdin);
        gets(c.rua);
        printf("\tBairro: ");
        fflush(stdin);
        gets(c.bairro);
        printf("\tN�mero: ");
        fflush(stdin);
        scanf("%i", &c.numero);
        printf("\tComplemento: ");
        fflush(stdin);
        gets(c.complemento);
        fseek(clientePtr, 0, SEEK_END);
        fwrite(&c, sizeof(c), 1, clientePtr);
        fflush(clientePtr);
    }
    else
    {
        printf("\n\n\tO c�digo %i j� foi usado anteriomente. Cadastro n�o realizado.\n\tTente novamente!\n\n", c.codigo);
    }
}

void listarClientes(FILE *clientePtr) // Mostra todos os clientes cadastrados
{
    cliente c;
    fseek(clientePtr, 0, SEEK_SET);
    fread(&c, sizeof(c), 1, clientePtr);
    while (!feof(clientePtr))
    {
        printf("\n\n\t[Dados do cliente]\n\n");
        printf("\tNome: %s\t C�digo: %i\n", c.nome, c.codigo);
        printf("\tTelefone: (%i)%i\n", c.ddd, c.telefone);
        printf("\tRua: %s\n\tBairro: %s\n\tN�mero: %i\n\tComplemento: %s\n", c.rua, c.bairro, c.numero, c.complemento);
        fread(&c, sizeof(c), 1, clientePtr);
    }
}

void pesquisarClientes(FILE *clientePtr) // Pesquisa cliente por codigo
{
    cliente c;
    int codigoPesquisado;
    fseek(clientePtr, 0, SEEK_SET);
    fread(&c, sizeof(c), 1, clientePtr);
    printf("\n\t[Pesquisar Cliente]\n");
    printf("\n\tDigite o c�digo do cliente a ser pesquisado: ");
    scanf("%i", &codigoPesquisado);
    while (!feof(clientePtr))
    {
        if (codigoPesquisado == c.codigo)
        {
            printf("\n\n\t[Dados do cliente]\n\n");
            printf("\tNome: %s\n", c.nome);
            printf("\tC�digo (CPF): %i\n", c.codigo);
            printf("\tTelefone: (%i)%i\n", c.ddd, c.telefone);
            printf("\tRua: %s\n\tBairro: %s\n\tN�mero: %i\n\tComplemento: %s\n", c.rua, c.bairro, c.numero, c.complemento);
        }

        fread(&c, sizeof(c), 1, clientePtr);
    }
    system("pause");
}

/*Parte do veiculo*/

int menuVeiculos()
{
    FILE *veiculoPtr;
    int op;

    if ((veiculoPtr = fopen("veiculosCadastrados.dat", "r+b")) == NULL)
    {
        printf("\tArquivo não existia... Criando arquivo...\n");

        if ((veiculoPtr = fopen("veiculosCadastrados.dat", "w+b")) == NULL)
        {
            printf("Erro na criação do arquivo!\n");
            exit(1);
        }
    }

    do
    {
        printf("\n\tBem vindo ao cadastro de veículo!\n\n");
        printf("\t1 - Cadastrar veículo\n");
        printf("\t2 - Alterar veículo\n");
        printf("\t3 - Listar veículos\n");
        printf("\t4 - Pesquisar veículos\n");
        printf("\t5 - Pesquisar veículos para locação\n");
        printf("\t0 - Voltar ao menu principal\n");
        printf("\tEscolha: ");
        scanf("%i", &op);
        switch (op)
        {
        case 1:
            printf("\n\tVocê escolheu cadastrar um veículo!\n\n");
            cadastrarVeiculos(veiculoPtr);
            break;

        case 2:
            printf("\n\tVocê escolheu alterar os dados do veículo!\n\n");
            //
            break;

        case 3:
            printf("\n\tVocê escolheu listar todos os veículos!\n\n");
            listarVeiculos(veiculoPtr);
            break;

        case 4:
            printf("\n\tVocê escolheu pesquisar os veículos!\n\n");
            pesquisarVeiculos(veiculoPtr);
            break;

        case 5:
            printf("\n\tVocê escolheu pesquisar veículos para locação!\n\n");
            pesquisarOcupantes(veiculoPtr);
            system("pause");
            break;
        }
    }

    while (op != 0);
    fclose(veiculoPtr);
    return 0;
}

int localizarVeiculos(FILE *veiculoPtr, int codigo) // função para verificar se o codigo do veiculo ja foi cadastrado antes
{
    int posicao = -1, achou = 0;
    veiculo v;
    fseek(veiculoPtr, 0, SEEK_SET);
    fread(&v, sizeof(v), 1, veiculoPtr);
    while (!feof(veiculoPtr) && !achou)
    {
        posicao++;
        if (v.codigoVeiculo == codigo)
        {
            achou = 1;
        }
        fread(&v, sizeof(v), 1, veiculoPtr);
    }
    if (achou)
    {
        return posicao;
    }
    else
    {
        return -1;
    }
}

void cadastrarVeiculos(FILE *veiculoPtr) // procedimento para cadastrar veiculo
{
    veiculo v;
    int posicao;
    printf("\tDigite o código do veículo: ");
    fflush(stdin);
    scanf("%d", &v.codigoVeiculo);

    posicao = localizarVeiculos(veiculoPtr, v.codigoVeiculo);

    if (posicao == -1)
    {
        printf("\tInforme o modelo: ");
        fflush(stdin);
        gets(v.modelo);

        printf("\tInforme a cor: ");
        fflush(stdin);
        gets(v.cor);

        printf("\tInforme a placa: ");
        fflush(stdin);
        scanf("%d", &v.placa);

        printf("\tInforme o valor da diária: R$");
        fflush(stdin);
        scanf("%f", &v.valorDiaria);

        printf("\tInforme a quantidade máxima de ocupantes: ");
        fflush(stdin);
        scanf("%d", &v.capacidadeMaxOcupantes);

        printf("\tInforme o status (ocupado/disponível): ");
        fflush(stdin);
        gets(v.status);

        fseek(veiculoPtr, 0, SEEK_END);

        fwrite(&v, sizeof(v), 1, veiculoPtr);
        fflush(veiculoPtr);
    }
    else
    {
        printf("\n\n\tCódigo %d já existe no arquivo. Inclusão não realizada. Tente novamente! \n", v.codigoVeiculo);
    }
}

void listarVeiculos(FILE *veiculoPtr) // Exibe todos os veiculos cadastrados
{
    veiculo v;
    fseek(veiculoPtr, 0, SEEK_SET);
    fread(&v, sizeof(v), 1, veiculoPtr);
    while (!feof(veiculoPtr))
    {
        printf("\n\n\t[Dados do veículo]\n\n");
        printf("\tModelo: %s\tCódigo: %i\n", v.modelo, v.codigoVeiculo);
        printf("\tCor: %s\n\tPlaca: %d\n\tValor da diária: R$ %2.2f", v.cor, v.placa, v.valorDiaria);
        printf("\tOcupantes: %d\tStatus: %s\n", v.capacidadeMaxOcupantes, v.status);
        fread(&v, sizeof(v), 1, veiculoPtr);
    }
}

void pesquisarVeiculos(FILE *veiculoPtr) // Pesquisa veiculo por codigo
{
    veiculo v;
    int codigoPesquisado;
    fseek(veiculoPtr, 0, SEEK_SET);
    fread(&v, sizeof(v), 1, veiculoPtr);
    printf("\n\t[Pesquisar Veículo]\n");
    printf("\n\tDigite o código do veículo a ser pesquisado: ");
    scanf("%i", &codigoPesquisado);
    while (!feof(veiculoPtr))
    {
        if (codigoPesquisado == v.codigoVeiculo)
        {
            printf("\n\n\t[Dados do veículo]\n\n");
            printf("\tModelo: %s\n\tCódigo: %i\n", v.modelo, v.codigoVeiculo);
            printf("\tCor: %s\n\tPlaca: %d\n\tValor da diária: R$%2.2f\n", v.cor, v.placa, v.valorDiaria);
            printf("\tOcupantes: %d\tStatus: %s\n", v.capacidadeMaxOcupantes, v.status);
        }

        fread(&v, sizeof(v), 1, veiculoPtr);
    }
    system("pause");
}

int menuLocacao()
{
    FILE *locacaoPtr;

    int op;

    if ((locacaoPtr = fopen("cadastraLocacao.dat", "r+b")) == NULL)
    {
        printf("Arquivo não existia...Criando arquivo...\n");

        if ((locacaoPtr = fopen("cadastraLocacao.dat", "w+b")) == NULL)
        {
            printf("Erro na criação do arquivo!\n");
            exit(1);
        }
        system("pause");
    }

    do
    {
        printf("\n\tBem vindo ao cadastro de locação!\n\n");
        printf("\t1 - Cadastrar locação\n");
        printf("\t2 - Alterar locação\n");
        printf("\t3 - Listar locações\n");
        printf("\t4 - Pesquisar locações de clientes\n");
        printf("\t0 - Voltar ao menu principal\n");
        printf("\tEscolha: ");
        scanf("%i", &op);
        switch (op)
        {
        case 1:
            printf("\n\tVocê escolheu cadastrar uma locação!\n\n");
            // pesquisarOcupantes(veiculoPtr);
            break;

        case 2:
            printf("\n\tVocê escolheu alterar os dados da locação!\n\n");
            // alteraLocacao(locacaoPtr);
            break;

        case 3:
            printf("\n\tVocê escolheu listar todas as locações!\n\n");
            // listarLocacao(locacaoPtr);
            break;

        case 4:
            printf("\n\tVocê escolheu pesquisar as locações de um cliente!\n\n");
            // pesquisarLocacaoClientes(locacaoPtr);
            system("pause");
            break;
        }

    } while (op != 0);
    fclose(locacaoPtr);
    return 0;
}

void pesquisarOcupantes(FILE *veiculoPtr) // Pesquisa veiculo por codigo
{
    veiculo v;
    int pesquisaOcupantes;
    fseek(veiculoPtr, 0, SEEK_SET);
    fread(&v, sizeof(v), 1, veiculoPtr);
    printf("\n\t[Pesquisar Ocupantes]\n");
    printf("\n\tDigite a quantidade de ocupantes a ser pesquisado: ");
    scanf("%i", &pesquisaOcupantes);
    while (!feof(veiculoPtr))
    {
        if (pesquisaOcupantes == v.capacidadeMaxOcupantes)
        {
            if (strcmp(v.status, "disponivel") == 0)
            {
                printf("\n\n\t[Dados do veículo]\n\n");
                printf("\tModelo: %s\n\tCódigo: %i\n", v.modelo, v.codigoVeiculo);
                printf("\tCor: %s\n\tPlaca: %d\n\tValor da diária: R$%2.2f\n", v.cor, v.placa, v.valorDiaria);
                printf("\tOcupantes: %d\tStatus: %s\n", v.capacidadeMaxOcupantes, v.status);
            }
        }

        fread(&v, sizeof(v), 1, veiculoPtr);
    }
    system("pause");
}

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
void alteraCliente(FILE *clientePtr);

// prototipo funções veiculo

int menuVeiculos();
int localizarVeiculos(FILE *veiculoPtr, int codigo);
void cadastrarVeiculos(FILE *veiculoPtr);
void listarVeiculos(FILE *veiculoPtr);
void pesquisarVeiculos(FILE *veiculoPtr);
void alteraVeiculo(FILE *veiculoPtr);

// prototipo funções locação

int menuLocacao(locacaoPtr, veiculoPtr, clientePtr, qtdDesejada);
int localizaLocacao(FILE *locacaoPtr, int codigo);
void cadastrarLocacao(FILE *locacaoPtr, FILE *veiculoPtr, FILE *clientePtr, int qtdDesejada);
void listaLocacaoDoCliente(FILE *veiculoPtr, FILE *clientePtr, FILE *locacaoPtr);
void listarLocacao(FILE *locacaoPtr);
void alteraLocacao(FILE *locacaoPtr);


int main(FILE *locacaoPtr, FILE *veiculoPtr, FILE *clientePtr, int qtdDesejada)
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
        printf("\t\t2. Menu veiculo\n");
        printf("\t\t3. Menu locacao\n\n");
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
            menuLocacao(veiculoPtr, clientePtr, qtdDesejada);
            break;
        }
    } while (op != 0);

    return 0;
}

void imprimirLinha() // imprime linha no menu pra deixar bonitinho
{
    printf("\n\t+---------------------------------------------------+\n");
}

/* Parte do cliente */

int menuClientes() // apresenta opções para funções da parte de cadastro de clientes
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
            alteraCliente(clientePtr);
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
    clientePtr = fopen("clientesCadastrados.dat", "r+b");

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
    clientePtr = fopen("clientesCadastrados.dat", "r+b");

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
    clientePtr = fopen("clientesCadastrados.dat", "r+b");

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
    clientePtr = fopen("clientesCadastrados.dat", "r+b");

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

void alteraCliente(FILE *clientePtr) // Função que altera os dados do cliente

{
    int codigo, posicao;
    cliente c;
    printf("\tDigite o codigo do cliente para alterar: ");
    scanf("%d", &codigo);
    posicao = localizarClientes(clientePtr, codigo);
    if (posicao != -1) // localizou o cliente
    {
        fseek(clientePtr, sizeof(c) * (posicao), SEEK_SET);
        fread(&c, sizeof(c), 1, clientePtr);
        printf("\n\n\t[Dados atuais do cliente]\n\n");
        printf("\tNome: %s\t Codigo: %i\n", c.nome, c.codigo);
        printf("\tTelefone: (%i)%i\n", c.ddd, c.telefone);
        printf("\tRua: %s\n\tBairro: %s\n\tNúmero: %i\n\tComplemento: %s\n", c.rua, c.bairro, c.numero, c.complemento);
        printf("\n\n\t[Alterar dados]\n\n");
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
        fseek(clientePtr, sizeof(c) * (posicao), SEEK_SET);
        fwrite(&c, sizeof(c), 1, clientePtr);
        fflush(clientePtr);
    }
}

/*Parte do veiculo*/

int menuVeiculos() // mostra opções para escolher determinadas funções da parte de veículos
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
        printf("\t1 - Cadastrar veiculo\n");
        printf("\t2 - Alterar veiculo\n");
        printf("\t3 - Listar veiculos\n");
        printf("\t4 - Pesquisar veiculos\n");
        printf("\t5 - Pesquisar veiculos para locação\n");
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
            alteraVeiculo(veiculoPtr);
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
            //
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
    veiculoPtr = fopen("veiculosCadastrados.dat", "r+b");

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
    veiculoPtr = fopen("veiculosCadastrados.dat", "r+b");

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

        printf("\tInforme o status (ocupado/disponivel): ");
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
    veiculoPtr = fopen("veiculosCadastrados.dat", "r+b");

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
    veiculoPtr = fopen("veiculosCadastrados.dat", "r+b");

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

void alteraVeiculo(FILE *veiculoPtr) // Função que altera os dados do veículo

{
    int codigo, posicao;
    veiculo v;
    printf("\tDigite o codigo do veiculo para alterar: ");
    scanf("%d", &codigo);
    posicao = localizarVeiculos(veiculoPtr, codigo);
    if (posicao != -1) // localizou o veiculo
    {
        fseek(veiculoPtr, sizeof(v) * (posicao), SEEK_SET);
        fread(&v, sizeof(v), 1, veiculoPtr);
        printf("\n\n\t[Dados atuais do veiculo]\n\n");
        printf("\tModelo: %s\tCódigo: %i\n", v.modelo, v.codigoVeiculo);
        printf("\tCor: %s\n\tPlaca: %d\n\tValor da diária: R$ %2.2f", v.cor, v.placa, v.valorDiaria);
        printf("\tOcupantes: %d\tStatus: %s\n", v.capacidadeMaxOcupantes, v.status);

        printf("\n\n\t[Alterar dados]\n\n");
        printf("\tInforme código do veículo: ");
        fflush(stdin);
        scanf("%d", &v.codigoVeiculo);

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

        fseek(veiculoPtr, sizeof(v) * (posicao), SEEK_SET);
        fwrite(&v, sizeof(v), 1, veiculoPtr);
        fflush(veiculoPtr);
    }
}

/*Parte da Locação*/

int menuLocacao(FILE *veiculoPtr, FILE *clientePtr, int qtdDesejada) // opções para escolher determinadas funções da parte de locação
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
            cadastrarLocacao(locacaoPtr, veiculoPtr, clientePtr, qtdDesejada);
            break;

        case 2:
            printf("\n\tVocê escolheu alterar os dados da locação!\n\n");
            alteraLocacao(locacaoPtr);
            break;

        case 3:
            printf("\n\tVocê escolheu listar todas as locações!\n\n");
            listarLocacao(locacaoPtr);
            break;

        case 4:
            printf("\n\tVocê escolheu pesquisar as locações de um cliente!\n\n");
            listaLocacaoDoCliente(veiculoPtr, clientePtr, locacaoPtr);
            system("pause");
            break;
        }

    } while (op != 0);
    fclose(locacaoPtr);
    return 0;
}

void pesquisarOcupantes(FILE *veiculoPtr, FILE *clientePtr, FILE *locacaoPtr, int qtdDesejada) // Verifica se há veículos disponíveis baseado na quantidade de ocupantes desejados
{
    printf("Entrou em pesquisar ocupantes.");
    veiculo v;
    locacao loc;
    veiculoPtr = fopen("veiculosCadastrados.dat", "r+b");
    clientePtr = fopen("clientesCadastrados.dat", "r+b");
    locacaoPtr = fopen("cadastraLocacao.dat", "r+b");

    fseek(veiculoPtr, 0, SEEK_SET);
    fread(&v, sizeof(v), 1, veiculoPtr);

    while (!feof(veiculoPtr))
    {
        if (qtdDesejada == v.capacidadeMaxOcupantes)
        {
            if (strcmp(v.status, "disponivel") == 0)
            {
                printf("\n\n\t[Dados do veículo]\n\n");
                printf("\tModelo: %s\n\tCódigo: %i\n", v.modelo, v.codigoVeiculo);
                printf("\tCor: %s\n\tPlaca: %d\n\tValor da diária: R$%2.2f\n", v.cor, v.placa, v.valorDiaria);
                printf("\tOcupantes: %d\tStatus: %s\n", v.capacidadeMaxOcupantes, v.status);

                fread(&v, sizeof(v), 1, veiculoPtr);
            }
        }

        fread(&v, sizeof(v), 1, veiculoPtr);
    }
    fclose(veiculoPtr);
}

// função a ser fatorada para o cadastro de locação

void cadastrarLocacao(FILE *locacaoPtr, FILE *veiculoPtr, FILE *clientePtr, int qtdDesejada) // cadastra uma locação
{
    locacao loc;
    veiculo v;
    cliente c;

    int posicaoCliente, posicaoLocacao, qtdOcupantes, mostrarVeiculosDisponiveis;

    // lendo os dados do teclado
    printf("Digite o código da locação a ser cadastrada: ");
    fflush(stdin);
    scanf("%d", &loc.codigoLoc);

    posicaoLocacao = localizaLocacao(locacaoPtr, loc.codigoLoc);

    if (posicaoLocacao == -1) // não tinha codigo no arquivo
    {
        printf("\tInforme o código do cliente que deseja realizar a locação: ");
        fflush(stdin);
        scanf("%d", &loc.codigo);
        posicaoCliente = localizarClientes(clientePtr, loc.codigo);

        if (posicaoCliente != -1) // tinha código
        {
            printf("\tInforme a quantidade de ocupantes que o cliente deseja: ");
            fflush(stdin);
            scanf("%d", &qtdDesejada);

            printf("\n\n\tAqui estão os veículos disponíveis para a locação: \n\n");
            pesquisarOcupantes(veiculoPtr, clientePtr, locacaoPtr, qtdDesejada);

            printf("\tInforme o código do veículo que o cliente deseja alugar: ");
            fflush(stdin);
            scanf("%d", &loc.codigoVeiculo);

            printf("\tInforme a data de retirada do veículo: ");
            fflush(stdin);
            scanf("%i", &loc.dataRetirada);

            printf("\tInforme a data prevista de devolução do veículo: ");
            fflush(stdin);
            scanf("%i", &loc.dataDevPrevista);
        }
        else
        {
            printf("\tCliente não encontrado. Você será redirecionado ao cadastro de cliente automaticamente.\n\n");
            cadastrarClientes(clientePtr);
        }

        fseek(locacaoPtr, 0, SEEK_END);           // posicionado o arquivo no final
        fwrite(&loc, sizeof(loc), 1, locacaoPtr); // gravando os dados
        fflush(locacaoPtr);
    }
    else
    {
        printf("\tCódigo %d já existe no arquivo. Inclusão não realizada!\n\n");
    }
}

int localizaLocacao(FILE *locacaoPtr, int codigo) // verifica se o código da locação já foi utilizado anteriormente
{
    int posicao = -1, achou = 0;
    locacao loc;
    fseek(locacaoPtr, 0, SEEK_SET);
    fread(&loc, sizeof(loc), 1, locacaoPtr);
    while (!feof(locacaoPtr) && !achou)
    {
        posicao++;
        if (loc.codigoLoc == codigo)
        {
            achou = 1;
        }
        fread(&loc, sizeof(loc), 1, locacaoPtr);
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

void listaLocacaoDoCliente(FILE *veiculoPtr, FILE *clientePtr, FILE *locacaoPtr) // Lista todas as locações de um determinado cliente
{
    int pesquisarLocacao;
    veiculo v;
    locacao loc;
    cliente c;
    veiculoPtr = fopen("veiculosCadastrados.dat", "r+b");
    clientePtr = fopen("clientesCadastrados.dat", "r+b");
    locacaoPtr = fopen("cadastraLocacao.dat", "r+b");

    printf("\t[Listagem de Locação]\n\n");
    printf("\tDigite o código do cliente para pesquisar suas locações: ");
    scanf("%i", &pesquisarLocacao);

    fseek(locacaoPtr, 0, SEEK_SET);
    fread(&loc, sizeof(loc), 1, locacaoPtr);

    while (!feof(locacaoPtr))
    {
        if (pesquisarLocacao == loc.codigo)
        {
            printf("\n\n\t[Dados da locação]\n\n");
            printf("\tCódigo do veículo: %i\n", loc.codigoVeiculo);
            printf("\tData de retirada: %i\n", loc.dataRetirada);
            printf("\tData de devolução prevista: %i\n", loc.dataDevPrevista);

            fread(&loc, sizeof(loc), 1, locacaoPtr);
        }

        fread(&loc, sizeof(loc), 1, locacaoPtr);
    }
    fclose(locacaoPtr);
}

void listarLocacao(FILE *locacaoPtr) // Lista TODAS as locações no geral
{
    locacao loc;
    locacaoPtr = fopen("cadastraLocacao.dat", "r+b");

    fseek(locacaoPtr, 0, SEEK_SET);
    fread(&loc, sizeof(loc), 1, locacaoPtr);
    while (!feof(locacaoPtr))
    {
        printf("\n\n\t[Dados da locação]\n\n");
        printf("\tCódigo da locação: %i\n", loc.codigoLoc);
        printf("\tCódigo do cliente: %i\n", loc.codigo);
        printf("\tCódigo do veículo: %i\n", loc.codigoVeiculo);
        printf("\tData de retirada: %i\n", loc.dataRetirada);
        printf("\tData de devolução prevista: %i\n", loc.dataDevPrevista);
        fread(&loc, sizeof(loc), 1, locacaoPtr);
    }
}

void alteraLocacao(FILE *locacaoPtr) // Função que altera os dados do veículo

{
    int codigo, posicao;
    locacao loc;
    printf("\tDigite o codigo da locação para alterar: ");
    scanf("%d", &codigo);
    posicao = localizaLocacao(locacaoPtr, codigo);
    if (posicao != -1) // localizou o veiculo
    {
        fseek(locacaoPtr, sizeof(loc) * (posicao), SEEK_SET);
        fread(&loc, sizeof(loc), 1, locacaoPtr);
        printf("\n\n\t[Dados atuais do veiculo]\n\n");
        printf("\tCódigo do veículo: %i\n", loc.codigoVeiculo);
        printf("\tData de retirada: %i\n", loc.dataRetirada);
        printf("\tData de devolução prevista: %i\n", loc.dataDevPrevista);

        printf("\n\n\t[Alterar dados]\n\n");
        printf("Digite o código da locação a ser cadastrada: ");
        fflush(stdin);
        scanf("%d", &loc.codigoLoc);

        printf("\tInforme o código do veículo que o cliente deseja alugar: ");
        fflush(stdin);
        scanf("%d", &loc.codigoVeiculo);

        printf("\tInforme a data de retirada do veículo: ");
        fflush(stdin);
        scanf("%i", &loc.dataRetirada);

        printf("\tInforme a data prevista de devolução do veículo: ");
        fflush(stdin);
        scanf("%i", &loc.dataDevPrevista);

        fseek(locacaoPtr, sizeof(loc) * (posicao), SEEK_SET);
        fwrite(&loc, sizeof(loc), 1, locacaoPtr);
        fflush(locacaoPtr);
    }
}

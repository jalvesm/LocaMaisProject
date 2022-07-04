#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

float seguro = 50;

// prototipo cliente
void imprimirLinha();
int menuClientes();
int localizarClientes(FILE *clientePtr, int codigo);
void cadastrarClientes(FILE *clientePtr);
void listarClientes(FILE *clientePtr);
void pesquisarClientes(FILE *clientePtr);

// prototipo veiculo
int menuVeiculos();
int localizarVeiculos(FILE *veiculoPtr, int codigo);
void cadastrarVeiculos(FILE *veiculoPtr);
void listarVeiculos(FILE *veiculoPtr);
void pesquisarVeiculos(FILE *veiculoPtr);

// prototipo locação
void localizaVeiculoComCapacidadeDeOcupantes(FILE *veiculoPtr, int qtdOcupantes);
float calculo_Valor_Parcial_Da_Locacao(FILE *veliculoPtr, int diaRetira, int diaDevolvePrevisto);
void cadastrarLocacao(FILE *locacaoPtr); // procedimento para cadastrar locação
void listarLocacao(FILE *locacaoPtr); // Exibe todos as locações cadastradas;
void pesquisarLocacao(FILE *locacaoPtr); // Pesquisa locação por codigo

struct TClientes
{
    char nome[50];
    int codigo;
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
    char cor[20];
    int placa;
    float valorDiaria;
    int capacidadeMaxOcupantes;
    char status[20];
};
typedef struct TVeiculo veiculo;

struct TLocacao
{
    int codigoLoc;
    int codigoCliente;
    int codigoVeiculo;
    int dataRetirada;
    int dataDevPrevista;
    int qtdOcupantesDesejados;
    char seguro[5];
    float valorParcialDaLoc;
    float valorAPagarComSeguro, valorAPagarSemSeguro;
    int dataDevReal;
    float multa;
    int diasDeAtraso;
    float totalAPagar;
};
typedef struct TLocacao locacao;

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
        printf("\t\t1. Cadastro de cliente\n");
        printf("\t\t2. Cadastro de veículo\n");
        printf("\t\t3. Cadastro de locação\n\n");

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
            // cadastrarLocacao(/*???????????*/);
            break;
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
        printf("\tArquivo não existia... Criando arquivo...\n");

        if ((clientePtr = fopen("clientesCadastrados.dat", "w+b")) == NULL)
        {
            printf("Erro na criação do arquivo!");
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
    printf("\n\tCódigo do cliente: ");
    fflush(stdin);
    scanf("%i", &c.codigo);
    posicao = localizarClientes(clientePtr, c.codigo);
    if (posicao == -1)
    {
        printf("\tNome do cliente: ");
        fflush(stdin);
        scanf("%s", c.nome);
        fflush(stdin);
        printf("\tTelefone: ");
        fflush(stdin);
        scanf("%i", &c.telefone);
        fflush(stdin);
        printf("\tRua: ");
        fflush(stdin);
        scanf("%s", &c.rua);
        fflush(stdin);
        printf("\tBairro: ");
        fflush(stdin);
        scanf("%s", &c.bairro);
        printf("\tNúmero: ");
        fflush(stdin);
        scanf("%i", &c.numero);
        printf("\tComplemento: ");
        fflush(stdin);
        scanf("%s", &c.complemento);
        fseek(clientePtr, 0, SEEK_END);
        fwrite(&c, sizeof(c), 1, clientePtr);
        fflush(clientePtr);
    }
    else
    {
        printf("\n\n\tO código %i já foi usado anteriomente. Cadastro não realizado.\n\tTente novamente!\n\n", c.codigo);
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
        printf("\tTelefone: %d\n", c.telefone);
        printf("\tRua: %s\n\tBairro: %s\n\tNúmero: %i\n\tComplemento: %s\n", c.rua, c.bairro, c.numero, c.complemento);
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
            printf("\tTelefone: %i\n", c.telefone);
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
            printf("Erro na criação do arquivo!");
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
            // alteraVeiculo(veiculoPtr);
            break;

        case 3:
            printf("\n\tVocê escolheu listar todos os veículos!\n\n");
            listarVeiculos(veiculoPtr);
            break;

        case 4:
            printf("\n\tVocê escolheu pesquisar os veículos!\n\n");
            pesquisarVeiculos(veiculoPtr);
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
        scanf("%s", &v.modelo);

        printf("\tInforme a cor: ");
        fflush(stdin);
        scanf("%s", &v.cor);

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
        scanf("%s", &v.status);

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

    if ((locacaoPtr = fopen("locacoesCadastradas.dat", "r+b")) == NULL)
    {
        printf("\tArquivo não existia... Criando arquivo...\n");

        if ((locacaoPtr = fopen("locacoesCadastradas.dat", "w+b")) == NULL)
        {
            printf("Erro na criação do arquivo!");
            exit(1);
        }
    }

    do
    {
        printf("\n\tBem vindo ao cadastro de locações!\n\n");
        printf("\t1 - Cadastrar locação\n");
        printf("\t2 - Listar locações\n");
        printf("\t3 - Pesquisar locações\n");
        printf("\t0 - Voltar ao menu principal\n");
        printf("\tEscolha: ");
        scanf("%i", &op);
        switch (op)
        {
        case 1:
            printf("\n\tVocê escolheu cadastrar uma locação!\n\n");
            cadastrarLocacao(clientePtr, veiculoPtr, locacaoPtr);
            break;

        case 2:
            printf("\n\tVocê escolheu listar todas as locacoes!\n\n");
            listarLocacao(locacaoPtr);
            break;

        case 3:
            printf("\n\tVocê escolheu pesquisar os veículos!\n\n");
            pesquisarLocacao(locacaoPtr);
            system("pause");
            break;
        }
    }
    while (op != 0);
    fclose(locacaoPtr);
    return 0;
}

int localizarLocacao(FILE *locacaoPtr, int codigo) // função para verificar se o codigo do veiculo ja foi cadastrado antes
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

void cadastrarLocacao( FILE *clientePtr, FILE *veiculoPtr, FILE *locacaoPtr )
{
    FILE *clientePtr;
    FILE *veiculoPtr;
    FILE *locacaoPtr;

    cliente c;
    locacao loc;
    veiculo v;

    int posicao1, posicao2, qtdOcupantes;

    printf("\tDigite o código do cliente: ");
    fflush(stdin);
    scanf("%d", &c.codigoCliente);

    posicao1 = localizarClientes(clientePtr, codigo);

    if (posicao == -1)
    {
        printf("Cliente não encontrado. Você será redirecionado ao cadastro de cliente.\n");
        cadastrarClientes(clientePtr);
    }
    else
    {
        printf("\tInforme a quantidade de ocupantes: ");
        fflush(stdin);
        scanf("%d", &loc.qtdOcupantesDesejados);

        posicao2 = localizarVeiculos(veiculoPtr, qtdOcupantes)

        printf("\tInforme a data prevista para devolução do veículo: ");
        fflush(stdin);
        scanf("%s", &loc.dataDevPrevista);

        printf("\tInforme a quantidade de ocupantes desejados pelo cliente: ");
        fflush(stdin);
        scanf("%d", &loc.qtdOcupantesDesejados);

        printf("\tCliente deseja seguro? sim/nao");			// rever função
        fflush(stdin);
        scanf("%s", &loc.seguro);

        fseek(locacaoPtr, 0, SEEK_END);

        fwrite(&loc, sizeof(loc), 1, locacaoPtr);
        fflush(locacaoPtr);
    }

    imprima = calculo_Valor_Parcial_Da_Locacao(veliculoPtr, loc., loc.dataRetirada, loc.dataDevPrevista)
    printf("O valor a ser pago pelo cliente é: R$%.2f", imprima);
}

void listarLocacao(FILE *locacaoPtr) // Exibe todos as locações cadastradas
{
    locacao loc;
    fseek(locacaoPtr, 0, SEEK_SET);
    fread(&loc, sizeof(loc), 1, locacaoPtr);
    while (!feof(locacaoPtr))
    {
        printf("\n\n\t[Dados da locação]\n\n");
        printf("\tCódigo: %d\n", loc.codigoLoc);
        printf("Data da retirada: %d", loc.dataRetirada);
		printf("Data prevista para devolução: %d", loc.dataDevPrevista);
        printf("\tOcupantes desejados para ocupar o veículo: %d \tSeguro: %s\n", loc.qtdOcupantesDesejados, loc.seguro);
        fread(&loc, sizeof(loc), 1, locacaoPtr);
    }
}

void pesquisarLocacao(FILE *locacaoPtr) // Pesquisa locação por codigo
{
    locacao loc;
    int codigoPesquisado;
    fseek(locacaoPtr, 0, SEEK_SET);
    fread(&loc, sizeof(loc), 1, locacaoPtr);
    printf("\n\t[Pesquisar Locação]\n");
    printf("\n\tDigite o código da locação a ser pesquisada: ");
    scanf("%d", &codigoPesquisado);
    while (!feof(locacaoPtr))
    {
        if (codigoPesquisado == loc.codigoLoc)
        {
            printf("\n\n\t[Dados da locação]\n\n");
        	printf("\tCódigo: %d\n", loc.codigoLoc);
	        printf("Data da retirada: %d", loc.dataRetirada);
			printf("Data prevista para devolução: %d", loc.dataDevPrevista);
    	    printf("\tOcupantes desejados para ocupar o veículo: %d \tSeguro: %s\n", loc.qtdOcupantesDesejados, loc.seguro);
        }

        fread(&loc, sizeof(loc), 1, locacaoPtr);
    }
    system("pause");
}

void alterStatusVeiculo(FILE *veiculoPtr)
{ 
	int codigo,posicao, condicao;
	veiculo v;
	printf("Diga qual o codigo do veículo para alterar a condição:");
	scanf("%d",&codigo);
	posicao = localizarVeiculos(veiculoPtr, codigo);
	if (posicao != -1) // localizou a mercadoria
	{ 
		fseek(veiculoPtr, sizeof(v)*(posicao), SEEK_SET);
        fread(&v, sizeof(v),1, veiculoPtr);
        printf("Codigo atual:%d \tStatus: %s\n",v.codigoVeiculo, v.status);
        printf("Nova condição: o veículo está disponível ou ocupado? ");
        fflush(stdin);
        scanf("%s", &v.status);
        fseek(veiculoPtr,sizeof(v)*(posicao ),SEEK_SET);
        fwrite(&v, sizeof(v),1, veiculoPtr);
        fflush(veiculoPtr);
}
}

void registrarBaixaLocacao(FILE *locacaoPtr /* em busca de parâmetros! */)
{
    cliente c;
    locacao loc;
    int diasDeAtraso;
    float multa;

    printf("Informe o código da locação para dar baixa: ");
    scanf("%d", loc.codigoLoc);

    // função para buscar locação
    // locação encontrada com sucesso! Nesta função, mostrar se o cliente solicitou seguro!, se sim, lembrar de cobrar R$50 a mais no final

    printf("Informe a data de devolução do veículo: ");
    scanf("%d", &bL.dataDevReal);

    bL.diasDeAtraso = (bL.dataDevReal - loc.dataDevPrevista);

    if (bL.diasDeAtraso != 0) // se o cliente atrasou a entrega do veículo...
    {
        //printf("O valor a pagar com multa é de R$%.2f", );
    }
    else
    {
        printf("Total a receber do cliente: R$%.2f", bL.totalAPagar);
    }
}

void localizaVeiculoComCapacidadeDeOcupantes(FILE *veiculoPtr, int qtdOcupantes)
{
    veiculo v;
    int posicao = -1, achou = 0;

    fseek(veiculoPtr, 0, SEEK_SET);
    fread(&v, sizeof(v), 1, veiculoPtr);

    while (!feof(veiculoPtr) && !achou)
    {
        posicao++;
        if (v.capacidadeMaxOcupantes == qtdOcupantes)
        {
            achou = 1;
            printf("Código do veículo: %d", v.codigoVeiculo);
            printf("Modelo do veículo: %s", v.modelo);
            printf("Quantidade de ocupantes: %d", v.capacidadeMaxOcupantes);
            fread(&v, sizeof(v), 1, veiculoPtr);
        }
        else
        {
            printf("não existem veículos disponíveis para a quantidade desejada!");
        }
    }
}


float calculo_Valor_Parcial_Da_Locacao(FILE *veliculoPtr, int diaRetira, int diaDevolvePrevisto)
{
    veiculo v;

    int posicao=-1,achou=0;
    float valor;

    fseek(veliculoPtr, 0, SEEK_SET);
    fread(&v, sizeof(v),1, veliculoPtr);
    while (!feof(veliculoPtr) && !achou)
    { posicao++;
    if (v.valorDiaria == valor)
    { 
        achou = 1;
    }
    fread(&v, sizeof(v),1, veliculoPtr);
    }
    if (achou)
    { 
        int qtd_de_dias_com_o_veiculo = diaRetira - diaDevolvePrevisto;
        float valor_parcial_da_locacao = v.valorDiaria * qtd_de_dias_com_o_veiculo;
    
        return valor_parcial_da_locacao;
    }
    else
    { 
        return -1;
    }
}

float calculaMulta(int diaRetira, int diaDevolveReal, float valor_parcial_da_locacao)
{
    int dias_de_atraso;
    float taxa = 30;   // 30 reais
    float multa = taxa * dias_de_atraso;        // R$ 30 reais por dia de atraso
    float valor_com_multa;
    
    valor_com_multa = valor_parcial_da_locacao * 1,05 + multa;
    return valor_com_multa;
}

float calculaSeguroComMulta( float valor_com_multa )
{
    float valor_Total = valor_com_multa + 50;
    return valor_Total;
}

float calculaSeguroSemMulta( float valor_parcial_da_locacao)
{
    float valor_Total = valor_parcial_da_locacao + 50;
    return valor_Total;
}

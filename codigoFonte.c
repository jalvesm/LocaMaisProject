#include <stdio.h>
#include <stdlib.h>
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
    char status[5];
};
typedef struct TVeiculo veiculo;

struct TLocacao
{
    int placa;
    int ocupantes;
};
typedef struct TLocacao locacao;


int menuClientes();
void cadastraClientes(FILE *fclientes);
int localizaCliente(FILE *fclientes, int codigo);
void listaClientes(FILE *fclientes);

void imprimirLinha();
void sairDoPrograma();
void cadastrarVeiculo(FILE *f);

int main()
{
    FILE *f;
    int op;

    imprimirLinha();
    printf("\t\t    MENU PRINCIPAL");
    imprimirLinha();

    printf("\n\n\tFavor escolher uma das opções abaixo:\n\n");
    printf("\t\t0. Sair do programa!\n");
    printf("\t\t1. Cadastro de cliente\n");
    printf("\t\t2. Cadastro de veículo\n");
    printf("\t\t3. Cadastro de locação\n");
    printf("\t\t4. Pesquisar cliente\n");
    printf("\t\t5. Pesquisar veículo\n");
    printf("\t\t6. Visualizar locação por cliente\n\n");
    
    printf("\nSua escolha: ");
    scanf("%d", &op);

    switch (op)
    {
    case 0:
        printf(">> 0. Sair do programa!\n\n");
        imprimirLinha();
        sairDoPrograma();
        break;

    case 1:
        printf(">> 1. Cadastro de cliente\n\n", op);
        imprimirLinha();
        menuClientes();
        break;

    case 2:
        printf(">> 2. Cadastro de veículo\n");
        imprimirLinha();
        cadastrarVeiculo(f);
        break;

    case 3:
        printf(">> 3. Cadastro de locação\n\n");
        imprimirLinha();
        // função Jô
        break;
            
    case 4:
        printf(">> 5. Pesquisar cliente\n\n");
        imprimirLinha();
        // função dudis;
        break;
    
    case 5:
        printf(">> 6. Pesquisar veículo\n\n");
        imprimirLinha();
        break;

    case 6:
        printf(">> 7. Visualizar locação por cliente\n\n");
        imprimirLinha();
        // função;
        break;
    }
    
    return 0;
}

void imprimirLinha()
{
    printf("\n+---------------------------------------------------+\n");
}

void sairDoPrograma()
{
    printf("\t\t    SAIR DO PROGRAMA");
    imprimirLinha();
}

void cadastrarVeiculo(FILE *f)
{ 
    struct veiculo *veiculoPtr;
	veiculo v;
	int posicao;

	//lendo os dados do teclado
	printf("Digite o código do veículo: ");
	fflush(stdin);
	scanf("%d",&v.codigoVeiculo);
	
	posicao = localizaVeiculo(f, v.codigoVeiculo);
	
	if (posicao == -1)                                      //não tinha codigo no arquivo
	{ 
		printf("Informe o modelo: ");
		fflush(stdin);
		scanf("%s", &v.modelo);
	
		printf("Informe a cor: ");
		fflush(stdin);
		scanf("%s", &v.cor);

		printf("Informe a placa: ");
        fflush(stdin);
		scanf("%d",&v.placa);

        printf("Informe o valor da diária: R$");
        fflush(stdin);
		scanf("%d",&v.valorDiaria);

        printf("Informe a quantidade máxima de ocupantes: ");
        fflush(stdin);
		scanf("%d",&v.qtdMaxOcupantes);

        printf("Informe o status (ocupado/disponível): ");
		fflush(stdin);
		scanf("%s", &v.status);

		fseek(f,0,SEEK_END); // posicionado o arquivo no final
	
		fwrite(&v, sizeof(v),1,f); //gravando os dados
		fflush(f);
	}
	else
	{ 
		printf("Código %d já existe no arquivo. Inclusão não realizada!\n");	
	}
}

int menuClientes()
{
    FILE *fclientes;
    int op;
    if ((fclientes = fopen("clientesCadastrados.dat", "r+b")) == NULL)
    {
        printf("\tArquivo não existia... Criando arquivo...\n");

        if ((fclientes = fopen("clientesCadastrados.dat", "w+b")) == NULL)
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
        printf("\t0 - Sair do programa\n");
        printf("\tEscolha: ");
        scanf("%i", &op);
        switch (op)
        {
        case 1:
            printf("\n\tVocê escolheu cadastrar um cliente!\n\n");
            cadastraClientes(fclientes);
            break;

        case 2:
            printf("\n\tVocê escolheu alterar os dados do cliente!\n\n");
            //alteraCliente(fclientes);
            break;

        case 3:
            printf("\n\tVocê escolheu listar todos os clientes!\n\n");
            listaClientes(fclientes);
            system("pause");
            break;
        }
    }

    while (op != 0);
    fclose(fclientes);
    return 0;
}

int localizaCliente(FILE *fclientes, int codigo)
{
    int posicao = -1, achou = 0;
    cliente c;
    fseek(fclientes, 0, SEEK_SET);
    fread(&c, sizeof(c), 1, fclientes);
    while (!feof(fclientes) && !achou)
    {
        posicao++;

        if (c.codigo == codigo)
        {
            achou = 1;
        }
        fread(&c, sizeof(c), 1, fclientes);
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

void cadastraClientes(FILE *fclientes)
{
    cliente c; 
    int posicao;
    printf("\n\tCódigo do cliente: ");
    fflush(stdin);
    scanf("%i", &c.codigo);
    posicao = localizaCliente(fclientes, c.codigo);
    if(posicao == -1)
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
        printf("\tNúmero: ");
        fflush(stdin);
        scanf("%i", &c.numero);
        printf("\tComplemento: ");
        fflush(stdin);
        gets(c.complemento);
        fseek(fclientes, 0, SEEK_END);
        fwrite(&c, sizeof(c), 1, fclientes);
        fflush(fclientes);
    }
    else
    {
        printf("\n\n\tO código %i já foi usado anteriomente. Cadastro não realizado.\n\tTente novamente!\n\n", c.codigo);
    }
}

void listaClientes(FILE *fclientes)
{
    cliente c;
    fseek(fclientes, 0, SEEK_SET);
    fread(&c, sizeof(c), 1, fclientes);
    while(!feof(fclientes))
    {
        printf("\n\n\t[Dados do cliente]\n");
        printf("\tNome: %s\n", c.nome);
        printf("\tCódigo (CPF): %i\n", c.codigo);
        printf("\tTelefone: (%i)%i\n", c.ddd, c.telefone);
        printf("\tRua: %s\n\tBairro: %s\n\tNúmero: %i\n\tComplemento: %s\n", c.rua, c.bairro, c.numero, c.complemento);
        fread(&c, sizeof(c), 1, fclientes);
    }
}

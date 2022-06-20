#include <stdio.h>
#include <stdlib.h>
#include <locale.h>


int main()
{
    setlocale (LC_ALL, "portuguese");

    int exibeTelaBoasVindas(void); // esse void deve ser o parâmetro que a função recebe!

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
        fputs("Error at opening File!", stderr); // stderr é o quê carai???????????????
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
    int inputMenuPrincipal;

    printf("\n\n");
    printf("+---------------------------------------------------+\n");
    printf("\t\t    MENU PRINCIPAL");
    printf("\n");
    printf("+---------------------------------------------------+\n");
    printf("|\n");
    printf("| Favor escolher uma das opções abaixo:");
    printf("\n|\n");
    printf("| 0. Sair do programa! _____________________________+\n");
    printf("| 1. Cadastro de cliente ___________________________+\n");
    printf("| 2. Cadastro de veículo ___________________________+\n");
    printf("| 3. Cadastro de locação ___________________________+\n");
    printf("| 4. Baixa na locação ______________________________+\n"); // [DÚVIDA SOBRE FUNÇÃO]
    printf("| 5. Pesquisar cliente _____________________________+\n");
    printf("| 6. Pesquisar veículo _____________________________+\n");
    printf("| 7. Visualizar locação por cliente ________________+\n");
    printf("|\n");
    printf("+---------------------------------------------------+\n");
    printf("|\n| Sua escolha: ");
    scanf("%d", &inputMenuPrincipal);

    switch (inputMenuPrincipal)
    {
    case 0:
        printf("|\n|\nVocê escolheu:\n| 0. Sair do programa!\n");
        void saiDoPrograma();
        break;
    
    case 1:
        printf("|\n|\nVocê escolheu:\n| 1. Cadastro de veículo\n");
        int cadastraCliente(/*precisa de parâmetros?*/);

    case 2:
        printf("|\n|\nVocê escolheu:\n| 2. Cadastro de locação\n");
        int cadastraCliente(/*precisa de parâmetros?*/);
    
    case 3:
        printf("|\n|\nVocê escolheu:\n| 3. Cadastro de locação\n");
        int cadastraCliente(/*precisa de parâmetros?*/);
    
    case 4:
        printf("|\n|\nVocê escolheu:\n| 4. Baixa na locação\n");
        int cadastraCliente(/*precisa de parâmetros?*/);
    
    case 5:
        printf("|\n|\nVocê escolheu:\n| 5. Pesquisar cliente\n");
        int cadastraCliente(/*precisa de parâmetros?*/);
    
    case 6:
        printf("|\n|\nVocê escolheu:\n| 6. Pesquisar veículo\n");
        int cadastraCliente(/*precisa de parâmetros?*/);

    case 7:
        printf("|\n|\nVocê escolheu:\n| 7. Visualizar locação por cliente\n");
        int cadastraCliente(/*precisa de parâmetros?*/);

    default:
        break;
    }
    
    return 0;
}

void saiDoPrograma()
{
    printf("\n\nFIM DO PROGRAMA!");
}
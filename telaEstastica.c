/* Autor....:Felipe souza de Jesus 
   Data.....:26/03/2025
   Objetivo.: Tela de cadastro de funcionarios
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#define valor 50
#define Max 12

void gotoxy(int x, int y)

{
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void tela()
{
    int i;
    system("cls");
    printf("-------------------------------------------------------------------------------\n");
    for (i = 0; i < 22; i++)
    {
        printf("|                                                                             |\n");
    }
    printf("-------------------------------------------------------------------------------\n");
    gotoxy(28, 02);
    printf("CADASTRO DE FUNCIONARIO");
    gotoxy(01, 01);
    printf("Autor..... Felipe Souza");
    gotoxy(01, 02);
    printf("Curso..... 2 ADS");
    gotoxy(01, 03);
    printf("Ano....... 2025");
    gotoxy(00, 04);
    printf("-------------------------------------------------------------------------------\n");
    gotoxy(00, 20);
    printf("-------------------------------------------------------------------------------\n");
}

void limpar()
{
    int i;
    for (i = 0; i < 15; i++)
    {
        gotoxy(1, 05 + i);
        printf("                                                                             ");
    }
    gotoxy(01, 21);
    printf("                                                                             ");
    gotoxy(01, 22);
    printf("                                                                             ");
}

void telaFuncionario()
{
    gotoxy(23, 6);
    printf("  CADASTRO FUNCIONARIO");
    gotoxy(25, 8);
    printf("Insira o nome.....:");
    gotoxy(25, 9);
    printf("Insira o endereco.:");
    gotoxy(25, 10);
    printf("Insira o codigo...:");
    gotoxy(25, 11);
    printf("Insira o salario..:");
}

int menuOpcao()
{
    int resp;
    system("cls");
    tela();
    gotoxy(31, 06);
    printf("MENU OPCOES");
    gotoxy(25, 8);
    printf("1-Cadastrar Funcionario");
    gotoxy(25, 9);
    printf("2-Consultar Funcionario");
    gotoxy(25, 10);
    printf("3-Editar Funcionario");
    gotoxy(25, 11);
    printf("4-Excluir usuario");
    gotoxy(25, 12);
    printf("5-Sair\n");
    gotoxy(01, 21);
    printf("Escolha uma opcao....");
    gotoxy(25, 21);
    scanf("%d", &resp);

    return resp;
}

typedef struct
{
    char nome[valor];
    char endereco[valor];
    int codigo;
    float salario;
} reg_funcionario;

typedef struct
{
    reg_funcionario func[Max];
    int inicio;
    int final;
} Lista;

// Inicializar lista
void inicializaLista(Lista *L)
{
    L->inicio = 0;
    L->final = 0;
    for (int i = 0; i < Max; i++)
    {
        L->func[i].nome[0] = '\0';
        L->func[i].endereco[0] = '\0';
        L->func[i].salario = 0;
        L->func[i].codigo = 0;
    }
}

void salvarUsuario(Lista *L)
{
    FILE *file = fopen("funcionarios.txt", "w");
    if (file == NULL)
    {
        gotoxy(20, 19);
        printf("Erro ao abrir o arquivo para escrita");
        return;
    }

    for (int i = 0; i < L->final; i++)
    {
        fprintf(file, "%d\n%s\n%s\n%.2f\n",
                L->func[i].codigo,
                L->func[i].nome,
                L->func[i].endereco,
                L->func[i].salario);
    }

    fclose(file);
}

void carregarFuncionario(Lista *L)
{
    FILE *file = fopen("funcionarios.txt", "r");
    if (file == NULL)
    {
        gotoxy(20, 19);
        printf("Nenhum dado encontrado");
        return;
    }

    while (fscanf(file, "%d\n%49[^\n]\n%49[^\n]\n%f\n",
                &L->func[L->final].codigo,
                L->func[L->final].nome,
                L->func[L->final].endereco,
                &L->func[L->final].salario) == 4)
    {
        L->final++;
        if (L->final >= Max)
        {
            break;
        }
    }
    fclose(file);
}

int validarCodigo(Lista *L, int codigo)
{
    for (int i = 0; i < L->final; i++)
    {
        if (L->func[i].codigo == codigo)
        {
            return -1;
        }
    }
    return 1;
}

void cadastrarFuncionario(Lista *L)
{
    reg_funcionario funcionario;
    int reiniciar, confirma, validar;

    do
    {
        limpar();
        telaFuncionario();
        if (L->final >= Max)
        {
            gotoxy(25, 12);
            printf("LISTA CHEIA");
            break;
        }

        gotoxy(20, 19);
        printf("Digite sair para nao cadastrar");
        // Nome
        gotoxy(45, 8);
        fflush(stdin);
        fgets(funcionario.nome, valor, stdin);

        if (strcmp(funcionario.nome, "sair\n") == 0)
        {
            return;
        }

        // endereco
        gotoxy(45, 9);
        fflush(stdin);
        fgets(funcionario.endereco, valor, stdin);

        if (strcmp(funcionario.endereco, "sair\n") == 0)
        {
            return;
        }
        
            do
        {
            // codigo
            do
            {
                gotoxy(45, 10);
                printf("                    ");
                gotoxy(45, 10);
                scanf("%d", &funcionario.codigo);
                if (funcionario.codigo <= 0)
                {
                    gotoxy(20, 19);
                    printf("                                         ");
                    gotoxy(20, 18);
                    printf("Impossivel cadastrar codigo menor que 0");
                    gotoxy(23, 19);
                    printf("Precione uma tecla para continuar");

                    getch();
                    gotoxy(18, 18);
                    printf("                                                          ");
                    gotoxy(18, 19);
                    printf("                                                          ");
                }
            } while (funcionario.codigo <= 0);

            validar = validarCodigo(L, funcionario.codigo);

            if (validar != 1)
            {
                gotoxy(25, 19);
                printf("Erro: Codigo ja cadastrado\n");
            }
        }
        while (validar != 1)
            ;

        do
        {
            // salario
            gotoxy(45, 11);
            scanf("%f", &funcionario.salario);
            if (funcionario.salario < 0)
            {
                gotoxy(45, 11);
                printf("                               ");
                gotoxy(25, 19);
                printf("Salario invalido \n");
            }
        } while (funcionario.salario < 0);

        gotoxy(01, 21);
        printf("Confirmar cadastro (1-Sim 2-Nao)........... ");
        gotoxy(48, 21);
        scanf("%d", &confirma);

        if (confirma == 1)
        {
            L->func[L->final] = funcionario;
            L->final++;
            salvarUsuario(L);
        }

        gotoxy(01, 21);
        printf("Cadastrar outro funcionario (1-Sim 2-Nao).... ");
        gotoxy(48, 21);
        scanf("%d", &reiniciar);
    } while (reiniciar == 1);
}

void mostrarLista(Lista *L)
{
    limpar();
    gotoxy(25, 05);
    printf("LISTA DE FUNCIONARIOS");
    gotoxy(01, 07);
    printf("Num)Nome                      |Salario       |Codigo      ");
    for (int i = 0; i < L->final; i++)
    {
        gotoxy(02, 8 + i);
        printf("%2d)%-20s\t%5.2f\t\t%5d", i + 1, L->func[i].nome, L->func[i].salario, L->func[i].codigo);
    }
}

void mostrarUsuario(Lista *L, int resp)
{
    limpar();
    gotoxy(30, 06);
    printf("USUARIO CONSULTADO");
    gotoxy(27, 10);
    printf("Nome.....:%s", L->func[resp - 1].nome);
    gotoxy(27, 12);
    printf("Endereco.:%s", L->func[resp - 1].endereco);
    gotoxy(27, 14);
    printf("Salario..:%.2f", L->func[resp - 1].salario);
    gotoxy(27, 16);
    printf("Codigo...:%d", L->func[resp - 1].codigo);
}

void ordenar_Codigo(Lista *L)
{
    reg_funcionario temp;
    int i, j;

    for (i = 0; i < L->final - 1; i++)
    {
        for (j = 0; j < L->final - 1 - i; j++)
        {
            if (L->func[j].codigo > L->func[j + 1].codigo)
            {
                temp.codigo = L->func[j].codigo;
                L->func[j].codigo = L->func[j + 1].codigo;
                L->func[j + 1].codigo = temp.codigo;
            }
        }
    }
}

void ordenar_Nome(Lista *L)
{
    int i;
    int j;
    reg_funcionario temp;

    limpar();
    for (i = 0; i < L->final - 1; i++)
    {
        for (j = 0; j < L->final - 1 - i; j++)
        {
            if (strcmp(L->func[j].nome, L->func[j + 1].nome) > 0)
            {
                strcpy(temp.nome, L->func[j].nome);
                strcpy(L->func[j].nome, L->func[j + 1].nome);
                strcpy(L->func[j + 1].nome, temp.nome);
            }
        }
    }
}

void ordenar_Salario(Lista *L)
{
    int i;
    int j;
    reg_funcionario temp;

    for (i = 0; i < L->final - 1; i++)
    {
        for (j = 0; j < L->final - 1 - i; j++)
        {
            if (L->func[j].salario < L->func[j + 1].salario)
            {
                temp.salario = L->func[j].salario;
                L->func[j].salario = L->func[j + 1].salario;
                L->func[j + 1].salario = temp.salario;
            }
        }
    }
}

void opcaoOrdenacao(Lista *L)
{
    int consulta;
    gotoxy(27, 06);
    printf("TIPOS DE ORDENACAO");
    gotoxy(22, 10);
    printf("1) Ordem Alfabetica");
    gotoxy(22, 12);
    printf("2) Ordem codigo");
    gotoxy(22, 14);
    printf("3) Ordem Salario");

    gotoxy(01, 21);
    printf("Qual maneira voce quer ordenar...... ");
    gotoxy(38, 21);
    scanf("%d", &consulta);

    switch (consulta)
    {
    case 1:
        ordenar_Nome(L);
        break;
    case 2:
        ordenar_Codigo(L);
        break;
    case 3:
        ordenar_Salario(L);
        break;
    }
}

void editarCadastro(Lista *L)

{
    int num, resp, control;
    reg_funcionario temp;

    limpar();
    if (L->inicio == L->final)
    {
        gotoxy(22, 12);
        printf("NAO HA FUNCIONARIOS CADASTRADOS");
        return;
    }
    opcaoOrdenacao(L);
    mostrarLista(L);

    gotoxy(01, 21);
    printf("Deseja editar algum usuario? (1-Sim 2-Nao).....");
    gotoxy(49, 21);
    scanf("%d", &num);

    if (num == 1)
    {
        do
        {
            gotoxy(01, 21);
            printf("Qual usuario voce deseja editar..... ");
            gotoxy(38, 21);
            scanf("%d", &resp);
            if (resp > L->final || resp < L->inicio)
            {
                gotoxy(20, 19);
                printf("Consulte um usuario valido ou 0 para sair");
            }
            else if (resp == 0)
            {
                return;
            }
        } while (resp > L->final || resp < L->inicio);

        mostrarUsuario(L, resp);
        gotoxy(01, 21);
        printf("Qual campo deseja editar?..... ");
        gotoxy(32, 21);
        scanf("%d", &control);
        switch (control)
        {
        case 1:
            limpar();
            gotoxy(25, 12);
            printf("Nome atual.....:%s", L->func[resp - 1].nome);
            gotoxy(25, 14);
            printf("Novo nome......:");
            gotoxy(42, 14);
            fflush(stdin);
            fgets(temp.nome, 50, stdin);

            strcpy(L->func[resp - 1].nome, temp.nome);
            salvarUsuario(L);
            break;
        case 2:
            limpar();
            gotoxy(25, 12);
            printf("Endereco atual.....:%s", L->func[resp - 1].endereco);
            gotoxy(25, 14);
            printf("Novo endereco......:");
            gotoxy(46, 14);
            fflush(stdin);
            fgets(temp.endereco, 50, stdin);

            strcpy(L->func[resp - 1].endereco, temp.endereco);
            salvarUsuario(L);
            break;

        case 3:
            limpar();
            gotoxy(25, 12);
            printf("Salario atual.....:%.2f", L->func[resp - 1].salario);
            gotoxy(25, 14);
            do
            {
                printf("Novo salario......:");
                gotoxy(45, 14);
                scanf("%f", &temp.salario);
                if (temp.salario < 0)
                {
                    gotoxy(25, 19);
                    printf("Insira um salario valido");
                }
                else
                {
                    gotoxy(25, 19);
                    printf("Cadastrado com sucesso");
                    L->func[resp - 1].salario = temp.salario;
                }
            } while (temp.salario < 0);
            salvarUsuario(L);
            break;

        case 4:
            limpar();
            gotoxy(20, 19);
            printf("Insira um codigo valido ou 0 para sair");
            gotoxy(25, 12);
            printf("Codigo atual.....:%d", L->func[resp - 1].codigo);

            do
            {
                gotoxy(25, 14);
                printf("Novo codigo......:");
                gotoxy(44, 14);
                scanf("%d", &temp.codigo);

                if (validarCodigo(L, temp.codigo) == -1)
                {

                    gotoxy(20, 19);
                    printf("                                           ");
                    gotoxy(20, 19);
                    printf("Codigo negado! Insira um codigo valido");
                }
                else if (temp.codigo == 0)
                {
                    return;
                }

            } while (validarCodigo(L, temp.codigo) == -1);

            gotoxy(18, 19);
            printf("                                               ");
            gotoxy(23, 19);
            printf("Cadastrado com sucesso");
            L->func[resp - 1].codigo = temp.codigo;

            salvarUsuario(L);
            break;
        }
    }
}

void excluirCadastro(Lista *L)
{
    limpar();
    int resp, temp, num;
    if (L->inicio == L->final)
    {
        gotoxy(22, 12);
        printf("NAO HA FUNCIONARIOS CADASTRADOS");
        return;
    }
    opcaoOrdenacao(L);
    mostrarLista(L);

    gotoxy(01, 21);
    printf("Deseja excluir algum usuario? (1-Sim 2-Nao).....");
    gotoxy(50, 21);
    scanf("%d", &resp);

    if (resp == 1)
    {
        do
        {
            gotoxy(01, 21);
            printf("Qual usuario voce deseja excluir?.... ");
            gotoxy(38, 21);
            scanf("%d", &temp);
            if (temp < L->inicio || temp > L->final)
            {
                gotoxy(20, 19);
                printf("Digite um usuario valido");
            }
        } while (temp < L->inicio || temp > L->final);
        mostrarUsuario(L, temp);

        gotoxy(01, 21);
        printf("Confirmar exclusao? Essa acao nao pode ser revertida (1-Sim 2-Nao).... ");
        gotoxy(72, 21);
        scanf("%d", &num);
        gotoxy(01, 21);
        printf("                                                                            ");
        if (num == 1)
        {
            gotoxy(23, 19);
            printf("Excluido com sucesso");
            for (int i = temp - 1; i < L->final - 1; i++)
            {
                L->func[i] = L->func[i + 1];
            }
            L->final--;
            salvarUsuario(L);
        }
    }
}

void consultarCadastro(Lista *L)
{
    int resp;

    limpar();
    if (L->final == L->inicio)
    {
        gotoxy(20, 12);
        printf("NAO HA FUNCIONARIOS CADASTRADOS");
    }

    opcaoOrdenacao(L);
    mostrarLista(L);

    gotoxy(01, 21);
    printf("Deseja consultar algum funcionario (1-Sim 2-Nao)....              ");
    gotoxy(53, 21);
    scanf("%d", &resp);

    if (resp != 1)
    {
        return;
    }
    do
    {
        gotoxy(25, 19);
        printf("Digite -1 para sair");
        gotoxy(01, 21);
        printf("Qual o usuario voce deseja consultar?..... ");
        gotoxy(44, 21);
        scanf("%d", &resp);

        if (resp == 0 || resp >= L->final)
        {
            gotoxy(25, 19);
            printf("Digite um usuario valido");
        }
        else if (resp == -1)
        {
            return;
        }

    } while (resp <= L->inicio || resp >= L->final);
    mostrarUsuario(L, resp);
}

int main()
{
    system("color 0a");
    Lista L;
    inicializaLista(&L);
    carregarFuncionario(&L);
    int menu, reiniciar;

    do
    {
        menu = menuOpcao();

        switch (menu)
        {
        case 1:
            cadastrarFuncionario(&L);
            break;
        case 2:
            consultarCadastro(&L);
            break;
        case 3:
            editarCadastro(&L);
            break;
        case 4:
            excluirCadastro(&L);
            break;

        default:
            return 0;
        }
        gotoxy(01, 21);
        printf("Voltar para o menu (1-Sim 2-Nao)..... ");
        gotoxy(39, 21);
        scanf("%d", &reiniciar);
    } while (reiniciar == 1);

    limpar();
    gotoxy(33, 12);
    printf("ATE A PROXIMA!");

    gotoxy(01, 25);
    return 0;
}

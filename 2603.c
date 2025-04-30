
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>

#define MAX 50

// Definição de registro de cliente (do primeiro programa)
typedef struct
{
    int cd_cliente;
    char nm_cliente[50];
    char ds_endereco[50];
    int nr_numero;
    char nr_documento[50];
    char ds_cidade[50];
    char ds_uf[05];
    char dt_cadastro[19];
    char nr_telefone[15];
} reg_cliente;

// Estrutura de lista duplamente encadeada (combinando ambos)
typedef struct TipoItem *TipoApontador;

typedef struct TipoItem
{
    reg_cliente info;
    TipoApontador ant;  // Ponteiro anterior (lista duplamente encadeada)
    TipoApontador prox; // Ponteiro próximo
} TipoItem;

typedef struct
{
    TipoApontador primeiro;
    TipoApontador ultimo;
} TipoLista;

// Funções de interface (do primeiro programa com adaptações)
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = (short)x;
    coord.Y = (short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void imprimir_linha(int linha)
{
    int i;
    gotoxy(01, linha);
    printf("+");
    for (i = 2; i < 80; i++)
    {
        gotoxy(i, linha);
        printf("-");
    }
    gotoxy(80, linha);
    printf("+");
}

void tela()
{
    int i;
    system("cls");
    imprimir_linha(1);

    gotoxy(03, 02);
    printf("Autor.........: Felipe");
    gotoxy(03, 03);
    printf("Instituicao...: Unicv");
    gotoxy(50, 02);
    printf("Data....: 02-04-2025");
    gotoxy(50, 03);
    printf("SISTEMA DE CADASTRO DE CLIENTES");

    gotoxy(02, 23);
    printf("MSG.:");

    for (i = 2; i < 24; i++)
    {
        gotoxy(01, i);
        printf("|");
        gotoxy(80, i);
        printf("|");
    }

    imprimir_linha(4);
    imprimir_linha(22);
    imprimir_linha(24);
}

void tela_cliente()
{
    tela();
    gotoxy(10, 7);
    printf("0 - Codigo do cliente........:");
    gotoxy(10, 9);
    printf("1 - Nome.....................:");
    gotoxy(10, 11);
    printf("2 - Endereco.................:");
    gotoxy(10, 13);
    printf("3 - Numero..................:");
    gotoxy(10, 15);
    printf("4 - Documento...............:");
    gotoxy(10, 17);
    printf("5 - Cidade..................:");
    gotoxy(10, 19);
    printf("6 - UF......................:");
    gotoxy(10, 21);
    printf("7 - Telefone................:");
}

// Funções de manipulação da lista (baseado no segundo programa)
void inicializar(TipoLista *L)
{
    L->primeiro = NULL;
    L->ultimo = NULL;
}

void cadastrarCliente(TipoLista *L)
{
    char opcao;

    do
    {
        TipoApontador novo = (TipoApontador)malloc(sizeof(TipoItem));

        if (novo == NULL)
        {
            gotoxy(10, 23);
            printf("Erro ao alocar memoria");
            getch();
            return;
        }

        tela_cliente();

        // Codigo
        gotoxy(42, 7);
        scanf("%d", &novo->info.cd_cliente);
        fflush(stdin);

        // Nome
        gotoxy(42, 9);
        fgets(novo->info.nm_cliente, 50, stdin);
        novo->info.nm_cliente[strcspn(novo->info.nm_cliente, "\n")] = 0;

        // Endereco
        gotoxy(42, 11);
        fgets(novo->info.ds_endereco, 50, stdin);
        novo->info.ds_endereco[strcspn(novo->info.ds_endereco, "\n")] = 0;

        // Numero
        gotoxy(42, 13);
        scanf("%d", &novo->info.nr_numero);
        fflush(stdin);

        // Documento
        gotoxy(42, 15);
        fgets(novo->info.nr_documento, 50, stdin);
        novo->info.nr_documento[strcspn(novo->info.nr_documento, "\n")] = 0;

        // Cidade
        gotoxy(42, 17);
        fgets(novo->info.ds_cidade, 50, stdin);
        novo->info.ds_cidade[strcspn(novo->info.ds_cidade, "\n")] = 0;

        // UF
        gotoxy(42, 19);
        fgets(novo->info.ds_uf, 5, stdin);
        novo->info.ds_uf[strcspn(novo->info.ds_uf, "\n")] = 0;

        // Telefone
        gotoxy(42, 21);
        fgets(novo->info.nr_telefone, 15, stdin);
        novo->info.nr_telefone[strcspn(novo->info.nr_telefone, "\n")] = 0;



        novo->ant = NULL;
        novo->prox = NULL;

        if (L->primeiro == NULL)
        {
            L->primeiro = novo;
            L->ultimo = novo;
        }
        else
        {
            novo->ant = L->ultimo;
            L->ultimo->prox = novo;
            L->ultimo = novo;
        }

        gotoxy(10, 23);
        printf("Cliente cadastrado com sucesso! Cadastrar outro? (S/N): ");

        opcao = getch();
        opcao = toupper(opcao);

        // Limpa a mensagem anterior
        gotoxy(10, 23);
        printf("                                                     ");

    } while (opcao == 'S');
}

void listarClientes(TipoLista *L)
{
    tela();
    TipoApontador atual = L->primeiro;
    int linha = 6;

    if (atual == NULL)
    {
        gotoxy(10, linha);
        printf("Nenhum cliente cadastrado!");
        getch();
        return;
    }

    gotoxy(10, linha++);
    printf("LISTA DE CLIENTES");
    linha++;

    while (atual != NULL)
    {
        gotoxy(10, linha++);
        printf("Codigo: %d", atual->info.cd_cliente);

        gotoxy(10, linha++);
        printf("Nome: %s", atual->info.nm_cliente);

        gotoxy(10, linha++);
        printf("Endereco: %s, %d", atual->info.ds_endereco, atual->info.nr_numero);

        gotoxy(10, linha++);
        printf("Documento: %s", atual->info.nr_documento);

        gotoxy(10, linha++);
        printf("Cidade: %s/%s", atual->info.ds_cidade, atual->info.ds_uf);

        gotoxy(10, linha++);
        printf("Telefone: %s", atual->info.nr_telefone);

        gotoxy(10, linha++);
        printf("Data Cadastro: %s", atual->info.dt_cadastro);

        linha++; // Espaço entre registros
        atual = atual->prox;
    }
    getch();
}

void consultar_cliente(TipoLista *L)
{
    int lin = 7;
    TipoApontador atual = L->primeiro;

    if (atual == NULL)
    {
        tela();
        gotoxy(10, lin);
        printf("Nenhum cliente cadastrado!");
        getch();
        return;
    }

    // Ordenação poderia ser implementada aqui se necessário
    // if (opc == 3) ordenar_por_codigo(L);
    // else ordenar_por_nome(L);

    while (atual != NULL)
    {
        if (lin == 7)
        {
            tela();
            gotoxy(15, 03);
            printf("LISTA DE CLIENTES - DETALHADA");

            gotoxy(02, 05);
            printf("Cd  Nome        Endereco           Documento  Cidade/UF     Telefone");
            gotoxy(02, 06);
            printf("--  ----------  ------------------ ---------  ----------    -----------");
        }

        gotoxy(02, lin);
        printf("%d", atual->info.cd_cliente);
        gotoxy(06, lin);
        printf("%s", atual->info.nm_cliente);
        gotoxy(18, lin);
        printf("%s, %d", atual->info.ds_endereco, atual->info.nr_numero);
        gotoxy(37, lin);
        printf("%s", atual->info.nr_documento);
        gotoxy(48, lin);
        printf("%s/%s", atual->info.ds_cidade, atual->info.ds_uf);
        gotoxy(62, lin);
        printf("%s", atual->info.nr_telefone);

        lin++;
        atual = atual->prox;

        if (lin > 22)
        {
            gotoxy(07, 23);
            printf("Pressione uma tecla para continuar...");
            getch();
            lin = 7;
        }
    }

    gotoxy(07, 23);
    printf("                                                     ");
    gotoxy(07, 23);
    printf("Fim da lista. ");
    getch();
}

void mostrarMenu()
{
    tela();
    gotoxy(10, 6);
    printf("MENU PRINCIPAL");
    gotoxy(10, 8);
    printf("1 - Cadastrar cliente");
    gotoxy(10, 10);
    printf("2 - Listar clientes");
    gotoxy(10, 12);
    printf("3 - Consultar Cliente");
    gotoxy(07, 23);
    printf("Opcao: ");
}

int main()
{
    TipoLista L;
    int opc;
    inicializar(&L);
    system("color 1f");
    setlocale(LC_ALL, "portuguese-brazilian");

    do
    {
        mostrarMenu();
        gotoxy(14, 23);
        scanf("%d", &opc);
        fflush(stdin);

        switch (opc)
        {
        case 1:
            cadastrarCliente(&L);
            break;
        case 2:
            listarClientes(&L);
            break;
        case 3:

            consultar_cliente(&L);
            break;
        default:
            gotoxy(10, 23);
            printf("Opcao invalida! Tente novamente.");
            getch();
        }
    } while (opc != 3);

    // Liberar memória alocada
    TipoApontador atual = L.primeiro;
    while (atual != NULL)
    {
        TipoApontador temp = atual;
        atual = atual->prox;
        free(temp);
    }

    return 0;
}

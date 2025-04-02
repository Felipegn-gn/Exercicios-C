/* Autor...: Felipe Souza
   Data....: 05/03/2025
   Objetivo: Criar uma folha de pagamento utilizando Lista Estatica */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define INICIO_ARRANJO 1
#define MAX 10

// Definicao de estrutura de daddos

typedef struct
{
    int codigo;
    char nome[50];
    char endereco[50];
    char cargo[50];
    char dt_admissao[11];
    char telefone[15];
    float salario;
} reg_funcionario;

typedef struct
{
    reg_funcionario func[MAX];
    int inicio;
    int fim;
} Lista;

void inicializar_lista(Lista *L)
{
    int i;
    L->inicio = INICIO_ARRANJO;
    L->fim = L->inicio;
    for (i = 0; i < MAX; i++)
    {
        L->func[i].codigo = 0;
        L->func[i].nome[0] = '\0';
        L->func[i].endereco[0] = '\0';
        L->func[i].cargo[0] = '\0';
        L->func[i].dt_admissao[0] = '\0';
        L->func[i].telefone[0] = '\0';
        L->func[i].salario = 0;
    }
}
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

    gotoxy(01, linha);
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
    gotoxy(03, 03);
    printf("Instituicao...: Unicv");

    gotoxy(03, 02);
    printf("Autor.........: Felipe");

    gotoxy(50, 02);
    printf("Data....: 05-03-2025");

    gotoxy(50, 03);
    printf("SISTEMA DE FOLHA DE PAGAMENTO");
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
void tela_funcionario()
{
    system("cls");
    tela();
    gotoxy(10, 7);
    printf("0 - Digite o codigo...........:                 ");
    gotoxy(10, 9);
    printf("1 - Nome......................:                 ");
    gotoxy(10, 11);
    printf("2 - Endereco..................:                 ");
    gotoxy(10, 13);
    printf("3 - Cargo.....................:                 ");
    gotoxy(10, 15);
    printf("4 - Data de admissao..........:                 ");
    gotoxy(10, 17);
    printf("5 - Telefone..................:                 ");
    gotoxy(10, 19);
    printf("6 - Salario...................:                 ");
}

// Funcao para inserir um funcionario na lista

// Funcao que pesquisa um funcionario na lista
int validarCodigo(Lista *L, int codigo)
{
    int i;

    for (i = 0; i < L->fim; i++)
    {
        if (L->func[i].codigo == codigo)
        {
            return i;
        }
    }
    return -1;
}

int cadastrar_codigo(){
    int *codigo;
    codigo = malloc(sizeof(int));
    do
    {

        gotoxy(07, 23);
        printf("                                                 ");
        gotoxy(42, 7);
        scanf("%d", codigo);

        if ((strlen(nome) == 1))
        {
            gotoxy(07, 23);

            printf("Nome do funcionario e obrigatorio.");
            getch();
            gotoxy(07, 23);

            printf("                                        ");
        }

    } while ((strlen(nome) == 1));
    return nome;
}
    
    
}

char *validarNome()
{
    char *nome;
    nome = malloc(sizeof(char) * 50);
    do
    {

        gotoxy(07, 23);
        printf("                                                 ");
        gotoxy(42, 9);
        fflush(stdin);
        fgets(nome, 50, stdin);

        if ((strlen(nome) == 1))
        {
            gotoxy(07, 23);

            printf("Nome do funcionario e obrigatorio.");
            getch();
            gotoxy(07, 23);

            printf("                                        ");
        }

    } while ((strlen(nome) == 1));
    return nome;
}

char *validarEndereco()
{
    char *endereco;
    endereco = malloc(sizeof(char) * 50);
    do
    {

        gotoxy(07, 23);
        printf("                                                 ");
        gotoxy(42, 11);
        fflush(stdin);
        fgets(endereco, 50, stdin);

        if ((strlen(endereco) == 1) )
        {
            gotoxy(07, 23);

            printf("Endereco do funcionario e obrigatorio.");
            getch();
            gotoxy(07, 23);

            printf("                                        ");
        }

    } while ((strlen(endereco) == 1) );
    return endereco;
}

char *validarCargo()
{
    char *cargo;
    cargo = malloc(sizeof(char) * 50);
    do
    {

        gotoxy(07, 23);
        printf("                                                 ");
        gotoxy(42, 13);
        fflush(stdin);
        fgets(cargo, 50, stdin);

        if ((strlen(cargo) == 1) )
        {
            gotoxy(07, 23);

            printf("Cargo do funcionario e obrigatorio.");
            getch();
            gotoxy(07, 23);

            printf("                                        ");
        }

    } while ((strlen(cargo) == 1) );
    return cargo;
}

char *validarData()
{
    char *dt_adimissao;
    dt_adimissao = malloc(sizeof(char) * 50);
    do
    {

        gotoxy(07, 23);
        printf("                                                 ");
        gotoxy(42, 15);
        fflush(stdin);
        fgets(dt_adimissao, 50, stdin);

        if ((strlen(dt_adimissao) == 1) )
        {
            gotoxy(07, 23);

            printf("Data de admissao do funcionario e obrigatorio.");
            getch();
            gotoxy(07, 23);

            printf("                                        ");
        }

    } while ((strlen(dt_adimissao) == 1) );
    return dt_adimissao;
}

char *validarTelefone()
{
    char *telefone;
    telefone = malloc(sizeof(char) * 50);
    do
    {

        gotoxy(07, 23);
        printf("                                                 ");
        gotoxy(42, 17);
        fflush(stdin);
        fgets(telefone, 50, stdin);

        if ((strlen(telefone) == 1) )
        {
            gotoxy(07, 23);

            printf("Telefone do funcionario e obrigatorio.");
            getch();
            gotoxy(07, 23);

            printf("                                        ");
        }

    } while ((strlen(telefone) == 1));
    return telefone;
}

float validarSalario()
{
    float *salario;
    salario = malloc(sizeof(float));
    do
    {

        gotoxy(07, 23);
        printf("                                                 ");
        gotoxy(42, 19);
        scanf("%f", salario);

        if (salario == 0)
        {
            gotoxy(07, 23);

            printf("Nome do funcionario e obrigatorio.");
            getch();
            gotoxy(07, 23);

            printf("                                        ");
        }

    } while (salario == 0);
    return *salario;
}
void CadastrarFuncionario(Lista *L)
{
    reg_funcionario funcionario;
    int resp;
    int controle;
    

    do
    {
        gotoxy(22, 21);
        printf("                                        ");
        tela();
        tela_funcionario();

        do
        {
            gotoxy(42, 7);
            printf("                   ");
            gotoxy(42, 7);
            funcionario.codigo = validarCodigo();
            controle = validarCodigo(L, funcionario.codigo);
            if(controle == 1)
            {
                gotoxy(22, 21);
                printf("                                      ");
                gotoxy(22, 21);
                printf("CODIGO JA CADASTRADO");
            }
            else
            {
                gotoxy(22, 21);
                printf("                                    ");
            }
        } while (controle == 1);

        strcpy(funcionario.nome,validarNome());

        strcpy(funcionario.endereco,validarEndereco());

        strcpy(funcionario.cargo,validarCargo());

        strcpy(funcionario.dt_admissao,validarData());


        strcpy(funcionario.telefone,validarTelefone());

        funcionario.salario = validarSalario();

        gotoxy(02, 23);
        printf("Quer confirmar o cadastro (1-Sim 2-Nao)....");
        scanf("%d", &resp);

        if (resp == 1)
        {
            L->func[L->fim] = funcionario;
            L->fim++;

            gotoxy(22, 21);
            printf("Funcionario cadastrado com sucesso.");
        }
        else
        {
            gotoxy(22, 21);
            printf("Cadastro cancelado.");
        }

        gotoxy(02, 23);
        printf("                                                   ");
        gotoxy(02, 23);
        printf("Quer cadastrar outro funcionario (1- Sim 2-Nao)");
        gotoxy(50, 23);
        scanf("%d", &resp);
    } while (resp == 1);
    gotoxy(02, 23);
    printf("                                                   ");
}

// Tela de alterar funcionario
void alterarFuncionario(Lista *L)
{
    int codigo, pos, resp;
    reg_funcionario funcionario;
    

    do
    {
        tela();

        // Solicita o código do funcionário
        gotoxy(02, 23);
        printf("Digite o codigo do funcionario: ");
        scanf("%d", &codigo);
        gotoxy(02, 23);
        printf("                                                   ");

        // Verifica se o funcionário existe
        pos = validarCodigo(L, codigo);
        if (pos == -1)
        {
            gotoxy(07, 23);
            printf("Funcionario nao encontrado.");
            getch();
            return; // Sai da função se o funcionário não for encontrado
        }

        // Exibe as informações atuais do funcionário
        gotoxy(10, 7);
        printf("=== Informacoes Atuais do Funcionario ===");
        gotoxy(10, 9);
        printf("Codigo...........: %d", L->func[pos].codigo);
        gotoxy(10, 11);
        printf("Nome.............: %s", L->func[pos].nome);
        gotoxy(10, 13);
        printf("Endereco.........: %s", L->func[pos].endereco);
        gotoxy(10, 15);
        printf("Cargo............: %s", L->func[pos].cargo);
        gotoxy(10, 17);
        printf("Data de Admissao.: %s", L->func[pos].dt_admissao);
        gotoxy(10, 19);
        printf("Telefone.........: %s", L->func[pos].telefone);
        gotoxy(10, 21);
        printf("Salario..........: %.2f", L->func[pos].salario);

        // Pergunta se o usuário deseja editar as informações
        gotoxy(02, 23);
        printf("Deseja editar as informacoes do funcionario? (1 - Sim / 2 - Nao): ");
        scanf("%d", &resp);
        gotoxy(02, 23);
        printf("                                                   ");

        if (resp == 1)
        {
            tela_funcionario();
            gotoxy(22, 5);
            printf("======== Novas Informacoes do Funcionario ========");

            // Solicita as novas informações do funcionário
            gotoxy(42, 7);
            scanf("%d", &funcionario.codigo);

            gotoxy(42, 9);
            fflush(stdin);
            fgets(funcionario.nome, 50, stdin);

            gotoxy(42, 11);
            fflush(stdin);
            fgets(funcionario.endereco, 50, stdin);

            gotoxy(42, 13);
            fflush(stdin);
            fgets(funcionario.cargo, 50, stdin);

            gotoxy(42, 15);
            fgets(funcionario.dt_admissao, 11, stdin);

            gotoxy(42, 17);
            fflush(stdin);
            fgets(funcionario.telefone, 15, stdin);

            gotoxy(42, 19);
            fflush(stdin);
            scanf("%f", &funcionario.salario);

            // Atualiza a lista com as novas informações
            L->func[pos] = funcionario;

            gotoxy(22, 21);
            printf("Informacoes alteradas com sucesso.");
        }

        // Pergunta se o usuário deseja verificar as novas informações
        gotoxy(02, 23);
        printf("Deseja verificar as novas informacoes do funcionario? (1 - Sim / 2 - Nao): ");
        scanf("%d", &resp);
        gotoxy(02, 23);
        printf("                                                   ");

        if (resp == 1)
        {
            tela();
            gotoxy(10, 7);
            printf("=== Informacoes Atuais do Funcionario ===");
            gotoxy(10, 9);
            printf("Codigo...........: %d", L->func[pos].codigo);
            gotoxy(10, 11);
            printf("Nome.............: %s", L->func[pos].nome);
            gotoxy(10, 13);
            printf("Endereco.........: %s", L->func[pos].endereco);
            gotoxy(10, 15);
            printf("Cargo............: %s", L->func[pos].cargo);
            gotoxy(10, 17);
            printf("Data de Admissao.: %s", L->func[pos].dt_admissao);
            gotoxy(10, 19);
            printf("Salario..........: %.2f", L->func[pos].salario);

            gotoxy(10, 23);
            printf("Pressione qualquer tecla para continuar...");
            getch();
        }

        // Pergunta se o usuário deseja voltar ao menu
        gotoxy(02, 23);
        printf("                                                   ");
        gotoxy(02, 23);
        printf("Voltar para o menu? (1-Sim 2-Nao).....");
        scanf("%d", &resp);

    } while (resp != 1); // Sai do loop se o usuário escolher voltar ao menu
}

void consultar_codigo(Lista *L)
{
    int pos, resp;
    reg_funcionario reg_func;

    do
    {
        tela();

        gotoxy(10, 07);
        printf("Digite o codigo do funcionario (0 para sair):");
        gotoxy(56, 07);
        printf("             "); // Limpa o campo anterior
        gotoxy(55, 07);
        scanf("%d", &reg_func.codigo);

        // Verifica se o usuário quer sair
        if (reg_func.codigo == 0)
        {
            break;
        }

        pos = validarCodigo(L, reg_func.codigo);
        if (pos == -1)
        {
            gotoxy(07, 23);
            printf("Codigo nao encontrado! Pressione qualquer tecla para continuar...");
            getch();
        }
        else
        {
            tela();
            reg_func = L->func[pos];
            gotoxy(10, 7);
            printf("Codigo...........: %d", reg_func.codigo);
            gotoxy(10, 9);
            printf("Nome.............: %s", reg_func.nome);
            gotoxy(10, 11);
            printf("Endereco.........: %s", reg_func.endereco);
            gotoxy(10, 13);
            printf("Cargo............: %s", reg_func.cargo);
            gotoxy(10, 15);
            printf("Data de Admissao.: %s", reg_func.dt_admissao);
            gotoxy(10, 17);
            printf("Telefone.........: %s", reg_func.telefone);
            gotoxy(10, 19);
            printf("Salario..........: %.2f", reg_func.salario);

            gotoxy(07, 23);
            printf("Pressione qualquer tecla para continuar...");
            getch();
        }

        gotoxy(07, 23);
        printf("Deseja consultar outro funcionario? (1 - Sim / 2 - Nao) ");
        scanf("%d", &resp);
        gotoxy(07, 23);
        printf("                                                                   ");

    } while (resp == 1);
}

void consultar_todos(Lista *L)
{

    int i;

    reg_funcionario reg_func;

    for (i = 0; i < L->fim; i++)
    {
        tela();
        tela_funcionario();

        reg_func = L->func[i];

        gotoxy(42, 7);
        printf("%d", reg_func.codigo);

        gotoxy(42, 9);
        printf("%s", reg_func.nome);

        gotoxy(42, 11);
        printf("%s", reg_func.endereco);

        gotoxy(42, 13);
        printf("%s", reg_func.cargo);

        gotoxy(42, 15);
        printf("%s", reg_func.dt_admissao);

        gotoxy(42, 17);
        printf("%s", reg_func.telefone);

        gotoxy(42, 19);
        printf("%.2f", reg_func.salario);

        gotoxy(07, 23);
        printf("Use as setas para navegar, Enter para sair.");

        int ch = getch();

        if (ch == 0 || ch == 224)
        {

            switch (getch())
            {

            case 75: // Seta para esquerda
                if (i == 0)
                {

                    i = i - 1;
                }
                else
                {
                    i = i - 2;
                }
                break;

            case 77: // seta para direita
                break;
            }
        }
        else if (ch == 13)
        {
            break;
        }

    }
    gotoxy(07, 23);
    printf("                                                                   ");

}

void ordenar_codigo(Lista *L)
{
    int i;
    int j;
    reg_funcionario aux;
    for (i = 0; i < L->fim - 1; i++)
    {
        for (j = i + 1; j < L->fim; j++)
        {
            if (L->func[i].codigo > L->func[j].codigo)
            {
                aux = L->func[i];
                L->func[i] = L->func[j];
                L->func[j] = aux;
            }
        }
    }
}
void ordenar_nome(Lista *L)
{
    int i;
    int j;
    reg_funcionario aux;
    for (i = 0; i < L->fim - 1; i++)
    {
        for (j = i + 1; j < L->fim; j++)
        {
            if (strcmp(L->func[i].nome, L->func[j].nome) > 0)
            {
                aux = L->func[i];
                L->func[i] = L->func[j];
                L->func[j] = aux;
            }
        }
    }
}

void consultar_lista(Lista *L, int opc)
{

    int i;
    int lin = 7;

    if (opc == 3)
    {
        ordenar_codigo(L);
    }
    else
    {
        ordenar_nome(L);
    }

    reg_funcionario reg_func;

    for (i = 1; i < L->fim; i++)
    {
        if (lin == 7)
        {
            tela();
            gotoxy(15, 03);
            if (opc == 3)
            {
                ordenar_codigo(L);
                printf("LISTA FUNCIONARIO - ORDENADO POR CODIGO");
            }
            else
            {
                ordenar_nome(L);
                printf("LISTA FUNCIONARIO - ORDENADO POR NOME");
            }

            gotoxy(02, 05);
            printf("Cd   Nome do funcionario                Cargo         dta.Admis     Salario");
            gotoxy(02, 06);
            printf("--   ---------------------------      ------------    --------------  --------");
        }

        reg_func = L->func[i];
        gotoxy(02, lin);
        printf("%d", reg_func.codigo);
        gotoxy(10, lin);
        printf("%s", reg_func.nome);
        gotoxy(45, lin);
        printf("%s", reg_func.cargo);
        gotoxy(59, lin);
        printf("%s", reg_func.dt_admissao);
        gotoxy(70, lin);
        printf("%9.2f", reg_func.salario);
        lin++;

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

void menu_consulta(Lista *L)
{
    int opc;
    do
    {
        tela();
        gotoxy(28, 03);
        printf("MENU CONSULTAR FUNCIONARIO");
        gotoxy(30, 10);
        printf("1 - Consulta por Codigo");

        gotoxy(30, 12);
        printf("2 - Consultar Fichario Completo");

        gotoxy(30, 14);
        printf("3 - Consulta Lista por Codigo");

        gotoxy(30, 16);
        printf("4 - Consulta Lista por Nome");

        gotoxy(30, 18);
        printf("5 - Voltar Menu Principal");

        gotoxy(02, 23);
        printf("Escolha uma opcao: ");
        scanf("%d", &opc);
        gotoxy(02, 23);
        printf("                                                   ");
        switch (opc)
        {
        case 1:
            consultar_codigo(L); // Consulta por nome
            break;
        case 2:
            consultar_todos(L); // Consulta por código
            break;
        case 3:
            consultar_lista(L, opc); // Consulta ordenada por código
            break;
        case 4:
            consultar_lista(L, opc);
            break;

        default:
            break;
        }
        gotoxy(02, 23);
        printf("Pressione qualquer tecla para continuar...");
        getch();

    } while (opc != 5);
}

void ExcluirFuncionario(Lista *L)
{
    int pos, resp;
    reg_funcionario reg_func;

    do
    {
        tela();

        // Solicita o código do funcionário
        gotoxy(02, 23);
        printf("Digite o codigo do funcionario a ser excluido: ");
        scanf("%d", &reg_func.codigo);
        gotoxy(02, 23);
        printf("                                                   ");

        // Verifica se o funcionário existe
        pos = validarCodigo(L, reg_func.codigo);
        if (pos == -1)
        {
            gotoxy(07, 23);
            printf("Funcionario nao encontrado.");
            getch();
            return; // Sai da função se o funcionário não for encontrado
        }
        else
        {

            // Exibe as informações do funcionário
            gotoxy(10, 7);
            printf("=== Informacoes do Funcionario a Ser Excluido ===");
            gotoxy(10, 9);
            printf("Codigo...........: %d", L->func[pos].codigo);
            gotoxy(10, 11);
            printf("Nome.............: %s", L->func[pos].nome);
            gotoxy(10, 13);
            printf("Endereco.........: %s", L->func[pos].endereco);
            gotoxy(10, 15);
            printf("Cargo............: %s", L->func[pos].cargo);
            gotoxy(10, 17);
            printf("Data de Admissao.: %s", L->func[pos].dt_admissao);
            gotoxy(10, 19);
            printf("Telefone.........: %s", L->func[pos].telefone);
            gotoxy(10, 21);
            printf("Salario..........: %.2f", L->func[pos].salario);
        }

        // Pergunta se o usuário deseja realmente excluir o funcionário
        gotoxy(02, 23);
        printf("Deseja realmente excluir este funcionario? (1 - Sim / 2 - Nao): ");
        scanf("%d", &resp);
        gotoxy(02, 23);
        printf("                                                                     ");

        if (resp == 1)
        {
            // Remove o funcionário da lista
            for (int i = pos; i < L->fim - 1; i++)
            {
                L->func[i] = L->func[i + 1]; // Desloca os elementos para a esquerda
            }
            L->fim--; // Atualiza o fim da lista

            gotoxy(22, 21);
            printf("                                                                ");
            gotoxy(22, 21);
            printf("Funcionario excluido com sucesso.");
        }
        else
        {
            gotoxy(22, 21);
            printf("Exclusao cancelada.");
        }

        gotoxy(07, 23);
        printf("Deseja excluir outro Funcionario? (1 - Sim / 2 - Nao)");
        scanf("%d", &resp);
        gotoxy(07, 23);
        printf("                                                                     ");
        getch();
    } while (resp == 1);
}


void Sair()
{
    tela();
    gotoxy(07, 23);
    printf("Deseja realmente sair? (1 - Sim / 2 - Nao): ");
    int resp;
    scanf("%d", &resp);

    if (resp == 1)
    {
        gotoxy(02, 23);
        printf("Saindo do sistema...");
        exit(0); // Encerra o programa
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
//Le os funcionarios de um arquivo
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
int telaEscolha()
{
    int opcao;
    tela();
    gotoxy(25, 10);
    printf("1 - Cadastrar Funcionario");
    gotoxy(25, 12);
    printf("2 - Alterar Funcionarios");
    gotoxy(25, 14);
    printf("3 - Excluir funcinario");
    gotoxy(25, 16);
    printf("4 - Menu de consulta");
    gotoxy(25, 18);
    printf("5 - Sair");
    gotoxy(25, 20);

    // Escolher a opcao do menu
    gotoxy(07, 23);
    printf(" Digite a sua opcao: ");
    scanf("%d", &opcao);
    return opcao;
    return 0;
}

int main()
{
    Lista L;
    int opcao, escolha;
    inicializar_lista(&L);

    do
    {
        opcao = telaEscolha();
        tela();

        switch (opcao)
        {
        case 1:
            CadastrarFuncionario(&L);
            break;
        case 2:
            alterarFuncionario(&L);
            break;
        case 3:
            ExcluirFuncionario(&L); // Nova função
            break;
        case 4:
            menu_consulta(&L);
            break;
        case 5:
            Sair(); // Nova função
            break;

        default:
            gotoxy(07, 23);
            printf("Opcao invalida! Tente novamente.");
            getch();
            break;
        }

        gotoxy(02, 23);
        printf("                                                   ");
        gotoxy(02, 23);
        printf("Voltar para o menu? (1-Sim 2-Nao).....");
        gotoxy(41, 23);
        scanf("%d", &escolha);
        gotoxy(02, 23);
        printf("                                                   ");
    } while (escolha == 1);

    return 0;
}

/*
 ============================================================================
 Autor      : Felipe Souza de Jesus Goncalves / Mateus Scacco
 Data       : 18/06/2025
 Equipe     : RA - 235291-2024 (Felipe) / RA - 23530-2024 (Mateus)
 Objetivo   : Sistema de Controle de Estoque completo e unificado,
              implementado com listas simplesmente e duplamente encadeadas.
 Versão     : Final Consolidada
 ============================================================================
*/

// --- BIBLIOTECAS PADRÃO ---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h> // Para getch()

// --- DEFINIÇÃO DAS ESTRUTURAS DE DADOS ---

// Estrutura para o registro de um produto
typedef struct
{
    int codigo_produto;
    char descricao_produto[50];
    char unidade_medida[4];
    char data_validade[11];
    float quantidade_estoque;
    float custo_medio_unitario;
    float valor_total_estoque;
} registro_produto;

// Nó da lista de produtos (simplesmente encadeada)
typedef struct TipoNoProduto *PonteiroNoProduto;
typedef struct TipoNoProduto
{
    registro_produto conteudo;
    PonteiroNoProduto proximo;
} TipoNoProduto;

// Descritor da lista de produtos
typedef struct
{
    PonteiroNoProduto Primeiro;
    PonteiroNoProduto Ultimo;
} TipoListaProdutos;

// Estrutura para o registro de uma movimentação de estoque
typedef struct
{
    char data_movim[11];
    int codigo_produto_movim;
    char tipo_movim; // 'E' para Entrada, 'S' para Saída
    float quantidade_movimentada;
    float valor_unitario_movim;
    float valor_total_movim;
} registro_movim;

// Nó da lista de movimentações (duplamente encadeada)
typedef struct TipoNoMovim *PonteiroNoMovim;
typedef struct TipoNoMovim
{
    PonteiroNoMovim anterior;
    registro_movim conteudo_movim;
    PonteiroNoMovim proximo;
} TipoNoMovim;

// Descritor da lista de movimentações
typedef struct
{
    PonteiroNoMovim Prim;
    PonteiroNoMovim Ult;
} TipoListaMovimentacoes;

// --- PROTÓTIPOS DAS FUNÇÕES ---

// Interface com o Usuário
void gotoxy(int x, int y);
void limpar();
void tela();
void menuPrincipal();
void menuProdutos(TipoListaProdutos *lista);
void menuMovimentacao(TipoListaMovimentacoes *listaMovim, TipoListaProdutos *listaProd);
void MenuConsultas(TipoListaProdutos *lista);

// Inicialização das Listas
void InicializarListaProdutos(TipoListaProdutos *lista);
void InicializarListaMovimentacoes(TipoListaMovimentacoes *lista);

// Persistência de Dados (Arquivo)
void SalvarDadosProdutos(TipoListaProdutos *lista, const char *nome_arquivo);
void CarregarDadosProdutos(TipoListaProdutos *lista, const char *nome_arquivo);
void SalvarDadosMovimentacoes(TipoListaMovimentacoes *lista, const char *nome_arquivo);
void CarregarDadosMovimentacoes(TipoListaMovimentacoes *lista, const char *nome_arquivo);

// Gestão de Produtos
int obterDadosProduto(registro_produto *produto, TipoListaProdutos *lista);
void InserirProdutoInicio(TipoListaProdutos *lista, registro_produto produto);
void InserirProdutoFinal(TipoListaProdutos *lista, registro_produto produto);
void InserirProdutoPosicao(TipoListaProdutos *lista, registro_produto produto, int posicao);
void gerenciarInsercao(TipoListaProdutos *lista);
int removerProdutoInicio(TipoListaProdutos *lista);
int removerProdutoFinal(TipoListaProdutos *lista);
int removerProdutoPosicao(TipoListaProdutos *lista, int posicao);
void gerenciarExclusao(TipoListaProdutos *lista);
void AlterarProduto(TipoListaProdutos *lista);

// Gestão de Movimentações
void CadastrarMovimentacoes(TipoListaMovimentacoes *lista, TipoListaProdutos *listaProdutos);
void ListarMovimentacoes(TipoListaMovimentacoes *lista, TipoListaProdutos *listaProdutos);

// Consultas e Ordenação
PonteiroNoProduto BuscarProdutoPorCodigo(TipoListaProdutos *lista, int codigo);
void OrdenarListaPorCodigo(TipoListaProdutos *lista);
void OrdenarListaPorNome(TipoListaProdutos *lista);
void ConsultarProdutoPorCodigoUI(TipoListaProdutos *lista);
void ConsultarListaProdutos(TipoListaProdutos *lista, int criterio);

// Relatórios
void RelatorioListaPrecos(TipoListaProdutos *lista);
void RelatorioBalancoFisicoFinanceiro(TipoListaProdutos *lista);

// --- FUNÇÃO PRINCIPAL ---
int main()
{
    TipoListaProdutos listaDeProdutos;
    TipoListaMovimentacoes listaDeMovimentacoes;
    int opcao;

    InicializarListaProdutos(&listaDeProdutos);
    InicializarListaMovimentacoes(&listaDeMovimentacoes);

    // Carrega dados dos arquivos ao iniciar
    CarregarDadosProdutos(&listaDeProdutos, "produtos.txt");
    CarregarDadosMovimentacoes(&listaDeMovimentacoes, "movimentacoes.txt");

    do
    {
        menuPrincipal();
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao)
        {
        case 1:
            menuProdutos(&listaDeProdutos);
            break;
        case 2:
            menuMovimentacao(&listaDeMovimentacoes, &listaDeProdutos);
            break;
        case 3:
            // Salva dados nos arquivos ao finalizar
            SalvarDadosProdutos(&listaDeProdutos, "produtos.txt");
            SalvarDadosMovimentacoes(&listaDeMovimentacoes, "movimentacoes.txt");
            gotoxy(8, 25);
            printf("Sistema finalizado. Dados salvos com sucesso!");
            getch();
            break;
        default:
            gotoxy(8, 25);
            printf("Opcao invalida! Pressione qualquer tecla para continuar.");
            getch();
        }
    } while (opcao != 3);

    limpar();
    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES DE INTERFACE ---

void gotoxy(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}

void limpar()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void tela()
{
    limpar();
    gotoxy(1, 1);
    printf("+----------------------------------------------------------------------------+");
    gotoxy(1, 2);
    printf("| UNICV - ESTRUTURA DE DADOS - PROF. RODNEY                                  |");
    gotoxy(1, 3);
    printf("|                SISTEMA DE CONTROLE DE ESTOQUE                              |");
    gotoxy(1, 4);
    printf("+----------------------------------------------------------------------------+");
    gotoxy(1, 24);
    printf("+----------------------------------------------------------------------------+");
    gotoxy(1, 25);
    printf("| MSG: ");
    gotoxy(8, 25);
}

void menuPrincipal()
{
    tela();
    gotoxy(28, 8);
    printf("MENU PRINCIPAL");
    gotoxy(25, 12);
    printf("1 - Menu Cadastro de Produto");
    gotoxy(25, 14);
    printf("2 - Menu Movimentacao de Estoque");
    gotoxy(25, 16);
    printf("3 - Finalizar o Programa");
    gotoxy(8, 25);
    printf("Digite sua opcao: ");
}

void menuProdutos(TipoListaProdutos *lista)
{
    int opcao;
    do
    {
        tela();
        gotoxy(28, 6);
        printf("MENU PRODUTO");
        gotoxy(25, 8);
        printf("1 - Cadastrar Produto (Inserir)");
        gotoxy(25, 10);
        printf("2 - Remover Produto (Excluir)");
        gotoxy(25, 12);
        printf("3 - Alterar dados do Produto");
        gotoxy(25, 14);
        printf("4 - Consultar / Listar Produtos");
        gotoxy(25, 16);
        printf("5 - Relatorio - Lista de Precos");
        gotoxy(25, 18);
        printf("6 - Relatorio - Balanco Fisico/Financeiro");
        gotoxy(25, 20);
        printf("0 - Retornar ao Menu Principal");
        gotoxy(8, 25);
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao)
        {
        case 1:
            gerenciarInsercao(lista);
            break;
        case 2:
            gerenciarExclusao(lista);
            break;
        case 3:
            AlterarProduto(lista);
            break;
        case 4:
            MenuConsultas(lista);
            break;
        case 5:
            RelatorioListaPrecos(lista);
            break;
        case 6:
            RelatorioBalancoFisicoFinanceiro(lista);
            break;
        case 0:
            break;
        default:
            gotoxy(8, 25);
            printf("Opcao invalida! Pressione qualquer tecla.");
            getch();
        }
    } while (opcao != 0);
}

void menuMovimentacao(TipoListaMovimentacoes *listaMovim, TipoListaProdutos *listaProd)
{
    int opcao;
    do
    {
        tela();
        gotoxy(22, 6);
        printf("MENU MOVIMENTACAO DE ESTOQUE");
        gotoxy(25, 10);
        printf("1 - Cadastrar Movimentacao (Entrada/Saida)");
        gotoxy(25, 12);
        printf("2 - Listar Movimentacoes");
        gotoxy(25, 14);
        printf("0 - Retornar ao Menu Principal");
        gotoxy(8, 25);
        printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao)
        {
        case 1:
            CadastrarMovimentacoes(listaMovim, listaProd);
            break;
        case 2:
            ListarMovimentacoes(listaMovim, listaProd);
            break;
        case 0:
            break;
        default:
            gotoxy(8, 25);
            printf("Opcao invalida! Pressione qualquer tecla.");
            getch();
        }
    } while (opcao != 0);
}

void MenuConsultas(TipoListaProdutos *lista)
{
    int opcao;
    do
    {
        tela();
        gotoxy(28, 8);
        printf("--- MENU DE CONSULTAS ---");
        gotoxy(25, 11);
        printf("1. Consultar por Codigo Especifico");
        gotoxy(25, 13);
        printf("2. Listar Todos (ordenado por Codigo)");
        gotoxy(25, 15);
        printf("3. Listar Todos (ordenado por Nome)");
        gotoxy(25, 17);
        printf("0. Voltar ao Menu Anterior");
        gotoxy(8, 25);
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1)
        {
            opcao = -1;
            fflush(stdin);
        }
        switch (opcao)
        {
        case 1:
            ConsultarProdutoPorCodigoUI(lista);
            break;
        case 2:
            ConsultarListaProdutos(lista, 1);
            break;
        case 3:
            ConsultarListaProdutos(lista, 2);
            break;
        case 0:
            break;
        default:
            gotoxy(8, 25);
            printf("Opcao invalida! Pressione qualquer tecla.");
            getch();
        }
    } while (opcao != 0);
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES DO SISTEMA ---

void InicializarListaProdutos(TipoListaProdutos *lista)
{
    lista->Primeiro = NULL;
    lista->Ultimo = NULL;
}

void InicializarListaMovimentacoes(TipoListaMovimentacoes *lista)
{
    lista->Prim = NULL;
    lista->Ult = NULL;
}

void SalvarDadosProdutos(TipoListaProdutos *lista, const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL)
    {
        perror("ERRO ao salvar produtos");
        return;
    }
    PonteiroNoProduto atual = lista->Primeiro;
    while (atual != NULL)
    {
        fprintf(arquivo, "%d;%s;%s;%s;%f;%f;%f\n",
                atual->conteudo.codigo_produto, atual->conteudo.descricao_produto,
                atual->conteudo.unidade_medida, atual->conteudo.data_validade,
                atual->conteudo.quantidade_estoque, atual->conteudo.custo_medio_unitario,
                atual->conteudo.valor_total_estoque);
        atual = atual->proximo;
    }
    fclose(arquivo);
}

void CarregarDadosProdutos(TipoListaProdutos *lista, const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL)
        return;

    InicializarListaProdutos(lista);
    registro_produto p;
    while (fscanf(arquivo, "%d;%49[^;];%3[^;];%10[^;];%f;%f;%f\n",
                  &p.codigo_produto, p.descricao_produto, p.unidade_medida,
                  p.data_validade, &p.quantidade_estoque,
                  &p.custo_medio_unitario, &p.valor_total_estoque) == 7)
    {
        InserirProdutoFinal(lista, p);
    }
    fclose(arquivo);
}

void SalvarDadosMovimentacoes(TipoListaMovimentacoes *lista, const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL)
    {
        perror("Erro ao salvar movimentacoes");
        return;
    }
    PonteiroNoMovim atual = lista->Prim;
    while (atual != NULL)
    {
        fprintf(arquivo, "%s;%d;%c;%f;%f;%f\n",
                atual->conteudo_movim.data_movim, atual->conteudo_movim.codigo_produto_movim,
                atual->conteudo_movim.tipo_movim, atual->conteudo_movim.quantidade_movimentada,
                atual->conteudo_movim.valor_unitario_movim, atual->conteudo_movim.valor_total_movim);
        atual = atual->proximo;
    }
    fclose(arquivo);
}

void CarregarDadosMovimentacoes(TipoListaMovimentacoes *lista, const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL)
        return;
    InicializarListaMovimentacoes(lista);
    registro_movim m;
    while (fscanf(arquivo, "%10[^;];%d;%c;%f;%f;%f\n",
                  m.data_movim, &m.codigo_produto_movim, &m.tipo_movim,
                  &m.quantidade_movimentada, &m.valor_unitario_movim,
                  &m.valor_total_movim) == 6)
    {
        PonteiroNoMovim novo = (PonteiroNoMovim)malloc(sizeof(TipoNoMovim));
        novo->conteudo_movim = m;
        novo->proximo = NULL;
        novo->anterior = lista->Ult;
        if (lista->Prim == NULL)
            lista->Prim = novo;
        else
            lista->Ult->proximo = novo;
        lista->Ult = novo;
    }
    fclose(arquivo);
}

PonteiroNoProduto BuscarProdutoPorCodigo(TipoListaProdutos *lista, int codigo)
{
    PonteiroNoProduto atual = lista->Primeiro;
    while (atual != NULL)
    {
        if (atual->conteudo.codigo_produto == codigo)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

void OrdenarListaPorCodigo(TipoListaProdutos *lista)
{
    if (lista->Primeiro == NULL)
        return;
    int trocou;
    PonteiroNoProduto ptr1;
    do
    {
        trocou = 0;
        ptr1 = lista->Primeiro;
        while (ptr1->proximo != NULL)
        {
            if (ptr1->conteudo.codigo_produto > ptr1->proximo->conteudo.codigo_produto)
            {
                registro_produto temp = ptr1->conteudo;
                ptr1->conteudo = ptr1->proximo->conteudo;
                ptr1->proximo->conteudo = temp;
                trocou = 1;
            }
            ptr1 = ptr1->proximo;
        }
    } while (trocou);
}

void OrdenarListaPorNome(TipoListaProdutos *lista)
{
    if (lista->Primeiro == NULL)
        return;
    int trocou;
    PonteiroNoProduto ptr1;
    do
    {
        trocou = 0;
        ptr1 = lista->Primeiro;
        while (ptr1->proximo != NULL)
        {
            if (stricmp(ptr1->conteudo.descricao_produto, ptr1->proximo->conteudo.descricao_produto) > 0)
            {
                registro_produto temp = ptr1->conteudo;
                ptr1->conteudo = ptr1->proximo->conteudo;
                ptr1->proximo->conteudo = temp;
                trocou = 1;
            }
            ptr1 = ptr1->proximo;
        }
    } while (trocou);
}

void CadastrarMovimentacoes(TipoListaMovimentacoes *lista, TipoListaProdutos *listaProdutos)
{
    registro_movim novaMovimentacao;
    tela();
    gotoxy(28, 6);
    printf("CADASTRO DE MOVIMENTACAO");
    gotoxy(25, 8);
    printf("Data da Movimentacao (DD/MM/AAAA): ");
    scanf("%10s", novaMovimentacao.data_movim);
    gotoxy(25, 9);
    printf("Codigo do Produto................: ");
    scanf("%d", &novaMovimentacao.codigo_produto_movim);
    PonteiroNoProduto produto = BuscarProdutoPorCodigo(listaProdutos, novaMovimentacao.codigo_produto_movim);
    if (produto == NULL)
    {
        gotoxy(8, 25);
        printf("ERRO: Produto com codigo %d nao encontrado!", novaMovimentacao.codigo_produto_movim);
        getch();
        return;
    }
    gotoxy(60, 9);
    printf("-> %s", produto->conteudo.descricao_produto);
    gotoxy(25, 10);
    printf("Tipo da Movimentacao (E/S).......: ");
    scanf(" %c", &novaMovimentacao.tipo_movim);
    novaMovimentacao.tipo_movim = toupper(novaMovimentacao.tipo_movim);
    gotoxy(25, 11);
    printf("Quantidade Movimentada...........: ");
    scanf("%f", &novaMovimentacao.quantidade_movimentada);

    if (novaMovimentacao.tipo_movim == 'E')
    {
        gotoxy(25, 12);
        printf("Valor Unitario da Entrada........: ");
        scanf("%f", &novaMovimentacao.valor_unitario_movim);
    }
    else
    {
        novaMovimentacao.valor_unitario_movim = produto->conteudo.custo_medio_unitario;
        gotoxy(25, 12);
        printf("Custo Medio (Saida)..............: %.2f", novaMovimentacao.valor_unitario_movim);
    }
    novaMovimentacao.valor_total_movim = novaMovimentacao.quantidade_movimentada * novaMovimentacao.valor_unitario_movim;
    gotoxy(25, 13);
    printf("Valor Total da Movimentacao......: %.2f", novaMovimentacao.valor_total_movim);

    if (novaMovimentacao.tipo_movim == 'S' && produto->conteudo.quantidade_estoque < novaMovimentacao.quantidade_movimentada)
    {
        gotoxy(8, 25);
        printf("ERRO: Saldo insuficiente! Disponivel: %.2f", produto->conteudo.quantidade_estoque);
        getch();
        return;
    }

    // --- LÓGICA DE CUSTO MÉDIO E ATUALIZAÇÃO DE ESTOQUE ---
    if (novaMovimentacao.tipo_movim == 'E')
    {
        float valor_estoque_atual = produto->conteudo.valor_total_estoque;
        float valor_entrada = novaMovimentacao.valor_total_movim;
        float nova_quantidade_total = produto->conteudo.quantidade_estoque + novaMovimentacao.quantidade_movimentada;
        produto->conteudo.quantidade_estoque = nova_quantidade_total;
        if (nova_quantidade_total > 0)
        {
            produto->conteudo.custo_medio_unitario = (valor_estoque_atual + valor_entrada) / nova_quantidade_total;
        }
        produto->conteudo.valor_total_estoque = produto->conteudo.quantidade_estoque * produto->conteudo.custo_medio_unitario;
    }
    else if (novaMovimentacao.tipo_movim == 'S')
    {
        produto->conteudo.quantidade_estoque -= novaMovimentacao.quantidade_movimentada;
        produto->conteudo.valor_total_estoque = produto->conteudo.quantidade_estoque * produto->conteudo.custo_medio_unitario;
    }
    else
    {
        gotoxy(8, 25);
        printf("ERRO: Tipo de movimentacao invalido (use 'E' ou 'S').");
        getch();
        return;
    }

    PonteiroNoMovim novoNo = (PonteiroNoMovim)malloc(sizeof(TipoNoMovim));
    novoNo->conteudo_movim = novaMovimentacao;
    novoNo->proximo = NULL;
    novoNo->anterior = lista->Ult;
    if (lista->Prim == NULL)
        lista->Prim = novoNo;
    else
        lista->Ult->proximo = novoNo;
    lista->Ult = novoNo;

    gotoxy(8, 25);
    printf("Movimentacao cadastrada com sucesso!");
    getch();
}

void ListarMovimentacoes(TipoListaMovimentacoes *lista, TipoListaProdutos *listaProdutos)
{
    tela();
    if (lista->Prim == NULL)
    {
        gotoxy(2, 6);
        printf("Nenhuma movimentacao registrada.");
        gotoxy(8, 25);
        printf("Pressione qualquer tecla para continuar...");
        getch();
        return;
    }
    int lin = 7;
    PonteiroNoMovim atual = lista->Prim;
    PonteiroNoProduto produto;
    while (atual != NULL)
    {
        if (lin == 7)
        {
            tela();
            gotoxy(20, 3);
            printf("HISTORICO DE MOVIMENTACOES");
            gotoxy(2, 5);
            printf("Data       Cod. Produto                    Tipo Qtd      Vl. Unit.  Vl. Total");
            gotoxy(2, 6);
            printf("---------- ---- -------------------------- ---- -------- ---------- ----------");
        }
        produto = BuscarProdutoPorCodigo(listaProdutos, atual->conteudo_movim.codigo_produto_movim);
        char *desc = (produto != NULL) ? produto->conteudo.descricao_produto : "NAO ENCONTRADO";
        gotoxy(2, lin);
        printf("%-10s %-4d %-26.26s %-4c %-8.2f %-10.2f %-10.2f",
               atual->conteudo_movim.data_movim, atual->conteudo_movim.codigo_produto_movim, desc,
               atual->conteudo_movim.tipo_movim, atual->conteudo_movim.quantidade_movimentada,
               atual->conteudo_movim.valor_unitario_movim, atual->conteudo_movim.valor_total_movim);
        lin++;
        if (lin > 22)
        {
            gotoxy(8, 25);
            printf("Pressione uma tecla para continuar...");
            getch();
            lin = 7;
        }
        atual = atual->proximo;
    }
    gotoxy(8, 25);
    printf("Fim da lista. Pressione qualquer tecla para voltar.");
    getch();
}

void AlterarProduto(TipoListaProdutos *lista)
{
    int codigo;
    tela();
    gotoxy(28, 6);
    printf("ALTERAR DADOS DO PRODUTO");
    gotoxy(25, 8);
    printf("Digite o codigo do produto a alterar: ");
    scanf("%d", &codigo);
    fflush(stdin);
    PonteiroNoProduto no = BuscarProdutoPorCodigo(lista, codigo);
    if (no == NULL)
    {
        gotoxy(8, 25);
        printf("ERRO: Produto com o codigo %d nao encontrado.", codigo);
        getch();
        return;
    }
    tela();
    gotoxy(20, 6);
    printf("ALTERAR PRODUTO (COD: %d - %s)", codigo, no->conteudo.descricao_produto);
    gotoxy(10, 9);
    printf("Nova Descricao (Enter para manter: '%s'): ", no->conteudo.descricao_produto);
    char nova_desc[50];
    fgets(nova_desc, 50, stdin);
    gotoxy(10, 11);
    printf("Nova Unid. Medida (Enter para manter: '%s'): ", no->conteudo.unidade_medida);
    char nova_unid[4];
    fgets(nova_unid, 4, stdin);
    gotoxy(10, 13);
    printf("Nova Data Validade (Enter para manter: '%s'): ", no->conteudo.data_validade);
    char nova_data[11];
    fgets(nova_data, 11, stdin);
    if (strlen(nova_desc) > 1)
    {
        strcpy(no->conteudo.descricao_produto, nova_desc);
        no->conteudo.descricao_produto[strcspn(no->conteudo.descricao_produto, "\n")] = 0;
    }
    if (strlen(nova_unid) > 1)
    {
        strcpy(no->conteudo.unidade_medida, nova_unid);
        no->conteudo.unidade_medida[strcspn(no->conteudo.unidade_medida, "\n")] = 0;
    }
    if (strlen(nova_data) > 1)
    {
        strcpy(no->conteudo.data_validade, nova_data);
        no->conteudo.data_validade[strcspn(no->conteudo.data_validade, "\n")] = 0;
    }
    gotoxy(8, 25);
    printf("Produto alterado com sucesso!");
    getch();
}

// ... Continuação das funções de Produto ...
int obterDadosProduto(registro_produto *produto, TipoListaProdutos *lista)
{
    gotoxy(25, 8);
    printf("Codigo do Produto..........: ");
    int cod_valido = 0;
    do
    {
        gotoxy(55, 8);
        printf("               ");
        gotoxy(55, 8);
        if (scanf("%d", &produto->codigo_produto) != 1)
        {
            fflush(stdin);
            gotoxy(8, 25);
            printf("ERRO: Codigo deve ser um numero.");
            getch();
            gotoxy(8, 25);
            printf("                                 ");
            continue;
        }
        if (BuscarProdutoPorCodigo(lista, produto->codigo_produto) != NULL)
        {
            gotoxy(8, 25);
            printf("ERRO: Codigo ja cadastrado.");
            getch();
            gotoxy(8, 25);
            printf("                           ");
        }
        else
        {
            cod_valido = 1;
        }
    } while (!cod_valido);
    fflush(stdin);
    gotoxy(25, 9);
    printf("Descricao do Produto.......: ");
    gotoxy(55, 9);
    fgets(produto->descricao_produto, 50, stdin);
    produto->descricao_produto[strcspn(produto->descricao_produto, "\n")] = 0;
    gotoxy(25, 10);
    printf("Unidade de Medida (UN/KG)..: ");
    gotoxy(55, 10);
    fgets(produto->unidade_medida, 4, stdin);
    produto->unidade_medida[strcspn(produto->unidade_medida, "\n")] = 0;
    gotoxy(25, 11);
    printf("Data Validade (DD/MM/AAAA).: ");
    gotoxy(55, 11);
    fgets(produto->data_validade, 11, stdin);
    produto->data_validade[strcspn(produto->data_validade, "\n")] = 0;
    produto->quantidade_estoque = 0;
    produto->custo_medio_unitario = 0;
    produto->valor_total_estoque = 0;
    gotoxy(8, 25);
    printf("Confirmar cadastro? (S/N): ");
    return (toupper(getch()) == 'S');
}

void gerenciarInsercao(TipoListaProdutos *lista)
{
    registro_produto p;
    tela();
    gotoxy(28, 6);
    printf("CADASTRAR PRODUTO");
    if (!obterDadosProduto(&p, lista))
    {
        gotoxy(8, 25);
        printf("Cadastro cancelado.             ");
        getch();
        return;
    }
    tela();
    gotoxy(28, 6);
    printf("LOCAL DE INSERCAO");
    gotoxy(25, 10);
    printf("1. Inserir no INICIO da lista");
    gotoxy(25, 12);
    printf("2. Inserir no FINAL da lista");
    gotoxy(25, 14);
    printf("3. Inserir por POSICAO");
    gotoxy(8, 25);
    printf("Escolha uma opcao: ");
    int op, pos;
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        InserirProdutoInicio(lista, p);
        break;
    case 2:
        InserirProdutoFinal(lista, p);
        break;
    case 3:
        gotoxy(8, 25);
        printf("Digite a POSICAO para inserir:       ");
        scanf("%d", &pos);
        InserirProdutoPosicao(lista, p, pos);
        break;
    default:
        gotoxy(8, 25);
        printf("Opcao invalida!                     ");
        getch();
    }
}

void InserirProdutoInicio(TipoListaProdutos *lista, registro_produto produto)
{
    PonteiroNoProduto novo = (PonteiroNoProduto)malloc(sizeof(TipoNoProduto));
    novo->conteudo = produto;
    novo->proximo = lista->Primeiro;
    lista->Primeiro = novo;
    if (lista->Ultimo == NULL)
        lista->Ultimo = novo;
    gotoxy(8, 25);
    printf("Produto inserido no INICIO com sucesso! ");
    getch();
}

void InserirProdutoFinal(TipoListaProdutos *lista, registro_produto produto)
{
    PonteiroNoProduto novo = (PonteiroNoProduto)malloc(sizeof(TipoNoProduto));
    novo->conteudo = produto;
    novo->proximo = NULL;
    if (lista->Primeiro == NULL)
    {
        lista->Primeiro = novo;
        lista->Ultimo = novo;
    }
    else
    {
        lista->Ultimo->proximo = novo;
        lista->Ultimo = novo;
    }
    if (strlen(produto.descricao_produto) > 0)
    { // Evita msg no carregamento
        gotoxy(8, 25);
        printf("Produto inserido no FINAL com sucesso!  ");
        getch();
    }
}

void InserirProdutoPosicao(TipoListaProdutos *lista, registro_produto produto, int posicao)
{
    if (posicao <= 1)
    {
        InserirProdutoInicio(lista, produto);
        return;
    }
    PonteiroNoProduto atual = lista->Primeiro, ant = NULL;
    int i = 1;
    while (atual != NULL && i < posicao)
    {
        ant = atual;
        atual = atual->proximo;
        i++;
    }
    if (ant == NULL)
    {
        InserirProdutoInicio(lista, produto);
        return;
    }
    if (atual == NULL && i == posicao)
    {
        InserirProdutoFinal(lista, produto);
        return;
    }
    if (i < posicao)
    {
        gotoxy(8, 25);
        printf("ERRO: Posicao invalida.");
        getch();
        return;
    }
    PonteiroNoProduto novo = (PonteiroNoProduto)malloc(sizeof(TipoNoProduto));
    novo->conteudo = produto;
    novo->proximo = atual;
    ant->proximo = novo;
    gotoxy(8, 25);
    printf("Produto inserido na posicao %d com sucesso!", posicao);
    getch();
}

int removerProdutoInicio(TipoListaProdutos *lista)
{
    if (lista->Primeiro == NULL)
        return 0;
    if (lista->Primeiro->conteudo.quantidade_estoque > 0)
        return -1;
    PonteiroNoProduto temp = lista->Primeiro;
    lista->Primeiro = temp->proximo;
    if (lista->Primeiro == NULL)
        lista->Ultimo = NULL;
    free(temp);
    return 1;
}

int removerProdutoFinal(TipoListaProdutos *lista)
{
    if (lista->Primeiro == NULL)
        return 0;
    if (lista->Ultimo->conteudo.quantidade_estoque > 0)
        return -1;
    PonteiroNoProduto temp = lista->Ultimo;
    if (lista->Primeiro == lista->Ultimo)
    {
        lista->Primeiro = NULL;
        lista->Ultimo = NULL;
    }
    else
    {
        PonteiroNoProduto penultimo = lista->Primeiro;
        while (penultimo->proximo != lista->Ultimo)
            penultimo = penultimo->proximo;
        penultimo->proximo = NULL;
        lista->Ultimo = penultimo;
    }
    free(temp);
    return 1;
}

int removerProdutoPosicao(TipoListaProdutos *lista, int posicao)
{
    if (posicao < 1 || lista->Primeiro == NULL)
        return 0;
    if (posicao == 1)
        return removerProdutoInicio(lista);
    PonteiroNoProduto ant = lista->Primeiro;
    int i = 1;
    while (i < posicao - 1 && ant != NULL)
    {
        ant = ant->proximo;
        i++;
    }
    if (ant == NULL || ant->proximo == NULL)
        return 0;
    PonteiroNoProduto temp = ant->proximo;
    if (temp->conteudo.quantidade_estoque > 0)
        return -1;
    ant->proximo = temp->proximo;
    if (temp == lista->Ultimo)
        lista->Ultimo = ant;
    free(temp);
    return 1;
}

void gerenciarExclusao(TipoListaProdutos *lista)
{
    int op, pos, res;
    tela();
    gotoxy(25, 8);
    printf("--- MENU DE EXCLUSAO ---");
    gotoxy(25, 10);
    printf("1. Excluir do INICIO");
    gotoxy(25, 11);
    printf("2. Excluir do FIM");
    gotoxy(25, 12);
    printf("3. Excluir por POSICAO");
    gotoxy(25, 14);
    printf("0. Voltar");
    gotoxy(8, 25);
    printf("Escolha uma opcao: ");
    scanf("%d", &op);
    switch (op)
    {
    case 1:
        res = removerProdutoInicio(lista);
        break;
    case 2:
        res = removerProdutoFinal(lista);
        break;
    case 3:
        gotoxy(8, 25);
        printf("Digite a POSICAO:                  ");
        scanf("%d", &pos);
        res = removerProdutoPosicao(lista, pos);
        break;
    default:
        gotoxy(8, 25);
        printf("Opcao Invalida ou cancelada.      ");
        getch();
        return;
    }
    gotoxy(8, 25);
    if (res == 1)
        printf("Produto removido com sucesso!       ");
    else if (res == 0)
        printf("ERRO: Lista vazia ou posicao invalida.");
    else
        printf("ERRO: Produto com estoque nao pode ser excluido.");
    getch();
}

void ConsultarProdutoPorCodigoUI(TipoListaProdutos *lista)
{
    int codigo;
    tela();
    gotoxy(2, 5);
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);
    PonteiroNoProduto no = BuscarProdutoPorCodigo(lista, codigo);
    tela();
    gotoxy(2, 6);
    if (no != NULL)
    {
        printf("Produto Encontrado:\n");
        printf("+------------------------------------------------+\n");
        printf("| Codigo.........: %-d\n", no->conteudo.codigo_produto);
        printf("| Descricao......: %-s\n", no->conteudo.descricao_produto);
        printf("| Qtd. Estoque...: %.2f %s\n", no->conteudo.quantidade_estoque, no->conteudo.unidade_medida);
        printf("| Custo Medio R$.: %.2f\n", no->conteudo.custo_medio_unitario);
        printf("| Valor Total R$.: %.2f\n", no->conteudo.valor_total_estoque);
        printf("| Data Validade..: %s\n", no->conteudo.data_validade);
        printf("+------------------------------------------------+\n");
    }
    else
    {
        printf("Produto com o codigo %d nao encontrado.", codigo);
    }
    gotoxy(8, 25);
    printf("Pressione qualquer tecla para continuar...");
    getch();
}

void ConsultarListaProdutos(TipoListaProdutos *lista, int criterio)
{
    if (lista->Primeiro == NULL)
    {
        tela();
        gotoxy(2, 6);
        printf("Nao ha produtos cadastrados.");
        gotoxy(8, 25);
        printf("Pressione qualquer tecla...");
        getch();
        return;
    }
    if (criterio == 1)
        OrdenarListaPorCodigo(lista);
    else
        OrdenarListaPorNome(lista);
    int lin = 7;
    PonteiroNoProduto atual = lista->Primeiro;
    while (atual != NULL)
    {
        if (lin == 7)
        {
            tela();
            gotoxy(20, 3);
            if (criterio == 1)
                printf("LISTA DE PRODUTOS POR CODIGO");
            else
                printf("LISTA DE PRODUTOS POR NOME");
            gotoxy(2, 5);
            printf("Codigo Descricao                                Estoque   Validade");
            gotoxy(2, 6);
            printf("------ --------------------------------------- --------- ----------");
        }
        gotoxy(2, lin);
        printf("%-6d %-39.39s %-9.2f %-10s", atual->conteudo.codigo_produto,
               atual->conteudo.descricao_produto, atual->conteudo.quantidade_estoque, atual->conteudo.data_validade);
        lin++;
        if (lin > 22)
        {
            gotoxy(8, 25);
            printf("Pressione uma tecla para continuar...");
            getch();
            lin = 7;
        }
        atual = atual->proximo;
    }
    gotoxy(8, 25);
    printf("Fim da lista. Pressione qualquer tecla para voltar.");
    getch();
}

void RelatorioListaPrecos(TipoListaProdutos *lista)
{
    if (lista->Primeiro == NULL)
    { /*... msg lista vazia ...*/
        return;
    }
    OrdenarListaPorNome(lista);
    int lin = 7;
    PonteiroNoProduto atual = lista->Primeiro;
    while (atual != NULL)
    {
        if (lin == 7)
        {
            tela();
            gotoxy(25, 3);
            printf("RELATORIO - LISTA DE PRECOS");
            gotoxy(2, 5);
            printf("Descricao do Produto                            Preco Unit. (R$) Unid.");
            gotoxy(2, 6);
            printf("----------------------------------------------- ---------------- -----");
        }
        gotoxy(2, lin);
        printf("%-47.47s %16.2f %-5s", atual->conteudo.descricao_produto,
               atual->conteudo.custo_medio_unitario, atual->conteudo.unidade_medida);
        lin++;
        if (lin > 22)
        { /*... pausa ...*/
            lin = 7;
        }
        atual = atual->proximo;
    }
    gotoxy(8, 25);
    printf("Fim do relatorio. Pressione qualquer tecla.");
    getch();
}

void RelatorioBalancoFisicoFinanceiro(TipoListaProdutos *lista)
{
    if (lista->Primeiro == NULL)
    { /*... msg lista vazia ...*/
        return;
    }
    OrdenarListaPorNome(lista);
    int lin = 7;
    float total_geral = 0;
    PonteiroNoProduto atual = lista->Primeiro;
    while (atual != NULL)
    {
        if (lin == 7)
        {
            tela();
            gotoxy(20, 3);
            printf("RELATORIO - BALANCO FISICO/FINANCEIRO");
            gotoxy(2, 5);
            printf("Descricao do Produto                            Qtd. Estoque  Vl. Total (R$)");
            gotoxy(2, 6);
            printf("----------------------------------------------- ------------  --------------");
        }
        gotoxy(2, lin);
        printf("%-47.47s %12.2f  %14.2f", atual->conteudo.descricao_produto,
               atual->conteudo.quantidade_estoque, atual->conteudo.valor_total_estoque);
        total_geral += atual->conteudo.valor_total_estoque;
        lin++;
        if (lin > 22)
        { /*... pausa ...*/
            lin = 7;
        }
        atual = atual->proximo;
    }
    gotoxy(2, lin + 1);
    printf("----------------------------------------------------------------------------");
    gotoxy(40, lin + 2);
    printf("VALOR TOTAL GERAL DO ESTOQUE: R$ %14.2f", total_geral);
    gotoxy(8, 25);
    printf("Fim do relatorio. Pressione qualquer tecla.");
    getch();
}
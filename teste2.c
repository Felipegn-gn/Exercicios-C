/*
Autor......: Felipe Souza de Jesus Goncalves / Mateus Scacco
Data.......: 18/06/2025
Equipe.....: RA - 235291-2024 - Felipe Souza
             RA - 23530-2024 - Mateus Scacco
Objetivo...: Sistema completo de Controle de Estoque utilizando listas encadeadas.
*/

// Bibliotecas Padrão
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>

// --- Estrutura para o registro de um produto ---
// Conforme especificado no documento de requisitos.
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

// --- Estrutura para o nó da lista de produtos (simplesmente encadeada) ---
// O sistema deve usar uma lista simplesmente encadeada para produtos. 
typedef struct TipoNoProduto *PonteiroNoProduto;
typedef struct TipoNoProduto
{
    registro_produto conteudo;
    PonteiroNoProduto proximo;
} TipoNoProduto;

// --- Estrutura para a lista de produtos ---
typedef struct
{
    PonteiroNoProduto Primeiro;
    PonteiroNoProduto Ultimo;
} TipoListaProdutos;

// --- Estrutura para o registro de uma movimentação de estoque ---
// Conforme especificado no documento de requisitos.
typedef struct
{
    char data_movim[11];
    int codigo_produto_movim;
    char tipo_movim;
    float quantidade_movimentada;
    float valor_unitario_movim;
    float valor_total_movim;
} registro_movim;

// --- Estrutura para o nó da lista de movimentações (duplamente encadeada) ---
// O sistema deve usar uma lista duplamente encadeada para movimentações. 
typedef struct TipoNoMovim *PonteiroNoMovim;
typedef struct TipoNoMovim
{
    PonteiroNoMovim anterior;
    registro_movim conteudo_movim;
    PonteiroNoMovim proximo;
} TipoNoMovim;

// --- Estrutura para a lista de movimentações ---
typedef struct
{
    PonteiroNoMovim Prim;
    PonteiroNoMovim Ult;
} TipoListaMovimentacoes;

// --- Funções de Interface (simuladas para compatibilidade) ---
// O programa deverá utilizar a tela Padrao definida. 
void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

void limpar() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void tela() {
    limpar();
    gotoxy(1, 1); printf("+----------------------------------------------------------------------------+");
    gotoxy(1, 2); printf("| UNICV - ESTRUTURA DE DADOS - PROF. RODNEY                                  |");
    gotoxy(1, 3); printf("|                SISTEMA DE CONTROLE DE ESTOQUE                              |");
    gotoxy(1, 4); printf("+----------------------------------------------------------------------------+");
    gotoxy(1, 24);printf("+----------------------------------------------------------------------------+");
    gotoxy(1, 25);printf("| MSG: ");
    gotoxy(8, 25);
}


// --- Protótipos de Funções ---

// Inicialização
void InicializarListaProdutos(TipoListaProdutos *lista);
void InicializarListaMovimentacoes(TipoListaMovimentacoes *lista);

// Persistência de Dados
void SalvarDadosProdutos(TipoListaProdutos *lista, const char *nome_arquivo);
void CarregarDadosProdutos(TipoListaProdutos *lista, const char *nome_arquivo);
void SalvarDadosMovimentacoes(TipoListaMovimentacoes *lista, const char *nome_arquivo);
void CarregarDadosMovimentacoes(TipoListaMovimentacoes *lista, const char *nome_arquivo);

// Busca e Ordenação
PonteiroNoProduto BuscarProdutoPorCodigo(TipoListaProdutos *lista, int codigo);
void OrdenarListaPorCodigo(TipoListaProdutos *lista);
void OrdenarListaPorNome(TipoListaProdutos *lista);

// Gestão de Produtos (Cadastro, Inserção, Remoção, Alteração)
void gerenciarInsercao(TipoListaProdutos *lista);
int obterDadosProduto(registro_produto *produto, TipoListaProdutos *lista);
void InserirProdutoInicio(TipoListaProdutos *lista, registro_produto produto);
void InserirProdutoFinal(TipoListaProdutos *lista, registro_produto produto);
void InserirProdutoPosicao(TipoListaProdutos *lista, registro_produto produto, int posicao);
void gerenciarExclusao(TipoListaProdutos *lista);
int removerProdutoInicio(TipoListaProdutos *lista);
int removerProdutoFinal(TipoListaProdutos *lista);
int removerProdutoPosicao(TipoListaProdutos *lista, int posicao);
void AlterarProduto(TipoListaProdutos *lista);

// Gestão de Movimentações
void CadastrarMovimentacoes(TipoListaMovimentacoes *lista, TipoListaProdutos *listaProdutos);
void ListarMovimentacoes(TipoListaMovimentacoes *lista, TipoListaProdutos *listaProdutos);

// Relatórios
void MenuConsultas(TipoListaProdutos *lista);
void ConsultarListaProdutos(TipoListaProdutos *lista, int criterio);
void ConsultarProdutoPorCodigoUI(TipoListaProdutos *lista);
void RelatorioListaPrecos(TipoListaProdutos *lista);
void RelatorioBalancoFisicoFinanceiro(TipoListaProdutos *lista);

// Menus e Principal
void menuPrincipal();
void menuProdutos(TipoListaProdutos *lista);
void menuMovimentacao(TipoListaMovimentacoes *lista, TipoListaProdutos *listaProdutos);


// --- Função Principal ---

int main() {
    TipoListaProdutos listaDeProdutos;
    TipoListaMovimentacoes listaDeMovimentacoes;
    int opcao;

    InicializarListaProdutos(&listaDeProdutos);
    InicializarListaMovimentacoes(&listaDeMovimentacoes);

    // Os dados deverão ser lidos de um arquivo de registros no início do programa. 
    CarregarDadosProdutos(&listaDeProdutos, "produtos.txt");
    CarregarDadosMovimentacoes(&listaDeMovimentacoes, "movimentacoes.txt");

    do {
        menuPrincipal();
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1:
                menuProdutos(&listaDeProdutos);
                break;
            case 2:
                menuMovimentacao(&listaDeMovimentacoes, &listaDeProdutos);
                break;
            case 3:
                // Ao finalizar o programa o Sistema deverá gravar em disco os dados. 
                SalvarDadosProdutos(&listaDeProdutos, "produtos.txt");
                SalvarDadosMovimentacoes(&listaDeMovimentacoes, "movimentacoes.txt");
                gotoxy(8, 25);
                printf("Sistema finalizado. Dados salvos com sucesso!");
                getch();
                break;
            default:
                gotoxy(8, 25);
                printf("Opcao invalida! Pressione qualquer tecla.");
                getch();
        }
    } while (opcao != 3);

    limpar();
    return 0;
}

// --- Implementação dos Menus ---

void menuPrincipal() {
    tela();
    gotoxy(28, 6); printf("MENU PRINCIPAL");
    gotoxy(25, 10); printf("1 - Menu Cadastro de Produto");
    gotoxy(25, 12); printf("2 - Menu Movimentacao de Estoque");
    gotoxy(25, 14); printf("3 - Finalizar o Programa");
    gotoxy(8, 25); printf("Digite sua opcao: ");
}

void menuProdutos(TipoListaProdutos *lista) {
    int opcao;
    do {
        tela();
        gotoxy(28, 6); printf("MENU PRODUTO");
        // Opções de inclusão: Inicio, Posição e Final da lista. 
        gotoxy(25, 8);  printf("1 - Cadastrar Produto (Inserir)");
        // Opções de exclusão: Inicio, Posição e Final da lista. 
        gotoxy(25, 10); printf("2 - Remover Produto (Excluir)");
        gotoxy(25, 12); printf("3 - Consultar/Listar Produtos");
        gotoxy(25, 14); printf("4 - Alterar dados do Produto");
        gotoxy(25, 16); printf("5 - Relatorio - Lista de Precos");
        gotoxy(25, 18); printf("6 - Relatorio - Balanco Fisico/Financeiro");
        gotoxy(25, 20); printf("0 - Retornar ao Menu Principal");
        gotoxy(8, 25); printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch (opcao) {
            case 1: gerenciarInsercao(lista); break;
            case 2: gerenciarExclusao(lista); break;
            case 3: MenuConsultas(lista); break;
            case 4: AlterarProduto(lista); break;
            case 5: RelatorioListaPrecos(lista); break;
            case 6: RelatorioBalancoFisicoFinanceiro(lista); break;
            case 0: break;
            default:
                gotoxy(8, 25);
                printf("Opcao invalida! Pressione qualquer tecla.");
                getch();
        }
    } while (opcao != 0);
}

void menuMovimentacao(TipoListaMovimentacoes *listaMovim, TipoListaProdutos *listaProd) {
    int opcao;
    do {
        tela();
        gotoxy(22, 6); printf("MENU MOVIMENTACAO DE ESTOQUE");
        // Opções de movimentação: entrada e saída de produtos. 
        gotoxy(25, 10); printf("1 - Cadastrar Movimentacao (Entrada/Saida)");
        gotoxy(25, 12); printf("2 - Listar Movimentacoes");
        gotoxy(25, 14); printf("0 - Retornar ao Menu Principal");
        gotoxy(8, 25); printf("Digite sua opcao: ");
        scanf("%d", &opcao);
        fflush(stdin);

        switch(opcao) {
            case 1: CadastrarMovimentacoes(listaMovim, listaProd); break;
            case 2: ListarMovimentacoes(listaMovim, listaProd); break;
            case 0: break;
            default:
                gotoxy(8, 25);
                printf("Opcao invalida! Pressione qualquer tecla.");
                getch();
        }
    } while (opcao != 0);
}


// --- Implementação das Funções do Sistema ---

// Funções de Inicialização
void InicializarListaProdutos(TipoListaProdutos *lista) {
    lista->Primeiro = NULL;
    lista->Ultimo = NULL;
}

void InicializarListaMovimentacoes(TipoListaMovimentacoes *lista) {
    lista->Prim = NULL;
    lista->Ult = NULL;
}

// Funções de Persistência (Arquivo)
void SalvarDadosProdutos(TipoListaProdutos *lista, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        perror("ERRO: Nao foi possivel abrir o arquivo para salvar os dados.");
        return;
    }
    PonteiroNoProduto atual = lista->Primeiro;
    while (atual != NULL) {
        fprintf(arquivo, "%d;%s;%s;%s;%f;%f;%f\n",
                atual->conteudo.codigo_produto, atual->conteudo.descricao_produto,
                atual->conteudo.unidade_medida, atual->conteudo.data_validade,
                atual->conteudo.quantidade_estoque, atual->conteudo.custo_medio_unitario,
                atual->conteudo.valor_total_estoque);
        atual = atual->proximo;
    }
    fclose(arquivo);
}

void CarregarDadosProdutos(TipoListaProdutos *lista, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        return; // Arquivo não existe ainda, normal na primeira execução.
    }
    InicializarListaProdutos(lista);
    registro_produto produto_lido;
    while (fscanf(arquivo, "%d;%49[^;];%3[^;];%10[^;];%f;%f;%f\n",
                  &produto_lido.codigo_produto, produto_lido.descricao_produto,
                  produto_lido.unidade_medida, produto_lido.data_validade,
                  &produto_lido.quantidade_estoque, &produto_lido.custo_medio_unitario,
                  &produto_lido.valor_total_estoque) == 7)
    {
        InserirProdutoFinal(lista, produto_lido); // Usa a função de inserção para popular a lista
    }
    fclose(arquivo);
}

void SalvarDadosMovimentacoes(TipoListaMovimentacoes *lista, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para salvar movimentações!");
        return;
    }
    PonteiroNoMovim atual = lista->Prim;
    while(atual != NULL) {
        fprintf(arquivo, "%s;%d;%c;%f;%f;%f\n",
            atual->conteudo_movim.data_movim, atual->conteudo_movim.codigo_produto_movim,
            atual->conteudo_movim.tipo_movim, atual->conteudo_movim.quantidade_movimentada,
            atual->conteudo_movim.valor_unitario_movim, atual->conteudo_movim.valor_total_movim);
        atual = atual->proximo;
    }
    fclose(arquivo);
}

void CarregarDadosMovimentacoes(TipoListaMovimentacoes *lista, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) return;
    InicializarListaMovimentacoes(lista);
    registro_movim movim_lida;
    while(fscanf(arquivo, "%10[^;];%d;%c;%f;%f;%f\n",
            movim_lida.data_movim, &movim_lida.codigo_produto_movim,
            &movim_lida.tipo_movim, &movim_lida.quantidade_movimentada,
            &movim_lida.valor_unitario_movim, &movim_lida.valor_total_movim) == 6)
    {
        PonteiroNoMovim novo = (PonteiroNoMovim)malloc(sizeof(TipoNoMovim));
        if(novo == NULL) {
            perror("ERRO FATAL: Falha de memoria ao carregar movimentacoes.");
            fclose(arquivo);
            return;
        }
        novo->conteudo_movim = movim_lida;
        novo->proximo = NULL;
        novo->anterior = lista->Ult;
        if(lista->Prim == NULL) {
            lista->Prim = novo;
        } else {
            lista->Ult->proximo = novo;
        }
        lista->Ult = novo;
    }
    fclose(arquivo);
}


// Funções de Gestão de Produtos
PonteiroNoProduto BuscarProdutoPorCodigo(TipoListaProdutos *lista, int codigo) {
    PonteiroNoProduto atual = lista->Primeiro;
    while (atual != NULL) {
        if (atual->conteudo.codigo_produto == codigo) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

int obterDadosProduto(registro_produto *produto, TipoListaProdutos *lista) {
    int codigo_valido = 0;
    // Layout da tela de cadastro. 
    gotoxy(25, 8); printf("Codigo do Produto..........: ");
    do {
        gotoxy(55, 8); printf("               ");
        gotoxy(55, 8);
        if (scanf("%d", &produto->codigo_produto) != 1) {
            fflush(stdin);
            gotoxy(8, 25); printf("ERRO: Codigo deve ser um numero. Pressione uma tecla.");
            getch();
            gotoxy(8, 25); printf("                                                     ");
            continue;
        }
        if (produto->codigo_produto <= 0) {
            gotoxy(8, 25); printf("ERRO: Codigo deve ser positivo. Pressione uma tecla.");
            getch();
            gotoxy(8, 25); printf("                                                     ");
        } else if (BuscarProdutoPorCodigo(lista, produto->codigo_produto) != NULL) {
            gotoxy(8, 25); printf("ERRO: Codigo ja cadastrado. Tente outro.");
            getch();
            gotoxy(8, 25); printf("                                       ");
        } else {
            codigo_valido = 1;
        }
    } while (!codigo_valido);
    fflush(stdin);

    gotoxy(25, 9); printf("Descricao do Produto.......: ");
    gotoxy(55, 9); fgets(produto->descricao_produto, 50, stdin);
    produto->descricao_produto[strcspn(produto->descricao_produto, "\n")] = 0;

    gotoxy(25, 10); printf("Unidade de Medida (Ex: UN): ");
    gotoxy(55, 10); fgets(produto->unidade_medida, 4, stdin);
    produto->unidade_medida[strcspn(produto->unidade_medida, "\n")] = 0;

    gotoxy(25, 11); printf("Data de Validade (DD/MM/AAAA): ");
    gotoxy(55, 11); fgets(produto->data_validade, 11, stdin);
    produto->data_validade[strcspn(produto->data_validade, "\n")] = 0;

    // Campos de estoque devem ser iniciados com zero. 
    produto->quantidade_estoque = 0;
    produto->custo_medio_unitario = 0;
    produto->valor_total_estoque = 0;

    gotoxy(8, 25); printf("Confirmar cadastro deste produto? (S/N): ");
    char confirma = toupper(getch());
    return (confirma == 'S');
}

void gerenciarInsercao(TipoListaProdutos *lista) {
    int opcao, posicao;
    registro_produto produto;
    
    tela();
    gotoxy(28, 6); printf("CADASTRAR PRODUTO");
    if (!obterDadosProduto(&produto, lista)) {
        gotoxy(8, 25); printf("                                             ");
        gotoxy(8, 25); printf("Cadastro cancelado pelo usuario.");
        getch();
        return;
    }
    
    tela();
    gotoxy(28, 6); printf("LOCAL DE INSERCAO");
    gotoxy(25, 10); printf("1. Inserir no INICIO da lista");
    gotoxy(25, 12); printf("2. Inserir no FINAL da lista");
    gotoxy(25, 14); printf("3. Inserir por POSICAO");
    gotoxy(8, 25); printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1: InserirProdutoInicio(lista, produto); break;
        case 2: InserirProdutoFinal(lista, produto); break;
        case 3:
            gotoxy(8, 25); printf("                                      ");
            gotoxy(8, 25); printf("Digite a POSICAO para inserir: ");
            scanf("%d", &posicao);
            InserirProdutoPosicao(lista, produto, posicao);
            break;
        default:
            gotoxy(8, 25); printf("Opcao invalida! Insercao cancelada.");
            getch();
    }
}

void InserirProdutoInicio(TipoListaProdutos *lista, registro_produto produto) {
    PonteiroNoProduto novo = (PonteiroNoProduto)malloc(sizeof(TipoNoProduto));
    if (novo == NULL) {
        gotoxy(8, 25); printf("ERRO FATAL: Falha ao alocar memoria."); getch(); return;
    }
    novo->conteudo = produto;
    novo->proximo = lista->Primeiro;
    lista->Primeiro = novo;
    if (lista->Ultimo == NULL) {
        lista->Ultimo = novo;
    }
    gotoxy(8, 25); printf("Produto inserido no INICIO com sucesso!"); getch();
}

void InserirProdutoFinal(TipoListaProdutos *lista, registro_produto produto) {
    PonteiroNoProduto novo = (PonteiroNoProduto)malloc(sizeof(TipoNoProduto));
    if (novo == NULL) {
         gotoxy(8, 25); printf("ERRO FATAL: Falha ao alocar memoria."); getch(); return;
    }
    novo->conteudo = produto;
    novo->proximo = NULL;
    if (lista->Primeiro == NULL) {
        lista->Primeiro = novo;
        lista->Ultimo = novo;
    } else {
        lista->Ultimo->proximo = novo;
        lista->Ultimo = novo;
    }
    // Apenas para carregamento silencioso
    if (strcmp(produto.descricao_produto, "") != 0) {
        gotoxy(8, 25); printf("Produto inserido no FINAL com sucesso!"); getch();
    }
}

void InserirProdutoPosicao(TipoListaProdutos *lista, registro_produto produto, int posicao) {
    if (posicao <= 1) { InserirProdutoInicio(lista, produto); return; }
    PonteiroNoProduto atual = lista->Primeiro;
    PonteiroNoProduto anterior = NULL;
    int i = 1;
    while (atual != NULL && i < posicao) {
        anterior = atual;
        atual = atual->proximo;
        i++;
    }
    if (anterior == NULL) { InserirProdutoInicio(lista, produto); return; }
    if (atual == NULL && i == posicao) { InserirProdutoFinal(lista, produto); return; }
    if (i < posicao) {
        gotoxy(8, 25); printf("ERRO: Posicao invalida. Produto nao inserido."); getch(); return;
    }
    PonteiroNoProduto novo = (PonteiroNoProduto)malloc(sizeof(TipoNoProduto));
    if (novo == NULL) {
        gotoxy(8, 25); printf("ERRO FATAL: Falha ao alocar memoria."); getch(); return;
    }
    novo->conteudo = produto;
    novo->proximo = atual;
    anterior->proximo = novo;
    gotoxy(8, 25); printf("Produto inserido na posicao %d com sucesso!", posicao); getch();
}


void gerenciarExclusao(TipoListaProdutos *lista) {
    int opcao, posicao, resultado;
    tela();
    gotoxy(25, 8); printf("--- MENU DE EXCLUSAO ---");
    gotoxy(25, 10); printf("1. Excluir produto do INICIO da lista");
    gotoxy(25, 11); printf("2. Excluir produto do FIM da lista");
    gotoxy(25, 12); printf("3. Excluir produto por POSICAO");
    gotoxy(25, 14); printf("0. Voltar");
    gotoxy(25, 16); printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    tela();
    gotoxy(2, 6);

    switch (opcao) {
        case 1:
            resultado = removerProdutoInicio(lista);
            if (resultado == 1) printf("Produto do inicio removido com sucesso!");
            else if (resultado == 0) printf("ERRO: A lista esta vazia.");
            else printf("ERRO: Produto com estoque, nao pode ser excluido.");
            break;
        case 2:
            resultado = removerProdutoFinal(lista);
            if (resultado == 1) printf("Produto do fim removido com sucesso!");
            else if (resultado == 0) printf("ERRO: A lista esta vazia.");
            else printf("ERRO: Produto com estoque, nao pode ser excluido.");
            break;
        case 3:
            printf("Digite a POSICAO do produto a excluir: ");
            scanf("%d", &posicao);
            resultado = removerProdutoPosicao(lista, posicao);
            if (resultado == 1) printf("Produto da posicao %d removido com sucesso!", posicao);
            else if (resultado == 0) printf("ERRO: Posicao invalida.");
            else printf("ERRO: Produto com estoque, nao pode ser excluido.");
            break;
        case 0: return;
        default: printf("Opcao invalida!"); break;
    }
    gotoxy(2, 8); printf("Pressione qualquer tecla para continuar...");
    getch();
}

int removerProdutoInicio(TipoListaProdutos *lista) {
    if (lista->Primeiro == NULL) return 0; // Lista vazia
    if (lista->Primeiro->conteudo.quantidade_estoque > 0) return -1; // Produto com saldo
    PonteiroNoProduto a_remover = lista->Primeiro;
    lista->Primeiro = a_remover->proximo;
    if (lista->Primeiro == NULL) lista->Ultimo = NULL;
    free(a_remover);
    return 1;
}

int removerProdutoFinal(TipoListaProdutos *lista) {
    if (lista->Primeiro == NULL) return 0;
    if (lista->Ultimo->conteudo.quantidade_estoque > 0) return -1;
    PonteiroNoProduto a_remover = lista->Ultimo;
    if (lista->Primeiro == lista->Ultimo) {
        lista->Primeiro = NULL;
        lista->Ultimo = NULL;
    } else {
        PonteiroNoProduto penultimo = lista->Primeiro;
        while (penultimo->proximo != lista->Ultimo) {
            penultimo = penultimo->proximo;
        }
        penultimo->proximo = NULL;
        lista->Ultimo = penultimo;
    }
    free(a_remover);
    return 1;
}

int removerProdutoPosicao(TipoListaProdutos *lista, int posicao) {
    if (lista->Primeiro == NULL || posicao < 1) return 0;
    if (posicao == 1) return removerProdutoInicio(lista);
    PonteiroNoProduto anterior = lista->Primeiro;
    int i = 1;
    while (i < posicao - 1 && anterior != NULL) {
        anterior = anterior->proximo;
        i++;
    }
    if (anterior == NULL || anterior->proximo == NULL) return 0;
    PonteiroNoProduto a_remover = anterior->proximo;
    if (a_remover->conteudo.quantidade_estoque > 0) return -1;
    anterior->proximo = a_remover->proximo;
    if (a_remover == lista->Ultimo) lista->Ultimo = anterior;
    free(a_remover);
    return 1;
}

void AlterarProduto(TipoListaProdutos *lista) {
    int codigo;
    char confirma;
    tela();
    gotoxy(28, 6); printf("ALTERAR DADOS DO PRODUTO");
    gotoxy(25, 8); printf("Digite o codigo do produto a alterar: ");
    scanf("%d", &codigo);
    fflush(stdin);

    PonteiroNoProduto produtoNode = BuscarProdutoPorCodigo(lista, codigo);
    if (produtoNode == NULL) {
        gotoxy(8, 25); printf("ERRO: Produto com o codigo %d nao encontrado.", codigo);
        getch();
        return;
    }

    tela();
    gotoxy(28, 6); printf("ALTERAR DADOS DO PRODUTO (CODIGO: %d)", codigo);
    gotoxy(10, 8); printf("Descricao atual: %s", produtoNode->conteudo.descricao_produto);
    gotoxy(10, 9); printf("Nova Descricao do Produto.......: ");
    char nova_descricao[50];
    fgets(nova_descricao, 50, stdin);
    nova_descricao[strcspn(nova_descricao, "\n")] = 0;

    gotoxy(10, 11); printf("Unidade Medida atual: %s", produtoNode->conteudo.unidade_medida);
    gotoxy(10, 12); printf("Nova Unidade de Medida (Ex: UN): ");
    char nova_unidade[4];
    fgets(nova_unidade, 4, stdin);
    nova_unidade[strcspn(nova_unidade, "\n")] = 0;

    gotoxy(10, 14); printf("Data de Validade atual: %s", produtoNode->conteudo.data_validade);
    gotoxy(10, 15); printf("Nova Data de Validade (DD/MM/AAAA): ");
    char nova_data[11];
    fgets(nova_data, 11, stdin);
    nova_data[strcspn(nova_data, "\n")] = 0;

    gotoxy(8, 25); printf("Confirmar alteracoes? (S/N): ");
    confirma = toupper(getch());

    if (confirma == 'S') {
        if(strlen(nova_descricao) > 0) strcpy(produtoNode->conteudo.descricao_produto, nova_descricao);
        if(strlen(nova_unidade) > 0) strcpy(produtoNode->conteudo.unidade_medida, nova_unidade);
        if(strlen(nova_data) > 0) strcpy(produtoNode->conteudo.data_validade, nova_data);
        gotoxy(8, 25); printf("                                             ");
        gotoxy(8, 25); printf("Produto alterado com sucesso!");
    } else {
        gotoxy(8, 25); printf("                                             ");
        gotoxy(8, 25); printf("Alteracao cancelada.");
    }
    getch();
}


// Funções de Movimentação
void CadastrarMovimentacoes(TipoListaMovimentacoes *lista, TipoListaProdutos *listaProdutos) {
    registro_movim novaMovimentacao;
    tela();
    gotoxy(28, 6); printf("CADASTRO DE MOVIMENTACAO");

    // Layout da tela de cadastro de movimentação. 
    gotoxy(25, 8); printf("Data da Movimentacao (DD/MM/AAAA): ");
    scanf("%10s", novaMovimentacao.data_movim);

    gotoxy(25, 9); printf("Codigo do Produto..........: ");
    scanf("%d", &novaMovimentacao.codigo_produto_movim);
    
    PonteiroNoProduto produto = BuscarProdutoPorCodigo(listaProdutos, novaMovimentacao.codigo_produto_movim);
    if (produto == NULL) {
        gotoxy(8, 25); printf("ERRO: Produto com codigo %d nao encontrado!", novaMovimentacao.codigo_produto_movim);
        getch();
        return;
    }
    gotoxy(55, 9); printf("-> %s", produto->conteudo.descricao_produto);

    gotoxy(25, 10); printf("Tipo da Movimentacao (E/S).: ");
    scanf(" %c", &novaMovimentacao.tipo_movim);
    novaMovimentacao.tipo_movim = toupper(novaMovimentacao.tipo_movim);

    gotoxy(25, 11); printf("Quantidade Movimentada.....: ");
    scanf("%f", &novaMovimentacao.quantidade_movimentada);

    if (novaMovimentacao.tipo_movim == 'E') {
        gotoxy(25, 12); printf("Valor Unitario da Entrada..: ");
        scanf("%f", &novaMovimentacao.valor_unitario_movim);
    } else { // Para saída, o valor unitário é o custo médio atual
        novaMovimentacao.valor_unitario_movim = produto->conteudo.custo_medio_unitario;
        gotoxy(25, 12); printf("Custo Medio (Saida)........: %.2f", novaMovimentacao.valor_unitario_movim);
    }

    novaMovimentacao.valor_total_movim = novaMovimentacao.quantidade_movimentada * novaMovimentacao.valor_unitario_movim;
    gotoxy(25, 13); printf("Valor Total da Movimentacao: %.2f", novaMovimentacao.valor_total_movim);

    // Validações
    // O Saldo do Estoque não poderá ser negativo. 
    if (novaMovimentacao.tipo_movim == 'S' && produto->conteudo.quantidade_estoque < novaMovimentacao.quantidade_movimentada) {
        gotoxy(8, 25); printf("ERRO: Saldo insuficiente no estoque! (Disponivel: %.2f)", produto->conteudo.quantidade_estoque);
        getch();
        return;
    }

    // Atualização do Estoque
    if (novaMovimentacao.tipo_movim == 'E') {
        // Implementação do Cálculo de Custo Médio. 
        float valor_estoque_atual = produto->conteudo.valor_total_estoque;
        float valor_entrada = novaMovimentacao.valor_total_movim;
        float nova_quantidade_total = produto->conteudo.quantidade_estoque + novaMovimentacao.quantidade_movimentada;

        produto->conteudo.quantidade_estoque = nova_quantidade_total;
        if (nova_quantidade_total > 0) {
            // Fórmula do Custo Médio. 
            produto->conteudo.custo_medio_unitario = (valor_estoque_atual + valor_entrada) / nova_quantidade_total;
        }
        produto->conteudo.valor_total_estoque = produto->conteudo.quantidade_estoque * produto->conteudo.custo_medio_unitario;

    } else if (novaMovimentacao.tipo_movim == 'S') {
        produto->conteudo.quantidade_estoque -= novaMovimentacao.quantidade_movimentada;
        produto->conteudo.valor_total_estoque = produto->conteudo.quantidade_estoque * produto->conteudo.custo_medio_unitario;
    } else {
        gotoxy(8, 25); printf("ERRO: Tipo de movimentacao invalido (deve ser 'E' ou 'S').");
        getch();
        return;
    }

    PonteiroNoMovim novoNo = (PonteiroNoMovim)malloc(sizeof(TipoNoMovim));
    if (novoNo == NULL) {
        gotoxy(8, 25); printf("Erro ao alocar memoria para movimentacao!"); getch(); return;
    }
    novoNo->conteudo_movim = novaMovimentacao;
    novoNo->proximo = NULL;
    novoNo->anterior = lista->Ult;

    if (lista->Prim == NULL) {
        lista->Prim = novoNo;
    } else {
        lista->Ult->proximo = novoNo;
    }
    lista->Ult = novoNo;

    gotoxy(8, 25); printf("Movimentacao cadastrada com sucesso!"); getch();
}

void ListarMovimentacoes(TipoListaMovimentacoes *lista, TipoListaProdutos *listaProdutos) {
    if (lista->Prim == NULL) {
        tela();
        gotoxy(2, 6); printf("Nenhuma movimentacao registrada.\n");
        printf("\nPressione qualquer tecla para continuar..."); getch();
        return;
    }

    int lin = 7;
    PonteiroNoMovim atual = lista->Prim;
    PonteiroNoProduto produto;

    while (atual != NULL) {
        if (lin == 7) {
            tela();
            gotoxy(20, 3); printf("HISTORICO DE MOVIMENTACOES");
            gotoxy(2, 5); printf("Data       Cod. Produto                    Tipo Qtd      Vl. Unit.  Vl. Total");
            gotoxy(2, 6); printf("---------- ---- -------------------------- ---- -------- ---------- ----------");
        }
        
        produto = BuscarProdutoPorCodigo(listaProdutos, atual->conteudo_movim.codigo_produto_movim);
        char* desc_produto = (produto != NULL) ? produto->conteudo.descricao_produto : "PRODUTO NAO ENCONTRADO";
        
        gotoxy(2, lin); printf("%-10s", atual->conteudo_movim.data_movim);
        gotoxy(13, lin); printf("%-4d", atual->conteudo_movim.codigo_produto_movim);
        gotoxy(18, lin); printf("%-26.26s", desc_produto);
        gotoxy(45, lin); printf("%-4c", atual->conteudo_movim.tipo_movim);
        gotoxy(50, lin); printf("%-8.2f", atual->conteudo_movim.quantidade_movimentada);
        gotoxy(59, lin); printf("%-10.2f", atual->conteudo_movim.valor_unitario_movim);
        gotoxy(70, lin); printf("%-10.2f", atual->conteudo_movim.valor_total_movim);

        lin++;
        if (lin > 22) {
            gotoxy(8, 25); printf("Pressione uma tecla para continuar..."); getch();
            lin = 7;
        }
        atual = atual->proximo;
    }
    gotoxy(8, 25); printf("                                              ");
    gotoxy(8, 25); printf("Fim da lista. Pressione qualquer tecla para voltar.");
    getch();
}



// Funções de Consulta e Relatórios
void OrdenarListaPorCodigo(TipoListaProdutos *lista) {
    if (lista->Primeiro == NULL) return;
    int trocou;
    PonteiroNoProduto ptr1;
    PonteiroNoProduto lptr = NULL;
    do {
        trocou = 0;
        ptr1 = lista->Primeiro;
        while (ptr1->proximo != lptr) {
            if (ptr1->conteudo.codigo_produto > ptr1->proximo->conteudo.codigo_produto) {
                registro_produto temp = ptr1->conteudo;
                ptr1->conteudo = ptr1->proximo->conteudo;
                ptr1->proximo->conteudo = temp;
                trocou = 1;
            }
            ptr1 = ptr1->proximo;
        }
        lptr = ptr1;
    } while (trocou);
}

void OrdenarListaPorNome(TipoListaProdutos *lista) {
    if (lista->Primeiro == NULL) return;
    int trocou;
    PonteiroNoProduto ptr1;
    PonteiroNoProduto lptr = NULL;
    do {
        trocou = 0;
        ptr1 = lista->Primeiro;
        while (ptr1->proximo != lptr) {
            if (stricmp(ptr1->conteudo.descricao_produto, ptr1->proximo->conteudo.descricao_produto) > 0) {
                registro_produto temp = ptr1->conteudo;
                ptr1->conteudo = ptr1->proximo->conteudo;
                ptr1->proximo->conteudo = temp;
                trocou = 1;
            }
            ptr1 = ptr1->proximo;
        }
        lptr = ptr1;
    } while (trocou);
}

void MenuConsultas(TipoListaProdutos *lista) {
    int opcao;
    do {
        tela();
        gotoxy(28, 8); printf("--- MENU DE CONSULTAS ---");
        gotoxy(25, 10); printf("1. Consultar por Codigo Especifico");
        gotoxy(25, 12); printf("2. Listar Todos (ordenado por Codigo)");
        gotoxy(25, 13); printf("3. Listar Todos (ordenado por Nome)");
        gotoxy(25, 15); printf("0. Voltar ao Menu Anterior");
        gotoxy(25, 17); printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
            fflush(stdin);
        }

        switch (opcao) {
            case 1: ConsultarProdutoPorCodigoUI(lista); break;
            case 2: ConsultarListaProdutos(lista, 1); break; // Critério 1 = Código
            case 3: ConsultarListaProdutos(lista, 2); break; // Critério 2 = Nome
            case 0: break;
            default:
                gotoxy(25, 19); printf("Opcao invalida! Pressione qualquer tecla.");
                getch();
        }
    } while (opcao != 0);
}

void ConsultarProdutoPorCodigoUI(TipoListaProdutos *lista) {
    int codigo_busca;
    tela();
    gotoxy(2, 5); printf("Digite o codigo do produto a buscar: ");
    scanf("%d", &codigo_busca);

    PonteiroNoProduto no_encontrado = BuscarProdutoPorCodigo(lista, codigo_busca);
    tela();
    gotoxy(2, 6);
    if (no_encontrado != NULL) {
        printf("Produto Encontrado:\n");
        printf("--------------------------------------------------\n");
        printf(" Codigo.........: %d\n", no_encontrado->conteudo.codigo_produto);
        printf(" Descricao......: %s\n", no_encontrado->conteudo.descricao_produto);
        printf(" Unidade Medida.: %s\n", no_encontrado->conteudo.unidade_medida);
        printf(" Data Validade..: %s\n", no_encontrado->conteudo.data_validade);
        printf(" Qtd. Estoque...: %.2f\n", no_encontrado->conteudo.quantidade_estoque);
        printf(" Custo Medio R$.: %.2f\n", no_encontrado->conteudo.custo_medio_unitario);
        printf(" Valor Total R$.: %.2f\n", no_encontrado->conteudo.valor_total_estoque);
        printf("--------------------------------------------------\n\n");
    } else {
        printf("Produto com o codigo %d nao encontrado.\n", codigo_busca);
    }
    printf("Pressione qualquer tecla para continuar...");
    getch();
}

void ConsultarListaProdutos(TipoListaProdutos *lista, int criterio) {
    if (lista->Primeiro == NULL) {
        tela();
        gotoxy(2, 6); printf("Nao ha produtos cadastrados na lista.\n");
        printf("\nPressione qualquer tecla para continuar..."); getch(); return;
    }
    if (criterio == 1) OrdenarListaPorCodigo(lista);
    else OrdenarListaPorNome(lista);

    int lin = 7;
    PonteiroNoProduto atual = lista->Primeiro;
    while (atual != NULL) {
        if (lin == 7) {
            tela();
            gotoxy(20, 3);
            if (criterio == 1) printf("LISTA DE PRODUTOS - ORDENADO POR CODIGO");
            else printf("LISTA DE PRODUTOS - ORDENADO POR NOME");
            gotoxy(2, 5); printf("Codigo Descricao                                Estoque   Validade");
            gotoxy(2, 6); printf("------ --------------------------------------- --------- ----------");
        }
        gotoxy(2, lin); printf("%-6d", atual->conteudo.codigo_produto);
        gotoxy(9, lin); printf("%-39.39s", atual->conteudo.descricao_produto);
        gotoxy(51, lin); printf("%-9.2f", atual->conteudo.quantidade_estoque);
        gotoxy(62, lin); printf("%-10s", atual->conteudo.data_validade);
        lin++;
        if (lin > 22) {
            gotoxy(8, 25); printf("Pressione uma tecla para continuar..."); getch();
            lin = 7;
        }
        atual = atual->proximo;
    }
    gotoxy(8, 25); printf("                                              ");
    gotoxy(8, 25); printf("Fim da lista. Pressione qualquer tecla para voltar.");
    getch();
}

void RelatorioListaPrecos(TipoListaProdutos *lista) {
    if (lista->Primeiro == NULL) {
        tela();
        gotoxy(2, 6); printf("Nao ha produtos cadastrados para gerar relatorio.\n");
        printf("\nPressione qualquer tecla para continuar..."); getch(); return;
    }
    // Relação de todos os produtos do estoque em ordem alfabética. 
    OrdenarListaPorNome(lista);

    int lin = 7;
    PonteiroNoProduto atual = lista->Primeiro;
    while (atual != NULL) {
        if (lin == 7) {
            tela();
            gotoxy(25, 3); printf("RELATORIO - LISTA DE PRECOS");
            gotoxy(2, 5); printf("Descricao do Produto                            Preco Unit. (R$) Unid.");
            gotoxy(2, 6); printf("----------------------------------------------- ---------------- -----");
        }
        gotoxy(2, lin); printf("%-47.47s", atual->conteudo.descricao_produto);
        gotoxy(50, lin); printf("%16.2f", atual->conteudo.custo_medio_unitario);
        gotoxy(68, lin); printf("%-5s", atual->conteudo.unidade_medida);
        lin++;
        if (lin > 22) {
            gotoxy(8, 25); printf("Pressione uma tecla para continuar..."); getch();
            lin = 7;
        }
        atual = atual->proximo;
    }
    gotoxy(8, 25); printf("                                              ");
    gotoxy(8, 25); printf("Fim do relatorio. Pressione qualquer tecla para voltar.");
    getch();
}

void RelatorioBalancoFisicoFinanceiro(TipoListaProdutos *lista) {
    if (lista->Primeiro == NULL) {
        tela();
        gotoxy(2, 6); printf("Nao ha produtos cadastrados para gerar balanco.\n");
        printf("\nPressione qualquer tecla para continuar..."); getch(); return;
    }
    // Relação de todos os produtos do estoque, em ordem alfabética. 
    OrdenarListaPorNome(lista);

    int lin = 7;
    float valor_total_geral = 0;
    PonteiroNoProduto atual = lista->Primeiro;

    while (atual != NULL) {
        if (lin == 7) {
            tela();
            gotoxy(20, 3); printf("RELATORIO - BALANCO FISICO/FINANCEIRO");
            gotoxy(2, 5); printf("Descricao do Produto                            Qtd. Estoque  Vl. Total (R$)");
            gotoxy(2, 6); printf("----------------------------------------------- ------------  --------------");
        }
        gotoxy(2, lin); printf("%-47.47s", atual->conteudo.descricao_produto);
        gotoxy(50, lin); printf("%12.2f", atual->conteudo.quantidade_estoque);
        gotoxy(65, lin); printf("%14.2f", atual->conteudo.valor_total_estoque);
        valor_total_geral += atual->conteudo.valor_total_estoque;
        lin++;
        if (lin > 22) {
            gotoxy(8, 25); printf("Pressione uma tecla para continuar..."); getch();
            lin = 7;
        }
        atual = atual->proximo;
    }
    
    gotoxy(2, lin + 1); printf("----------------------------------------------------------------------------");
    gotoxy(40, lin + 2); printf("VALOR TOTAL GERAL DO ESTOQUE: R$ %14.2f", valor_total_geral);
    
    gotoxy(8, 25); printf("                                              ");
    gotoxy(8, 25); printf("Fim do relatorio. Pressione qualquer tecla para voltar.");
    getch();
}
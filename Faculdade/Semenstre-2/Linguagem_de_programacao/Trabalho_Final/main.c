#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Str_max 101
#define BUFFER_SIZE 256

typedef struct Livro{
    char * titulo;
    char* autor;
    long long ISBN;
    int dia,mes,ano;
}Livro;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void removerQuebraLinha(char* str) {
    size_t i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}


typedef struct No{
    Livro livro;
    struct No* prox;
}No;

No * alocarNo(){
    No* no = (No*)malloc(sizeof(No));
    no->prox = NULL;
    no->livro.titulo = (char *)malloc(Str_max);
    no->livro.autor = (char *)malloc(Str_max);
    return no;
}

void lerLivro(No* no){
    if(no == NULL) return;
    limparBuffer();
    printf("Titulo: ");
    fgets(no->livro.titulo,Str_max,stdin);
    removerQuebraLinha(no->livro.titulo);//Removendo \n da string lida por fgets

    printf("Autor: ");
    fgets(no->livro.autor,Str_max,stdin);
    removerQuebraLinha(no->livro.autor);//Removendo \n da string lida por fgets

    printf("ISBN: ");
    scanf("%I64d",&no->livro.ISBN);//Usei I64d para ler int grande porque lld não esta funcionando na minha máquina
    limparBuffer();

    printf("Data publicacao (dd/mm/aaaa):");
    scanf("%d/%d/%d",&no->livro.dia,&no->livro.mes,&no->livro.ano);

    printf("\n---------------------\n");
    printf("\n");
    limparBuffer();
}

void novoLivro(No** lista){
    No * novo = alocarNo();
    lerLivro(novo);
    novo->prox = *lista;
    *lista = novo;
}

void removerLivro(No** lista,long long isbn){
    if(*lista == NULL)return;
    
    No * atual = *lista;
    No * anterior = NULL;
    
    while(atual->livro.ISBN != isbn && atual != NULL){
        anterior = atual;
        atual = atual->prox;
    }
    
    if(atual == NULL){
        printf("Livro não encontrado");
        return;
    }
    
    if (anterior == NULL) {
        *lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual->livro.autor);
    free(atual->livro.titulo);
    free(atual);
    return;
}


void imprimirLivro(No* lista){
		No* atual = lista;
    while(atual != NULL){
		printf("\n--- Livro ---\n");
        printf("Titulo: %s\n",atual->livro.titulo);
        printf("Autor: %s\n",atual->livro.autor);
        printf("Data de Publicação: %02d/%02d/%d\n",atual->livro.dia,atual->livro.mes,atual->livro.ano);
        printf("ISBN: %I64d\n",atual->livro.ISBN);
        atual= atual->prox;
    }
    printf("\n---------------------\n");
}

void lerESalvarDeAqruivo(No ** lista, char* caminho){

    FILE *arquivo = fopen(caminho, "r");

    // Verifica se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
    }

    // Operações com o arquivo...
    char linha[BUFFER_SIZE];
    while (fgets(linha, sizeof(linha), arquivo)) {
        
        long long isbn;
        char titulo[Str_max];
        char autor[Str_max];
        int d, m, a;
    
        //Verifica se leu 6 campos
        if (sscanf(linha, "%I64d;%100[^;];%100[^;];%d/%d/%d",
            &isbn, titulo, autor, &d, &m, &a) == 6) {
        }
            
        No *novo = alocarNo();
        novo->livro.ISBN = isbn;
        strcpy( novo->livro.titulo,titulo);
        strcpy(novo->livro.autor,autor);
        novo->livro.dia = d;
        novo->livro.mes = m;
        novo->livro.ano =a;

        printf(autor);

        novo->prox = *lista;
        *lista = novo;

        
    }
    // Fecha o arquivo
    fclose(arquivo);
}

void sobrEscreverArquivo(No ** lista, char* caminho){
    No * atual = *lista;
    
    FILE *arquivo = fopen(caminho, "w");

    if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
    }

    while(atual != NULL){
        fprintf(arquivo,"%I64d;%s;%s;%02d/%02d/%d\n",
            atual->livro.ISBN,
            atual->livro.titulo,
            atual->livro.autor,
            atual->livro.dia,
            atual->livro.mes,
            atual->livro.ano
        );


        atual = atual->prox;
    }


    fclose(arquivo);
    printf("Dados escritos com sucesso!\n");
}


int main() {
    No * lista = NULL;
    int escolhaMenu = 0;
    long long isbnToRemove = 0;
    lerESalvarDeAqruivo(&lista,"..\\Biblioteca.txt");

    while(escolhaMenu != 4){
        printf("-----Menu-----\n1)Adicionar livro\n2)Listar todos os livros\n3)Remover livro por ISBN\n4)Sair\n");
        scanf("%d",&escolhaMenu);
        switch (escolhaMenu){
        case 1:
            novoLivro(&lista);
            break;
        case 2:
            imprimirLivro(lista);
            break;
        case 3: 
            printf("Insira o ISBN do livro a ser removido: ");
            scanf("%I64d",&isbnToRemove);
            removerLivro(&lista,isbnToRemove);
            break;
        case 4:
            printf("Finalizando...");
            break;
        default:
            printf("Valor inválido, tente novamente!\n");
            break;
        }
    }    

    sobrEscreverArquivo(&lista,"..\\Biblioteca.txt");//Sobreescrevendo antes de finalizar o programa
    return 0;
}
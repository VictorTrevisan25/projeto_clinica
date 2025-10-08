#ifndef PET_H_INCLUDED
#define PET_H_INCLUDED

#include <time.h>
#include <string.h>


typedef struct nascimento
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct pet
{
    int ID;
    char nome[50];
    char especie[30];
    int idade;
    Data data;
    int prioridade; // 0 emergencia 1 normal
} Pet;

typedef struct no
{
    Pet info;
    struct no *prox;
} No;

typedef struct fila
{
    No *ini;
    No *fim;
} Fila;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int idExiste(Fila *f, int id)
{
    No *aux = f->ini;
    while(aux != NULL)
    {
        if(aux->info.ID == id) return 1;
        aux = aux->prox;
    }
    return 0;
}

int gerarID(Fila *f) {
    int id;
    do {
        id = 100 + rand() % 900; // rand () limita a gerar numero entre 100 e 999
    } while(idExiste(f, id)); //roda enquanto o ID ja existeir
    return id;
}

void imprimeDados(Pet p)
{
    printf("\n");
     printf("ID: %d | Nome: %s | Especie: %s | Idade: %d | Nasc: %d/%d/%d | Prioridade: %d",
           p.ID, p.nome, p.especie, p.idade, p.data.dia, p.data.mes, p.data.ano, p.prioridade);
    printf("\n");
}


Fila* CriaFila()
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

int verificaVazia(Fila *f)
{
    return (f->ini == NULL); // Retorna 1 vazia, 0 caso contrario
}

No* insereFim(No *fim, Pet a)
{
    No *p = (No*)malloc(sizeof(No));
    p->info = a;
    p->prox = NULL;
    if(fim != NULL)
    {
        fim->prox = p;
    }
    return p;
}

void InsereFila(Fila *f, Pet v)
{
    f->fim = insereFim(f->fim, v);
    if(f->ini == NULL)
    {
        f->ini = f->fim;
    }
}

No* retiraInicio (No* ini)
{
    No* p = ini->prox;
    free(ini);
    return p;
}

Pet* retiraFila(Fila *f)
{
   No *v;
   if(verificaVazia(f)== 1)
   {
       printf("a Fila esta vazia.");
       exit(0);
   }
   v->info = f->ini->info;
   f->ini=retiraInicio(f->ini);
   if(f->ini == NULL)
   {
       f->fim=NULL; //a fila ficou vazia
   }
    return v;
}

void imprimeFila(Fila *f)
{
    if (verificaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }

    No *aux = f->ini;
    while(aux != NULL)
    {

        printf("ID: %d | Nome: %s | Especie: %s | Idade: %d | Nasc: %d/%d/%d | Prioridade: %d\n",
               aux->info.ID, aux->info.nome, aux->info.especie, aux->info.idade,
               aux->info.data.dia, aux->info.data.mes, aux->info.data.ano, aux->info.prioridade);
        aux = aux->prox;
    }
}

void apagaFila(Fila *f)
{
    No *p = f->ini;
    while(p != NULL)
    {
        No *aux = p->prox;
        free(p);
        p = aux;
    }
    free(f);
}

void novoPet(Fila *f, Fila *id, int prioridade)
{
    Pet novoPetInfo;

    novoPetInfo.ID = gerarID(id);

    printf("Nome: ");
    fgets(novoPetInfo.nome, sizeof(novoPetInfo.nome), stdin);
    novoPetInfo.nome[strcspn(novoPetInfo.nome, "\n")] = '\0'; // Remove a quebra de linha

    printf("Especie: ");
    fgets(novoPetInfo.especie, sizeof(novoPetInfo.especie), stdin);
    novoPetInfo.especie[strcspn(novoPetInfo.especie, "\n")] = '\0';

    printf("Idade: ");
    scanf("%d", &novoPetInfo.idade);

    printf("Data de nascimento (DD MM AAAA): ");
    scanf("%d %d %d", &novoPetInfo.data.dia, &novoPetInfo.data.mes, &novoPetInfo.data.ano);

    // Limpa o buffer para a proxima iteracao do menu principal
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    novoPetInfo.prioridade = prioridade;

    InsereFila(f, novoPetInfo);

    // Adiciona o ID usado na fila de IDs
    Pet auxID;
    auxID.ID = novoPetInfo.ID;
    InsereFila(id, auxID);
}


void proxAtendimento(Fila *f, Fila *fa)
{
    if (verificaVazia(f)) {
        printf("Fila de atendimento vazia.\n");
        return;
    }
    No *v;
    v = retiraFila(f);
    Pet petAtendido = v->info;
    printf("Pet a ser atendido:\n");
    imprimeDados(petAtendido);
    InsereFila(fa, petAtendido); // Insere na fila de atendidos
    printf("\nPet movido para a fila de atendidos.\n");
}

int procurarPorId(Fila *f, int id)
{
    No *aux = f->ini;
    while(aux != NULL)
    {
        if(aux->info.ID == id)
        {
            printf("\nPet Encontrado:\n");
            imprimeDados(aux->info);
            return 0; // Encontrado
        }
        aux = aux->prox;
    }
    return 1; // Nao encontrado
}


int procuraPorNome(Fila *f, char n[20])
{
    No *aux = f->ini;
    while(aux != NULL)
    {
        if(strcmp(aux->info.nome, n) == 0) // strcmp retorna 0 se as strings sao iguais
        {
            printf("\nPet Encontrado:\n");
            imprimeDados(aux->info);
            return 0; // Encontrado
        }
        aux = aux->prox;
    }
    return 1; // Nao encontrado
}

#endif

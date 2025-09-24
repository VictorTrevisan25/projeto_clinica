#ifndef PET_H_INCLUDED
#define PET_H_INCLUDED
#include <time.h>

typedef struct nascimento
{
    int dia;
    int mes;
    int ano;
}Data;
typedef struct pet
{
    int ID;
    char nome[20];
    char especie[20];
    int idade;
    Data data;
    int prioridade; //0 emergencia 1 normal
}Pet;

typedef struct no
{
    Pet info;
    struct no *prox;
}No;

typedef struct fila
{
    No *ini;
    No *fim;
}Fila;

Fila* CriaFila ()
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

//função para verificar se uma fila esta vazia
int verificaVazia(Fila *f)
{
    return f->ini == NULL ? 1:0;
}

No* insereFim(No *fim , Pet a)
{
    No *p = (No*)malloc(sizeof(No));
    p->info=a;
    p->prox=NULL;
    if(fim != NULL)
    {
        fim->prox=p;
    }
    return p;
}

void InsereFila(Fila *f ,Pet v)
{
    f->fim= insereFim(f->fim,v);
    if(f->fim==NULL)
    {
        f->ini=f->fim; //se a fila estiver vazia ele iguala o fim e o inicio ja que o elemento inserido sera o primeiro
    }
}

No* retiraInicio(No *ini)
{
    No *p = ini->prox;
    free(ini);
    return p;
}
No* retiraFila(Fila *f)
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
    No *aux;
    aux= f->ini;
    printf("A fila segue o seguinte padrão: ID | Nome | Espécie | Idade | Data de Nascimento | Prioridade\n");
    printf("\n\t\t");
    while(aux != NULL)
    {
        printf("%d | %c | %c | %d | %d/%d/%d | Prioridade: %d", aux->info.ID, aux->info.nome , aux->info.especie , aux->info.idade , aux->info.data.dia, aux->info.data.mes, aux->info.data.ano, aux->info.prioridade);
        aux=aux->prox;
    }
    printf("\n");

}

Fila* apagaFila(Fila *f)
{
    No *p = f->ini;
    while(p != NULL)
    {
        No *aux = p->prox;
        free(p);
        p=aux;
    }
    free(f);
    return NULL;
}


void novoPet(Fila *f, Fila *id, int prioridade)
{
    No *novo = (No*)malloc(sizeof(No));
    if(novo ==NULL)
    {
        printf("erro ao alocar memoria");
        exit(0);
    }

    novo->info.ID= gerarID(id);
    int c;
    while((c= getchar())!= '\n' && c!= EOF);

    printf("Nome:\n");
    fgets(novo->info.nome, sizeof(novo->info.nome), stdin);
    novo->info.nome[strcspn(novo->info.nome, "\n")] = '\0';

    printf("Especie:\n ");
    fgets(novo->info.especie , sizeof(novo->info.especie), stdin);
    novo->info.especie[ strcspn(novo->info.especie, "\n")] = '\0';

    printf("Idade:\n");
    scanf("%d", &novo->info.idade);

    printf("Data de nascimento.\n Dia:");
    scanf("%d",&novo->info.data.dia);

    printf("\n Mes:");
    scanf("%d",&novo->info.data.mes);

    printf("\n Ano:");
    scanf("%d",&novo->info.data.ano);

    novo->info.prioridade = prioridade;
    Pet auxID;
    auxID.ID = novo->info.ID;
    InsereFila(f, novo->info);
    InsereFila(id ,auxID );
}

void imprimeDados(Fila *f, int v)
{
    No *aux;
    aux=f->ini;
    printf("A fila segue o seguinte padrão: ID | Nome | Espécie | Idade | Data de Nascimento | Prioridade\n");
    for(v ; v>0 ; v--)
    {
        aux=aux->prox;
    }
    printf("%d | %c | %c | %d | %d/%d/%d | Prioridade: %d", aux->info.ID, aux->info.nome , aux->info.especie , aux->info.idade , aux->info.data.dia, aux->info.data.mes, aux->info.data.ano, aux->info.prioridade);
}

void proxAtendimento(Fila *f,Fila *fa)
{
    No *v;
    printf("Proximo paciente a ser atendido:");
    imprimeDados(f,1);
    v=retiraFila(f);
    InsereFila(fa,v->info);

}

int procurarPorId(Fila *f , int id)
{
    No *aux;
    int cont = 1;
    aux=f->ini;
    while(aux != NULL)
    {
        if(aux->info.ID == id)
        {
            printf("Pet Encontrado \n");
            imprimeDados(f,cont);
            return 0;
        }
        aux=aux->prox;
        cont ++;
    }
    return 1;
}
int procuraPorNome(Fila *f, char n[20])
{
    No *aux;
    int cont = 1;
    aux=f->ini;
    while(aux != NULL)
    {
        if(aux->info.nome == n)
        {
            printf("Pet Encontrado");
            imprimeDados(f , cont);
            return 0;
        }
        aux=aux->prox;
        cont ++;
    }
    return 1;
}


//função de criar ID
int gerarID(Fila *f) {
    int id;
    do {
        id = 100 + rand() % 900;
    } while(idExiste(f, id));  // repete enquanto o ID já existir
    return id;
}

int idExiste(Fila *f,int id)
{
    No *aux=f->ini;
    while(aux != NULL)
    {
        if(aux->info.ID == id) return 1;
        aux=aux->prox;
    }
    return 0;
}
#endif


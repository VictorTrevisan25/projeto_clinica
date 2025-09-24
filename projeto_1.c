#include <stdlib.h>
#include <stdio.h>
#include "PET.h"

int main()
{
    srand(time(NULL)); //inicializa gerador de numeros aleatorios para o ID
    int op,valor,a;
    char n[20];
    Pet *aux;
    Fila *FE , *FN , *FA ,*ID;
    FE= CriaFila();
    FN=CriaFila();
    FA= CriaFila();
    ID= CriaFila();



    do
    {
        system("cls");
        printf("\t\t\t MENU\n");
        printf("1- Inserir um Pet na Fila de Atendimento.\n");
        printf("2- Atender Pet.\n");
        printf("3- Buscar por Pet.\n");
        printf("4- Imprimir Fila de Pacientes.\n");
        printf("5- Imprimir Informações do proximo paciente.\n");
        printf("6- Imprimir pacientes Atendidos.\n");
        printf("7- Finalizar sistema.\n");
        printf("OBS: pacientes da fila de Emergencia = 0 e os da fila normal = 1\n");

        scanf("%d",&op);

        switch(op)
        {
        case 1: //inserir um Pet
            printf("Esse Pet deve ir para qual fila?\n 0- Emergencia \n 1-Normal \n");
            scanf("%d",&valor);
            printf("Informe as informacoes do Pet\n");
            if(valor==0)
            {
                novoPet(FE, ID ,0);
            }
            else
            {
                novoPet(FN,ID,1);
            }

            system("pause");
            break;

        case 2://atender pet
            if(verificaVazia(FE)== 1)
               {
                   if(verificaVazia(FN) == 1)
                    {
                        printf("Nao ha pets nas filas de atendimento.");
                        system("pause");
                        break;
                    }
                    else
                    {
                        printf("Proximo pet a ser Atendido esta na Fila Normal: \n ");
                        proxAtendimento(FN,FA);
                        system("pause");
                        break;
                    }
               }
               else
               {
                    printf("Proximo pet a ser Atendido esta Na Lista de Emergencia: \n ");
                    proxAtendimento(FE,FA);
               }
            system("pause");
            break;
        case 3://buscar pet por nome ou id
            printf("Como deseja procurar o Pet 1- ID 2- Nome");
            scanf("%d",&valor);
            if(n == 1)
            {
                printf("Digite o ID do pet:");
                scanf("%d",&valor);
                valor = procurarPorId(FE , valor);
                if(valor == 1)
                {
                    procurarPorId(FN , valor);
                    if(valor == 1)
                    {
                        valor = procurarPorId(FA , valor);
                        if(valor == 0)
                        {
                            printf("Esse Pet ja foi Atendido");
                        }
                    }

                }
                printf("Pet Não Encontrado");
            }
            else
            {
                printf("Digite o nome do Pet:");
                scanf("%c",&n);
                valor = procuraPorNome(FE , n);
                if(valor == 1)
                {
                    valor = procuraPorNome(FN , n);
                    if(valor == 1)
                    {
                        valor = procuraPorNome(FA , n);
                        if(valor == 0)
                        {
                            printf("Esse Pet ja foi Atendido");
                        }
                    }
                }
                printf("Pet Não Encontrado");
            }
            system("pause");
            break;
        case 4://imprimir pets e informações deles da lista normal e de emergencia
            printf("As Informações dos pets seguem a seguinte ordem: \n ID | Nome | Espécie | Idade | Data de Nascimento | Prioridade");
            printf("FILA DE EMERGENCIA:\n");
            imprimeFila(FE);
            printf("\n FILA NORMAL:\n");
            imprimeFila(FN);
            system("pause");
            break;
        case 5://imprimir prox paciente a ser atendido
            printf("Proximo pet a ser atendido:");
            //verifica se a lista de emergencia esta vazia
            valor = verificaVazia(FE);
            if(valor == 0)
            {
                //impeime 1 elemento info lista emergencia
                imprimeDados(FE,1);
            }
            else
            {
                //imprime 1 elemento info  lista normal
                imprimeDados(FN,1);
            }
            system("pause");
            break;
        case 6://imprimir lista de atendidos
            imprimeFila(FA);
            system("pause");
            break;

            }
    }while(op =! 7);

    apagaFila(FE);
    apagaFila(FN);
    apagaFila(FA);
}

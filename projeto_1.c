#include <stdlib.h>
#include <stdio.h>
#include "PET.h"

int main()
{
    srand(time(NULL)); //inicializa gerador de numeros aleatorios para o ID
    int op,valor,a;
    char n[50];
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
        printf("5- Imprimir Informa��es do proximo paciente.\n");
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
                printf("Pet N�o Encontrado");
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
                printf("Pet N�o Encontrado");
            }
            system("pause");
            break;
        case 4://imprimir pets e informacoes deles da lista normal e de emergencia
            printf("As Informa��es dos pets seguem a seguinte ordem: \n ID | Nome | Esp�cie | Idade | Data de Nascimento | Prioridade");
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
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include "PET.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL)); // Inicializa gerador de numeros aleatorios para o ID
    int op, valor;
    char nomeBusca[20];
    Fila *FE, *FN, *FA, *ID;
    FE = CriaFila();
    FN = CriaFila();
    FA = CriaFila();
    ID = CriaFila();

    do
    {
        system("cls"); // limpar tela no Windows
        printf("=============================================\n");
        printf("        CLINICA VETERINARIA - MENU           \n");
        printf("=============================================\n");
        printf("1 - Inserir um Pet na Fila de Atendimento\n");
        printf("2 - Atender Pet\n");
        printf("3 - Buscar por Pet\n");
        printf("4 - Imprimir Fila de Pacientes\n");
        printf("5 - Ver Proximo Paciente\n");
        printf("6 - Imprimir Pacientes Atendidos\n");
        printf("7 - Finalizar Sistema\n");
        printf("---------------------------------------------\n");
        printf("OBS: Emergencia = 0 | Normal = 1\n");
        printf("=============================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &op);
        limparBuffer();

        switch(op)
        {
            case 1: // Inserir um Pet
                printf("\n---------------------------------------------\n");
                printf(">> Inserir Pet na Fila <<\n");
                printf("Esse Pet deve ir para qual fila?\n");
                printf("0 - Emergencia\n1 - Normal\n");
                printf("---------------------------------------------\n");
                scanf("%d", &valor);
                limparBuffer();

                printf("\nInforme as informacoes do Pet:\n");
                if(valor == 0)
                    novoPet(FE, ID, 0);
                else
                    novoPet(FN, ID, 1);

                printf("\n[OK] Pet inserido com sucesso!\n");
                system("pause");
                break;

            case 2: // Atender pet
                printf("\n---------------------------------------------\n");
                if(verificaVazia(FE) == 0)
                {
                    printf("[ATENDIMENTO] Proximo pet da Fila de Emergencia:\n");
                    proxAtendimento(FE, FA);
                }
                else if (verificaVazia(FN) == 0)
                {
                    printf("[ATENDIMENTO] Proximo pet da Fila Normal:\n");
                    proxAtendimento(FN, FA);
                }
                else
                {
                    printf("[ERRO] Nao ha pets nas filas de atendimento.\n");
                }
                printf("---------------------------------------------\n");
                system("pause");
                break;

            case 3: // Buscar pet
                printf("\n---------------------------------------------\n");
                printf(">> Buscar Pet <<\n");
                printf("1 - Buscar por ID\n2 - Buscar por Nome\n");
                printf("---------------------------------------------\n");
                scanf("%d", &valor);
                limparBuffer();

                if(valor == 1)
                {
                    int idBusca;
                    printf("Digite o ID do pet: ");
                    scanf("%d", &idBusca);
                    limparBuffer();

                    if (procurarPorId(FE, idBusca) == 1 &&
                        procurarPorId(FN, idBusca) == 1 &&
                        procurarPorId(FA, idBusca) == 1)
                        printf("\n[ERRO] Pet com ID %d nao encontrado.\n", idBusca);
                }
                else
                {
                    printf("Digite o nome do Pet: ");
                    fgets(nomeBusca, sizeof(nomeBusca), stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                    if (procuraPorNome(FE, nomeBusca) == 1 &&
                        procuraPorNome(FN, nomeBusca) == 1 &&
                        procuraPorNome(FA, nomeBusca) == 1)
                        printf("\n[ERRO] Pet com nome '%s' nao encontrado.\n", nomeBusca);
                }
                printf("---------------------------------------------\n");
                system("pause");
                break;

            case 4: // Imprimir filas
                printf("\n---------------------------------------------\n");
                printf(">> FILA DE EMERGENCIA <<\n");
                imprimeFila(FE);
                printf("\n>> FILA NORMAL <<\n");
                imprimeFila(FN);
                printf("---------------------------------------------\n");
                system("pause");
                break;

            case 5: // Proximo paciente
                printf("\n---------------------------------------------\n");
                printf(">> Proximo Pet a ser atendido <<\n");
                if(verificaVazia(FE) == 0)
                    imprimeDados(FE->ini->info);
                else if(verificaVazia(FN) == 0)
                    imprimeDados(FN->ini->info);
                else
                    printf("[ERRO] Nenhuma fila com pets aguardando.\n");
                printf("---------------------------------------------\n");
                system("pause");
                break;

            case 6: // Atendidos
                printf("\n---------------------------------------------\n");
                printf(">> FILA DE ATENDIDOS <<\n");
                imprimeFila(FA);
                printf("---------------------------------------------\n");
                system("pause");
                break;

            case 7:
                printf("\n[SAINDO] Finalizando o sistema...\n");
                break;

            default:
                printf("\n[ERRO] Opcao invalida! Tente novamente.\n");
                system("pause");
                break;
        }
    } while(op != 7);

    apagaFila(FE);
    apagaFila(FN);
    apagaFila(FA);
    apagaFila(ID);

    return 0;
}

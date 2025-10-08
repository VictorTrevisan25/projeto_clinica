#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include "PET.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL)); // Inicializa gerador de numeros aleatorios para o ID
    int op, valor;
    char nomeBusca[50];
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

                    if (procurarPorId(FE, idBusca, FA) == 1 &&
                        procurarPorId(FN, idBusca, FA) == 1 &&
                        procurarPorId(FA, idBusca, FA) == 1)
                        printf("\n[ERRO] Pet com ID %d nao encontrado.\n", idBusca);
                }
                else
                {
                    printf("Digite o nome do Pet: ");
                    fgets(nomeBusca, sizeof(nomeBusca), stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                    if (procuraPorNome(FE, nomeBusca, FA) == 1 &&
                        procuraPorNome(FN, nomeBusca, FA) == 1 &&
                        procuraPorNome(FA, nomeBusca, FA) == 1)
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

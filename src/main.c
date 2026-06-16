#include "../include/feed.h"
#include "../include/post.h"
#include "../include/utils.h"
#include <stdio.h>

void mostrar_menu() {
    printf("\n=== Administracao FlashGram ===\n");
    printf("1. Adicionar novo post manualmente\n");
    printf("2. Ver, editar ou remover post\n");
    printf("3. Apresentar feed ordenado\n");
    printf("4. Guardar feed final\n");
    printf("0. Sair do programa\n");
}

int main() {

    int opcao;

    do {
        mostrar_menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
            case 1:
            {

                break;
            }

            case 2:
            {

                break;
            }

            case 3:
            {

                break;
            }

            case 4:
            {

                break;
            }
        
            case 0:
                printf("A encerrar sistema");
                break;

            default:
                printf("Opcao Inválida");
                break;
        }

    } while (opcao != 0);
}
#include "../include/feed.h"
#include "../include/post.h"
#include <stdio.h>
#include <string.h>

void mostrar_menu() {
    printf("\n=== Administracao FlashGram ===\n");
    printf("1. Adicionar novo post\n");
    printf("2. Alterar post\n");
    printf("3. Remover post\n");
    printf("4. Listar post\n");
    printf("5. Apresentar feed\n");
    printf("6. Guardar feed\n");
    printf("0. Sair do programa\n");
    printf("Escolha uma opcao: ");
}

int main() {
    int opcao, id;
    char desc[150], infl[50];
    int gostos, coments, views;

    do {
        mostrar_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                getchar(); // Limpar o '\n' deixado pelo scanf da opcao
                printf("\n--- Adicionar Novo Post ---\n");
                
                printf("Descricao: ");
                fgets(desc, sizeof(desc), stdin);
                desc[strcspn(desc, "\n")] = 0; 

                printf("Influencer: ");
                fgets(infl, sizeof(infl), stdin);
                infl[strcspn(infl, "\n")] = 0;

                printf("Gostos: ");
                scanf("%d", &gostos);
                
                printf("Comentarios: ");
                scanf("%d", &coments);
                
                printf("Visualizacoes: ");
                scanf("%d", &views);

                guardar_post(0, desc, infl, gostos, coments, views); 
                break;

            case 2:
                printf("ID do post a alterar: ");
                scanf("%d", &id);
                getchar(); 

                printf("\n--- Alterar Post [%d] ---\n", id);
                
                printf("Descricao: ");
                fgets(desc, sizeof(desc), stdin);
                desc[strcspn(desc, "\n")] = 0; 

                printf("Influencer: ");
                fgets(infl, sizeof(infl), stdin);
                infl[strcspn(infl, "\n")] = 0;

                printf("Gostos: ");
                scanf("%d", &gostos);
                
                printf("Comentarios: ");
                scanf("%d", &coments);
                
                printf("Visualizacoes: ");
                scanf("%d", &views);

                guardar_post(id, desc, infl, gostos, coments, views);
                break;

            case 3:
                printf("ID do post a remover: ");
                scanf("%d", &id);
                remover_post(id);
                break;

            case 4:
                printf("ID do post a listar: ");
                scanf("%d", &id);
                listar_post(id);
                break;

            case 5:
                calcularFeedOrdenado();
                break;

            case 6:
                guardarFeedOrdenado();
                break;
        
            case 0:
                printf("A encerrar sistema...\n");
                limpar_memoria_posts(); 
                break;

            default:
                printf("Opcao Invalida!\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}
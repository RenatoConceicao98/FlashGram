#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/file_manager.h"

Post** carregar_dados(const char *ficheiro_posts, const char *ficheiro_pop, int *total) {
    FILE *fp = fopen(ficheiro_posts, "r");
    if (!fp) return NULL;

    Post **lista = NULL;
    int count = 0;
    char linha[256];

    while (fgets(linha, sizeof(linha), fp)) {
        // Alocação dinâmica do array de ponteiros
        Post **temp = realloc(lista, (count + 1) * sizeof(Post *));
        if (!temp) break;
        lista = temp;

        // Supondo uma função criar_post definida em post.c
        // Aqui farias o parsing da linha com strtok e criarias o post
        lista[count] = criar_post(1, "Exemplo", "Influencer", "Categoria", 100, 50, 10);
        count++;
    }
    
    *total = count;
    fclose(fp);
    return lista;
}
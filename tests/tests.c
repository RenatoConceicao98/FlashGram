#include <stdio.h>
#include <assert.h>
#include "../include/post.h"
#include "../include/feed.h"

// =========================================================
// TESTE DE UNIDADE
// =========================================================
void test_unidade_popularidade() {
    Post p;
    p.id = 1;

    int resultado, id=1;
    resultado = listar_post(id);

    assert(resultado == 1);
    printf("Função listar validada\n");
}

void criar_arquivos_teste() {
    FILE *f1 = fopen("posts.csv", "w");
    if (f1) {
        fprintf(f1, "1;Aprender C e espetacular;TechGuru;Educacao\n");
        fprintf(f1, "2;Foto do meu Peugeot 308;CarLover;Auto\n");
        fclose(f1);
    }

    FILE *f2 = fopen("popularidade.csv", "w");
    if (f2) {
        fprintf(f2, "1;1000;150;20\n");
        fprintf(f2, "2;500;50;5\n");
        fclose(f2);
    }
}


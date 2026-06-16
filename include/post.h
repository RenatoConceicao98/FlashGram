#ifndef POST_H
#define POST_H

typedef struct {
    int id;
    char descricao[150];
    char influencer[50];
    char categoria[50];
    int visualizacoes;
    int gostos;
    int comentarios;
    float popularidade;
} Post;

void guardar_post(int id);

void remover_post(int id);

void listar_post(int id);

void limpar_memoria_posts();

#endif
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


int carregar_dados(); 

void guardar_post(int id, const char *descricao, const char *influencer, int gostos, int comentarios, int visualizacoes);

void remover_post(int id);

int listar_post(int id);

void limpar_memoria_posts();

int obter_total_posts();

Post* obter_feed_principal();

#endif
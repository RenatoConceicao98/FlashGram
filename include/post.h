#ifndef POST_H
#define POST_H

typedef struct {
    int id;
    char *descricao;
    char *influencer;
    char *categoria;
    float popularidade;
    // ... campos de popularidade
} Post;

// No post.c, terás algo como:
Post **lista_posts; // Array de ponteiros para alocação dinâmica
int total_posts;

/**
 * Vai carregar todos os posts guardados nos ficheiros para a memória
 * 
 * Retorno: Apenas retornará uma mensagem se algo correr mal para alertar, senão não terá retorno
*/
carregar_posts();


/**
 * Vai carregar os restantes dados relativos aos posts para a memória
 * 
 * Retorno: Apenas retornará uma mensagem se algo correr mal para alertar, senão não terá retorno
*/
carregar_popularidade();





#endif
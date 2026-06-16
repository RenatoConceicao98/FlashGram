#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/post.h" 


static Post *post = NULL; 
static int total_posts = 0;


static int obterProxID() {
    int maior_id = 0;
    
    for (int i = 0; i < total_posts; i++) {
        if (post[i].id > maior_id) {
            maior_id = post[i].id;
        }
    }
    
    return maior_id + 1;
}

int carregar_dados() {

    //Abrir post.csv
    FILE *f_posts = fopen("posts.csv", "r");
    if (f_posts == NULL) {
        printf("Erro ao abrir posts.csv\n");
        return 0;
    }

    //Abrir popilaridade.csv
    FILE *f_pop = fopen("popularidade.csv", "r");
    if (f_pop == NULL) {
        printf("Erro ao abrir popularidade.csv\n");
        return 0; 
    }

    // Ignora a primeira linha (cabeçalho)
    fscanf(f_posts, "%*[^\n]\n");
    fscanf(f_pop, "%*[^\n]\n");

    while (!feof(f_posts)) {
        Post *temp = realloc(post, (total_posts + 1) * sizeof(Post));
        if (temp == NULL) {
            printf("Erro: Memoria insuficiente.\n");
            break;
        }
        post = temp;

        // Lê os 4 dados principais do post
        int lidos = fscanf(f_posts, "%d;%d;%d;%d\n",
                           &post[total_posts].id,
                           post[total_posts].descricao,
                           post[total_posts].influencer,
                           post[total_posts].categoria);

        if (lidos == 4) {
            post[total_posts].visualizacoes = 0;
            post[total_posts].gostos = 0;
            post[total_posts].comentarios = 0;
            post[total_posts].popularidade = 0.0f;
            total_posts++;
        }
        else {
            printf("Erro ao ler dados");
        }

    }
    
    while (!feof(f_pop)) {
        int id_temp, views_temp, gostos_temp, coments_temp;
        
        // Lê as 4 métricas para variáveis temporárias
        int lidos = fscanf(f_pop, "%d;%d;%d;%d\n", &id_temp, &views_temp, &gostos_temp, &coments_temp);

        if (lidos == 4) {
            // Procura o post com este ID
            for (int i = 0; i < total_posts; i++) {
                if (post[i].id == id_temp) {
                    post[i].visualizacoes = views_temp;
                    post[i].gostos = gostos_temp;
                    post[i].comentarios = coments_temp;
                    
                    // Recalcula a popularidade com os novos dados
                    post[i].popularidade = (0.5f * post[i].gostos + 0.3f * post[i].comentarios + 0.2f * post[i].visualizacoes) / 100.0f;
                    break; 
                }
            }
        }
        else {
            printf("Erro ao ler dados");
        }

    }

    //Fechar ficheiros
    fclose(f_pop);
    fclose(f_posts);

    printf("Foram carregados %d posts com sucesso!\n", total_posts);
    return 1;
}

void guardar_post(int id) {
    int idx = -1;

    if (id > 0) {
        for (int i = 0; i < total_posts; i++) {
            if (post[i].id == id) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            printf("Post não encontrado.\n");
            return;
        }

    } 
    else 
    {
        Post *temp = realloc(post, (total_posts + 1) * sizeof(Post));
        if (temp == NULL) {
            printf("Memória insuficiente\n");
            return;
        }
        post = temp; 
        idx = total_posts;
        post[idx].id = obterProxID();
    }

    getchar(); 

    printf("Descricao: ");
    fgets(post[idx].descricao, sizeof(post[idx].descricao), stdin);
    post[idx].descricao[strcspn(post[idx].descricao, "\n")] = 0; 

    printf("Influencer: ");
    fgets(post[idx].influencer, sizeof(post[idx].influencer), stdin);
    post[idx].influencer[strcspn(post[idx].influencer, "\n")] = 0;

    printf("Gostos: ");
    scanf("%d", &post[idx].gostos);
    
    printf("Comentarios: ");
    scanf("%d", &post[idx].comentarios);
    
    printf("Visualizacoes: ");
    scanf("%d", &post[idx].visualizacoes);

    post[idx].popularidade = (0.5f * post[idx].gostos + 0.3f * post[idx].comentarios + 0.2f * post[idx].visualizacoes) / 100.0f;

    if (id == 0) {
        total_posts++;
        printf("Post adicionado com sucesso!\n");
    } else {
        printf("Post alterado com sucesso!\n");
    }
}


void remover_post(int id) {

    if (total_posts == 0 || post == NULL) {
        printf("O feed esta vazio\n");
        return;
    }

    int idRemover = -1;

    for (int i = 0; i < total_posts; i++) {
        if (post[i].id == id) {
            idRemover = i;
        }
    }

    // Se o ciclo terminou e continua a -1, o ID nao existe
    if (idRemover == -1) {
        printf(" Post nao encontrado.\n");
        return;
    }

    // Deslocar todos os posts seguintes uma posicao para tras
    for (int i = idRemover; i < total_posts - 1; i++) {
        post[i] = post[i + 1];
    }

    // Reduzir o contador de posts
    total_posts--;

    // 5. Ajustar a memoria dinamica 
    if (total_posts > 0) {
        Post *temp = realloc(post, total_posts * sizeof(Post));
        if (temp != NULL) {
            post = temp; // Atualiza para o novo bloco encolhido
        }
    } else {
        free(post);
        post = NULL;
    }

    printf(" Post com ID %d removido \n", id);
}


void listar_post(int id) {

    if (total_posts == 0 || post == NULL) {
        printf("Nao ha posts para apresentar\n");
        return;
    }

    for (int i = 0; i < total_posts; i++) {
        
        if (post[i].id == id) {
            printf("Influencer : %s\n", post[i].influencer);
            printf("Descricao  : %s\n", post[i].descricao);
            printf("Categoria  : %s\n", post[i].categoria);
            printf("Popularidade   : %d Gostos | %d Comentarios | %d Views\n", post[i].gostos, post[i].comentarios, post[i].visualizacoes);
            printf("Popularidade: %.2f\n", post[i].popularidade);
            printf("-------------------------------\n");
            
            return; 
        }
    }
    printf("Post nao foi encontrado no sistema.\n");
}


void limpar_memoria_posts() {

    if (post != NULL) {
        free(post);
        post = NULL;
        total_posts = 0;
        printf("Memoria libertada\n");
    }
}
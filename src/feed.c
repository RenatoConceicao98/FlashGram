#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "feed.h"
#include "post.h"


int comparar_posts(const void *a, const void *b) {
    // Fazemos o cast genérico para a struct Post
    Post *p1 = (Post *)a;
    Post *p2 = (Post *)b;

    // Regra A: Maior popularidade primeiro
    if (p1->popularidade < p2->popularidade) return 1;
    if (p1->popularidade > p2->popularidade) return -1;

    // Regra B: Desempate por ID (maior ID = mais recente = primeiro)
    if (p1->id < p2->id) return 1;
    if (p1->id > p2->id) return -1;

    return 0;
}



void calcularFeedOrdenado() {
    int total = obter_total_posts();
    Post *feed = obter_feed_principal();

    if (total == 0 || feed == NULL) {
        printf("[AVISO] Nao existem posts para apresentar no feed.\n");
        return;
    }

    // 1. Ordenação rápida nativa do C
    qsort(feed, total, sizeof(Post), comparar_posts);
    
    // 

    // 2. Regra dos "3 Influencers" (Evitar monopólio no feed)
    for (int i = 0; i < total - 2; i++) {
        if (strcmp(feed[i].influencer, feed[i+1].influencer) == 0 &&
            strcmp(feed[i].influencer, feed[i+2].influencer) == 0) {
            
            // Procurar o próximo influencer diferente
            int idx_troca = -1;
            for (int j = i + 3; j < total; j++) {
                if (strcmp(feed[i].influencer, feed[j].influencer) != 0) {
                    idx_troca = j;
                    break;
                }
            }

            // Fazer a troca (Swap) das structs inteiras
            if (idx_troca != -1) {
                Post temp = feed[i+2];
                feed[i+2] = feed[idx_troca];
                feed[idx_troca] = temp;
            }
        }
    }

    printf("\n======================================================\n");
    printf("                  FEED FLASHGRAM                      \n");
    printf("======================================================\n");
    for (int i = 0; i < total; i++) {
        printf("[%03d] Pop: %.2f | %-15s | %s\n", 
               feed[i].id, 
               feed[i].popularidade, 
               feed[i].influencer, 
               feed[i].descricao);
    }
    printf("======================================================\n");
}



void guardarFeedOrdenado() {
    int total = obter_total_posts();
    Post *feed = obter_feed_principal();

    if (total == 0 || feed == NULL) {
        printf("[ERRO] Feed vazio, nada para guardar.\n");
        return;
    }

    // Abre o ficheiro em modo de escrita ("w" - cria de novo ou substitui)
    FILE *f = fopen("feed_ordenado.csv", "w");
    if (f == NULL) {
        printf("[ERRO] Nao foi possivel criar o ficheiro feed_ordenado.csv\n");
        return;
    }

    // Escrever o cabeçalho
    fprintf(f, "ID;Descricao;Influencer;Categoria;Views;Gostos;Comentarios;Popularidade\n");

    // Escrever os dados já ordenados pelo calcularFeedOrdenado()
    for (int i = 0; i < total; i++) {
        fprintf(f, "%d;%s;%s;%s;%d;%d;%d;%.2f\n",
                feed[i].id,
                feed[i].descricao,
                feed[i].influencer,
                feed[i].categoria,
                feed[i].visualizacoes,
                feed[i].gostos,
                feed[i].comentarios,
                feed[i].popularidade);
    }

    fclose(f);
    printf("Feed final guardado no ficheiro 'feed_ordenado.csv'.\n");
}
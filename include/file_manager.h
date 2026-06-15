#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "post.h"

// Função para ler o CSV e retornar um array dinâmico de posts
Post** carregar_dados(const char *ficheiro_posts, const char *ficheiro_pop, int *total);

// Função para guardar o feed final
void guardar_feed(const char *nome_ficheiro, Post **feed, int total);

#endif
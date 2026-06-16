#ifndef FEED_H
#define FEED_H

typedef struct {
    int id;
    int pontuacao;
    int id_post;
} Feed; 

void calcularFeedOrdenado();

void guardarFeedOrdenado();


#endif
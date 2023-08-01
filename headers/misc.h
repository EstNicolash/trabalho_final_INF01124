#ifndef MISC_H
#define MISC_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PLAYERS_FILE "files/players.csv"
#define TAGS_FILE "files/tags.csv"
#define MINIRATING_FILE "files/minirating.csv"
#define RATING_FILE "files/rating.csv"
#define NAME_LEN 100    // Tamanho máximo para guardar nome do jagador
#define POSITIONS_LEN 4 // Tamanho máximo para guardar uma posição do jogador
#define POSITIONS_NUM 14 // Tamanho máximo de posições do futebol
#define ID 10            // Máximo de chars de uma string fifa_id
#define NUM_TESTES 4
#define BUFFER_SIZE 150

#define PRIME 11 // Número primo usado na função de hashing
typedef unsigned int uint;
extern uint hash_func(int key, uint size);
extern uint a_pow10[10]; // Potencias de 10 até 10^10

struct count_rating_data {
  int fifa_id;
  int total_rating;
  double rating_sum;
};
typedef struct count_rating_data CountRatingData;
#endif

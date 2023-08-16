#ifndef MISC_H
#define MISC_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define PLAYERS_FILE "files/players.csv"
#define TAGS_FILE "files/tags.csv"
#define MINIRATING_FILE "files/minirating.csv"
#define RATING_FILE "files/rating.csv"
#define NAME_LEN 100     // Tamanho máximo para guardar nome do jagador
#define POSITIONS_LEN 40 // Tamanho máximo para guardar uma posição do jogador
#define POSITIONS_NUM 14 // Tamanho máximo de posições do futebol
#define ID 10            // Máximo de chars de uma string fifa_id
#define NUM_TESTES 4
#define BUFFER_SIZE 150
#define USER_INPUT 20

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

struct palyer_data {
  int fifa_id;
  char name[NAME_LEN];
  char positions[POSITIONS_LEN];
  CountRatingData *rating;
  //  Série de ponteiros para estruturas de dados diferentes?
};
typedef struct palyer_data PlayerData;

struct user_review {
  int fifa_id;
  double rating;
};
typedef struct user_review user_review;
struct user_data {
  int user_id;
  // ReviewList *review_list
};

#endif

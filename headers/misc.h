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
#define NAME_LEN 100      // Tamanho máximo para guardar nome do jagador
#define POSITIONS_LEN 40  // Tamanho máximo para guardar uma posição do jogador
#define POSITIONS_NUM 14  // Tamanho máximo de posições do futebol
#define ID 10             // Máximo de chars de uma string fifa_id
#define NUM_TESTES 4
#define BUFFER_SIZE 150
#define USER_INPUT 20
#define HEAP_SIZE 20

#define PRIME 11  // Número primo usado na função de hashing
typedef unsigned int uint;
extern uint hash_func(int key, uint size);

extern uint hash_func2(int key, uint size);
extern uint a_pow10[10];  // Potencias de 10 até 10^10

extern uint debug_count;
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

////////////////////////////
struct user_review {
    int fifa_id;
    double rating;
};
typedef struct user_review UserReview;

////////////////////////////////
struct review_heap {
    int end;
    UserReview reviews[HEAP_SIZE];
};
typedef struct review_heap ReviewHeap;

/////////////////////////////
struct user_data {
    int user_id;
    ReviewHeap user_reviews;
};
typedef struct user_data UserData;

struct user_list {
    UserData user_data;
    struct user_list *next;
};
typedef struct user_list *UserList;

struct user_tag {
    int user_id;    //usuário que gerou a tag
    int sofifa_id;  //id do jogador referente à tag
    char *tag_text;
};
typedef struct user_tag UserTag;

void print_player_info(PlayerData *player);

void print_player_info_header();
void print_player_info_header_mais_rating();
void print_player_info_mais_rating(PlayerData *player, double rating);
#endif

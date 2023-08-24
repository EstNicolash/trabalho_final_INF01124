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
#define NAME_LEN 150      // Tamanho máximo para guardar nome do jagador
#define POSITIONS_LEN 40  // Tamanho máximo para guardar uma posição do jogador
#define POSITIONS_NUM 14  // Tamanho máximo de posições do futebol
#define ID 10             // Máximo de chars de uma string fifa_id
#define NUM_TESTES 4      //
#define BUFFER_SIZE 150
#define USER_INPUT 20  //Input inicial para selecionar o tipo de busca
#define HEAP_SIZE 20   //Tamanho da Heap de reviews
#define PRIME 11       // Número primo usado na função de hashing
#define POS 4          //Máximo tamanho de um string de posições
#define M 10           //?
#define NUM_POS 13     //Número de posições do futebol

typedef unsigned int uint;

//Funções de uso geral
extern uint hash_func(int key, uint size);
extern uint hash_func2(int key, uint size);
extern uint a_pow10[10];  // Potencias de 10 até 10^10
extern uint debug_count;  //Contador global para debugar

/* Tipo CountRatingData
 *
 * Guarda o todo da avaliação de um jogador
 *
 * Estrutura:
 *  - fifa_id: ID do jogador
 *  - total_rating: Número total de avaliações(count)
 *  - rating_sum: Soma de avaliações
 */
struct count_rating_data {
    int fifa_id;
    int total_rating;
    double rating_sum;
};
typedef struct count_rating_data CountRatingData;

/* Tipo PlayerData
 *
 * Guarda as informações gerais de um jogador
 *
 * Estrutura:
 *  - fifa_id: ID do jogador
 *  - name: Nome do jogador
 *  - positions: Texto de suas posições
 *  - rating: Ponteiro para sua avaliação geral(CountRatingData)
 */
struct palyer_data {
    int fifa_id;
    char name[NAME_LEN];
    char positions[POSITIONS_LEN];
    CountRatingData *rating;
    //  Série de ponteiros para estruturas de dados diferentes?
};
typedef struct palyer_data PlayerData;

/* Tipo UserReview 
 *
 * Guarda as informações da review de um jagador por um usuário
 *
 * Estrutura:
 *  - fifa_id: ID do jogador
 *  - rating: Avaliação
 */
struct user_review {
    int fifa_id;
    double rating;
};
typedef struct user_review UserReview;

/* Tipo ReviewHeap 
 *
 * Guarda as 20 maiores avaliações de um usuário 
 *
 * Estrutura:
 *  - end: última posição com elemento válido do array 
 *  - sorted: Flag para saber se o vetor já foi ordenado
 *  - review: Vetor com as avaliações
 */
struct review_heap {
    int end;
    bool sorted;
    UserReview reviews[HEAP_SIZE];
};
typedef struct review_heap ReviewHeap;

/* Tipo UserData
 *
 * Guarda um usuário e suas avaliações  
 *
 * Estrutura:
 *  - user_id: ID do usuário
 *  - user_reviews: Avaliações feitas pelo usuário
 */
struct user_data {
    int user_id;
    ReviewHeap user_reviews;
};
typedef struct user_data UserData;

/* Tipo UseList
 *
 * Lista de dados de usuários  
 *
 * Estrutura:
 *  - user_data: dados do usuário
 *  - next: próximo elemento da lista
 */
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
char **list_tags(char tag_list[NAME_LEN], int *num_tags);
char *strlwr(char *str);
void pos_input_fix(char pos[POS], char input[POS + 2]);
void name_input_fix(char name[NAME_LEN], char input[NAME_LEN]);
int tag_input_valid(char *tag_input);
bool valid_position(char pos[POS]);
#endif

#ifndef POSITIONS_RANKING_H
#define POSITIONS_RANKING_H
#include "count_rating_hash_table.h"
#include "misc.h"

uint positions_ranking_pos_cod(char pos[POS]);

/* Tipo RatingList
 *
 * Lista que guarda de forma ordenada os reviews globais de um jogador
 * 
 * rating: Avaliação global do jogador
 * player: Ponteiro para o dado do jogador
 *
 */
struct ordered_list {
    double rating;
    PlayerData *player;
    struct ordered_list *next;
};
typedef struct ordered_list *RatingList;

/* Tipo RatingTable
 *  
 *  - Uma tabela com lista de avaliações para cada posição
 *
 */
struct rating_pos_table {
    RatingList positions_table[NUM_POS];
};

typedef struct rating_pos_table RatingTable;
void positions_ranking_list_insertion(RatingList *list, double rating, PlayerData *player);
void positions_table_insertion(RatingTable *positions_table, CountRatingHashTable *count_rating_hash_table, PlayerData *player);
RatingTable positions_ranking_init();
void positions_ranking_list_print(RatingList list, int n);

#endif

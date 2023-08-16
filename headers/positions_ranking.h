#ifndef POSITIONS_RANKING_H
#define POSITIONS_RANKING_H
#include "count_rating_hash_table.h"
#include "misc.h"
#define POS 3
#define M 10
#define NUM_POS 13
uint positions_ranking_pos_cod(char pos[POS]);
struct ordered_list {
  double rating;
  PlayerData *player;
  struct ordered_list *next;
};

typedef struct ordered_list *RatingList;

struct rating_pos_table {
  RatingList positions_table[NUM_POS];
};
typedef struct rating_pos_table RatingTable;

void positions_ranking_list_insertion(RatingList *list, double rating,
                                      PlayerData *player);
void positions_table_insertion(RatingTable *positions_table,
                               CountRatingHashTable *count_rating_hash_table,
                               PlayerData *player);

RatingTable positions_ranking_init();

void positions_ranking_list_print(RatingList list, int n);
#endif

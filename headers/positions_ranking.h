#ifndef POSITIONS_RANKING_H
#define POSITIONS_RANKING_H
#include "misc.h"
#define POS 3
#define M 10au
#define NUM_POS 13
uint positions_ranking_pos_decod(char pos[POS]);
uint positions_ranking_player_set_pos(char pos[POSITIONS_LEN],
                                      PlayerData player);
struct ordered_list {
  double rating;
  PlayerData *player;
  struct ordered_list *next;
};

typedef struct ordered_list *RatingList;

struct rating_pos_table {
  RatingList *positions[NUM_POS];
};
typedef struct rating_pos_table RatingTable;

void positions_ranking_list_insertion(RatingList *list, double rating,
                                      PlayerData *player);
/*
struct positions_ranking_bptree_node {
  bool is_leaf;
  int num_keys;
  int *keys;

  struct positions_ranking_bptree_node *next;
  struct positions_ranking_bptree_node *parent;
};
typedef struct positions_ranking_bptree_node PosRBPTreeNode;
*/
#endif

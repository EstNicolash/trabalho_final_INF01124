#ifndef COUNT_RATING_LIST_H
#define COUNT_RATING_LIST_H
#include "misc.h"

// Estrutura count_rating_list: Dados e ponteiro pra próxima count_rating_lista
struct count_rating_list {
  CountRatingData data;
  struct count_rating_list *next;
};
typedef struct count_rating_list *CountRatingList;

void count_rating_list_init(CountRatingList *list);
void count_rating_list_print(CountRatingList list);
void count_rating_list_insertion_end(CountRatingList *list,
                                     CountRatingData data);
int count_rating_list_length(CountRatingList list);
CountRatingData *count_rating_list_search(CountRatingList list, int key);
void count_rating_list_destruct(CountRatingList *list);

#endif

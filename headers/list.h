#ifndef LIST_H
#define LIST_H
#include "misc.h"

struct Data {
  int fifa_id;
  int total_rating;
  double rating_sum;
};
typedef struct Data Data;
typedef Data Player;
// Estrutura list: Dados e ponteiro pra próxima lista
struct list {
  Data data;
  struct list *next;
};
typedef struct list *List;

void list_init(List *list);
void list_print(List list);
void count_rating_list_insertion_end(List *list, Data data);
int list_length(List list);
Data *list_search(List list, int key);
void list_destruct(List *list);

#endif

#ifndef LIST_H
#define LIST_H
#include "misc.h"

// Estrutura list: Dados e ponteiro pra próxima lista
struct list {
  Data data;
  struct list *next;
};
typedef struct list *List;

void list_init(List *list);
void list_print(List list);
void list_insertion_begin(List *list, Data data);
int list_length(List list);
Data *list_search(List list, int key);
void list_destruct(List *list);

#endif

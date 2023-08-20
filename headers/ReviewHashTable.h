#ifndef REVIEW_HASH_TABLE_H
#define REVIEW_HASH_TABLE_H

#include "misc.h"

struct ReviewHashTable {
    int size;                          //tamanho da hashtable
    UserList user_review_hashtable[];  //vetor de listas de avaliações
};
typedef struct ReviewHashTable ReviewHashTable;

ReviewHashTable *reviews_hash_table_init(int size);  //aloca uma hashtable do tamanho desejado

void user_list_insertion(UserList *user_list, int user_id, UserReview user_review);
UserData *reviews_hash_table_search(ReviewHashTable *hashtable, int user_id);
void reviews_hash_table_insertion(ReviewHashTable *hashtable1, int user_id, UserReview user_review);
void review_heap_init(ReviewHeap *heap);
void review_heap_insertion(ReviewHeap *heap, UserReview user_review);
void review_heap_heapfy_insert(ReviewHeap *heap, int index);
UserData *users_list_search(UserList list, int id);
void review_heap_heapsort(ReviewHeap *heap);
#endif

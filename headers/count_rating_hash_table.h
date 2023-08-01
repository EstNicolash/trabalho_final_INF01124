#ifndef COUNT_RATING_HASH_TABLE_H
#define COUNT_RATING_HASH_TABLE_H

#include "misc.h"

#include "count_rating_list.h"

// Estrutura count_rating_hash_table:
// size: Tamanho da tabela
// count_rating_hash_table: Um vetor de listas com tamanho de size
struct count_rating_hash_table {
  uint size;
  List count_rating_hash_table[];
};

typedef struct count_rating_hash_table CountRatingHashTable;

CountRatingHashTable *count_rating_hash_table_init(uint size);
void count_rating_hash_table_print(
    CountRatingHashTable *count_rating_hash_table);
void count_rating_hash_table_insertion(
    CountRatingHashTable *count_rating_hash_table, Data data);
void count_rating_hash_table_destruct(
    CountRatingHashTable *count_rating_hash_table);
Data *
count_rating_hash_table_search(CountRatingHashTable *count_rating_hash_table,
                               int key);
#endif

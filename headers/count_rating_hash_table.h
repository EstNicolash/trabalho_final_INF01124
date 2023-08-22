#ifndef COUNT_RATING_HASH_TABLE_H
#define COUNT_RATING_HASH_TABLE_H

#include "count_rating_list.h"
#include "misc.h"
/* Tipo CountRatingHashTable
 *
 * size: Tamanho da tabela
 * count_rating_hash_table: Um vetor de listas com tamanho de size
 */
struct count_rating_hash_table {
    uint size;
    CountRatingList count_rating_hash_table[];
};
typedef struct count_rating_hash_table CountRatingHashTable;

CountRatingHashTable *count_rating_hash_table_init(uint size);
void count_rating_hash_table_print(CountRatingHashTable *count_rating_hash_table);
void count_rating_hash_table_insertion(CountRatingHashTable *count_rating_hash_table, CountRatingData data);
CountRatingData *count_rating_hash_table_search(CountRatingHashTable *count_rating_hash_table, int key);
#endif

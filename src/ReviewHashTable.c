#include "../headers/ReviewHashTable.h"

ReviewHashTable *reviews_hash_table_init(int size)
{
    ReviewHashTable *hashtable1 = malloc(sizeof(int) + size * sizeof(ReviewList));
    hashtable1->size = size;

    // Inicizaliza todas listas da tabela
    for (int i = 0; i < size; ++i)
        review_list_initialize(&hashtable1->hashtable[i]);

    return hashtable1;
}

void reviews_hash_table_insertion(ReviewHashTable *hashtable1, int reviewing_user_id, int fifa_id, double rating)
{
    uint index = hash_func(reviewing_user_id,hashtable1->size);
    hashtable1->hashtable[index] = review_list_insert(hashtable1->hashtable[index],reviewing_user_id,fifa_id,rating);
}

void reviews_hash_table_print(ReviewHashTable *hashtable1)
{
    for (uint i = 0; i < hashtable1->size; i++)
    {
        if (hashtable1->hashtable[i])
        {
            printf("\n[%d][Node]", i);
            review_list_print(hashtable1->hashtable[i]);
        }
        else
        {
            printf("\n[%d][Empty Node]", i);
        }
    }
}

ReviewList *get_top20_reviews(ReviewHashTable *hashtable1, int user_id)
{
    int hash = hash_func(user_id, hashtable1->size);
    return list_highest_reviews(hashtable1->hashtable[hash], user_id);
}




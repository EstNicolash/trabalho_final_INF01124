#include "../headers/ReviewList.h"

struct ReviewHashTable
{
    int size; //tamanho da hashtable
    ReviewList *hashtable[]; //vetor de listas de avalia��es
};
typedef struct ReviewHashTable ReviewHashTable;

ReviewHashTable *reviews_hash_table_init(int size); //aloca uma hashtable do tamanho desejado

void reviews_hash_table_insertion(ReviewHashTable *hashtable1, int reviewing_user_id, int fifa_id, double rating); //insere uma avalia��o na hashtable

void reviews_hash_table_print(ReviewHashTable *hashtable1); //imprime todo o conte�do da hashtable

ReviewList *get_top20_reviews(ReviewHashTable *hashtable1, int user_id); //retorna uma lista de avalia��es contendo as 20 maiores avalia��es do usu�rio pesquisado


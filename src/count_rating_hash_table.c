#include "../headers/count_rating_hash_table.h"

/* count_rating_hash_table_init
 *
 * @brief: Inicialização/Criação de uma tabela hash
 *
 * @size: Tamanho da tabela hash
 *
 * @return: Endereço da tabel hash criada
 *
 */
CountRatingHashTable *count_rating_hash_table_init(uint size) {
    CountRatingHashTable *count_rating_hash_table = (CountRatingHashTable *)malloc(sizeof(uint) + size * sizeof(CountRatingList));
    count_rating_hash_table->size = size;

    // Inicizaliza todas listas da tabela
    for (uint i = 0; i < size; ++i) count_rating_list_init(&count_rating_hash_table->count_rating_hash_table[i]);

    return count_rating_hash_table;
}

/* count_rating_hash_table_print
 *
 * @brief: Printa a tabela hash no console
 *
 * @count_rating_hash_table: Endereço de uma tabela hash
 */
void count_rating_hash_table_print(CountRatingHashTable *count_rating_hash_table) {
    for (uint i = 0; i < count_rating_hash_table->size; i++) {
        if (count_rating_hash_table->count_rating_hash_table[i]) {
            printf("\n[%d][Node]", i);
            count_rating_list_print(count_rating_hash_table->count_rating_hash_table[i]);
        } else {
            printf("\n[%d][Empty Node]", i);
        }
    }
}

/* count_rating_hash_table_insertion
 *
 * @brief: Insere um elemento na tabela hash
 *
 * @count_rating_hash_table: Endereço de uma tabela hash
 * @data: Dado do elemento a ser inserido
 *
 */
void count_rating_hash_table_insertion(CountRatingHashTable *count_rating_hash_table, CountRatingData data) {
    // Insere na lista da posição dada pelo hash da chave do dado.
    count_rating_list_insertion_end(&(count_rating_hash_table->count_rating_hash_table[hash_func(data.fifa_id, count_rating_hash_table->size)]),
                                    data);
}

/* count_rating_hash_table_search
 *
 * @biref: Busca na tabela o dado que possuir a chave
 *
 * @count_rating_hash_table: Endereço de uma tabela
 * @key: Chave do dado a ser buscado
 *
 * @return: NULL se não encontrar, o endereço do dado se encontrar
 */
CountRatingData *count_rating_hash_table_search(CountRatingHashTable *count_rating_hash_table, int key) {
    // Busca o dado na lista determinada pelo hash da chave de busca
    return count_rating_list_search(count_rating_hash_table->count_rating_hash_table[hash_func(key, count_rating_hash_table->size)], key);
}

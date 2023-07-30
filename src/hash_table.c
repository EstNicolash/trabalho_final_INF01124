#include "hash_table.h"

/* hash_func
 *
 * @brief: Funçção de hash, usando um valor inteiro como base para efetuar o
 * hashing
 *
 * @param key: o valor de entrada na tabela a ser transformado
 * @param size: o tamanho da tabela hash
 *
 * @return: O valor hash
 */
uint hash_func(int key, uint size) {
  uint hash = 0;
  int i = 0;

  while ((int)key / a_pow10[i] != 0) {
    hash = (hash * PRIME + (((int)key / a_pow10[i]) % 10)) % size;
    i++;
  }

  return hash;
}

/* hash_table_init
 *
 * @brief: Inicialização/Criação de uma tabela hash
 *
 * @param size: Tamanho da tabela hash
 *
 * @return: Endereço da tabel hash criada
 *
 */
HashTable *hash_table_init(uint size) {

  HashTable *hash_table =
      (HashTable *)malloc(sizeof(uint) + size * sizeof(List));
  hash_table->size = size;

  // Inicizaliza todas listas da tabela
  for (uint i = 0; i < size; ++i)
    list_init(&hash_table->hash_table[i]);

  return hash_table;
}

/* hash_table_print
 *
 * @brief: Printa a tabela hash no console
 *
 * @param hash_table: Endereço de uma tabela hash
 */
void hash_table_print(HashTable *hash_table) {
  for (uint i = 0; i < hash_table->size; i++) {

    if (hash_table->hash_table[i]) {

      printf("\n[%d][Node]", i);
      list_print(hash_table->hash_table[i]);
    } else {

      printf("\n[%d][Empty Node]", i);
    }
  }
}

/* hash_table_insertion
 *
 * @brief: Insere um elemento na tabela hash
 *
 * @param hash_table: Endereço de uma tabela hash
 * @param data: Dado do elemento a ser inserido
 *
 */
void hash_table_insertion(HashTable *hash_table, Data data) {

  // Insere na lista da posição dada pelo hash da chave do dado.
  list_insertion_begin(
      &(hash_table->hash_table[hash_func(data.fifa_id, hash_table->size)]),
      data);
}

/* hash_table_search
 *
 * @biref: Busca na tabela o dado que possuir a chave
 *
 * @param hash_table: Endereço de uma tabela
 * @param key: Chave do dado a ser buscado
 *
 * @return: NULL se não encontrar, o endereço do dado se encontrar
 */
Data *hash_table_search(HashTable *hash_table, int key) {

  // Busca o dado na lista determinada pelo hash da chave de busca
  return list_search(hash_table->hash_table[hash_func(key, hash_table->size)],
                     key);
}

/* hash_destruct
 *
 * Destrói a tabela...
 *
 *
 *
 */
void hash_destruct(HashTable *hash_table) {
  for (uint i = 0; i < hash_table->size; i++)
    list_destruct(&(hash_table->hash_table[i]));

  free(hash_table);
  hash_table = NULL;
}

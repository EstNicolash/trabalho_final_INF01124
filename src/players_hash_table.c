#include "../headers/players_hash_table.h"

/* players_hash_table_init
 *
 * @brief: Inicialização/Criação de uma tabela hash
 *
 * @param size: Tamanho da tabela hash
 *
 * @return: Endereço da tabel hash criada
 *
 */
PlayersHashTable *players_hash_table_init(uint size) {

  PlayersHashTable *players_hash_table =
      (PlayersHashTable *)malloc(sizeof(uint) + size * sizeof(PlayersList));
  players_hash_table->size = size;

  // Inicizaliza todas listas da tabela
  for (uint i = 0; i < size; ++i)
    players_list_init(&players_hash_table->players_hash_table[i]);

  return players_hash_table;
}

/* players_hash_table_print
 *
 * @brief: Printa a tabela hash no console
 *
 * @param players_hash_table: Endereço de uma tabela hash
 */
void players_hash_table_print(PlayersHashTable *players_hash_table) {
  for (uint i = 0; i < players_hash_table->size; i++) {

    if (players_hash_table->players_hash_table[i]) {

      printf("\n[%d][Node]", i);
      players_list_print(players_hash_table->players_hash_table[i]);
    } else {

      printf("\n[%d][Empty Node]", i);
    }
  }
}

/* players_hash_table_insertion
 *
 * @brief: Insere um elemento na tabela hash
 *
 * @param players_hash_table: Endereço de uma tabela hash
 * @param data: Dado do elemento a ser inserido
 *
 */
PlayerData *players_hash_table_insertion(PlayersHashTable *players_hash_table,
                                         PlayerData data) {

  // Insere na lista da posição dada pelo hash da chave do dado.

  return players_list_insertion_begin(
      &(players_hash_table->players_hash_table[hash_func(
          data.fifa_id, players_hash_table->size)]),
      data);
}

/* players_hash_table_search
 *
 * @biref: Busca na tabela o dado que possuir a chave
 *
 * @param players_hash_table: Endereço de uma tabela
 * @param key: Chave do dado a ser buscado
 *
 * @return: NULL se não encontrar, o endereço do dado se encontrar
 */
PlayerData *players_hash_table_search(PlayersHashTable *players_hash_table,
                                      int key) {

  // Busca o dado na lista determinada pelo hash da chave de busca
  return players_list_search(
      players_hash_table
          ->players_hash_table[hash_func(key, players_hash_table->size)],
      key);
}

/* hash_destruct
 *
 * Destrói a tabela...
 *
 *
 *
 */
void players_hash_table_destruct(PlayersHashTable *players_hash_table) {
  for (uint i = 0; i < players_hash_table->size; i++)
    players_list_destruct(&(players_hash_table->players_hash_table[i]));

  free(players_hash_table);
  players_hash_table = NULL;
}

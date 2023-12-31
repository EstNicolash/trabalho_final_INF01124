#ifndef PLAYERS_HASH_TABLE_H
#define PLAYERS_HASH_TABLE_H

#include "misc.h"
#include "players_list.h"

/* Tipo PlayersHashTable
 *
 * Estrutura:
 * size: Tamanho da tabela
 * players_hash_table: Um vetor de listas de jogadores com tamanho de size
 */
struct players_hash_table {
    uint size;
    PlayersList players_hash_table[];
};

typedef struct players_hash_table PlayersHashTable;
PlayersHashTable *players_hash_table_init(uint size);
void players_hash_table_print(PlayersHashTable *players_hash_table);
PlayerData *players_hash_table_insertion(PlayersHashTable *players_hash_table, PlayerData data);
PlayerData *players_hash_table_search(PlayersHashTable *players_hash_table, int key);

#endif

#ifndef PLAYERS_LIST_H
#define PLAYERS_LIST_H
#include "misc.h"

/* PlayersList
 *
 * - Lista de jogadores
 *
 * data: Dado do jogador
 * next: proximo elemento da lista
 *
 */
struct players_list {
    PlayerData data;
    struct players_list *next;
};
typedef struct players_list *PlayersList;

void players_list_init(PlayersList *list);
void players_list_print(PlayersList list);
PlayerData *players_list_insertion_begin(PlayersList *list, PlayerData data);
int players_list_length(PlayersList list);
PlayerData *players_list_search(PlayersList list, int key);
void players_list_destruct(PlayersList *list);

#endif

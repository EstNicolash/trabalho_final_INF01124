#include "../headers/positions_ranking.h"

void positions_ranking_list_insertion(RatingList *list, double rating,
                                      PlayerData *player) {

  RatingList new_node = malloc(sizeof(struct ordered_list));
  new_node->player = player;
  new_node->rating = rating;
  new_node->next = NULL;

  if (*list) {

    RatingList aux = NULL;
    RatingList aux2 = *list;

    while (aux2 != NULL && rating <= aux->rating) {
      aux = aux2;
      aux2 = aux2->next;
    }

    new_node->next = aux2;

    if (aux) {
      aux->next = new_node;
      return;
    }
  }

  *list = new_node;
}

uint positions_ranking_pos_cod(char pos[POS]) {
  uint cod;

  if (pos[0] == 'G')
    return 0; // Goalkeeper

  if (pos[1] == 'D')
    return 4; // Central Defensive Midfielder

  if (pos[1] == 'A')
    return 8; // Central Attacking Midfielder

  if (pos[1] == 'F')
    return 11; // Center Forward

  if (pos[0] == 'S')
    return 12; // Striker

  if (pos[0] == 'C') {

    if (pos[1] == 'B')
      return 1; // Centerback

    if (pos[1] == 'M')
      return 5; // Central Midfielder
  }

  if (pos[0] == 'R') {

    if (pos[1] == 'B')
      return 2; // Rightback

    if (pos[1] == 'M')
      return 6; // Right Midfielder

    if (pos[1] == 'W')
      return 10; // Right Wing
  }

  if (pos[0] == 'L') {

    if (pos[1] == 'B')
      return 3; // Leftback

    if (pos[1] == 'M')
      return 7; // Left Midfielder

    if (pos[1] == 'W')
      return 9; // Left Wing
  }

  return 20; // Miss
}

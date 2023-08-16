#include "../headers/positions_ranking.h"
#include <string.h>

void positions_ranking_list_insertion(RatingList *list, double rating,
                                      PlayerData *player) {

  RatingList new_node = malloc(sizeof(struct ordered_list));
  new_node->player = player;
  new_node->rating = rating;
  new_node->next = NULL;

  if (*list) {

    RatingList aux = NULL;
    RatingList aux2 = *list;

    while (aux2 != NULL && rating <= aux2->rating) {
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

  return 0; // Miss
}

void positions_table_insertion(RatingTable *positions_table,
                               CountRatingHashTable *count_rating_hash_table,
                               PlayerData *player) {

  char buffer[POSITIONS_LEN];
  char *token;

  CountRatingData *review;
  review =
      count_rating_hash_table_search(count_rating_hash_table, player->fifa_id);
  player->rating = review;

  if (review) {
    if (review->total_rating >= 1000) {

      strncpy(buffer, player->positions, POSITIONS_LEN);

      // printf("BUFFER: %s; Name: %s\n", buffer, player->name);

      token = strtok(buffer, ", ");

      // printf("token: %s\n", token);

      // printf("%d\n", positions_ranking_pos_cod(token));
      positions_ranking_list_insertion(
          &(positions_table->positions_table[positions_ranking_pos_cod(token)]),
          (double)review->rating_sum / review->total_rating, player);

      // printf("Teste 2\n");
      while (token = strtok(NULL, ", ")) {
        // printf("token = %s\n", token);

        // printf("%d\n", positions_ranking_pos_cod(token));

        positions_ranking_list_insertion(
            &(positions_table
                  ->positions_table[positions_ranking_pos_cod(token)]),
            (double)review->rating_sum / review->total_rating, player);
      }
    }
  }
}

RatingTable positions_ranking_init() {
  RatingTable a;
  for (int i = 0; i < NUM_POS; ++i)
    a.positions_table[i] = NULL;

  return a;
}

void positions_ranking_list_print(RatingList list, int n) {
  RatingList aux = list;
  for (int i = 0; i < n; i++) {

    if (aux == NULL)
      break;

    printf("%d \t %s \t %s \t %f \t %d\n", aux->player->fifa_id,
           aux->player->name, aux->player->positions,
           (double)aux->player->rating->rating_sum /
               aux->player->rating->total_rating,
           aux->player->rating->total_rating);

    aux = aux->next;
  }
}

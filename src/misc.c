#include "../headers/misc.h"
uint a_pow10[10] = {1,     10,     10,      100,      1000,
                    10000, 100000, 1000000, 10000000, 100000000};
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

void print_player_info(PlayerData *player){
    printf("%-10d \t %-50s \t %15s \t %-3f \t %5d \n\n", player->fifa_id, player->name, player->positions, (double)player->rating->rating_sum / player->rating->total_rating, player->rating->total_rating);
}

void print_player_info_header(){
    printf("=======================================================================================================================\n");
    printf("%-10s \t\t %s \t %55s \t %3s \t %5s \n", "sofifa_id", "name", "player_positions", "rating", "count");
    printf("_______________________________________________________________________________________________________________________\n\n");
}
uint debug_count;

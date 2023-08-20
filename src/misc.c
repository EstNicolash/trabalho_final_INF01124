#include "../headers/misc.h"
uint a_pow10[10] = {1, 10, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
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
        hash = ((hash << 8) * (PRIME << 6) + (((int)key / a_pow10[i]) % 10)) % size;
        ++i;
    }

    return hash;
}

uint hash_func2(int key, uint size) {
    uint hash = 0;
    int i = 0;

    while ((int)key / a_pow10[i] != 0) {
        hash = (i * 2654435761 * a_pow10[i] + hash) % size;
        ++i;
    }

    return hash;
}
void print_player_info(PlayerData *player) {
    printf("%-10d \t %-50s \t %15s \t %-3f \t %5d \n\n", player->fifa_id, player->name, player->positions,
           (double)player->rating->rating_sum / player->rating->total_rating, player->rating->total_rating);
}

void print_player_info_header() {
    printf("=======================================================================================================================\n");
    printf("%-10s \t %s \t %55s \t %3s \t %5s \n", "sofifa_id", "name", "player_positions", "rating", "count");
    printf("_______________________________________________________________________________________________________________________\n\n");
}
void print_player_info_mais_rating(PlayerData *player, double rating) {
    printf("%-10d \t %-50s \t %15f \t %-3d \t %5f \n\n", player->fifa_id, player->name,
           (double)player->rating->rating_sum / player->rating->total_rating, player->rating->total_rating, rating);
}

void print_player_info_header_mais_rating() {
    printf("=======================================================================================================================\n");
    printf("%-10s \t %-50s \t %15s \t %s \t %s \n", "sofifa_id", "name", "global rating", "count", "rating");
    printf("_______________________________________________________________________________________________________________________\n\n");
}
uint debug_count;

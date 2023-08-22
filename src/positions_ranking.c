#include "../headers/positions_ranking.h"

#include <string.h>

/* positions_ranking_list_insertion
 * 
 * Insere de forma ordenada o joador no ranking da posição
 *
 * @list: Lista de poisções para inserir o jogador
 * @rating: Avaliação
 * @player: Ponteiro para o dado de um jogador
 *
 */
void positions_ranking_list_insertion(RatingList *list, double rating, PlayerData *player) {
    RatingList new_node = malloc(sizeof(struct ordered_list));
    new_node->player = player;
    new_node->rating = rating;
    new_node->next = NULL;

    if (*list) {
        RatingList aux = NULL;
        RatingList aux2 = *list;

        //Navega pela lista e para na posição correta da avaliação
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

    //Inicia a lista se lista estiver vazia
    *list = new_node;
}

/*  positions_ranking_pos_cod
 *
 *  Retorna o indíce da posição na tabela posições
 *
 *  @pos: String com a posição
 *  @return: indíce 
 */
uint positions_ranking_pos_cod(char pos[POS]) {
    if (pos[0] == 'G') return 0;  // Goalkeeper

    if (pos[1] == 'D') return 4;  // Central Defensive Midfielder

    if (pos[1] == 'A') return 8;  // Central Attacking Midfielder

    if (pos[1] == 'F') return 11;  // Center Forward

    if (pos[0] == 'S') return 12;  // Striker

    if (pos[0] == 'C') {
        if (pos[1] == 'B') return 1;  // Centerback

        if (pos[1] == 'M') return 5;  // Central Midfielder
    }

    if (pos[0] == 'R') {
        if (pos[1] == 'B') return 2;  // Rightback

        if (pos[1] == 'M') return 6;  // Right Midfielder

        if (pos[1] == 'W') return 10;  // Right Wing
    }

    if (pos[0] == 'L') {
        if (pos[1] == 'B') return 3;  // Leftback

        if (pos[1] == 'M') return 7;  // Left Midfielder

        if (pos[1] == 'W') return 9;  // Left Wing
    }

    return 0;  // Miss
}

/*  positions_table_insertion
 *
 *  @brief: Insere na tabela de posições ranqueda
 *
 *  @positions_table: Tabela de posições
 *  @count_rating_hash_table: Tabela hash com as avaliações globais[
 *  @player: Dado do jogador a ser avaliada inserção na tebela de posições rankeada
 */
void positions_table_insertion(RatingTable *positions_table, CountRatingHashTable *count_rating_hash_table, PlayerData *player) {
    char buffer[POSITIONS_LEN];
    char *token;

    CountRatingData *review;
    review = count_rating_hash_table_search(count_rating_hash_table, player->fifa_id);

    player->rating = review;

    // Se encontrou uma avaliação jgoador
    if (review) {
        // Insere na tabela apenas se mais de 1000 avaliações
        if (review->total_rating >= 1000) {
            strncpy(buffer, player->positions, POSITIONS_LEN);

            //Processa cada posição da string de posições do jogador e insere na respectivo ranking da tabela
            token = strtok(buffer, ", ");

            positions_ranking_list_insertion(&(positions_table->positions_table[positions_ranking_pos_cod(token)]),
                                             (double)review->rating_sum / review->total_rating, player);

            while (token = strtok(NULL, ", ")) {
                positions_ranking_list_insertion(&(positions_table->positions_table[positions_ranking_pos_cod(token)]),
                                                 (double)review->rating_sum / review->total_rating, player);
            }
        }
    }
}
/* positions_ranking_init
 *
 * @return: Retorna a tabela de posições inicializada
 *
 */
RatingTable positions_ranking_init() {
    RatingTable a;

    //Null para o poneiro do primeiro elemento da lista para todas as listas
    for (int i = 0; i < NUM_POS; ++i) a.positions_table[i] = NULL;

    return a;
}
/*
 * PRINT!!!
 *
 */
void positions_ranking_list_print(RatingList list, int n) {
    RatingList aux = list;
    print_player_info_header();
    for (int i = 0; i < n; i++) {
        if (aux == NULL) break;

        print_player_info(aux->player);

        aux = aux->next;
    }
}

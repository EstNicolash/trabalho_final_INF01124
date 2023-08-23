#include "../headers/misc.h"

#include <ctype.h>
#include <string.h>

//Vetor com potencias de 10 para acesso rápido
uint a_pow10[10] = {1, 10, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

/* hash_func
 *
 * @brief: Funçção de hash, usando um valor inteiro como base para efetuar o
 * hashing
 *
 * @key: o valor de entrada na tabela a ser transformado
 * @size: o tamanho da tabela hash
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
/*
uint hash_func2(int key, uint size) {
    uint hash = 0;
    int i = 0;

    while ((int)key / a_pow10[i] != 0) {
        hash = (i * 2654435761 * a_pow10[i] + hash) % size;
        ++i;
    }

    return hash;
}*/
//Funções de print para a tabela no console
void print_player_info(PlayerData *player) {
    if (player->rating)
        printf("%-10d \t %-50s \t %15s \t %-3f \t %5d \n\n", player->fifa_id, player->name, player->positions,
               (double)player->rating->rating_sum / player->rating->total_rating, player->rating->total_rating);
    else
        printf("%-10d \t %-50s \t %15s \t %-3f \t %5d \n\n", player->fifa_id, player->name, player->positions, 0.0, 0);
}

void print_player_info_header() {
    printf("=======================================================================================================================\n");
    printf("%-10s \t %s \t %65s \t %3s \t %5s \n", "sofifa_id", "name", "player_positions", "rating", "count");
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

//Contador para debugar
uint debug_count;

/* list_tags
 *
 *  @brief: Processa a entrada <lista de tags> para a busca pela tag (pesquisa 2.4).
 *
 *  @tag_list: A <lista de tags> antes de ser devidamente processada, isto é, a linha intera do buffer do console.
 *  @num_tags: Ponteiro para a quantidade de tags na lista de tags.
 *
 *  @return list_of_tags: Um array de strings com cada posição contendo uma tag.
 *
 *  Exemplo: tag_list = 'ab a''sa'  'ma', então list_of_tags = {"ab a", "sa", "ma"} e num_tags = 3 
 *
 */
char **list_tags(char tag_list[NAME_LEN], int *num_tags) {
    *num_tags = 0;
    char **list_of_tags;
    list_of_tags = malloc(sizeof(char *) * NAME_LEN);
    for (int i = 0; i < NAME_LEN; ++i) list_of_tags[i] = malloc(sizeof(char) * NAME_LEN);

    int array_index = 0;
    //printf("tags:%s num:%d\n", tag_list, *num_tags);
    for (int i = 0; i < NAME_LEN; ++i) {
        int j = 0;

        //Processa uma tag apartir do primeiro ' até o último '.
        if (tag_list[i] == 39) {
            ++i;

            while (tag_list[i] != 39) {
                list_of_tags[array_index][j] = tag_list[i];
                ++i;
                ++j;
            }

            list_of_tags[array_index][j] = '\0';
            list_of_tags[array_index][0] = list_of_tags[array_index][0];

            ++array_index;
            ++(*num_tags);
        }
    }

    return list_of_tags;
}

/*  strlwr 
 *
 *  @brief: Transforma todas as letras de uma string em minúsculo.
 *
 *  @str: String 
 *
 *  @return a string toda em minúsclo.
 */
char *strlwr(char *str) {
    for (int i = 0; i < strlen(str); i++) str[i] = tolower(str[i]);

    return str;
}

void pos_input_fix(char pos[POS], char input[2 * POS]) {
    int i = 0;
    int j = 0;

    printf("%s\n", input);
    while (input[i] == 39) ++i;
    while (input[i] != 39) {
        pos[j] = input[i];
        ++j;
        ++i;
    }

    for (int i = 0; i < POS; ++i) pos[i] = toupper(pos[i]);
}

void name_input_fix(char name[NAME_LEN], char input[NAME_LEN]) {
    char *tk = strtok(input, " ");
    tk[0] = toupper(tk[0]);
    strncpy(name, tk, strlen(tk));

    while (tk = strtok(NULL, " ")) {
        tk[0] = toupper(tk[0]);
        strcat(name, " ");
        strcat(name, tk);
    };
}

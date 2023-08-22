#include "../headers/players_list.h"

#include <stdio.h>
/* list_init
 * Inicializa a lista com NULL
 * @*list: Ponteiro para uma lista
 */
void players_list_init(PlayersList *list) {
    *list = NULL;
}

/*list_print
 *
 * Printa a lista no terminal
 *
 * @list: Lista para imprimir
 */

void players_list_print(PlayersList list) {
    while (list) {
        printf("[fifa_id: %d, name: %s positions: %s", list->data.fifa_id, list->data.name, list->data.positions);

        printf("]");
        list = list->next;
    }
    printf("\n");
}

/* players_list_insertion_begin
 *
 * @brief: Insere elemento no começo da lista
 *
 * @list: Endereço do primeiro elemento da lista(a lista)
 * @data: Dado do jogador a ser inserido na lista
 *
 */
PlayerData *players_list_insertion_begin(PlayersList *list, PlayerData data) {
    PlayersList new_list = (PlayersList)malloc(sizeof(struct players_list));
    new_list->data = data;
    new_list->next = *list;

    *list = new_list;
    return &(new_list->data);
}
/* list_destruct
 *
 * @brief: Destói a lista
 *
 * @param list: Endereço da lista a ser destruída
 *
 */
void players_list_destruct(PlayersList *list) {
    while (*list) {
        PlayersList aux = *list;
        *list = aux->next;
        free(aux);
    }
}

/* list_length
 *
 * @brief: calculca o tamanho da lista
 *
 * @param list: A lista a ser verificada o tamanho
 *
 * @return: O tamanho de list
 *
 */
int players_list_length(PlayersList list) {
    int count = 0;
    while (list) {
        list = list->next;
        ++count;
    }
    return count;
}

/* players_list_search
 *
 * @brief: Busca na lista o jogador pela seu ID

 * @list: A lista onde a busca é efetuda
 * @key: ID do jogador
 *
 * @return: NULL se o dado não estiver na lista, o endereço do dado caso seja
 * encontrado
 *
 */
PlayerData *players_list_search(PlayersList list, int key) {
    while (list) {
        if (list->data.fifa_id == key) return &(list->data);

        list = list->next;
    }
    return NULL;
}

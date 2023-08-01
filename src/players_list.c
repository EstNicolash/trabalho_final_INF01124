#include "../headers/players_list.h"
#include <stdio.h>
/* list_init
 * Inicializa a lista com NULL
 * @param *list: Ponteiro para uma lista
 *
 * */
void players_list_init(PlayersList *list) { *list = NULL; }

/*list_print
 *
 * Printa a lista no terminal
 *
 * @param list: Lista para imprimir
 */

void players_list_print(PlayersList list) {
  while (list) {
    printf("[fifa_id: %d, name: %s positions: ", list->data.fifa_id,
           list->data.name);

    for (int i = 0; list->data.positions[i] != NULL; ++i)
      printf("%s ", list->data.positions[i]);

    printf("]");
    list = list->next;
  }
  printf("\n");
}

/* list_insertion_begin
 *
 * @brief: Insere elemento no começo da lista
 *
 * @param list: Endereço do primeiro elemento da lista(a lista)
 * @param data: Dado do elemento a ser isnerido na lista
 *
 */
void players_list_insertion_begin(PlayersList *list, PlayerData data) {

  PlayersList new_list = (PlayersList)malloc(sizeof(struct players_list));
  new_list->data = data;
  new_list->next = *list;

  *list = new_list;
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

/* list_search
 *
 * @brief: Busca na lista o dado de acordo com o a chave inserida

 * @param list: A lista onde a busca é efetuda
 * @param key: A chava em inteiro do dado a ser encontrado
 *
 * @return: NULL se o dado não estiver na lista, o endereço do dado caso seja
 * encontrado
 *
 */
PlayerData *players_list_search(PlayersList list, int key) {
  while (list) {

    if (list->data.fifa_id == key)
      return &(list->data);

    list = list->next;
  }
  return NULL;
}

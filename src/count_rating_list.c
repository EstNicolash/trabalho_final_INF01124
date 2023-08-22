#include "../headers/count_rating_list.h"
/* count_rating_list_list_init
 * Inicializa a lista com NULL
 * @list: Ponteiro para uma lista
 */
void count_rating_list_init(CountRatingList *list) {
    *list = NULL;
}

/* count_rating_list_print
 *
 * Printa a lista no terminal
 *
 * @list: Lista para imprimir
 */
void count_rating_list_print(CountRatingList list) {
    while (list) {
        printf("[fifa_id: %d, total: %d sum: %f]", list->data.fifa_id, list->data.total_rating, list->data.rating_sum);
        list = list->next;
    }
    printf("\n");
}

/* count_rating_list_insertion_end
 *
 * @brief: Insere ou modifica a avaliação total do jogador 
 *
 * @list: Endereço do primeiro elemento da lista(a lista)
 * @data: Dado do elemento a ser isnerido na lista
 *
 */
void count_rating_list_insertion_end(CountRatingList *list, CountRatingData data) {
    if (*list) {
        CountRatingList aux = *list;

        //percorre a lista
        while (aux->next) {
            //Se o id da lista for igual ao dado inserido, há jogador na lista então apenas atualiza
            if (aux->data.fifa_id == data.fifa_id) {
                aux->data.total_rating++;
                aux->data.rating_sum += data.rating_sum;
                return;
            }

            aux = aux->next;
        }

        //Caso só haja um elemento da lista e este elemento for o jogador na inserção
        if (aux->data.fifa_id == data.fifa_id) {
            aux->data.total_rating++;
            aux->data.rating_sum += data.rating_sum;
            return;
        }

        //Se há lista mas não há o jogador não está nela, aloca um nodo da lista para o jogador
        CountRatingList new_list = (CountRatingList)malloc(sizeof(struct count_rating_list));
        new_list->data = data;
        new_list->next = NULL;

        aux->next = new_list;

        return;
    }

    //Se não há lista, cria nova lista
    CountRatingList new_list = (CountRatingList)malloc(sizeof(struct count_rating_list));
    new_list->data = data;
    new_list->next = NULL;

    *list = new_list;

    return;
}
/* list_destruct
 *
 * @brief: Destói a lista
 *
 * @list: Endereço da lista a ser destruída
 *
 */
void count_rating_list_destruct(CountRatingList *list) {
    while (*list) {
        CountRatingList aux = *list;
        *list = aux->next;
        free(aux);
    }
}

/* list_length
 *
 * @brief: calculca o tamanho da lista
 *
 * @ list: A lista a ser verificada o tamanho
 *
 * @return: O tamanho de list
 *
 */
int count_rating_list_length(CountRatingList list) {
    int count = 0;
    while (list) {
        list = list->next;
        ++count;
    }
    return count;
}

/* count_rating_list_search
 *
 * @brief: Busca na lista o dado de acordo com o a chave inserida
 *
 * @list: A lista onde a busca é efetuda
 * @key: A chava em inteiro do dado a ser encontrado
 *
 * @return: NULL se o dado não estiver na lista, o endereço do dado caso seja
 * encontrado
 *
 */
CountRatingData *count_rating_list_search(CountRatingList list, int key) {
    while (list) {
        if (list->data.fifa_id == key) return &(list->data);

        list = list->next;
    }
    return NULL;
}

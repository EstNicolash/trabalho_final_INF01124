#include "../headers/ReviewHashTable.h"

#include "../headers/misc.h"

/* reviews_hash_table_init
 *
 * @brief: Inicializa a tabela hash
 *
 * @size: tamanho da tabela
 *
 * @return: Ponteiro para a tabela Inicializada
 */
ReviewHashTable *reviews_hash_table_init(int size) {
    ReviewHashTable *hashtable1 = malloc(sizeof(int) + size * sizeof(struct user_list));
    hashtable1->size = size;

    // Inicizaliza todas listas da tabela
    for (int i = 0; i < size; ++i) hashtable1->user_review_hashtable[i] = NULL;

    return hashtable1;
}

/* reviews_heap_heapfy
 *
 * @brief: Heapfy na heap de avaliaçoes!
 *
 * @heap: Heap de avaliaçoes
 * @root: Posição do array que começa o heapfy
 *
 */
void reviews_heap_heapfy(ReviewHeap *heap, int root) {
    int min = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < heap->end && heap->reviews[min].rating > heap->reviews[left].rating) min = left;

    if (right < heap->end && heap->reviews[min].rating > heap->reviews[right].rating) min = right;

    if (min != root) {
        UserReview aux = heap->reviews[root];
        heap->reviews[root] = heap->reviews[min];
        heap->reviews[min] = aux;

        reviews_heap_heapfy(heap, min);
    }
}

/* review_heap_init
 *
 * @brief: Inicia a heap
 * @heap: Heap a ser Inicializada
 *
 */
void review_heap_init(ReviewHeap *heap) {
    heap->end = 0;
    heap->sorted = false;

    for (int i = 0; i < HEAP_SIZE; ++i) {
        heap->reviews[i].fifa_id = -1;
        heap->reviews[i].rating = -1;
    }
}
/* review_heap_insertion(
 *
 * @brief: Insere avaliação na heap de avaliações
 *
 * @heap: heap
 * @user_review: Avaliação a ser inserida
 *
 * Dado a inicilização: a heap já está formada. A inserção ocorre sempre no primeiro elemento
 * da heap, ou seja, o elemento substitui o menor elemento da heap caso seja maior
 *
 */
void review_heap_insertion(ReviewHeap *heap, UserReview user_review) {
    if (heap->end == HEAP_SIZE && user_review.rating < heap->reviews[0].rating) return;

    if (heap->end == HEAP_SIZE) {
        heap->reviews[0] = user_review;
        reviews_heap_heapfy(heap, 0);
        return;
    }

    int i = heap->end;
    UserReview aux;
    heap->reviews[heap->end] = user_review;
    ++(heap->end);

    while (i != 0 && heap->reviews[(i - 1) / 2].rating > heap->reviews[i].rating) {
        aux = heap->reviews[(i - 1) / 2];
        heap->reviews[(i - 1) / 2] = heap->reviews[i];
        heap->reviews[i] = aux;
        i = (i - 1) / 2;
    }
}

/* review_heap_heapsort
 *
 * @brief: Heapsort na heap de avaliações
 * 
 * @heap: Heap a ser ordenada
 *
 *
 */
void review_heap_heapsort(ReviewHeap *heap) {
    heap->sorted = true;
    UserReview aux;
    heap->end = HEAP_SIZE - 1;

    for (int i = heap->end; i >= 0; --i) {
        aux = heap->reviews[0];
        heap->reviews[0] = heap->reviews[i];
        heap->reviews[i] = aux;
        --(heap->end);
        reviews_heap_heapfy(heap, 0);
    }
}

/* user_list_insertion
 * 
 * @brief: INSERE a avaliação e/ou o usuário na lista
 *
 * @user_list: A lista
 * @user_id: O ID do usuário
 * @user_review: A avaliação
 *
 */
void user_list_insertion(UserList *user_list, int user_id, UserReview user_review) {
    UserList aux = *user_list;
    //printf("User: %d", user_id);
    //printf("User: %d fifa: %d rating: %f\n", user_id, user_review.fifa_id, user_review.rating);
    if (aux) {
        while (aux->next) {
            //Se jogador já está na lista
            if (aux->user_data.user_id == user_id) {
                review_heap_insertion(&(aux->user_data.user_reviews), user_review);
                return;
            }

            aux = aux->next;
        }

        //Idem
        if (aux->user_data.user_id == user_id) {
            review_heap_insertion(&(aux->user_data.user_reviews), user_review);
            return;
        }

        //Se jogador não foi alocado na lista:
        UserList new_user = malloc(sizeof(struct user_list));
        new_user->user_data.user_id = user_id;
        new_user->next = NULL;
        review_heap_init(&new_user->user_data.user_reviews);
        review_heap_insertion(&(new_user->user_data.user_reviews), user_review);
        aux->next = new_user;

        return;
    }

    //Se lista vazia:
    UserList new_user = malloc(sizeof(struct user_list));

    new_user->user_data.user_id = user_id;
    new_user->next = NULL;
    review_heap_init(&new_user->user_data.user_reviews);
    review_heap_insertion((&new_user->user_data.user_reviews), user_review);

    *user_list = new_user;

    return;
}

/* reviews_hash_table_insertion
 * 
 * @brief: Insere um jogador e uma avaliação ou atualiza o jogador com a avaliação
 *
 * @hashtable1: tabela hash dos usuários
 * @user_id: ID DO USUÀRIO
 * @user_review: Avaliação a ser inserida
 */
void reviews_hash_table_insertion(ReviewHashTable *hashtable1, int user_id, UserReview user_review) {
    uint index = hash_func(user_id, hashtable1->size);
    user_list_insertion(&(hashtable1->user_review_hashtable[index]), user_id, user_review);
}

/* users_list_search
 *
 * @brief: Pesquisa na lista de usuários
 *
 * @list: lista
 * @id: id
 *
 * @return: Ponteiro para o dado do usuário
 */
UserData *users_list_search(UserList list, int id) {
    while (list) {
        if (list->user_data.user_id == id) return &(list->user_data);

        list = list->next;
    }

    return NULL;
}
UserData *reviews_hash_table_search(ReviewHashTable *hashtable, int user_id) {
    return users_list_search(hashtable->user_review_hashtable[hash_func(user_id, hashtable->size)], user_id);
}

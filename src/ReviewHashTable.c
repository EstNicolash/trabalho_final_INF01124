#include "../headers/ReviewHashTable.h"

#include "../headers/misc.h"

ReviewHashTable *reviews_hash_table_init(int size) {
    ReviewHashTable *hashtable1 = malloc(sizeof(int) + size * sizeof(struct user_list));
    hashtable1->size = size;

    // Inicizaliza todas listas da tabela
    for (int i = 0; i < size; ++i) hashtable1->user_review_hashtable[i] = NULL;

    return hashtable1;
}

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

void review_heap_init(ReviewHeap *heap) {
    heap->end = HEAP_SIZE;
    heap->sorted = false;

    for (int i = 0; i < HEAP_SIZE; ++i) {
        heap->reviews[i].fifa_id = -1;
        heap->reviews[i].rating = -1;
    }
}

void review_heap_insertion(ReviewHeap *heap, UserReview user_review) {
    if (user_review.rating < heap->reviews[0].rating) return;

    heap->reviews[0] = user_review;
    reviews_heap_heapfy(heap, 0);

    if (heap->end != HEAP_SIZE) ++heap->end;
}

void review_heap_heapsort(ReviewHeap *heap) {
    heap->sorted = true;
    UserReview aux;
    heap->end = HEAP_SIZE - 1;
    for (int i = heap->end; i > 0; --i) {
        aux = heap->reviews[0];
        heap->reviews[0] = heap->reviews[heap->end];
        heap->reviews[heap->end] = aux;
        --heap->end;
        reviews_heap_heapfy(heap, 0);
    }
}
void review_heap_heapfy_insert(ReviewHeap *heap, int index) {
    int root = (index - 1) / 2;

    if (heap->reviews[root].rating > heap->reviews[index].rating) {
        UserReview aux = heap->reviews[root];
        heap->reviews[root] = heap->reviews[index];
        heap->reviews[index] = aux;

        review_heap_heapfy_insert(heap, root);
    }
}

void user_list_insertion(UserList *user_list, int user_id, UserReview user_review) {
    UserList aux = *user_list;
    //printf("User: %d", user_id);
    //printf("User: %d fifa: %d rating: %f\n", user_id, user_review.fifa_id, user_review.rating);
    if (aux) {
        while (aux->next) {
            if (aux->user_data.user_id == user_id) {
                review_heap_insertion(&(aux->user_data.user_reviews), user_review);
                return;
            }

            aux = aux->next;
        }

        if (aux->user_data.user_id == user_id) {
            review_heap_insertion(&(aux->user_data.user_reviews), user_review);
            return;
        }

        UserList new_user = malloc(sizeof(struct user_list));
        new_user->user_data.user_id = user_id;
        new_user->next = NULL;
        review_heap_init(&new_user->user_data.user_reviews);
        review_heap_insertion(&(new_user->user_data.user_reviews), user_review);
        aux->next = new_user;

        return;
    }

    UserList new_user = malloc(sizeof(struct user_list));

    new_user->user_data.user_id = user_id;
    new_user->next = NULL;
    review_heap_init(&new_user->user_data.user_reviews);
    review_heap_insertion((&new_user->user_data.user_reviews), user_review);

    *user_list = new_user;

    return;
}

void reviews_hash_table_insertion(ReviewHashTable *hashtable1, int user_id, UserReview user_review) {
    uint index = hash_func(user_id, hashtable1->size);
    user_list_insertion(&(hashtable1->user_review_hashtable[index]), user_id, user_review);
}

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

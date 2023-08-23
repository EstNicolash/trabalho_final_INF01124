#include "../headers/id_list.h"

id_list *initialize_id_list() {
    return NULL;
}

void insert_id_list(id_list **list1, int player_id) {
    int repeated = 0;
    id_list *new_node = (id_list *)malloc(sizeof(id_list));
    new_node->player_id = player_id;
    new_node->next = NULL;

    id_list *aux = *list1;
    if (aux == NULL) {
        *list1 = new_node;
    } else {
        if (aux->player_id == player_id)
            repeated = 1;
        else
            while (aux->next != NULL && !repeated) {
                if (aux->player_id == player_id) repeated = 1;
                aux = aux->next;
            }
        if (!repeated)
            aux->next = new_node;
        else
            free(new_node);
    }
}

void print_id_list(id_list *list1) {
    id_list *aux = list1;
    if (aux == NULL) {
        printf("\nLISTA VAZIA");
    } else {
        while (aux != NULL) {
            printf("\nID: %d", aux->player_id);
            aux = aux->next;
        }
    }
}

void free_id_list(id_list *list1) {
    id_list *aux = list1;
    id_list *next;
    while (aux != NULL) {
        next = aux->next;
        free(aux);
        aux = next;
    }
}

int isIDPresent(id_list *list1, int player_id)  //verifica se um id de jogador está contido na lista
{
    id_list *aux = list1;
    if (aux != NULL) {
        while (aux != NULL) {
            if (aux->player_id == player_id) return 1;
            aux = aux->next;
        }
    }
    return 0;
}

id_list *id_list_cpy(id_list *src) {
    id_list *cpy = initialize_id_list();
    id_list *aux = src;

    while (aux) {
        insert_id_list(&cpy, aux->player_id);
        aux = aux->next;
    }

    return cpy;
}

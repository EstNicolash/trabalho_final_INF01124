#include "../headers/id_list.h"

id_list *initialize_id_list()
{
    return NULL;
}

void insert_id_list(id_list **list1, int player_id)
{
    id_list *new_node = (id_list *)malloc(sizeof(id_list));
    new_node->player_id = player_id;
    new_node->next = NULL;

    id_list *aux = *list1;
    if (aux == NULL)
    {
        *list1 = new_node;
    }
    else
    {
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = new_node;
    }
}

void print_id_list(id_list *list1)
{
    id_list *aux = list1;
    if (aux == NULL)
    {
        printf("\nLISTA VAZIA");
    }
    else
    {
        while (aux != NULL)
        {
            printf("\nID: %d", aux->player_id);
            aux = aux->next;
        }
    }
}

void free_id_list(id_list *list1)
{
    id_list *aux = list1;
    id_list *next;
    while (aux != NULL)
    {
        next = aux->next;
        free(aux);
        aux = next;
    }
}

int isIDPresent(id_list *list1, int player_id) //verifica se um id de jogador está contido na lista
{
    id_list *aux = list1;
    if (aux != NULL)
    {
        while (aux != NULL)
        {
            if(aux->player_id == player_id)
                return 1;
            aux = aux->next;
        }
    }
    return 0;
}

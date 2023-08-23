#include <malloc.h>
#include <stdio.h>

/*
 Estrutura id_list:
 player_id: id do jogador
 next: ponteiro para próxima estrutura id_list
 */
struct id_list {
    int player_id;
    struct id_list *next;
};
struct id_list;
typedef struct id_list id_list;

id_list *initialize_id_list();
void insert_id_list(id_list **list1, int player_id);
void print_id_list(id_list *list1);
void free_id_list(id_list *list1);
int isIDPresent(id_list *list1, int player_id);
id_list *id_list_cpy(id_list *src);

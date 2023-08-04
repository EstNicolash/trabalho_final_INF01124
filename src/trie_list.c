#include "../headers/trie_list.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

listnode *initialize_list() { return NULL; }

void insert_list(listnode **list1, player_data player) {
  listnode *new_node = (listnode *)malloc(sizeof(listnode));
  new_node->player.name = player.name;
  new_node->player.id = player.id;
  new_node->next = NULL;

  listnode *aux = *list1;
  if (aux == NULL) {
    *list1 = new_node;
  } else {
    while (aux->next != NULL) {
      aux = aux->next;
    }
    aux->next = new_node;
  }
}

void print_list(listnode *list1) {
  listnode *aux = list1;
  if (aux == NULL) {
    printf("\nLISTA VAZIA");
  } else {
    while (aux != NULL) {
      printf("\nJOGADOR: %s ID: %d", aux->player.name, aux->player.id);
      aux = aux->next;
    }
  }
}

void free_list(listnode *list1) {
  listnode *aux = list1;
  listnode *next;
  while (aux != NULL) {
    next = aux->next;
    free(aux);
    aux = next;
  }
}

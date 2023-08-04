#include "../headers/trie.h"
#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

char charAt(char string[], int index) {
  if (index < strlen(string))
    return string[index];
  else
    return '\0';
}

void initialize_trie(TRIE *tree) {
  tree->root = initialize_node('a');
  tree->value = 0;
}

trienode *initialize_node(char value) {
  int i = 0;
  trienode *new_node;
  new_node = (trienode *)malloc(sizeof(trienode));
  new_node->isEnd = 0;
  for (i = 0; i < ALPHABET_SIZE; i++) {
    new_node->children[i] = NULL;
  }
  new_node->value = value;

  // printf("\nALLOCATED");
  return new_node;
}

int hasChild(trienode *node1, int index) {
  if (node1 == NULL) {
    return 0;
  }
  return node1->children[index] != 0;
}

void insert_trie(TRIE tree, char player_name[], int player_id) {
  int offset = 0;
  int length = strlen(player_name);
  trienode *current_node = tree.root;
  char current_char = '\0';
  trienode *aux = NULL;

  while (offset < length) {
    current_char = charAt(player_name, offset);
    if (hasChild(current_node,
                 (int)current_char)) // se o nodo já possui a próxima letra,
                                     // pula para ela (índice da letra no vetor
                                     // é seu valor ascii)
    {
      aux = current_node->children[(int)current_char];
      current_node = aux;
    } else // senão, aloca nova letra/nodo
    {
      aux = initialize_node(current_char);
      current_node->children[(int)current_char] = aux;
      current_node = aux;
    }
    offset++;
  }
  current_node->isEnd = player_id;
  // printf("\nINSERTED %d",length);
}

void print_node(trienode *node1) {
  printf("\nVALUE: %c CHILDREN: ", node1->value);
  int i;
  for (i = LETTERS_BOT; i < LETTERS_TOP; i++) {
    printf("%c: ", i);
    if (hasChild(node1, i)) {
      printf("1  ");
    } else {
      printf("0  ");
    }
  }
}

int isPresent(TRIE tree, char name[]) {
  int offset = 0;
  int length = strlen(name);
  trienode *current_node = tree.root;
  char current_char = '\0';
  trienode *aux = NULL;

  while (offset < length) {
    current_char = charAt(name, offset);
    if (hasChild(current_node, (int)current_char)) {
      aux = current_node->children[(int)current_char];
      current_node = aux;
    } else {
      // printf("\nNOT FOUND");
      return 0;
    }
    offset++;
  }
  if (current_node->isEnd) {
    // printf("\nFOUND");
    return 1;
  }
  // printf("\nNOT FOUND");
  return 0;
}

trienode *
findEndOfPrefix(trienode *root,
                char *prefix) // posiciona o ponteiro no nodo correspondente a
                              // última letra do prefixo
{
  int offset = 0;
  int prefix_length = strlen(prefix);
  char current_char;
  trienode *aux = root;

  while (offset < prefix_length) {
    current_char = charAt(prefix, offset);

    if (hasChild(aux, (int)current_char)) {
      aux = aux->children[(int)current_char];
    } else {
      return NULL;
    }
    offset++;
  }
  // printf("\nNODO FINAL: %c",aux->value);
  return aux;
}

listnode *
list_all(TRIE tree,
         char prefix[]) // retorna lista com todos os jogadores encotrados
{
  trienode *root;
  listnode *list_of_players;

  root = findEndOfPrefix(tree.root, prefix);
  list_of_players = initialize_list();
  list_nodes(&list_of_players, prefix, root);

  return list_of_players;
}

void list_nodes(listnode **list_of_players, char *current_word,
                trienode *current_node) // a partir da útlima letra do prefixo,
                                        // lista todos as palavras encontradas
{
  char *next_word = NULL;
  player_data player_aux;

  if (current_node != NULL) {
    if (current_node->isEnd) {
      player_aux.id = current_node->isEnd;
      player_aux.name = malloc(sizeof(char) * 32);
      strcpy(player_aux.name, current_word);
      insert_list(list_of_players, player_aux);
      printf("\n%s", current_word);
    }
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++) {
      if (hasChild(current_node, i)) {

        next_word = concat_char(current_word, (char)i);
        list_nodes(list_of_players, next_word, current_node->children[i]);
      }
    }
  }
  if (next_word != NULL) {
    free(next_word);
  }
}

char *concat_char(char str[], char c) {
  int current_length = strlen(str);
  char *next_word = malloc(sizeof(char) * (current_length + 2));
  strcpy(next_word, str);
  next_word[current_length] = c;
  next_word[current_length + 1] = '\0';
  return next_word;
}

void toupper_str(char str[]) {
  if (str != NULL) {
    int i = 0;
    while (str[i] != '\0') {
      str[i] = toupper(str[i]);
      i++;
    }
  }
}

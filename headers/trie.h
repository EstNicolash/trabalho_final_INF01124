#include "trie_list.h"
#define ALPHABET_SIZE 128 // tamanho do vetor de descendentes para o nodo
#define LETTERS_BOT 65    // in�cio das letras mai�sculas na tabela ascii
#define LETTERS_TOP 90    // fim das letras mai�sculas na tabela ascii

/*
 Estrutura trienode:
 value: caractere representado pelo nodo dentro da �rvore
 isEnd: flag de nodo terminador, cont�m 0 se n�o � terminador de palavra, ou
 cont�nm o id do jogador se �
*/
struct trienode {
  char value;
  int isEnd; // 0 se n�o � nodo terminador de palavra. Se �, corresponde ao id
             // do jogador
  struct trienode *children[ALPHABET_SIZE]; // vetor de descendentes
};
struct trienode;
typedef struct trienode trienode;
/*
 Estrutura trienode:
 value: placeholder para alguma informa��o sobre a �rvore
 root: ponteiro para a primeira estrutura trienode
*/
typedef struct trie {
  int value;
  trienode *root;
} TRIE;

void initialize_trie(TRIE *tree); // inicializa a �rvore trie

trienode *initialize_node(
    char value); // aloca, inicializa e retorna um ponteiro para um novo nodo

void print_node(
    trienode *node1); // printa o valor do nodo seguido de seus descendentes,
                      // indicando se cada um existe (1) ou n�o (0)

void insert_trie(TRIE tree, char player_name[],
                 int player_id); // insere uma palavra na �rvore trie

int hasChild(
    trienode *node1,
    int c); // verifica se um nodo da �rvore tem a letra como descendente

int isPresent(
    TRIE tree,
    char name[]); // verifica se uma palavra est� dentro detro da �rvore trie

trienode *
findEndOfPrefix(trienode *root,
                char *prefix); // posiciona o ponteiro no nodo correspondente �
                               // �ltima letra do prefixo

listnode *list_all(TRIE tree,
                   char prefix[]); // retorna uma nova lista com todas os
                                   // jogadores com o prefixo dado

void list_nodes(listnode **list_of_words, char *current_word,
                trienode *current_node); // fun��o interna usada por list_all

char charAt(
    char string[],
    int index); // retorna o caractere presente no �ndice dado dentro da palavra

char *
concat_char(char str[],
            char c); // aloca e retorna um ponteiro para uma nova palavra, que
                     // tem o caractere inserido no final e tamanho maior em 1

void toupper_str(
    char str[]); // converte todos os caracteres da palavra em mai�sculo

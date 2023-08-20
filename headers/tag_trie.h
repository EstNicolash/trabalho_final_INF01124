#include "id_list.h"
#include "misc.h"

#define TRIE_ALPHABET_SIZE 30  // tamanho do vetor de descendentes para o nodo
#define SPACE_INDEX 26
#define LOWER_START 97
#define LOWER_END 122
#define UPPER_START 65
#define UPPER_END 90
/*
 Estrutura tag_trienode:
 value: caractere representado pelo nodo dentro da Ã¡rvore
 list_of_ids: lista de id's aos quais foi atribuÃ­da a tag, serve como flag de nodo terminador,
  sendo == NULL se nÃ£o Ã© terminador de palavra, caso contrÃ¡rio,
  contÃ©m a lista de ids de jogadores que possuem aquela tag
  last_of_list: ponteiro para o Ãºtlimo elemento da lista, para acelerar a inclusÃ£o de elementos
*/
struct tag_trienode {
    char value;
    id_list *list_of_ids;  // NULL se não é terminador de palavra, caso contrário, contém a lista de ids de jogadores que possuem aquela tag
    struct tag_trienode *children[TRIE_ALPHABET_SIZE];  // vetor de descendentes
    id_list *last_of_list;
};
struct tag_trienode;
typedef struct tag_trienode tag_trienode;
/*
 Estrutura tag_trienode:
 value: placeholder para alguma informaÃ§Ã£o sobre a Ã¡rvore
 root: ponteiro para a primeira estrutura tag_trienode
*/
typedef struct tag_trie {
    int value;
    tag_trienode *root;
} TAG_TRIE;

void initialize_tag_trie(TAG_TRIE *tree);  // inicializa a árvore trie
void initialize_tag_trie(TAG_TRIE *tree);  // inicializa a Ã¡rvore trie

tag_trienode *initialize_tag_trienode(char value);  // aloca, inicializa e retorna um ponteiro para um novo nodo

uint getIndexFromChar(char char_value);  //mapeia um caractere para um indice no vetor, que vai de 0 até 26

void print_tag_trienode(tag_trienode *node1);  // printa o valor do nodo seguido de seus descendentes,
                                               // indicando se cada um existe (1) ou não (0)

void insert_tag_trie(TAG_TRIE tree, UserTag new_tag);  // insere uma palavra na árvore trie

int hasTagChild(tag_trienode *node1,
                char char_value);  // verifica se um nodo da árvore tem a letra como descendente

int isTagPresent(TAG_TRIE tree,
                 char name[]);           // verifica se uma palavra está dentro detro da árvore trie
uint getIndexFromChar(char char_value);  //mapeia um caractere para um indice no vetor, que vai de 0 atÃ© 26

void print_tag_trienode(tag_trienode *node1);  // printa o valor do nodo seguido de seus descendentes,
                                               // indicando se cada um existe (1) ou nÃ£o (0)

void insert_tag_trie(TAG_TRIE tree, UserTag new_tag);  // insere uma palavra na Ã¡rvore trie

int hasTagChild(tag_trienode *node1,
                char char_value);  // verifica se um nodo da Ã¡rvore tem a letra como descendente

int isTagPresent(TAG_TRIE tree,
                 char name[]);  // verifica se uma palavra estÃ¡ dentro detro da Ã¡rvore trie

char getCharFromTag(char string[],
                    int index);  // retorna o caractere presente no índice dado dentro da palavra

id_list *list_all_ids(TAG_TRIE tree, char *tag_text);
//retorna uma lista com todos os id's que tem a tag pesquisada
char getCharFromTag(char string[],
                    int index);  // retorna o caractere presente no Ã­ndice dado dentro da palavra

id_list *list_all_ids(TAG_TRIE tree, char *tag_text);
//retorna uma lista com todos os id's que tem a tag pesquisada

id_list *intersection(id_list *list1, id_list *list2);
//retorna uma lista de id's jogadores contendo apenas os id's que estÃ£o nas duas listas simulateamente

id_list *intersection_multiple(TAG_TRIE tree, char *tags[], int num_tags);
//recebe um vetor de tags e retorna os id's dos jogadores que possuem todas as tags simultaneamente

id_list *intersection(id_list *list1, id_list *list2);
//retorna uma lista de id's jogadores contendo apenas os id's que estão nas duas listas simulateamente

id_list *intersection_multiple(TAG_TRIE tree, char *tags[], int num_tags);
//recebe um vetor de tags e retorna os id's dos jogadores que possuem todas as tags simultaneamente

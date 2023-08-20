#include "id_list.h"
#include "misc.h"

#define TRIE_ALPHABET_SIZE 27  // tamanho do vetor de descendentes para o nodo
#define SPACE_INDEX 26
#define LOWER_START 97
#define LOWER_END 122
#define UPPER_START 65
#define UPPER_END 90
/*
 Estrutura tag_trienode:
 value: caractere representado pelo nodo dentro da √°rvore
 list_of_ids: lista de id's aos quais foi atribu√≠da a tag, serve como flag de nodo terminador,
  sendo == NULL se n√£o √© terminador de palavra, caso contr√°rio,
  cont√©m a lista de ids de jogadores que possuem aquela tag
  last_of_list: ponteiro para o √∫tlimo elemento da lista, para acelerar a inclus√£o de elementos
*/
struct tag_trienode {
<<<<<<< HEAD
    char value;
    id_list *list_of_ids;  // NULL se n„o È terminador de palavra, caso contr·rio, contÈm a lista de ids de jogadores que possuem aquela tag
    struct tag_trienode *children[TRIE_ALPHABET_SIZE];  // vetor de descendentes
=======
  char value;
    id_list *list_of_ids; // NULL se n√£o √© terminador de palavra, caso contr√°rio, cont√©m a lista de ids de jogadores que possuem aquela tag
    id_list *last_of_list; 
  struct tag_trienode *children[TRIE_ALPHABET_SIZE]; // vetor de descendentes
>>>>>>> origin/master
};
struct tag_trienode;
typedef struct tag_trienode tag_trienode;
/*
 Estrutura tag_trienode:
 value: placeholder para alguma informa√ß√£o sobre a √°rvore
 root: ponteiro para a primeira estrutura tag_trienode
*/
typedef struct tag_trie {
    int value;
    tag_trienode *root;
} TAG_TRIE;

<<<<<<< HEAD
void initialize_tag_trie(TAG_TRIE *tree);  // inicializa a ·rvore trie
=======
void initialize_tag_trie(TAG_TRIE *tree); // inicializa a √°rvore trie
>>>>>>> origin/master

tag_trienode *initialize_tag_trienode(char value);  // aloca, inicializa e retorna um ponteiro para um novo nodo

<<<<<<< HEAD
uint getIndexFromChar(char char_value);  //mapeia um caractere para um indice no vetor, que vai de 0 atÈ 26

void print_tag_trienode(tag_trienode *node1);  // printa o valor do nodo seguido de seus descendentes,
                                               // indicando se cada um existe (1) ou n„o (0)

void insert_tag_trie(TAG_TRIE tree, UserTag new_tag);  // insere uma palavra na ·rvore trie

int hasTagChild(tag_trienode *node1,
                char char_value);  // verifica se um nodo da ·rvore tem a letra como descendente

int isTagPresent(TAG_TRIE tree,
                 char name[]);  // verifica se uma palavra est· dentro detro da ·rvore trie
=======
uint getIndexFromChar(char char_value); //mapeia um caractere para um indice no vetor, que vai de 0 at√© 26

void print_tag_trienode(
    tag_trienode *node1); // printa o valor do nodo seguido de seus descendentes,
                      // indicando se cada um existe (1) ou n√£o (0)

void insert_tag_trie(TAG_TRIE tree, UserTag new_tag); // insere uma palavra na √°rvore trie

int hasTagChild(
    tag_trienode *node1,
    char char_value); // verifica se um nodo da √°rvore tem a letra como descendente

int isTagPresent(
    TAG_TRIE tree,
    char name[]); // verifica se uma palavra est√° dentro detro da √°rvore trie
>>>>>>> origin/master

char getCharFromTag(char string[],
                    int index);  // retorna o caractere presente no Ìndice dado dentro da palavra

<<<<<<< HEAD
id_list *list_all_ids(TAG_TRIE tree, char *tag_text);
//retorna uma lista com todos os id's que tem a tag pesquisada
=======
char getCharFromTag(
    char string[],
    int index); // retorna o caractere presente no √≠ndice dado dentro da palavra

id_list *list_all_ids(TAG_TRIE tree,
                      char *tag_text);
                      //retorna uma lista com todos os id's que tem a tag pesquisada

id_list *intersection(id_list *list1,
                      id_list *list2);
                      //retorna uma lista de id's jogadores contendo apenas os id's que est√£o nas duas listas simulateamente

id_list *intersection_multiple(TAG_TRIE tree,
                                char *tags[],
                                 int num_tags);
                                 //recebe um vetor de tags e retorna os id's dos jogadores que possuem todas as tags simultaneamente

>>>>>>> origin/master

id_list *intersection(id_list *list1, id_list *list2);
//retorna uma lista de id's jogadores contendo apenas os id's que est„o nas duas listas simulateamente

id_list *intersection_multiple(TAG_TRIE tree, char *tags[], int num_tags);
//recebe um vetor de tags e retorna os id's dos jogadores que possuem todas as tags simultaneamente

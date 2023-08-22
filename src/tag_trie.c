#include "../headers/tag_trie.h"

char getCharFromTag(char string[], int index) {
    if (index < strlen(string))
        return string[index];
    else
        return '\0';
}

void initialize_tag_trie(TAG_TRIE *tree) {
    tree->root = initialize_tag_trienode('a');
    tree->value = 0;
}

uint getIndexFromChar(char char_value) {
    return ((int)char_value) - 32;
}

tag_trienode *initialize_tag_trienode(char value) {
    int i = 0;
    tag_trienode *new_node;
    new_node = (tag_trienode *)malloc(sizeof(tag_trienode));
    new_node->list_of_ids = NULL;
    for (i = 0; i < TRIE_ALPHABET_SIZE; i++) { new_node->children[i] = NULL; }
    new_node->value = value;

    // printf("\nALLOCATED");
    return new_node;
}

int hasTagChild(tag_trienode *node1, char char_value) {
    if (node1 == NULL) { return 0; }
    return node1->children[getIndexFromChar(char_value)] != 0;
}

void insert_tag_trie(TAG_TRIE tree, UserTag new_tag) {
    int offset = 0;
    int length = strlen(new_tag.tag_text);
    tag_trienode *current_node = tree.root;
    char current_char = '\0';
    tag_trienode *aux = NULL;
    id_list *new_id;

    while (offset < length) {
        current_char = getCharFromTag(new_tag.tag_text, offset);
        if (hasTagChild(current_node,
                        current_char))  // se o nodo já possui a próxima letra,
        // pula para ela (índice da letra no vetor
        // é seu valor ascii)
        {
            aux = current_node->children[getIndexFromChar(current_char)];
            current_node = aux;
        } else  // senão, aloca nova letra/nodo
        {
            aux = initialize_tag_trienode(current_char);
            current_node->children[getIndexFromChar(current_char)] = aux;
            current_node = aux;
        }
        offset++;
    }
    insert_id_list(&current_node->list_of_ids, new_tag.sofifa_id);
    //printf("\nINSERTED %d",length);
}

void print_tag_trienode(tag_trienode *node1) {
    printf("\nVALUE: %c CHILDREN: ", node1->value);
    int i;
    for (i = 97; i < 122; i++) {
        printf("%c: ", i);
        if (hasTagChild(node1, i)) {
            printf("1  ");
        } else {
            printf("0  ");
        }
    }
}

int isTagPresent(TAG_TRIE tree, char tag[]) {
    int offset = 0;
    int length = strlen(tag);
    tag_trienode *current_node = tree.root;
    char current_char = '\0';
    tag_trienode *aux = NULL;

    while (offset < length) {
        current_char = getCharFromTag(tag, offset);
        if (hasTagChild(current_node, current_char)) {
            aux = current_node->children[getIndexFromChar(current_char)];
            current_node = aux;
        } else {
            // printf("\nNOT FOUND");
            return 0;
        }
        offset++;
    }
    if (current_node->list_of_ids) {
        // printf("\nFOUND");
        return 1;
    }
    // printf("\nNOT FOUND");
    return 0;
}

id_list *list_all_ids(TAG_TRIE tree, char *tag_text) {
    int offset = 0;
    int tag_text_length = strlen(tag_text);
    char current_char;
    tag_trienode *aux = tree.root;

    while (offset < tag_text_length) {
        current_char = getCharFromTag(tag_text, offset);

        if (hasTagChild(aux, current_char)) {
            aux = aux->children[getIndexFromChar(current_char)];
        } else {
            return NULL;
        }
        offset++;
    }
    if (aux->list_of_ids) { return aux->list_of_ids; }
    return NULL;
}

id_list *intersection(id_list *list1, id_list *list2) {
    id_list *aux;
    id_list *new_list;

    new_list = initialize_id_list();
    aux = list1;
    while (aux != NULL) {
        if (isIDPresent(list2, aux->player_id)) { insert_id_list(&new_list, aux->player_id); }
        aux = aux->next;
    }
    return new_list;
}

id_list *intersection_multiple(TAG_TRIE tree, char *tags[], int num_tags) {
    int current = 0;
    id_list *temp1 = initialize_id_list();
    id_list *temp2 = initialize_id_list();
    id_list *intersection_temp = initialize_id_list();

    if (num_tags > 0)
        if (num_tags > 1) {
            intersection_temp = list_all_ids(tree, tags[0]);
            for (current = 1; current < num_tags; current++) {
                temp1 = intersection_temp;
                temp2 = list_all_ids(tree, tags[current]);
                intersection_temp = intersection(intersection_temp, temp2);
                free_id_list(temp1);
                free_id_list(temp2);
            }
        } else
            intersection_temp = list_all_ids(tree, tags[0]);

    return intersection_temp;
}

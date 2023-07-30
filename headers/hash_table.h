#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "misc.h"
#define PRIME 11 // Número primo usado na função de hashing

#include "list.h"

// Estrutura Hash_Table:
// size: Tamanho da tabela
// hash_table: Um vetor de listas com tamanho de size
struct Hash_Table {
  uint size;
  List hash_table[];
};

typedef struct Hash_Table HashTable;

HashTable *hash_table_init(uint size);
void hash_table_print(HashTable *hash_table);
void hash_table_insertion(HashTable *hash_table, Data data);
uint hash_func(int key, uint size);
void hash_table_destruct(HashTable *hash_table);
Data *hash_table_search(HashTable *hash_table, int key);
#endif

#include "../headers/csv.h"
#include "../headers/hash_table.h"
#include <stdio.h>
#include <string.h>

int main() {
  int i = 0;
  HashTable *jogadores = hash_table_init(10);
  Player player;

  char *row;
  int cols = 0;

  CsvHandle handle = CsvOpen(PLAYERS_FILE);
  row = CsvReadNextRow(handle);

  while (row = CsvReadNextRow(handle)) {
    if (i == 20)
      break;

    const char *col;

    col = CsvReadNextCol(row, handle);
    printf("fifa_id: %s\n", col);
    player.fifa_id = atoi(col);

    col = CsvReadNextCol(row, handle);
    strncpy(player.name, col, NAME_LEN);

    cols = 0;
    while (col = CsvReadNextCol(row, handle)) {
      strncpy(player.positions[cols], col, ID);

      cols++;
    }
    ++i;
    hash_table_insertion(jogadores, player);
  }
  hash_table_print(jogadores);
  return 0;
}

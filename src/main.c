#include "../headers/count_rating_hash_table.h"
#include "../headers/csv.h"
#include <time.h>

int main() {
  clock_t start, end;

  start = clock();

  CountRatingHashTable *count_rating = count_rating_hash_table_init(10000);
  CountRatingHashTable *teste = count_rating_hash_table_init(
      70000); // Teste de peso de alocação de memória na performance do programa
  CountRatingData rating;
  rating.total_rating = 1;
  char *row;
  const char *col;

  CsvHandle players_handle = CsvOpen(PLAYERS_FILE);
  CsvHandle rating_handle = CsvOpen(RATING_FILE);
  CsvHandle tags_handle = CsvOpen(TAGS_FILE);
  if (tags_handle && rating_handle && tags_handle) {

    // Leirura do arquivo rating
    row = CsvReadNextRow(rating_handle);

    uint count_row = 0;
    while (row = CsvReadNextRow(rating_handle)) {
      rating.rating_sum = 0;

      col = CsvReadNextCol(row, rating_handle); // Leitura do user_id
      col = CsvReadNextCol(row, rating_handle); // Leitura do fifa_id

      rating.fifa_id = atoi(col);

      col = CsvReadNextCol(row, rating_handle); // Leitura do rating
      rating.rating_sum = strtod(col, NULL);

      count_rating_hash_table_insertion(count_rating, rating);
      count_row++;
    }
    // count_rating_hash_table_print(count_rating);
    printf("Rating Row = %d\n", count_row);

    // Leitura do arquivo players.csv
    count_row = 0;
    row = CsvReadNextRow(
        players_handle); // Descartando informações desnecessárias
    while (row = CsvReadNextRow(players_handle)) {

      col = CsvReadNextCol(row, players_handle); // Leitura do fifa_id
      col = CsvReadNextCol(row, players_handle); // Leitura do nome

      while (col = CsvReadNextCol(row, rating_handle))
        ; // Leitura das posições

      count_row++;
    }
    printf("Players Row = %d\n", count_row);

    // Leitura do arquvo tags.csv
    row = CsvReadNextRow(tags_handle);
    count_row = 0;
    while (row = CsvReadNextRow(tags_handle)) {

      col = CsvReadNextCol(row, tags_handle); // Leitura do user_id
      col = CsvReadNextCol(row, tags_handle); // Leitura do fifa_id
      col = CsvReadNextCol(row, tags_handle); // Leitura da Tag

      ++count_row;
    }

    printf("Tags Row = %d\n", count_row);
    CsvClose(tags_handle);
    CsvClose(players_handle);
    CsvClose(rating_handle);
    end = clock();
    printf("Tempo de execução da etapa inicial: %fs\n",
           (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
  }

  printf("Erro ao abrir um arquivo.\n");
  return -1;
}

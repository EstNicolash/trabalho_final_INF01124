#include "../headers/count_rating_hash_table.h"
#include "../headers/csv.h"

int main() {
  CountRatingHashTable *count_rating = count_rating_hash_table_init(10000);

  CountRatingData rating;
  rating.total_rating = 1;
  char *row;
  const char *col;

  CsvHandle rating_handle = CsvOpen(RATING_FILE);
  row = CsvReadNextRow(rating_handle);

  uint count_row = 0;
  while (row = CsvReadNextRow(rating_handle)) {
    rating.rating_sum = 0;
    col = CsvReadNextCol(row, rating_handle);
    col = CsvReadNextCol(row, rating_handle);
    rating.fifa_id = atoi(col);
    col = CsvReadNextCol(row, rating_handle);
    rating.rating_sum = strtod(col, NULL);
    count_rating_hash_table_insertion(count_rating, rating);
    count_row++;
  }
  count_rating_hash_table_print(count_rating);
  printf("Row: %d", count_row);
  return 0;
}

#include "../headers/count_rating_hash_table.h"
#include "../headers/csv.h"
#include "../headers/players_hash_table.h"
#include "../headers/positions_ranking.h"
#include "../headers/trie.h"
#include <stdio.h>
#include <string.h>

int main() {
  
  ////////////////////////////////////////////////////////////////////////
  //
  // Etapa 1 - Leitura dos arquivo e processamento das estruturas de dados
  //
  //////////////////////////////////////////////////////////////////////////
  clock_t start, end;

  start = clock();

  PlayersHashTable *players = players_hash_table_init(10007); // Hash Table que guarda os jogadores pelo seu fifa_id
  CountRatingHashTable *count_rating = count_rating_hash_table_init(10007);//Hash Table que acumula as avaiações dos jogadores pelo fifa_id
  CountRatingHashTable *teste = count_rating_hash_table_init(70000); // Teste de peso de alocação de memória na performance do programa


  RatingTable pos_rank = positions_ranking_init(); //Tabela Hash que guarda as avaliações dos jogadores

  TRIE name_search;//Trie dos nomes do jogadores
  initialize_trie(&name_search);

  PlayerData player;
  PlayerData *player_pointer;
  CountRatingData rating; 
                          
  rating.total_rating = 1;//Inicialização do valor inicial da contagem total de avaliações

  char *row;//Linha do arquivo
  const char *col;//Coluna do arquivo
  uint count_row = 0;//Contagem das linhas

  //Abertura dos arquivos
  CsvHandle players_handle = CsvOpen(PLAYERS_FILE);
  CsvHandle rating_handle = CsvOpen(RATING_FILE);
  CsvHandle tags_handle = CsvOpen(TAGS_FILE);

  if (tags_handle && rating_handle && tags_handle) {
    /////////////////////////////////////////////////////////
    //
    // Leirura do arquivo rating.csv
    //
    // /////////////////////////////////////////////////////
    row = CsvReadNextRow(rating_handle);//Info "inutil"

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
    

    ///////////////////////////////////////////////////////////
    //
    // Leitura do arquivo players.csv
    //
    // ///////////////////////////////////////////////////////
    count_row = 0;

    row = CsvReadNextRow(players_handle); // Descartando informações desnecessárias
                                          
    while (row = CsvReadNextRow(players_handle)) {

      col = CsvReadNextCol(row, players_handle); // Leitura do fifa_id
      player.fifa_id = atoi(col);

      col = CsvReadNextCol(row, players_handle); // Leitura do nome
      strncpy(player.name, col, NAME_LEN);

      // Leitura das posições
      col = CsvReadNextCol(row, players_handle);
      strncpy(player.positions, col, POSITIONS_LEN);
        
      //Inserções
      player_pointer = players_hash_table_insertion(players, player);
      positions_table_insertion(&pos_rank, count_rating, player_pointer);
      insert_trie(name_search, player.name, player.fifa_id);

      count_row++;
    }
    printf("Players Row = %d\n", count_row);


    //////////////////////////////////////////////////////////  
    //
    // Leitura do arquvo tags.csv
    //
    // ///////////////////////////////////////////////////////
    
    row = CsvReadNextRow(tags_handle);//Informação "inutil"
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

    printf("Tempo de execução da etapa inicial: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);


    //positions_ranking_list_print(pos_rank.positions_table[positions_ranking_pos_cod("ST")], 10);
    
    
    //////////////////////////////////////////////////
    //
    // Etapa 2 - Interação do usuário
    //
    ////////////////////////////////////////////////// 
    
    char user_input[USER_INPUT] = {'a'};//Entrada do usuário, escolha do tipo de pesquisa
    int input_num;

    //Variáveis para o retorno das buscas:
    PlayerData *fifa_search;
    CountRatingData *rating_search;

    listnode *prefix_search = initialize_list();

    char N[50] = {'/0'};//Valor N da pesquisa topN
    char pos[POS];//

    while (strncmp(user_input, "quit", USER_INPUT) != 0) {

      fflush(stdin);

      printf("$>");

      fflush(stdin);

      scanf("%s", user_input);

      // Extra: Pesquisa por Fifa ID
      if (strncmp(user_input, "fifa", USER_INPUT) == 0) {

        scanf("%d", &input_num);
        fflush(stdin);

        fifa_search = players_hash_table_search(players, input_num);

        if (fifa_search) {
          rating_search = count_rating_hash_table_search(count_rating, input_num);

          printf("%d \t %s \t %s \t %d \t %f\n", fifa_search->fifa_id,
                 fifa_search->name, fifa_search->positions,
                 rating_search->total_rating,
                 (double)rating_search->rating_sum /rating_search->total_rating);

          continue;
        }

        printf("Miss\n");
        continue;
      }

      // 2.1 Pesquisa por prefixo
      if (strncmp(user_input, "player", USER_INPUT) == 0) {
        scanf("%s", player.name);

        fflush(stdin);
        prefix_search = list_all(name_search, player.name);
        print_list(prefix_search);
        continue;
      }

      // 2.2 Pesquisa sobre jogadores avaliados por usuários
      if(strncmp(user_input, "user", USER_INPUT) == 0){
        
          scanf("%d", &input_num);
          fflush(stdin);




          continue;
      }

      // 2.3 Pesquisa TopN de uma posição
      if (strncmp(user_input, "top", POS) == 0) {

        int j = 0;
        
        //Determina o valor de N
        for (int i = 3; i < strlen(user_input); ++i, ++j)
          N[j] = user_input[i];

        scanf("%s", pos);//posição

        positions_ranking_list_print(pos_rank.positions_table[positions_ranking_pos_cod(pos)], atoi(N));

        continue;
      }


    }
    return 0;
  }

  printf("Erro ao abrir um arquivo.\n");
  return -1;
}

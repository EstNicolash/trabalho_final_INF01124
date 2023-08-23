
#include <ctype.h>
#include <string.h>

#include "../headers/ReviewHashTable.h"
#include "../headers/count_rating_hash_table.h"
#include "../headers/csv.h"
#include "../headers/misc.h"
#include "../headers/players_hash_table.h"
#include "../headers/positions_ranking.h"
#include "../headers/tag_trie.h"
#include "../headers/trie.h"

int main() {
    /**************************************************************************************
    ////////////////////////////////////////////////////////////////////////
    //
    // Etapa 1 - Leitura dos arquivo e processamento das estruturas de dados
    //
    //////////////////////////////////////////////////////////////////////////
    *************************************************************************************/
    clock_t start, end;

    start = clock();

    PlayersHashTable *players = players_hash_table_init(10007);                // Hash Table que guarda os jogadores pelo seu fifa_id
    CountRatingHashTable *count_rating = count_rating_hash_table_init(10007);  //Hash Table que acumula as avaiações dos jogadores pelo fifa_id
    ReviewHashTable *reviews = reviews_hash_table_init(50000);                 //Hash table com usuários e suas reviews(Para pesquisa 2.2)
    TAG_TRIE tags;                                                             //Trie com as tags e seus jogadores(Para pesquisa 2.4)
    RatingTable pos_rank = positions_ranking_init();  //Tabela que guarda as avaliações dos jogadores por posição (Pesquisa 2.3)
    TRIE name_search;                                 //Trie dos nomes do jogadores(Para pesquisa 2.1)

    initialize_tag_trie(&tags);
    initialize_trie(&name_search);

    PlayerData player;
    PlayerData *player_pointer;
    CountRatingData rating;
    UserReview u_rev;
    UserTag tag_row;
    int user_id;
    char n[NAME_LEN];
    rating.total_rating = 1;  //Inicialização do valor inicial da contagem total de avaliações
                              //
    char *row;                //Linha do arquivo
    const char *col;          //Coluna do arquivo
    //uint count_row = 0;       //Contagem das linhas

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
        row = CsvReadNextRow(rating_handle);  //Info "inutil"

        while (row = CsvReadNextRow(rating_handle)) {
            rating.rating_sum = 0;

            col = CsvReadNextCol(row, rating_handle);  // Leitura do user_id
            user_id = atoi(col);

            col = CsvReadNextCol(row, rating_handle);  // Leitura do fifa_id

            rating.fifa_id = atoi(col);
            u_rev.fifa_id = rating.fifa_id;

            col = CsvReadNextCol(row, rating_handle);  // Leitura do rating
            rating.rating_sum = strtod(col, NULL);
            u_rev.rating = rating.rating_sum;

            count_rating_hash_table_insertion(count_rating, rating);
            reviews_hash_table_insertion(reviews, user_id, u_rev);

            //            count_row++;
        }
        //printf("Rating Row = %d\n", count_row);

        ///////////////////////////////////////////////////////////
        //
        // Leitura do arquivo players.csv
        //
        // ///////////////////////////////////////////////////////
        //count_row = 0;

        row = CsvReadNextRow(players_handle);  // Descartando informações desnecessárias

        while (row = CsvReadNextRow(players_handle)) {
            col = CsvReadNextCol(row, players_handle);  // Leitura do fifa_id
            player.fifa_id = atoi(col);

            col = CsvReadNextCol(row, players_handle);  // Leitura do nome
            strncpy(player.name, col, NAME_LEN);

            // Leitura das posições
            col = CsvReadNextCol(row, players_handle);
            strncpy(player.positions, col, POSITIONS_LEN);
            //printf("%d %s %s \n", player.fifa_id, player.name, player.positions);
            //Inserções
            player_pointer = players_hash_table_insertion(players, player);
            positions_table_insertion(&pos_rank, count_rating, player_pointer);
            insert_trie(name_search, player.name, player.fifa_id);

            // count_row++;
        }
        //printf("Players Row = %d\n", count_row);

        //////////////////////////////////////////////////////////
        //
        // Leitura do arquvo tags.csv
        //
        /////////////////////////////////////////////////////////

        row = CsvReadNextRow(tags_handle);  //Informação "inutil"
        //count_row = 0;
        tag_row.tag_text = malloc(sizeof(char) * NAME_LEN);

        while (row = CsvReadNextRow(tags_handle)) {
            col = CsvReadNextCol(row, tags_handle);  // Leitura do user_id
            tag_row.user_id = atoi(col);

            col = CsvReadNextCol(row, tags_handle);  // Leitura do fifa_id
            tag_row.sofifa_id = atoi(col);

            col = CsvReadNextCol(row, tags_handle);  // Leitura da Tag
                                                     //
            strncpy(tag_row.tag_text, col, NAME_LEN);
            //            printf("%d %d %s\n", tag_row.user_id, tag_row.sofifa_id, tag_row.tag_text);
            insert_tag_trie(tags, tag_row);

            // ++count_row;
        }

        //  printf("Tags Row = %d\n", count_row);

        //Fechar arquivos
        CsvClose(tags_handle);
        CsvClose(players_handle);
        CsvClose(rating_handle);

        end = clock();

        printf("Tempo de execução da etapa inicial: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);

        /******************************************************************************************************************
        //////////////////////////////////////////////////
        //
        // Etapa 2 - Interação do usuário
        //
        //////////////////////////////////////////////////
        *********************************************************************************************************************/

        char user_input[USER_INPUT] = {'a'};  //Entrada do usuário, escolha do tipo de pesquisa
        int input_num;                        //Entrada numérica do usuário

        //Variáveis para o retorno das buscas:
        PlayerData *fifa_search;
        CountRatingData *rating_search;
        UserData *user_search;

        while (strncmp(user_input, "quit", 4) != 0) {
            fflush(stdin);

            printf("$>");

            fflush(stdin);

            scanf("%s", user_input);
            //strncpy(user_input, "tags", 5);

            // Extra: Pesquisa por Fifa ID
            if (strncmp(user_input, "fifa", USER_INPUT) == 0) {
                scanf("%d", &input_num);
                fflush(stdin);

                fifa_search = players_hash_table_search(players, input_num);

                if (fifa_search) {
                    rating_search = count_rating_hash_table_search(count_rating, input_num);

                    print_player_info_header();
                    print_player_info(fifa_search);

                    continue;
                }

                printf("Miss\n");
                continue;
            }

            /////////////////////////////////////////
            //
            //  2.1 Pesquisa por prefixo
            //
            // ////////////////////////////////////
            if (strncmp(user_input, "player", USER_INPUT) == 0) {
                int k = 0;
                char name[NAME_LEN];
                scanf("%[^\n]%*c", player.name);

                //name_input_fix(name, player.name);
                //printf("%s\n", name);
                while (player.name[k] == ' ') ++k;  //Ignora espaços iniciais

                for (int i = 0; i < strlen(player.name); ++i, ++k) name[i] = player.name[k];
                name[0] = toupper(name[0]);

                //printf("%s \n", player.name);

                fflush(stdin);

                listnode *aux = initialize_list();
                listnode *prefix_search = initialize_list();

                //printf("Teste\n");
                prefix_search = list_all(name_search, name);
                //printf("Teste\n");
                aux = prefix_search;

                print_player_info_header();

                while (prefix_search) {
                    fifa_search = players_hash_table_search(players, prefix_search->player.id);

                    if (fifa_search) print_player_info(fifa_search);

                    //printf("%d %f %s\n", fifa_search->fifa_id, fifa_search->name, fifa_search->positions);
                    prefix_search = prefix_search->next;
                    free(aux);
                    aux = prefix_search;
                }

                continue;
            }
            ///////////////////////////////////////////////////////////////
            //
            // 2.2 Pesquisa sobre jogadores avaliados por usuários
            //
            //////////////////////////////////////////////////////////////
            if (strncmp(user_input, "user", USER_INPUT) == 0) {
                scanf("%d", &input_num);
                fflush(stdin);

                user_search = reviews_hash_table_search(reviews, input_num);

                if (user_search == NULL) continue;

                print_player_info_header_mais_rating();

                if (!user_search->user_reviews.sorted) review_heap_heapsort(&(user_search->user_reviews));

                for (int i = 0; i < HEAP_SIZE; ++i) {
                    if (user_search->user_reviews.reviews[i].fifa_id != -1) {
                        fifa_search = players_hash_table_search(players, user_search->user_reviews.reviews[i].fifa_id);
                        print_player_info_mais_rating(fifa_search, user_search->user_reviews.reviews[i].rating);
                    }
                }

                continue;
            }
            ////////////////////////////////////////////////////////////
            //
            // 2.3 Pesquisa TopN de uma posição
            //
            ///////////////////////////////////////////////////////////
            if (strncmp(user_input, "top", 3) == 0) {
                char pos_input[POS * 2];  // '<Posição>'
                char pos[POS];            //<Posição>
                char N[10];               //Valor N da pesquisa topN
                int j = 0;
                int i = 3;
                //printf("%s %c tste\n", user_input, user_input[i]);
                //Determina o valor de N
                while ('0' <= user_input[i] && user_input[i] <= '9') {
                    // printf("i:%c\n", user_input[i]);
                    N[j] = user_input[i];
                    ++j;
                    ++i;
                    // printf("f:%c\n", user_input[i]);
                }
                //printf("teste\n");

                scanf("%s", pos_input);  //posição

                pos_input_fix(pos, pos_input);

                positions_ranking_list_print(pos_rank.positions_table[positions_ranking_pos_cod(pos)], atoi(N));

                continue;
            }
            //////////////////////////////////////////////////////////
            //
            //  2.4 Pesquisa por Tags
            //
            /////////////////////////////////////////////////////////
            if (strncmp((user_input), "tags", 4) == 0) {
                char **list_of_tags;         //Lista de tags processada num array
                int num_tags = 0;            //Número de tags
                char tags_buffer[NAME_LEN];  //Lista de tags

                scanf("%99[^\n]", tags_buffer);
                //strncpy(tags_buffer, "'Brazil' 'Dribbler' ", 25);

                id_list *l1 = initialize_id_list();

                list_of_tags = list_tags(tags_buffer, &num_tags);
                //printf("Teste %d\n", num_tags);
                l1 = intersection_multiple(tags, list_of_tags, num_tags);
                //printf("Teste2\n");
                id_list *aux = l1;
                //print_id_list(l1);
                print_player_info_header();

                while (l1) {
                    //                   printf("%d\n", l1->player_id);
                    fifa_search = players_hash_table_search(players, l1->player_id);

                    print_player_info(fifa_search);

                    l1 = l1->next;
                    free(aux);
                    aux = l1;
                }
                for (int i = 0; i < NAME_LEN; ++i) { free(list_of_tags[i]); }
                free(list_of_tags);

                continue;
            }
        }
        return 0;
    }

    printf("Erro ao abrir um arquivo.\n");
    return -1;
}

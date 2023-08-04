/*
 Estrutura player_data:
 name: String referente ao nome
 id: valor correspondente ao sofifa_id
 */
typedef struct {
  char *name;
  int id;

} player_data;
/*
 Estrutura listnode:
 player: cole��o de dados referentes ao jogador
 next: ponteiro para pr�xima estrutura listnode
 */
struct listnode {
  player_data player;
  struct listnode *next;
};
struct listnode;
typedef struct listnode listnode;

listnode *initialize_list();
void insert_list(listnode **list1, player_data player);
void print_list(listnode *list1);
void free_list(listnode *list1);

#include "../headers/misc.h"
#include <stdio.h>
#include <malloc.h>

struct ReviewList
{
    int reviewing_player_id; //id do usuario que fez a avaliação
    int fifa_id; //jogador avaliado
    double rating; //nota dada pelo usuário
    struct ReviewList *next;
};
typedef struct ReviewList ReviewList;

void review_list_initialize(ReviewList **list); //incializa a lista com vazio

void review_list_print(ReviewList *list); //imprime cada review da lista, mostrando o id do usuário que fez o review, id do jogador e a nota dada

ReviewList *review_list_insert(ReviewList *list, int reviewing_player_id, int fifa_id, double rating); //insere um review na lista

int review_list_count(ReviewList *list, int user_id); //conta do numero de reviews da lista quie pertencem ao usuário pesquisado

ReviewList *list_highest_reviews(ReviewList *list, int user_id); //retorna uma lista de reviews com os 2 maiores reviews de um dado usuário

void quickSort(double array[], int id_array[], int low, int high); //quicksort para ordenar a lista de reviews

int partition(double array[], int id_array[], int low, int high); //particionador para quicksort

void swap(int *a, int *b);

void swap_double(double *a, double *b);

#include "../headers/ReviewList.h"

ReviewList *review_list_insert(ReviewList *list,int reviewing_player_id, int fifa_id, double rating)
{
    ReviewList *new_node = (ReviewList *) malloc(sizeof(ReviewList));
    new_node->reviewing_player_id = reviewing_player_id;
    new_node->fifa_id = fifa_id;
    new_node->rating = rating;
    new_node->next = NULL;

    ReviewList *aux = list;
    if(aux == NULL)
    {
        list = new_node;
    }
    else
    {
        while(aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = new_node;
    }
    return list;
}

int review_list_count(ReviewList *list, int user_id)
{
    ReviewList *aux = list;
    int count = 0;
    while(aux)
    {
        if(aux->reviewing_player_id == user_id)
        {
            count++;
        }
        aux = aux->next;
    }
    return count;
}

void review_list_print(ReviewList *list)
{
    ReviewList *aux = list;
    while(aux != NULL)
    {
        printf("\nUser: %d, PlayerID: %d Rating: %f",aux->reviewing_player_id,aux->fifa_id,aux->rating);
        aux = aux->next;
    }
}

ReviewList *list_highest_reviews(ReviewList *list, int user_id)
{
    int index = 0;
    int length = review_list_count(list, user_id);

    ReviewList *top20;
    review_list_initialize(&top20);

    int *id_temp = malloc(sizeof(int) * length);
    double *rating_temp = malloc(sizeof(double) * length);

    ReviewList *aux = list;
    while(aux)
    {
        if(aux->reviewing_player_id == user_id)
        {
            id_temp[index] = aux->fifa_id;
            rating_temp[index] = aux->rating;
            index++;
        }
        aux = aux->next;
    }
    quickSort(rating_temp,id_temp,0,length - 1);

    if(length > USER_INPUT)
        length = USER_INPUT;
    for(index = 0; index < length; index++)
        top20 = review_list_insert(top20,user_id,id_temp[index],rating_temp[index]);

    return top20;
}

// function to swap elements
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void swap_double(double *a, double *b) {
  double temp = *a;
  *a = *b;
  *b = temp;
}

int partition(double array[], int id_array[], int low, int high) {

  int pivot = array[high];

  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (array[j] >= pivot) {

      i++;

      swap_double(&array[i], &array[j]);
      swap(&id_array[i], &id_array[j]);
    }
  }

  swap_double(&array[i + 1], &array[high]);
  swap(&id_array[i + 1], &id_array[high]);

  return (i + 1);
}

void quickSort(double array[], int id_array[], int low, int high) {
  if (low < high) {

    int pivot = partition(array,id_array, low, high);

    quickSort(array,id_array, low, pivot - 1);
    quickSort(array,id_array, pivot + 1, high);
  }
}

void review_list_initialize(ReviewList **list)
{
    *list = NULL;
}

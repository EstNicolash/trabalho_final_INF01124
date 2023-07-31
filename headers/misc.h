#ifndef MISC_H
#define MISC_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PLAYERS_FILE "files/players.csv"
#define TAGS_FILE "files/tags.csv"
#define MINIRATING_FILE "files/minirating.csv"
#define RATING_FILE "files/rating.csv"
#define NAME_LEN 100    // Tamanho máximo para guardar nome do jagador
#define POSITIONS_LEN 4 // Tamanho máximo para guardar uma posição do jogador
#define POSITIONS_NUM 14 // Tamanho máximo de posições do futebol
#define ID 10            // Máximo de chars de uma string fifa_id
#define NUM_TESTES 4
#define BUFFER_SIZE 150

typedef unsigned int uint;

extern uint a_pow10[10]; // Potencias de 10 até 10^10

#endif

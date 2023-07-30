#ifndef MISC_H
#define MISC_H

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LEN 100    // Tamanho máximo para guardar nome do jagador
#define POSITIONS_LEN 4 // Tamanho máximo para guardar uma posição do jogador
#define POSITIONS_NUM 14 // Tamanho máximo de posições do futebol
#define ID 10            // Máximo de chars de uma string fifa_id
#define PLAYERS_FILE "players.csv"
#define OUTPUT_0 "experimento1000.txt"
#define OUTPUT_1 "experimento2000.txt"
#define OUTPUT_2 "experimento4000.txt"
#define OUTPUT_3 "experimento8000.txt"
#define CONSULTA "consultas-fifa.txt"
#define NUM_TESTES 4
#define BUFFER_SIZE 150

typedef unsigned int uint;

extern uint count_consultas; // Número de consultas para encontra um jogador
extern uint tamanho_experimentos[NUM_TESTES]; // vetor que guarda o tamanho da
                                              // tabela hash
extern uint a_pow10[10]; // Potencias de 10 até 10^10

// Guarda informação do jogador
struct Data {
  int fifa_id;
  char name[NAME_LEN];
  char positions[POSITIONS_LEN][POSITIONS_NUM];
};
typedef struct Data Data;
typedef Data Player;

#endif

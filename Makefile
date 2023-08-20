
# Compilador
CC = gcc

# Bibliotecas
LIBS = -lm

# Diretórios
SRC = ./src/
OBJ = ./obj/
HDR = ./headers/
BIN = ./bin/
PROG_NAME = main

	#Modelo:
	#$(CC) -c $(SRC)file_name.c -I $(HDR) -o $(OBJ)file_name.o
	#$(CC) $(SRC)$(PROG_NAME).c	$(OBJ)*.o -I $(HDR) -o $(BIN)$(PROG_NAME)
All:
	$(CC) -c $(SRC)misc.c -I $(HDR) -o $(OBJ)misc.o
	$(CC) -c $(SRC)csv.c -I $(HDR) -o $(OBJ)csv.o
	$(CC) -c $(SRC)count_rating_list.c -I $(HDR) -o $(OBJ)count_rating_list.o
	$(CC) -c $(SRC)count_rating_hash_table.c -I $(HDR) -o $(OBJ)count_rating_hash_table.o
	$(CC) -c $(SRC)players_list.c -I $(HDR) -o $(OBJ)players_list.o
	$(CC) -c $(SRC)players_hash_table.c -I $(HDR) -o $(OBJ)players_hash_table.o
	$(CC) -c $(SRC)trie_list.c -I $(HDR) -o $(OBJ)trie_list.o
	$(CC) -c $(SRC)trie.c -I $(HDR) -o $(OBJ)trie.o
	$(CC) -c $(SRC)positions_ranking.c -I $(HDR) -o $(OBJ)positions_ranking.o
	$(CC) -c $(SRC)ReviewHashTable.c -I $(HDR) -o $(OBJ)ReviewHashTable.o
	$(CC) -c $(SRC)id_list.c -I $(HDR) -o $(OBJ)id_list.o
	$(CC) -c $(SRC)tag_trie.c -I $(HDR) -o $(OBJ)tag_trie.o
	$(CC) $(SRC)$(PROG_NAME).c $(OBJ)*.o -I $(HDR) -o $(BIN)$(PROG_NAME).bin
debug:
	$(CC) -g -c $(SRC)misc.c -I $(HDR) -o $(OBJ)misc.o
	$(CC) -g -c $(SRC)csv.c -I $(HDR) -o $(OBJ)csv.o
	$(CC) -g -c $(SRC)count_rating_list.c -I $(HDR) -o $(OBJ)count_rating_list.o
	$(CC) -g -c $(SRC)count_rating_hash_table.c -I $(HDR) -o $(OBJ)count_rating_hash_table.o
	$(CC) -g -c $(SRC)players_list.c -I $(HDR) -o $(OBJ)players_list.o
	$(CC) -g -c $(SRC)players_hash_table.c -I $(HDR) -o $(OBJ)players_hash_table.o
	$(CC) -g -c $(SRC)trie_list.c -I $(HDR) -o $(OBJ)trie_list.o
	$(CC) -g -c $(SRC)trie.c -I $(HDR) -o $(OBJ)trie.o
	$(CC) -g -c $(SRC)positions_ranking.c -I $(HDR) -o $(OBJ)positions_ranking.o
	$(CC) -g -c $(SRC)ReviewHashTable.c -I $(HDR) -o $(OBJ)ReviewHashTable.o
	$(CC) -g -c $(SRC)id_list.c -I $(HDR) -o $(OBJ)id_list.o
	$(CC) -g -c $(SRC)tag_trie.c -I $(HDR) -o $(OBJ)tag_trie.o
	$(CC) -g $(SRC)$(PROG_NAME).c $(OBJ)*.o -I $(HDR) -o $(BIN)$(PROG_NAME)_debug.bin
run:
	$(BIN)$(PROG_NAME).bin


clean:
	rm ./bin/* ./obj/*

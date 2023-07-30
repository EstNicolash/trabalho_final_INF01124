
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
	$(CC) -c $(SRC)list.c -I $(HDR) -o $(OBJ)list.o
	$(CC) -c $(SRC)hash_table.c -I $(HDR) -o $(OBJ)hash_table.o
	$(CC) $(SRC)$(PROG_NAME).c $(OBJ)*.o -I $(HDR) -o $(BIN)$(PROG_NAME).bin
debug:

run:
	$(BIN)$(PROG_NAME).bin


clean:
	rm ./bin/* ./obj/*

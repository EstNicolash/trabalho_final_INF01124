
# Compilador
CC = gcc

# Bibliotecas
LIBS = -lm

# Diretórios
SRC = ./src/
OBJ = ./obj/
HDR = ./headers/
BIN = ./bin/
PROG_NAME = main.bin

All:
	#Modelo:
	#$(CC) -c $(SRC)file_name.c -I $(HDR) -o $(OBJ)file_name.o
	#$(CC) $(SRC)$(PROG_NAME).c	$(OBJ)*.o -I $(HDR) -o $(BIN)$(PROG_NAME)

	$(CC) $(SRC)$(PROG_NAME).c -I $(HDR) -o $(BIN)$(PROG_NAME)
debug:

run:
	$(BIN)$(PROG_NAME)


clean:
	rm ./bin/* ./obj/*

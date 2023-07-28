
# Compilador
CC = gcc

# Bibliotecas
LIBS = -lm

# Diretórios
SRC = ./src/
OBJ = ./obj/
HDR = ./headers/
BIN = ./bin/

All:
	#Modelo:
	#$(CC) -c $(SRC)file_name.c -I $(HDR) -o $(OBJ)file_name.o
	#$(CC) $(SRC)program_file_name.c	$(OBJ)*.o -I $(HDR) -o program_file_name

debug:

clean:
	rm ./bin/* ./obj/*

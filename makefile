PROJECT_NAME = roap #target file name
CC = gcc #compiler
CFLAGS = -Wall -std=c99 -O3
OBJECTS = main.c  #objects
all:	$(PROJECT_NAME)
#$(PROJECT_NAME): $(OBJECTS)
gcc	-Wall	-std=c99	-O3	-o	roap	main.c	Funcoes_aux.c	Funcoes_aux.h	Ficheiros_dados.c	Ficheiros_dados.h	A\'s.c	A\'s.h

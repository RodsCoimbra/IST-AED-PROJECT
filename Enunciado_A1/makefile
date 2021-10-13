# Makefile do projeto RoaP

PROJECT_NAME = roap #target file name
CC = gcc #compiler
CFLAGS = -Wall -std=c99 -g 
OBJECTS = main2.o #objects
all: $(PROJECT_NAME)
$(PROJECT_NAME): $(OBJECTS)
    $(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT_NAME)
main2.o: main2.c

FILES_1=$(shell ls A1/*)
FILES_2=$(shell ls A2/*)
FILES_3=$(shell ls A3/*)
FILES_4=$(shell ls A4/*)
FILES_5=$(shell ls A5/*)
FILES_6=$(shell ls A6/*)
Saladas=$(shell ls Saladas/*)
FILES=${FILES_1} ${FILES_2} ${FILES_3} ${FILES_4} ${FILES_5} ${FILES_6} ${Saladas}
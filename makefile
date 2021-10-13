PROJECT_NAME = roap #target file name
CC = gcc #compiler
CFLAGS = -Wall -std=c99 -O3
OBJECTS = main.c  #objects
all:	$(PROJECT_NAME)
$(PROJECT_NAME): $(OBJECTS)
	$(CC)	$(CFLAGS)	$(OBJECTS)	-o	$(PROJECT_NAME)
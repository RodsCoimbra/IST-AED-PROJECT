#ifndef Funcoes_aux_h
#define Funcoes_aux_h
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include "A's.h"
#include "Ficheiros_dados.h"

int out (int l, int c, int lin, int col);
void freetabela(short** maze, int lin);
int mod(short** maze, int l, int c, int lin, int col,char* modo, int l2, int c2);
void separar(char* str);
void fechar (FILE* fmaze, FILE* fsol);
#endif 
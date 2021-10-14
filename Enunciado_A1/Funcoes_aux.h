#ifndef Funcoes_aux_h
#define Funcoes_aux_h
#include <stdio.h>

int out (int l, int c, int lin, int col);
void freetabela(int** maze, int lin);
int mod(int** maze, int l, int c, int lin, int col,char* modo, int l2, int c2);
void separar(char* str);
void fechar (FILE* fmaze, FILE* fsol);
#endif 
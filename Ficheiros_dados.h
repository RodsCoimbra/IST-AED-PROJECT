#ifndef Ficheiros_dados_h
#define Ficheiros_dados_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include "Funcoes_aux.h"


void Labirinto (char modo, FILE* fmaze, FILE* fsol);
void open_files(FILE* fmaze,FILE* fsol,char* fileread,char* filewrite);

#endif
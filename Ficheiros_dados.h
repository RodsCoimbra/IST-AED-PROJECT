#ifndef Ficheiros_dados_h
#define Ficheiros_dados_h

#include "stdio.h"

void Labirinto(FILE *fmaze, FILE *fsol);
void open_files(FILE **fmaze, FILE **fsol, char *fileread, char *filewrite);

#endif
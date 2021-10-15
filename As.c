/*bibliotecas do projeto*/
#include "As.h"
#include "Funcoes_aux.h"
#include "Ficheiros_dados.h"
/*bibliotecas do projeto*/
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int FA1 (int** maze, int l, int c, int lin, int col) { /*identifica o tipo da cécula de indicada*/
    int A1= out(l, c, lin, col);    /*a função out vai retornar o numero da célula correspondente às coordenadas (l,c)*/    
    if(A1 != -2){
    A1 = maze[l][c];}
    return A1;
}

int FA2 (int** maze, int l, int c, int lin, int col) { /*indica se algum vizinho da célula indicada é uma célula branca*/
    if ((out(l, c, lin, col)==-2)) return -2;   /*verificação se a célula não está fora do tabuleiro*/
    /*verificação do tipo das células vizinhas e se estas cumprem a condição de ser branca*/
    if ((out(l+1, c, lin, col)!=-2 && maze[l+1][c]==0) || (out(l, c+1, lin, col)!=-2 && maze[l][c+1]==0) || (out(l-1, c, lin, col)!=-2 && maze[l-1][c]==0) || (out(l, c-1, lin, col)!=-2 && maze[l][c-1]==0)){ 
        return 1;}
    return 0;
}

int FA3 (int** maze, int l, int c, int lin, int col) { /*indica se algum vizinho da célula indicada é uma célula cizenta*/
    if ((out(l, c, lin, col)==-2)) return -2;   /*verificação se a célula não está fora do tabuleiro*/
    /*verificação do tipo das células vizinhas e se estas cumprem a condição de ser cizenta*/
    if ((out(l+1, c, lin, col)!=-2 && maze[l+1][c]>=1) || (out(l, c+1, lin, col)!=-2 && maze[l][c+1]>=1) || (out(l-1, c, lin, col)!=-2 && maze[l-1][c]>=1) || (out(l, c-1, lin, col)!=-2 && maze[l][c-1]>=1)){
    return 1;}
    return 0;
}

int FA4 (int** maze, int l, int c, int lin, int col) { /*indica se algum vizinho da célula indicada é uma célula preta*/
    if ((out(l, c, lin, col)==-2)) return -2;   /*verificação se a célula não está fora do tabuleiro*/
    /*verificação do tipo das células vizinhas e se estas cumprem a condição de ser preta*/
    if ((out(l+1, c, lin, col)!=-2 && maze[l+1][c]==-1) || (out(l, c+1, lin, col)!=-2 && maze[l][c+1]==-1) || (out(l-1, c, lin, col)!=-2 && maze[l-1][c]==-1) || (out(l, c-1, lin, col)!=-2 && maze[l][c-1]==-1)){
    return 1;}
    return 0;
}

int FA5 (int** maze, int l, int c, int lin, int col) { /*indica se a célula de entrada é quebrável*/
    if (out(l, c, lin, col)==-2) return -2;
    else if (maze[l][c]<=0) return -1;
    /*vê se as duas células vizinhas na vertical e depois na horizontal são brancas*/
    else if ((out(l-1, c, lin, col) != -2) && (out(l+1, c, lin, col)!=-2) && maze[l-1][c]==0 && maze[l+1][c]==0){
        return 1;}
    else if ((out(l, c+1, lin, col) !=-2) && (out(l, c-1, lin, col) !=-2) && maze[l][c-1]==0 && maze[l][c+1]==0){
        return 1;}
    else {
        return 0;}
}

 int FA6 (int** maze, int l, int c, int lin, int col, int l2, int c2){  /*para duas células de entrada a função indica se pertencem à mesma sala do labirinto*/
     /*Baseado no weighted quick union algorithm*/    
    int i=0, j=0;
    int *id = (int *) malloc((lin+1)*(col+1) * sizeof(int));
    int *sz = (int *) malloc((lin+1)*(col+1) * sizeof(int));
    for (i = 0; i < ((lin+1)*(col+1)); i++) {
    sz[i] = 1;
    id[i] = i;
    }
    /*for (int p = 0; p <= lin; p++){
        for(int q = 0; q <= col; q++){
        i = p*(col+1) + q;
        printf("%2d ", id[i]);
        }
        printf("\n");
    }*/

    for (int p = 0; p <= lin; p++) {
        for(int q = 0; q <= col-1; q++){
            i = p*(col+1) + q;
            j = p*(col+1) + q + 1;
            if(maze[p][q] == 0 && p>0 && maze[p-1][q] == 0)
            {
                id[i] = id[(p-1)*(col+1) + q];
            }
            if(maze[p][q+1] == 0 && p>0 && maze[p-1][q+1] == 0)
            {
                id[j] = id[(p-1)*(col+1) + q + 1];
            }
            if(maze[p][q] == 0 && maze[p][q+1] == 0){
            for (; i!=id[i] ; i = id[i]);
            for (; j!=id[j]; j = id[j]);
        
    if (i == j) continue;
    if (sz[i] < sz[j]) {
     id[i] = j; 
     sz[j] += sz[i];
    } 
    else {
        id[j] = i;
        sz[i] += sz[j];
    }
    }
    }
    }
    /*for (int q = 0; q <= col; q++) {
        for(int p = 0; p <= lin-1; p++){
            if(maze[p][q] == 0 && maze[p+1][q] == 0){
            for (i = p*(col) + q; i!=id[i] ; i = id[i]);
            for (j = p*(col) + q + 1; j!=id[j]; j = id[j]);
        }
    if (i == j) continue;
    if (sz[i] < sz[j]) {
     id[i] = j; 
     sz[j] += sz[i];
    } 
    else {
        id[j] = i; 
        sz[i] += sz[j];
    }
    }
    }*/
    for(i =(l*(col+1))+c; i!= id[i]; i = id[i]);
    for(j =(l2*(col+1))+c2; j!=id[j]; j = id[j]);

    if (i == j){
    free(id);
    free(sz);
    return 1;
    }
    else{
    free(id);
    free(sz);
    return 0;}


    }
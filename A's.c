#include "A's.h"


int FA1 (short** maze, int l, int c, int lin, int col) {
    int A1= out(l, c, lin, col);
    if(A1 != -2){
    A1 = maze[l][c];}
    return A1;
}

int FA2 (short** maze, int l, int c, int lin, int col) {
    if ((out(l, c, lin, col)==-2)) return -2;
    if ((out(l+1, c, lin, col)!=-2 && maze[l+1][c]==0) || (out(l, c+1, lin, col)!=-2 && maze[l][c+1]==0) || (out(l-1, c, lin, col)!=-2 && maze[l-1][c]==0) || (out(l, c-1, lin, col)!=-2 && maze[l][c-1]==0)){ 
        return 1;}
    return 0;
}

int FA3 (short** maze, int l, int c, int lin, int col) {
    if ((out(l, c, lin, col)==-2)) return -2;
    if ((out(l+1, c, lin, col)!=-2 && maze[l+1][c]>=1) || (out(l, c+1, lin, col)!=-2 && maze[l][c+1]>=1) || (out(l-1, c, lin, col)!=-2 && maze[l-1][c]>=1) || (out(l, c-1, lin, col)!=-2 && maze[l][c-1]>=1)){
    return 1;}
    return 0;
}

int FA4 (short** maze, int l, int c, int lin, int col) {
    if ((out(l, c, lin, col)==-2)) return -2;
    if ((out(l+1, c, lin, col)!=-2 && maze[l+1][c]==-1) || (out(l, c+1, lin, col)!=-2 && maze[l][c+1]==-1) || (out(l-1, c, lin, col)!=-2 && maze[l-1][c]==-1) || (out(l, c-1, lin, col)!=-2 && maze[l][c-1]==-1)){
    return 1;}
    return 0;
}

int FA5 (short** maze, int l, int c, int lin, int col) {
    if (out(l, c, lin, col)==-2) return -2;
    else if (maze[l][c]<=0) return -1;
    else if ((out(l-1, c, lin, col) != -2) && (out(l+1, c, lin, col)!=-2) && maze[l-1][c]==0 && maze[l+1][c]==0){
        return 1;}
    else if ((out(l, c+1, lin, col) !=-2) && (out(l, c-1, lin, col) !=-2) && maze[l][c-1]==0 && maze[l][c+1]==0){
        return 1;}
    else {
        return 0;}
}

 int FA6 (short** maze, int l, int c, int lin, int col, int l2, int c2,short fim) {
        maze[l][c] = -6;
        if(maze[l2][c2] != -6){
            if((lin >= l+1) && (maze[l+1][c] == 0) && (fim == 0)){ /*cima*/
                fim = FA6(maze, l+1, c, lin, col, l2, c2, fim);}
            if((col >= c+1) && (maze[l][c+1] == 0 && fim == 0)){ /*direita*/
                fim = FA6(maze, l, c+1, lin, col, l2, c2, fim);
                }
            if((l >= 1) && (maze[l-1][c] == 0 && fim == 0)){      /*baixo*/
                fim = FA6(maze, l-1, c, lin, col, l2, c2,fim);
                }
            if((c >= 1) && (maze[l][c-1] == 0 && fim == 0)){      /*esquerda*/
                fim = FA6(maze, l, c-1, lin, col, l2, c2,fim);
                }
            if(fim==0){
                return 0;
                }
            else{
                return 1;
            }
        }
        else {
            return 1;
            }
 }